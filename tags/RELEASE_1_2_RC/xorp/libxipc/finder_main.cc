// -*- c-basic-offset: 4; tab-width: 8; indent-tabs-mode: t -*-

// Copyright (c) 2001-2005 International Computer Science Institute
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software")
// to deal in the Software without restriction, subject to the conditions
// listed in the XORP LICENSE file. These conditions include: you must
// preserve this copyright notice, and you cannot mention the copyright
// holders in advertising related to the Software without their permission.
// The Software is provided WITHOUT ANY WARRANTY, EXPRESS OR IMPLIED. This
// notice is a summary of the XORP LICENSE file; the license in that file is
// legally binding.

#ident "$XORP: xorp/libxipc/finder_main.cc,v 1.17 2005/08/04 11:07:14 bms Exp $"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef HAVE_SYS_TYPES_H
#include <sys/types.h>
#endif
#ifdef HAVE_SYS_SOCKET_H
#include <sys/socket.h>
#endif
#ifdef HAVE_ARPA_INET_H
#include <arpa/inet.h>
#endif
#ifdef HAVE_NETDB_H
#include <netdb.h>
#endif
#ifdef HAVE_NET_IF_H
#include <net/if.h>
#endif

#include "finder_module.h"

#include "libxorp/xorp.h"
#include "libxorp/xlog.h"
#include "libxorp/eventloop.hh"

#include "libcomm/comm_api.h"

#include "sockutil.hh"
#include "finder_server.hh"
#include "permits.hh"

#ifdef HAVE_GETOPT_H
#include <getopt.h>
#endif

static bool gbl_sig_exit = false;			// Exit signal() recv

static bool
print_twirl()
{
    static const char t[] = { '\\', '|', '/', '-' };
    static const size_t nt = sizeof(t) / sizeof(t[0]);
    static size_t n = 0;
    static char erase = '\0';

    printf("%c%c", erase, t[n % nt]); fflush(stdout);
    n++;
    erase = '\b';
    return true;
}

static void
usage()
{
    fprintf(stderr, "Usage: finder [-hv] "
	    "[-a <allowed host>] "
	    "[-n <allowed net>] "
	    "[-p <port>] "
	    "[-i <interface>]\n");
}

void
finder_sig_handler(int s)
{
    if (s == SIGINT) {
	fprintf(stderr, "SIGINT received. Exiting.\n");
#ifdef SIGHUP
    } else if (s == SIGHUP) {
	fprintf(stderr, "SIGHUP received. Exiting.\n");
#endif
    } else if (s == SIGTERM) {
	fprintf(stderr, "SIGTERM received. Exiting.\n");
    } else {
	fprintf(stderr, "SIGNAL (%d) received. Exiting.\n", s);
    }
    gbl_sig_exit = true;
}

static void
finder_main(int argc, char* const argv[])
{
    bool	run_verbose = false;
    list<IPv4>  bind_addrs;
    uint16_t	bind_port = FinderConstants::FINDER_DEFAULT_PORT();

#ifdef SIGHUP
    signal(SIGHUP, finder_sig_handler);
#endif
    signal(SIGINT, finder_sig_handler);
    signal(SIGTERM, finder_sig_handler);
#ifdef SIGPIPE
    signal(SIGPIPE, finder_sig_handler);
#endif

    int ch;
    while ((ch = getopt(argc, argv, "a:i:n:p:hv")) != -1) {
	switch (ch) {
	case 'a':
	    //
	    // User is specifying an IPv4 address to accept finder
	    // connections from.
	    //
	    try {
		add_permitted_host(IPv4(optarg));
	    } catch (const InvalidString&) {
		fprintf(stderr, "%s is not a valid IPv4 address.\n", optarg);
		usage();
		exit(-1);
	    }
	    break;
	case 'i':
	    //
	    // User is specifying which interface to bind finder to
	    //
	    try {
		IPv4 bind_addr = IPv4(optarg);
		in_addr ina;
		bind_addr.copy_out(ina);
		if (is_ip_configured(ina) == false) {
		    fprintf(stderr,
			    "%s is not the address of an active interface.\n",
			    optarg);
		    exit(-1);
		}
		bind_addrs.push_back(bind_addr);
	    } catch (const InvalidString&) {
		fprintf(stderr, "%s is not a valid interface address.\n",
			optarg);
		usage();
		exit(-1);
	    }
	    break;
	case 'n':
	    //
	    // User is specifying a network address to accept finder
	    // connections from.
	    //
	    try {
		add_permitted_net(IPv4Net(optarg));
	    } catch (const InvalidString&) {
		fprintf(stderr, "%s is not a valid IPv4 network.\n", optarg);
		usage();
		exit(-1);
	    }
	    break;
	case 'p':
	    bind_port = static_cast<uint16_t>(atoi(optarg));
	    if (bind_port == 0) {
		fprintf(stderr, "0 is not a valid port.\n");
		exit(-1);
	    }
	    break;
	case 'v':
	    fprintf(stderr, "Finder\n");
	    run_verbose = true;
	    break;
	case 'h':
	default:
	    usage();
	    exit(-1);
	}
    }

    argc -= optind;
    argv += optind;

    if (argc != 0) {
	usage();
	exit(-1);
    }

    //
    // Add preferred ipc address on host
    //
    XorpUnexpectedHandler x(xorp_unexpected_handler);
    try {
	EventLoop e;
	FinderServer fs(e, FinderConstants::FINDER_DEFAULT_HOST(), bind_port);

	list<IPv4>::const_iterator ci = bind_addrs.begin();
	while (ci != bind_addrs.end()) {
	    if (fs.add_binding(*ci, bind_port) == false) {
		XLOG_WARNING("Failed to bind interface %s port %d\n",
			     ci->str().c_str(), bind_port);
	    } else if (run_verbose) {
		XLOG_INFO("Finder bound to interface %s port %d\n",
			  ci->str().c_str(), bind_port);
	    }
	    ++ci;
	}
	XorpTimer twirl;
	if (run_verbose)
	    twirl = e.new_periodic(250, callback(print_twirl));

	while (gbl_sig_exit == false) {
	    e.run();
	}
    } catch (const InvalidPort& i) {
	fprintf(stderr, "%s: a finder may already be running.\n",
		i.why().c_str());
    } catch (...) {
	xorp_catch_standard_exceptions();
    }
}

int
main(int argc, char * const argv[])
{
    //
    // Initialize and start xlog
    //
    xlog_init(argv[0], NULL);
    xlog_set_verbose(XLOG_VERBOSE_LOW);		// Least verbose messages
    // XXX: verbosity of the error messages temporary increased
    xlog_level_set_verbose(XLOG_LEVEL_ERROR, XLOG_VERBOSE_HIGH);
    xlog_add_default_output();
    xlog_start();

    // Initialize comm library.
    comm_init();

    finder_main(argc, argv);

    // Cleanup comm library.
    comm_exit();

    //
    // Gracefully stop and exit xlog
    //
    xlog_stop();
    xlog_exit();

    return 0;
}
