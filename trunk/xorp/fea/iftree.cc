// -*- c-basic-offset: 4; tab-width: 8; indent-tabs-mode: t -*-

// Copyright (c) 2001-2007 International Computer Science Institute
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

#ident "$XORP: xorp/fea/iftree.cc,v 1.54 2007/12/22 21:23:41 pavlin Exp $"

#include "fea_module.h"

#include "libxorp/xorp.h"
#include "libxorp/xlog.h"
#include "libxorp/debug.h"
#include "libxorp/c_format.hh"
#include "libxorp/vif.hh"

#include "iftree.hh"


/* ------------------------------------------------------------------------- */
/* IfTreeItem code */

string
IfTreeItem::str() const
{
    struct {
	State st;
	const char* desc;
    } t[] = { { CREATED, "CREATED" },
	      { DELETED, "DELETED" },
	      { CHANGED, "CHANGED" }
    };

    string r;
    for (size_t i = 0; i < sizeof(t) / sizeof(t[0]); i++) {
	if ((_st & t[i].st) == 0)
	    continue;
	if (r.empty() == false)
	    r += ",";
	r += t[i].desc;
    }

    return (r);
}

/* ------------------------------------------------------------------------- */
/* IfTree code */

void
IfTree::clear()
{
    _interfaces.clear();
}

int
IfTree::add_interface(const string& ifname)
{
    IfTreeInterface* ifp = find_interface(ifname);

    if (ifp != NULL) {
	ifp->mark(CREATED);
	return (XORP_OK);
    }

    _interfaces.insert(IfMap::value_type(ifname, IfTreeInterface(ifname)));

    return (XORP_OK);
}

IfTreeInterface*
IfTree::find_interface(const string& ifname)
{
    IfTree::IfMap::iterator iter = _interfaces.find(ifname);

    if (iter == interfaces().end())
	return (NULL);

    return (&iter->second);
}

const IfTreeInterface*
IfTree::find_interface(const string& ifname) const
{
    IfTree::IfMap::const_iterator iter = _interfaces.find(ifname);

    if (iter == interfaces().end())
	return (NULL);

    return (&iter->second);
}

IfTreeInterface*
IfTree::find_interface(uint32_t pif_index)
{
    IfTree::IfMap::iterator iter;

    for (iter = _interfaces.begin(); iter != _interfaces.end(); ++iter) {
	if (iter->second.pif_index() == pif_index)
	    return (&iter->second);
    }

    return (NULL);
}

const IfTreeInterface*
IfTree::find_interface(uint32_t pif_index) const
{
    IfTree::IfMap::const_iterator iter;

    for (iter = _interfaces.begin(); iter != _interfaces.end(); ++iter) {
	if (iter->second.pif_index() == pif_index)
	    return (&iter->second);
    }

    return (NULL);
}

IfTreeVif*
IfTree::find_vif(const string& ifname, const string& vifname)
{
    IfTreeInterface* ifp = find_interface(ifname);

    if (ifp == NULL)
	return (NULL);

    return (ifp->find_vif(vifname));
}

const IfTreeVif*
IfTree::find_vif(const string& ifname, const string& vifname) const
{
    const IfTreeInterface* ifp = find_interface(ifname);

    if (ifp == NULL)
	return (NULL);

    return (ifp->find_vif(vifname));
}

IfTreeVif*
IfTree::find_vif(uint32_t pif_index)
{
    IfTree::IfMap::iterator iter;

    //
    // XXX: Find the first vif that matches the physical index
    //
    for (iter = _interfaces.begin(); iter != _interfaces.end(); ++iter) {
	IfTreeVif* vifp = iter->second.find_vif(pif_index);
	if (vifp != NULL)
	    return (vifp);
    }

    return (NULL);
}

const IfTreeVif*
IfTree::find_vif(uint32_t pif_index) const
{
    IfTree::IfMap::const_iterator iter;

    //
    // XXX: Find the first vif that matches the physical index
    //
    for (iter = _interfaces.begin(); iter != _interfaces.end(); ++iter) {
	const IfTreeVif* vifp = iter->second.find_vif(pif_index);
	if (vifp != NULL)
	    return (vifp);
    }

    return (NULL);
}

IfTreeAddr4*
IfTree::find_addr(const string& ifname, const string& vifname,
		  const IPv4& addr)
{
    IfTreeVif* vifp = find_vif(ifname, vifname);

    if (vifp == NULL)
	return (NULL);

    return (vifp->find_addr(addr));
}

const IfTreeAddr4*
IfTree::find_addr(const string& ifname, const string& vifname,
		  const IPv4& addr) const
{
    const IfTreeVif* vifp = find_vif(ifname, vifname);

    if (vifp == NULL)
	return (NULL);

    return (vifp->find_addr(addr));
}

IfTreeAddr6*
IfTree::find_addr(const string& ifname, const string& vifname,
		  const IPv6& addr)
{
    IfTreeVif* vifp = find_vif(ifname, vifname);

    if (vifp == NULL)
	return (NULL);

    return (vifp->find_addr(addr));
}

const IfTreeAddr6*
IfTree::find_addr(const string& ifname, const string& vifname,
		  const IPv6& addr) const
{
    const IfTreeVif* vifp = find_vif(ifname, vifname);

    if (vifp == NULL)
	return (NULL);

    return (vifp->find_addr(addr));
}

bool
IfTree::find_interface_vif_by_addr(const IPvX& addr,
				   const IfTreeInterface*& ifp,
				   const IfTreeVif*& vifp) const
{
    IfTree::IfMap::const_iterator ii;
    IfTreeInterface::VifMap::const_iterator vi;
    IfTreeVif::IPv4Map::const_iterator ai4;
    IfTreeVif::IPv6Map::const_iterator ai6;

    ifp = NULL;
    vifp = NULL;

    //
    // Iterate through all interfaces and vifs
    //
    for (ii = interfaces().begin(); ii != interfaces().end(); ++ii) {
	const IfTreeInterface& fi = ii->second;
	for (vi = fi.vifs().begin(); vi != fi.vifs().end(); ++vi) {
	    const IfTreeVif& fv = vi->second;

	    //
	    // IPv4 address test
	    //
	    if (addr.is_ipv4()) {
		IPv4 addr4 = addr.get_ipv4();
		for (ai4 = fv.ipv4addrs().begin();
		     ai4 != fv.ipv4addrs().end();
		     ++ai4) {
		    const IfTreeAddr4& a4 = ai4->second;

		    if (a4.addr() == addr4) {
			// Found a match
			ifp = &fi;
			vifp = &fv;
			return (true);
		    }
		}
		continue;
	    }

	    //
	    // IPv6 address test
	    //
	    if (addr.is_ipv6()) {
		IPv6 addr6 = addr.get_ipv6();
		for (ai6 = fv.ipv6addrs().begin();
		     ai6 != fv.ipv6addrs().end();
		     ++ai6) {
		    const IfTreeAddr6& a6 = ai6->second;

		    if (a6.addr() == addr6) {
			// Found a match
			ifp = &fi;
			vifp = &fv;
			return (true);
		    }
		}
		continue;
	    }
	}
    }

    return (false);
}

bool
IfTree::find_interface_vif_same_subnet_or_p2p(const IPvX& addr,
					      const IfTreeInterface*& ifp,
					      const IfTreeVif*& vifp) const
{
    IfTree::IfMap::const_iterator ii;
    IfTreeInterface::VifMap::const_iterator vi;
    IfTreeVif::IPv4Map::const_iterator ai4;
    IfTreeVif::IPv6Map::const_iterator ai6;

    ifp = NULL;
    vifp = NULL;

    //
    // Iterate through all interfaces and vifs
    //
    for (ii = interfaces().begin(); ii != interfaces().end(); ++ii) {
	const IfTreeInterface& fi = ii->second;
	for (vi = fi.vifs().begin(); vi != fi.vifs().end(); ++vi) {
	    const IfTreeVif& fv = vi->second;

	    //
	    // IPv4 address test
	    //
	    if (addr.is_ipv4()) {
		IPv4 addr4 = addr.get_ipv4();
		for (ai4 = fv.ipv4addrs().begin();
		     ai4 != fv.ipv4addrs().end();
		     ++ai4) {
		    const IfTreeAddr4& a4 = ai4->second;

		    // Test if same subnet
		    IPv4Net subnet(a4.addr(), a4.prefix_len());
		    if (subnet.contains(addr4)) {
			// Found a match
			ifp = &fi;
			vifp = &fv;
			return (true);
		    }

		    // Test if same p2p
		    if (! a4.point_to_point())
			continue;
		    if ((a4.addr() == addr4) || (a4.endpoint() == addr4)) {
			// Found a match
			ifp = &fi;
			vifp = &fv;
			return (true);
		    }
		}
		continue;
	    }

	    //
	    // IPv6 address test
	    //
	    if (addr.is_ipv6()) {
		IPv6 addr6 = addr.get_ipv6();
		for (ai6 = fv.ipv6addrs().begin();
		     ai6 != fv.ipv6addrs().end();
		     ++ai6) {
		    const IfTreeAddr6& a6 = ai6->second;

		    // Test if same subnet
		    IPv6Net subnet(a6.addr(), a6.prefix_len());
		    if (subnet.contains(addr6)) {
			// Found a match
			ifp = &fi;
			vifp = &fv;
			return (true);
		    }

		    // Test if same p2p
		    if (! a6.point_to_point())
			continue;
		    if ((a6.addr() == addr6) || (a6.endpoint() == addr6)) {
			// Found a match
			ifp = &fi;
			vifp = &fv;
			return (true);
		    }
		}
		continue;
	    }
	}
    }

    return (false);
}

int
IfTree::remove_interface(const string& ifname)
{
    IfTreeInterface* ifp = find_interface(ifname);

    if (ifp == NULL)
	return (XORP_ERROR);

    ifp->mark(DELETED);

    return (XORP_OK);
}

/**
 * Recursively create a new interface or update its state if it already exists.
 *
 * @param other_iface the interface with the state to copy from.
 * @return XORP_OK on success, otherwise XORP_ERROR.
 */
int
IfTree::update_interface(const IfTreeInterface& other_iface)
{
    IfTreeInterface* this_ifp;
    IfTreeInterface::VifMap::iterator vi;
    IfTreeInterface::VifMap::const_iterator ov;

    //
    // Add the interface if we don't have it already
    //
    this_ifp = find_interface(other_iface.ifname());
    if (this_ifp == NULL) {
	add_interface(other_iface.ifname());
	this_ifp = find_interface(other_iface.ifname());
	XLOG_ASSERT(this_ifp != NULL);
    }

    //
    // Update the interface state
    //
    if (! this_ifp->is_same_state(other_iface))
	this_ifp->copy_state(other_iface);

    //
    // Update existing vifs and addresses
    //
    for (vi = this_ifp->vifs().begin(); vi != this_ifp->vifs().end(); ++vi) {
	IfTreeVif& this_vif = vi->second;
	const IfTreeVif* other_vifp;

	other_vifp = other_iface.find_vif(this_vif.vifname());
	if (other_vifp == NULL) {
	    this_vif.mark(DELETED);
	    continue;
	}
	const IfTreeVif& other_vif = *other_vifp;

	if (! this_vif.is_same_state(other_vif))
	    this_vif.copy_state(other_vif);

	//
	// Update the IPv4 addresses
	//
	IfTreeVif::IPv4Map::iterator ai4;
	for (ai4 = this_vif.ipv4addrs().begin();
	     ai4 != this_vif.ipv4addrs().end();
	     ++ai4) {
	    IfTreeAddr4& this_addr = ai4->second;
	    const IfTreeAddr4* other_ap;
	    other_ap = other_vif.find_addr(this_addr.addr());
	    if (other_ap == NULL) {
		this_addr.mark(DELETED);
		continue;
	    }
	    if (! this_addr.is_same_state(*other_ap))
		this_addr.copy_state(*other_ap);
	}

	//
	// Update the IPv6 addresses
	//
	IfTreeVif::IPv6Map::iterator ai6;
	for (ai6 = this_vif.ipv6addrs().begin();
	     ai6 != this_vif.ipv6addrs().end();
	     ++ai6) {
	    IfTreeAddr6& this_addr = ai6->second;
	    const IfTreeAddr6* other_ap;
	    other_ap = other_vif.find_addr(this_addr.addr());
	    if (other_ap == NULL) {
		this_addr.mark(DELETED);
		continue;
	    }
	    if (! this_addr.is_same_state(*other_ap))
		this_addr.copy_state(*other_ap);
	}
    }

    //
    // Add the new vifs and addresses
    //
    for (ov = other_iface.vifs().begin();
	 ov != other_iface.vifs().end();
	 ++ov) {
	const IfTreeVif& other_vif = ov->second;
	IfTreeVif* this_vifp;

	if (this_ifp->find_vif(other_vif.vifname()) != NULL)
	    continue;		// The vif was already updated

	//
	// Add the vif
	//
	this_ifp->add_vif(other_vif.vifname());
	this_vifp = this_ifp->find_vif(other_vif.vifname());
	XLOG_ASSERT(this_vifp != NULL);
	IfTreeVif& this_vif = *this_vifp;
	this_vif.copy_state(other_vif);

	//
	// Add the IPv4 addresses
	//
	IfTreeVif::IPv4Map::const_iterator oa4;
	for (oa4 = other_vif.ipv4addrs().begin();
	     oa4 != other_vif.ipv4addrs().end();
	     ++oa4) {
	    const IfTreeAddr4& other_addr = oa4->second;
	    IfTreeAddr4* this_ap;
	    this_ap = this_vif.find_addr(other_addr.addr());
	    if (this_ap != NULL)
		continue;	// The address was already updated

	    // Add the address
	    this_vif.add_addr(other_addr.addr());
	    this_ap = this_vif.find_addr(other_addr.addr());
	    XLOG_ASSERT(this_ap != NULL);
	    this_ap->copy_state(other_addr);
	}

	//
	// Add the IPv6 addresses
	//
	IfTreeVif::IPv6Map::const_iterator oa6;
	for (oa6 = other_vif.ipv6addrs().begin();
	     oa6 != other_vif.ipv6addrs().end();
	     ++oa6) {
	    const IfTreeAddr6& other_addr = oa6->second;
	    IfTreeAddr6* this_ap;
	    this_ap = this_vif.find_addr(other_addr.addr());
	    if (this_ap != NULL)
		continue;	// The address was already updated

	    // Add the address
	    this_vif.add_addr(other_addr.addr());
	    this_ap = this_vif.find_addr(other_addr.addr());
	    XLOG_ASSERT(this_ap != NULL);
	    this_ap->copy_state(other_addr);
	}
    }

    return (XORP_OK);
}

/**
 * Delete interfaces labelled as ready for deletion, call finalize_state()
 * on remaining interfaces, and set state to NO_CHANGE.
 */
void
IfTree::finalize_state()
{
    IfMap::iterator ii = _interfaces.begin();
    while (ii != _interfaces.end()) {
	//
	// If interface is marked as deleted, delete it.
	//
	if (ii->second.is_marked(DELETED)) {
	    _interfaces.erase(ii++);
	    continue;
	}
	//
	// Call finalize_state on interfaces that remain
	//
	ii->second.finalize_state();
	++ii;
    }
    set_state(NO_CHANGE);
}

string
IfTree::str() const
{
    string r;
    IfMap::const_iterator ii;

    //
    // Print the interfaces
    //
    for (ii = interfaces().begin(); ii != interfaces().end(); ++ii) {
	const IfTreeInterface& fi = ii->second;
	r += fi.str() + string("\n");

	//
	// Print the vifs
	//
	for (IfTreeInterface::VifMap::const_iterator vi = fi.vifs().begin();
	     vi != fi.vifs().end();
	     ++vi) {
	    const IfTreeVif& fv = vi->second;
	    r += string("  ") + fv.str() + string("\n");

	    //
	    // Print the IPv4 addresses
	    //
	    for (IfTreeVif::IPv4Map::const_iterator ai = fv.ipv4addrs().begin();
		 ai != fv.ipv4addrs().end();
		 ++ai) {
		const IfTreeAddr4& a = ai->second;
		r += string("    ") + a.str() + string("\n");
	    }

	    //
	    // Print the IPv6 addresses
	    //
	    for (IfTreeVif::IPv6Map::const_iterator ai = fv.ipv6addrs().begin();
		 ai != fv.ipv6addrs().end();
		 ++ai) {
		const IfTreeAddr6& a = ai->second;
		r += string("    ") + a.str() + string("\n");
	    }
	}
    }

    return (r);
}

/**
 * Align user supplied configuration with the device configuration.
 *
 * Inside the FEA there may be multiple configuration representations,
 * typically one the user modifies and one that mirrors the hardware.
 * Errors may occur pushing the user config down onto the hardware and
 * we need a method to update the user config from the h/w config that
 * exists after the config push.  We can't just copy the h/w config since
 * the user config is restricted to configuration set by the user.
 *
 * The alignment works as follows:
 * 1. If an interface in the local tree is marked as "soft", its
 *    state is not modified.
 * 2. If an interface in the local tree is marked as
 *    "default_system_config", the rest of the processing is not
 *    applied, and the following rules are used instead:
 *    (a) If the interface is not in the other tree, it is marked
 *        as "disabled" and its vifs are marked for deletion.
 *    (b) Otherwise, its state (and the subtree below it) is copied
 *        as-is from the other tree.
 * 3. If an item in the local tree is not in the other tree, it is
 *    marked as deleted in the local tree.
 * 4. If an item in the local tree is in the other tree, its state
 *    is copied from the other tree to the local tree by applying
 *    the following rules:
 *    (a) If an interface in the local tree is "flipped", then it
 *        is still marked as "flipped".
 *    (b) If the item in the local tree is not "enabled", then
 *        the state is still marked as not "enabled".
 *
 * @param other the configuration tree to align state with.
 * @return modified configuration structure.
 */
IfTree&
IfTree::align_with(const IfTree& other)
{
    IfTree::IfMap::iterator ii;

    //
    // Iterate through all interfaces
    //
    for (ii = interfaces().begin(); ii != interfaces().end(); ++ii) {
	IfTreeInterface& fi = ii->second;
	const string& ifname = fi.ifname();
	bool fi_enabled = fi.enabled();
	bool fi_flipped = fi.flipped();
	const IfTreeInterface* other_ifp = other.find_interface(ifname);

	//
	// Ignore "soft" interfaces
	//
	if (fi.is_soft())
	    continue;

	//
	// Special processing for "default_system_config" interfaces
	//
	if (fi.default_system_config()) {
	    if (other_ifp != NULL) {
		update_interface(*other_ifp);
	    } else {
		fi.set_enabled(false);
		IfTreeInterface::VifMap::iterator vi;
		for (vi = fi.vifs().begin(); vi != fi.vifs().end(); ++vi) {
		    IfTreeVif& fv = vi->second;
		    fv.mark(DELETED);
		}
	    }
	    continue;
	}

	//
	// Mark for deletion if not in the other tree
	//
	if (other_ifp == NULL) {
	    fi.mark(DELETED);
	    continue;
	}

	//
	// Copy state from the other tree
	//
	if (! fi.is_same_state(*other_ifp)) {
	    fi.copy_state(*other_ifp);
	    if (! fi_enabled)
		fi.set_enabled(fi_enabled);
	    if (fi_flipped)
		fi.set_flipped(fi_flipped);
	}

	//
	// Align the vif state
	//
	IfTreeInterface::VifMap::iterator vi;
	for (vi = fi.vifs().begin(); vi != fi.vifs().end(); ++vi) {
	    IfTreeVif& fv = vi->second;
	    const string& vifname = fv.vifname();
	    bool fv_enabled = fv.enabled();
	    const IfTreeVif* other_vifp = other_ifp->find_vif(vifname);

	    //
	    // Mark for deletion if not in the other tree
	    //
	    if (other_vifp == NULL) {
		fv.mark(DELETED);
		continue;
	    }

	    //
	    // Copy state from the other tree
	    //
	    if (! fv.is_same_state(*other_vifp)) {
		fv.copy_state(*other_vifp);
		if (! fv_enabled)
		    fv.set_enabled(fv_enabled);
	    }

	    //
	    // Align the IPv4 address state
	    //
	    IfTreeVif::IPv4Map::iterator ai4;
	    for (ai4 = fv.ipv4addrs().begin();
		 ai4 != fv.ipv4addrs().end();
		 ++ai4) {
		IfTreeAddr4& fa = ai4->second;
		bool fa_enabled = fa.enabled();
		const IfTreeAddr4* other_ap = other_vifp->find_addr(fa.addr());

		//
		// Mark for deletion if not in the other tree
		//
		if (other_ap == NULL) {
		    fa.mark(DELETED);
		    continue;
		}

		//
		// Copy state from the other tree
		//
		if (! fa.is_same_state(*other_ap)) {
		    fa.copy_state(*other_ap);
		    if (! fa_enabled)
			fa.set_enabled(fa_enabled);
		}
	    }

	    //
	    // Align the IPv4 address state
	    //
	    IfTreeVif::IPv6Map::iterator ai6;
	    for (ai6 = fv.ipv6addrs().begin();
		 ai6 != fv.ipv6addrs().end();
		 ++ai6) {
		IfTreeAddr6& fa = ai6->second;
		bool fa_enabled = fa.enabled();
		const IfTreeAddr6* other_ap = other_vifp->find_addr(fa.addr());

		//
		// Mark for deletion if not in the other tree
		//
		if (other_ap == NULL) {
		    fa.mark(DELETED);
		    continue;
		}

		//
		// Copy state from the other tree
		//
		if (! fa.is_same_state(*other_ap)) {
		    fa.copy_state(*other_ap);
		    if (! fa_enabled)
			fa.set_enabled(fa_enabled);
		}
	    }
	}
    }

    return (*this);
}

/**
 * Prepare configuration for pushing and replacing previous configuration.
 *
 * If the previous configuration is to be replaced with new configuration,
 * we need to prepare the state that will delete, update, and add the
 * new state as appropriate.
 * The preparation works as follows:
 * - All items in the local tree are preserved and are marked as created.
 * - All items in the other tree that are not in the local tree are
 *   added to the local tree and are marked as deleted.
 *
 * @param other the configuration tree to be used to prepare the
 * replacement state.
 * @return modified configuration structure.
 */
IfTree&
IfTree::prepare_replacement_state(const IfTree& other)
{
    IfTree::IfMap::iterator ii;
    IfTree::IfMap::const_iterator oi;

    //
    // Mark all entries in the local tree as created
    //
    for (ii = interfaces().begin(); ii != interfaces().end(); ++ii) {
	IfTreeInterface& fi = ii->second;
	fi.mark(CREATED);

	// Mark all vifs
	IfTreeInterface::VifMap::iterator vi;
	for (vi = fi.vifs().begin(); vi != fi.vifs().end(); ++vi) {
	    IfTreeVif& fv = vi->second;
	    fv.mark(CREATED);

	    // Mark all IPv4 addresses
	    IfTreeVif::IPv4Map::iterator ai4;
	    for (ai4 = fv.ipv4addrs().begin();
		 ai4 != fv.ipv4addrs().end();
		 ++ai4) {
		ai4->second.mark(CREATED);
	    }

	    // Mark all IPv6 addresses
	    IfTreeVif::IPv6Map::iterator ai6;
	    for (ai6 = fv.ipv6addrs().begin();
		 ai6 != fv.ipv6addrs().end();
		 ++ai6) {
		ai6->second.mark(CREATED);
	    }
	}
    }

    //
    // Iterate through all interfaces in the other tree
    //
    for (oi = other.interfaces().begin();
	 oi != other.interfaces().end();
	 ++oi) {
	const IfTreeInterface& other_iface = oi->second;
	const string& ifname = other_iface.ifname();
	IfTreeInterface* ifp = find_interface(ifname);
	if (ifp == NULL) {
	    //
	    // Add local interface and mark it for deletion.
	    //
	    // Mark local interface for deletion if not present in other.
	    //
	    add_interface(ifname);
	    ifp = find_interface(ifname);
	    XLOG_ASSERT(ifp != NULL);
	    ifp->copy_state(other_iface);
	    ifp->mark(DELETED);
	}

	//
	// Iterate through all vifs in the other tree
	//
	IfTreeInterface::VifMap::const_iterator ov;
	for (ov = other_iface.vifs().begin();
	     ov != other_iface.vifs().end();
	     ++ov) {
	    const IfTreeVif& other_vif = ov->second;
	    const string& vifname = other_vif.vifname();
	    IfTreeVif* vifp = ifp->find_vif(vifname);
	    if (vifp == NULL) {
		//
		// Add local vif and mark it for deletion.
		//
		ifp->add_vif(vifname);
		vifp = ifp->find_vif(vifname);
		XLOG_ASSERT(vifp != NULL);
		vifp->copy_state(other_vif);
		vifp->mark(DELETED);
	    }

	    //
	    // Iterate through all IPv4 addresses in the other tree
	    //
	    IfTreeVif::IPv4Map::const_iterator oa4;
	    for (oa4 = other_vif.ipv4addrs().begin();
		 oa4 != other_vif.ipv4addrs().end();
		 ++oa4) {
		const IfTreeAddr4& other_addr = oa4->second;
		IfTreeAddr4* ap = vifp->find_addr(other_addr.addr());
		if (ap == NULL) {
		    //
		    // Add local IPv4 address and mark it for deletion.
		    //
		    vifp->add_addr(other_addr.addr());
		    ap = vifp->find_addr(other_addr.addr());
		    XLOG_ASSERT(ap != NULL);
		    ap->copy_state(other_addr);
		    ap->mark(DELETED);
		}
	    }

	    //
	    // Iterate through all IPv6 addresses in the other tree
	    //
	    IfTreeVif::IPv6Map::const_iterator oa6;
	    for (oa6 = other_vif.ipv6addrs().begin();
		 oa6 != other_vif.ipv6addrs().end();
		 ++oa6) {
		const IfTreeAddr6& other_addr = oa6->second;
		IfTreeAddr6* ap = vifp->find_addr(other_addr.addr());
		if (ap == NULL) {
		    //
		    // Add local IPv6 address and mark it for deletion.
		    //
		    vifp->add_addr(other_addr.addr());
		    ap = vifp->find_addr(other_addr.addr());
		    XLOG_ASSERT(ap != NULL);
		    ap->copy_state(other_addr);
		    ap->mark(DELETED);
		}
	    }
	}
    }

    return (*this);
}

/**
 * Prune bogus deleted state.
 * 
 * If an item in the local tree is marked as deleted, but is not
 * in the other tree, then it is removed.
 * 
 * @param old_iftree the old tree with the state that is used as reference.
 * @return the modified configuration tree.
 */
IfTree&
IfTree::prune_bogus_deleted_state(const IfTree& old_iftree)
{
    IfTree::IfMap::iterator ii;

    //
    // Iterate through all interfaces
    //
    ii = _interfaces.begin();
    while (ii != _interfaces.end()) {
	IfTreeInterface& fi = ii->second;
	const string& ifname = fi.ifname();
	if (! fi.is_marked(DELETED)) {
	    ++ii;
	    continue;
	}
	const IfTreeInterface* old_ifp;
	old_ifp = old_iftree.find_interface(ifname);
	if (old_ifp == NULL) {
	    // Remove this item from the local tree
	    _interfaces.erase(ii++);
	    continue;
	}

	//
	// Iterate through all vifs
	//
	IfTreeInterface::VifMap::iterator vi;
	vi = fi.vifs().begin();
	while (vi != fi.vifs().end()) {
	    IfTreeVif& fv = vi->second;
	    const string& vifname = fv.vifname();
	    if (! fv.is_marked(DELETED)) {
		++vi;
		continue;
	    }
	    const IfTreeVif* old_vifp;
	    old_vifp = old_ifp->find_vif(vifname);
	    if (old_vifp == NULL) {
		// Remove this item from the local tree
		fi.vifs().erase(vi++);
		continue;
	    }

	    //
	    // Iterate through all IPv4 addresses
	    //
	    IfTreeVif::IPv4Map::iterator ai4;
	    ai4 = fv.ipv4addrs().begin();
	    while (ai4 != fv.ipv4addrs().end()) {
		IfTreeAddr4& fa = ai4->second;
		if (! fa.is_marked(DELETED)) {
		    ++ai4;
		    continue;
		}
		const IfTreeAddr4* old_ap;
		old_ap = old_vifp->find_addr(fa.addr());
		if (old_ap == NULL) {
		    // Remove this item from the local tree
		    fv.ipv4addrs().erase(ai4++);
		    continue;
		}
		++ai4;
	    }

	    //
	    // Iterate through all IPv6 addresses
	    //
	    IfTreeVif::IPv6Map::iterator ai6;
	    ai6 = fv.ipv6addrs().begin();
	    while (ai6 != fv.ipv6addrs().end()) {
		IfTreeAddr6& fa = ai6->second;
		if (! fa.is_marked(DELETED)) {
		    ++ai6;
		    continue;
		}
		const IfTreeAddr6* old_ap;
		old_ap = old_vifp->find_addr(fa.addr());
		if (old_ap == NULL) {
		    // Remove this item from the local tree
		    fv.ipv6addrs().erase(ai6++);
		    continue;
		}
		++ai6;
	    }
	    ++vi;
	}
	++ii;
    }

    return (*this);
}

/* ------------------------------------------------------------------------- */
/* IfTreeInterface code */

IfTreeInterface::IfTreeInterface(const string& ifname)
    : IfTreeItem(),
      _ifname(ifname),
      _pif_index(0),
      _enabled(false),
      _discard(false),
      _unreachable(false),
      _management(false),
      _default_system_config(false),
      _mtu(0),
      _no_carrier(false),
      _flipped(false),
      _interface_flags(0)
{}

int
IfTreeInterface::add_vif(const string& vifname)
{
    IfTreeVif* vifp = find_vif(vifname);

    if (vifp != NULL) {
	vifp->mark(CREATED);
	return (XORP_OK);
    }

    _vifs.insert(VifMap::value_type(vifname, IfTreeVif(ifname(), vifname)));

    return (XORP_OK);
}

int
IfTreeInterface::remove_vif(const string& vifname)
{
    IfTreeVif* vifp = find_vif(vifname);

    if (vifp == NULL)
	return (XORP_ERROR);

    vifp->mark(DELETED);

    return (XORP_OK);
}

IfTreeVif*
IfTreeInterface::find_vif(const string& vifname)
{
    IfTreeInterface::VifMap::iterator iter = _vifs.find(vifname);

    if (iter == _vifs.end())
	return (NULL);

    return (&iter->second);
}

const IfTreeVif*
IfTreeInterface::find_vif(const string& vifname) const
{
    IfTreeInterface::VifMap::const_iterator iter = _vifs.find(vifname);

    if (iter == _vifs.end())
	return (NULL);

    return (&iter->second);
}

IfTreeVif*
IfTreeInterface::find_vif(uint32_t pif_index)
{
    IfTreeInterface::VifMap::iterator iter;

    for (iter = _vifs.begin(); iter != _vifs.end(); ++iter) {
	if (iter->second.pif_index() == pif_index)
	    return (&iter->second);
    }

    return (NULL);
}

const IfTreeVif*
IfTreeInterface::find_vif(uint32_t pif_index) const
{
    IfTreeInterface::VifMap::const_iterator iter;

    for (iter = _vifs.begin(); iter != _vifs.end(); ++iter) {
	if (iter->second.pif_index() == pif_index)
	    return (&iter->second);
    }

    return (NULL);
}

IfTreeAddr4*
IfTreeInterface::find_addr(const string& vifname, const IPv4& addr)
{
    IfTreeVif* vif = find_vif(vifname);

    if (vif == NULL)
	return (NULL);

    return (vif->find_addr(addr));
}

const IfTreeAddr4*
IfTreeInterface::find_addr(const string& vifname, const IPv4& addr) const
{
    const IfTreeVif* vif = find_vif(vifname);

    if (vif == NULL)
	return (NULL);

    return (vif->find_addr(addr));
}

IfTreeAddr6*
IfTreeInterface::find_addr(const string& vifname, const IPv6& addr)
{
    IfTreeVif* vif = find_vif(vifname);

    if (vif == NULL)
	return (NULL);

    return (vif->find_addr(addr));
}

const IfTreeAddr6*
IfTreeInterface::find_addr(const string& vifname, const IPv6& addr) const
{
    const IfTreeVif* vif = find_vif(vifname);

    if (vif == NULL)
	return (NULL);

    return (vif->find_addr(addr));
}

void
IfTreeInterface::finalize_state()
{
    //
    // Iterate through all vifs
    //
    VifMap::iterator vi = _vifs.begin();
    while (vi != _vifs.end()) {
	//
	// If interface is marked as deleted, delete it.
	//
	if (vi->second.is_marked(DELETED)) {
	    _vifs.erase(vi++);
	    continue;
	}
	//
	// Call finalize_state on vifs that remain
	//
	vi->second.finalize_state();
	++vi;
    }
    set_state(NO_CHANGE);
}

string
IfTreeInterface::str() const
{
    string r = c_format("Interface %s { pif_index = %u } { enabled := %s } "
			"{ discard := %s } { unreachable := %s } "
			"{ management = %s } { default_system_config = %s }"
			"{ mtu := %u } { mac := %s } { no_carrier = %s } "
			"{ flipped := %s } { flags := %u }",
			_ifname.c_str(),
			XORP_UINT_CAST(_pif_index),
			bool_c_str(_enabled),
			bool_c_str(_discard),
			bool_c_str(_unreachable),
			bool_c_str(_management),
			bool_c_str(_default_system_config),
			XORP_UINT_CAST(_mtu),
			_mac.str().c_str(),
			bool_c_str(_no_carrier),
			bool_c_str(_flipped),
			XORP_UINT_CAST(_interface_flags));
    r += string(" ") + IfTreeItem::str();

    return (r);
}

/* ------------------------------------------------------------------------- */
/* IfTreeVif code */

IfTreeVif::IfTreeVif(const string& ifname, const string& vifname)
    : IfTreeItem(),
      _ifname(ifname),
      _vifname(vifname),
      _pif_index(0),
      _vif_index(Vif::VIF_INDEX_INVALID),
      _enabled(false),
      _broadcast(false),
      _loopback(false),
      _point_to_point(false),
      _multicast(false),
      _pim_register(false),
      _vif_flags(0),
      _is_vlan(false),
      _vlan_id(0)
{}

int
IfTreeVif::add_addr(const IPv4& addr)
{
    IfTreeAddr4* ap = find_addr(addr);

    if (ap != NULL) {
	ap->mark(CREATED);
	return (XORP_OK);
    }

    _ipv4addrs.insert(IPv4Map::value_type(addr, IfTreeAddr4(addr)));

    return (XORP_OK);
}

int
IfTreeVif::remove_addr(const IPv4& addr)
{
    IfTreeAddr4* ap = find_addr(addr);

    if (ap == NULL)
	return (XORP_ERROR);

    ap->mark(DELETED);

    return (XORP_OK);
}

int
IfTreeVif::add_addr(const IPv6& addr)
{
    IfTreeAddr6* ap = find_addr(addr);

    if (ap != NULL) {
	ap->mark(CREATED);
	return (XORP_OK);
    }

    _ipv6addrs.insert(IPv6Map::value_type(addr, IfTreeAddr6(addr)));

    return (XORP_OK);
}

int
IfTreeVif::remove_addr(const IPv6& addr)
{
    IfTreeAddr6* ap = find_addr(addr);

    if (ap == NULL)
	return (XORP_ERROR);

    ap->mark(DELETED);

    return (XORP_OK);
}

IfTreeAddr4*
IfTreeVif::find_addr(const IPv4& addr)
{
    IfTreeVif::IPv4Map::iterator iter = _ipv4addrs.find(addr);

    if (iter == _ipv4addrs.end())
	return (NULL);

    return (&iter->second);
}

const IfTreeAddr4*
IfTreeVif::find_addr(const IPv4& addr) const
{
    IfTreeVif::IPv4Map::const_iterator iter = _ipv4addrs.find(addr);

    if (iter == _ipv4addrs.end())
	return (NULL);

    return (&iter->second);
}

IfTreeAddr6*
IfTreeVif::find_addr(const IPv6& addr)
{
    IfTreeVif::IPv6Map::iterator iter = _ipv6addrs.find(addr);

    if (iter == _ipv6addrs.end())
	return (NULL);

    return (&iter->second);
}

const IfTreeAddr6*
IfTreeVif::find_addr(const IPv6& addr) const
{
    IfTreeVif::IPv6Map::const_iterator iter = _ipv6addrs.find(addr);

    if (iter == _ipv6addrs.end())
	return (NULL);

    return (&iter->second);
}

void
IfTreeVif::finalize_state()
{
    //
    // Iterate through all IPv4 addresses
    //
    for (IPv4Map::iterator ai = _ipv4addrs.begin(); ai != _ipv4addrs.end(); ) {
	//
	// If address is marked as deleted, delete it.
	//
	if (ai->second.is_marked(DELETED)) {
	    _ipv4addrs.erase(ai++);
	    continue;
	}
	//
	// Call finalize_state on addresses that remain
	//
	ai->second.finalize_state();
	++ai;
    }

    //
    // Iterate through all IPv6 addresses
    //
    for (IPv6Map::iterator ai = _ipv6addrs.begin(); ai != _ipv6addrs.end(); ) {
	//
	// If address is marked as deleted, delete it.
	//
	if (ai->second.is_marked(DELETED)) {
	    _ipv6addrs.erase(ai++);
	    continue;
	}
	//
	// Call finalize_state on interfaces that remain
	//
	ai->second.finalize_state();
	++ai;
    }
    set_state(NO_CHANGE);
}

string
IfTreeVif::str() const
{
    string pim_register_str;
    string vif_index_str;
    string vlan_str;

    //
    // XXX: Conditionally print the pim_register flag, because it is
    // used only by the MFEA.
    //
    if (_pim_register) {
	pim_register_str = c_format("{ pim_register := %s } ",
				    bool_c_str(_pim_register));
    }
    // XXX: Conditionally print the vif_index, because it is rarely used
    if (_vif_index != Vif::VIF_INDEX_INVALID) {
	vif_index_str = c_format("{ vif_index := %u } ",
				 XORP_UINT_CAST(_vif_index));
    }
    // XXX: Conditionally print the VLAN ID
    if (_is_vlan) {
	vlan_str = c_format("{ vlan_id = %u } ", _vlan_id);
    }
    vif_index_str += pim_register_str;
    vif_index_str += vlan_str;

    string r = c_format("VIF %s { pif_index = %u } { enabled := %s } "
			"{ broadcast := %s } { loopback := %s } "
			"{ point_to_point := %s } { multicast := %s } "
			"{ flags := %u }",
			_vifname.c_str(), XORP_UINT_CAST(_pif_index),
			bool_c_str(_enabled), bool_c_str(_broadcast),
			bool_c_str(_loopback), bool_c_str(_point_to_point),
			bool_c_str(_multicast), XORP_UINT_CAST(_vif_flags));
    r += vif_index_str + string(" ") + IfTreeItem::str();

    return (r);
}

/* ------------------------------------------------------------------------- */
/* IfTreeAddr4 code */

int
IfTreeAddr4::set_prefix_len(uint32_t prefix_len)
{
    if (prefix_len > IPv4::addr_bitlen())
	return (XORP_ERROR);

    _prefix_len = prefix_len;
    mark(CHANGED);

    return (XORP_OK);
}

void
IfTreeAddr4::set_bcast(const IPv4& baddr)
{
    _oaddr = baddr;
    mark(CHANGED);
}

IPv4
IfTreeAddr4::bcast() const
{
    if (broadcast())
	return (_oaddr);

    return (IPv4::ZERO());
}

void
IfTreeAddr4::set_endpoint(const IPv4& oaddr)
{
    _oaddr = oaddr;
    mark(CHANGED);
}

IPv4
IfTreeAddr4::endpoint() const
{
    if (point_to_point())
	return (_oaddr);

    return (IPv4::ZERO());
}

void
IfTreeAddr4::finalize_state()
{
    set_state(NO_CHANGE);
}

string
IfTreeAddr4::str() const
{
    string r = c_format("IPv4Addr %s { enabled := %s } { broadcast := %s } "
			"{ loopback := %s } { point_to_point := %s } "
			"{ multicast := %s } "
			"{ prefix_len := %u }",
			_addr.str().c_str(), bool_c_str(_enabled),
			bool_c_str(_broadcast), bool_c_str(_loopback),
			bool_c_str(_point_to_point), bool_c_str(_multicast),
			XORP_UINT_CAST(_prefix_len));
    if (_point_to_point)
	r += c_format(" { endpoint := %s }", _oaddr.str().c_str());
    if (_broadcast)
	r += c_format(" { broadcast := %s }", _oaddr.str().c_str());
    r += string(" ") + IfTreeItem::str();

    return (r);
}

/* ------------------------------------------------------------------------- */
/* IfTreeAddr6 code */

int
IfTreeAddr6::set_prefix_len(uint32_t prefix_len)
{
    if (prefix_len > IPv6::addr_bitlen())
	return (XORP_ERROR);

    _prefix_len = prefix_len;
    mark(CHANGED);

    return (XORP_OK);
}

void
IfTreeAddr6::set_endpoint(const IPv6& oaddr)
{
    _oaddr = oaddr;
    mark(CHANGED);
}

IPv6
IfTreeAddr6::endpoint() const
{
    if (point_to_point())
	return (_oaddr);

    return (IPv6::ZERO());
}

void
IfTreeAddr6::finalize_state()
{
    set_state(NO_CHANGE);
}

string
IfTreeAddr6::str() const
{
    string r = c_format("IPv6Addr %s { enabled := %s } "
			"{ loopback := %s } { point_to_point := %s } "
			"{ multicast := %s } "
			"{ prefix_len := %u }",
			_addr.str().c_str(), bool_c_str(_enabled),
			bool_c_str(_loopback),
			bool_c_str(_point_to_point), bool_c_str(_multicast),
			XORP_UINT_CAST(_prefix_len));
    if (_point_to_point)
	r += c_format(" { endpoint := %s }", _oaddr.str().c_str());
    r += string(" ") + IfTreeItem::str();

    return (r);
}
