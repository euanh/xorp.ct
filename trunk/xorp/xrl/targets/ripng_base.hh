/*
 * Copyright (c) 2001-2003 International Computer Science Institute
 * See LICENSE file for licensing, conditions, and warranties on use.
 *
 * DO NOT EDIT THIS FILE - IT IS PROGRAMMATICALLY GENERATED
 *
 * Generated by 'tgt-gen'.
 *
 * $XORP: xorp/xrl/targets/ripng_base.hh,v 1.4 2004/03/01 19:53:58 hodson Exp $
 */


#ifndef __XRL_INTERFACES_RIPNG_BASE_HH__
#define __XRL_INTERFACES_RIPNG_BASE_HH__

#undef XORP_LIBRARY_NAME
#define XORP_LIBRARY_NAME "XrlRipngTarget"

#include "libxorp/xlog.h"
#include "libxipc/xrl_cmd_map.hh"

class XrlRipngTargetBase {
protected:
    XrlCmdMap* _cmds;

public:
    /**
     * Constructor.
     *
     * @param cmds an XrlCmdMap that the commands associated with the target
     *		   should be added to.  This is typically the XrlRouter
     *		   associated with the target.
     */
    XrlRipngTargetBase(XrlCmdMap* cmds = 0);

    /**
     * Destructor.
     *
     * Dissociates instance commands from command map.
     */
    virtual ~XrlRipngTargetBase();

    /**
     * Set command map.
     *
     * @param cmds pointer to command map to associate commands with.  This
     * argument is typically a pointer to the XrlRouter associated with the
     * target.
     *
     * @return true on success, false if cmds is null or a command map has
     * already been supplied.
     */
    bool set_command_map(XrlCmdMap* cmds);

    /**
     * Get Xrl instance name associated with command map.
     */
    inline const string& name() const { return _cmds->name(); }

    /**
     * Get version string of instance.
     */
    inline const char* version() const { return "ripng/0.0"; }

protected:

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get name of Xrl Target
     */
    virtual XrlCmdError common_0_1_get_target_name(
	// Output values,
	string&	name) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get version string from Xrl Target
     */
    virtual XrlCmdError common_0_1_get_version(
	// Output values,
	string&	version) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get status of Xrl Target
     */
    virtual XrlCmdError common_0_1_get_status(
	// Output values,
	uint32_t&	status,
	string&	reason) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Request clean shutdown of Xrl Target
     */
    virtual XrlCmdError common_0_1_shutdown() = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Announce target birth.
     */
    virtual XrlCmdError finder_event_observer_0_1_xrl_target_birth(
	// Input values,
	const string&	target_class,
	const string&	target_instance) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Announce target death.
     */
    virtual XrlCmdError finder_event_observer_0_1_xrl_target_death(
	// Input values,
	const string&	target_class,
	const string&	target_instance) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Add an address to run RIP process on. The addition of address is not
     *  instantaneous, RIP has to instantiate state in the FEA to send and
     *  receive packets. Once instantiated the address must be explicitly
     *  enabled with set_rip_address_enabled.
     *
     *  @param ifname the interface that owns vif that has address.
     *
     *  @param vifname virtual interface owning address.
     *
     *  @param addr the address to be added.
     */
    virtual XrlCmdError ripng_0_1_add_rip_address(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv6&	addr) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Remove an address RIP process is running on.
     *
     *  @param ifname the interface that owns vif that has address.
     *
     *  @param vifname virtual interface owning address.
     *
     *  @param addr the address to be removed.
     */
    virtual XrlCmdError ripng_0_1_remove_rip_address(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv6&	addr) = 0;

    virtual XrlCmdError ripng_0_1_set_rip_address_enabled(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv6&	addr,
	const bool&	enabled) = 0;

    virtual XrlCmdError ripng_0_1_rip_address_enabled(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv6&	addr,
	// Output values,
	bool&	enabled) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Set cost metric associated with address.
     */
    virtual XrlCmdError ripng_0_1_set_cost(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv6&	addr,
	const uint32_t&	cost) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get cost metric associated with address.
     */
    virtual XrlCmdError ripng_0_1_cost(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv6&	addr,
	// Output values,
	uint32_t&	cost) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Set horizon type applied to routes advertised from address.
     *
     *  @param horizon name of horizon type. Permitted values: "none",
     *  "poison-reverse" "split-horizon-poison-reverse"
     */
    virtual XrlCmdError ripng_0_1_set_horizon(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv6&	addr,
	const string&	horizon) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get horizon type applied to routes advertised from address.
     */
    virtual XrlCmdError ripng_0_1_horizon(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv6&	addr,
	// Output values,
	string&	horizon) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Make RIP passive (receive only) on interface/vif/address.
     */
    virtual XrlCmdError ripng_0_1_set_passive(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv6&	addr,
	const bool&	passive) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get value indicating whether RIP is passive (receive only) on
     *  interface/vif/address.
     */
    virtual XrlCmdError ripng_0_1_passive(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv6&	addr,
	// Output values,
	bool&	passive) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Accept and respond to non-RIP requests.
     */
    virtual XrlCmdError ripng_0_1_set_accept_non_rip_requests(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv6&	addr,
	const bool&	accept) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get value indicating whether non-RIP requests are accepted and
     *  responded to on interface/vif/address.
     */
    virtual XrlCmdError ripng_0_1_accept_non_rip_requests(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv6&	addr,
	// Output values,
	bool&	accept) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Accept default route from peers.
     */
    virtual XrlCmdError ripng_0_1_set_accept_default_route(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv6&	addr,
	const bool&	accept) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Accessor for whether default route is accepted from peers.
     */
    virtual XrlCmdError ripng_0_1_accept_default_route(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv6&	addr,
	// Output values,
	bool&	accept) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Advertise default route (if present).
     */
    virtual XrlCmdError ripng_0_1_set_advertise_default_route(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv6&	addr,
	const bool&	advertise) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Accessor for whether default route is advertised.
     */
    virtual XrlCmdError ripng_0_1_advertise_default_route(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv6&	addr,
	// Output values,
	bool&	advertise) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Set period that routes associated with reception address will expire in
     *  the absence of updates.
     */
    virtual XrlCmdError ripng_0_1_set_route_expiry_seconds(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv6&	addr,
	const uint32_t&	t_secs) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get period that routes associated with reception address will expire in
     *  the absence of updates.
     */
    virtual XrlCmdError ripng_0_1_route_expiry_seconds(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv6&	addr,
	// Output values,
	uint32_t&	t_secs) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Set period that routes associated with reception address will be
     *  deleted after they've expired.
     */
    virtual XrlCmdError ripng_0_1_set_route_deletion_seconds(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv6&	addr,
	const uint32_t&	t_secs) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get period that routes associated with reception address will be
     *  deleted after they've expired.
     */
    virtual XrlCmdError ripng_0_1_route_deletion_seconds(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv6&	addr,
	// Output values,
	uint32_t&	t_secs) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Set period that route table requests should be sent from address when
     *  no peers are associated with it.
     */
    virtual XrlCmdError ripng_0_1_set_table_request_seconds(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv6&	addr,
	const uint32_t&	t_secs) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Set period that route table requests should be sent from address when
     *  no peers are associated with it.
     */
    virtual XrlCmdError ripng_0_1_table_request_seconds(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv6&	addr,
	// Output values,
	uint32_t&	t_secs) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Set minimum period between the unsolicited sending of the routing table
     *  from address.
     */
    virtual XrlCmdError ripng_0_1_set_unsolicited_response_min_seconds(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv6&	addr,
	const uint32_t&	t_secs) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get minimum period between the unsolicited sending of the routing table
     *  from address.
     */
    virtual XrlCmdError ripng_0_1_unsolicited_response_min_seconds(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv6&	addr,
	// Output values,
	uint32_t&	t_secs) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Set maximum period between the unsolicited sending of the routing table
     *  from address.
     */
    virtual XrlCmdError ripng_0_1_set_unsolicited_response_max_seconds(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv6&	addr,
	const uint32_t&	t_secs) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get maximum period between the unsolicited sending of the routing table
     *  from address.
     */
    virtual XrlCmdError ripng_0_1_unsolicited_response_max_seconds(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv6&	addr,
	// Output values,
	uint32_t&	t_secs) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Set minimum period between sending triggered updates from address.
     */
    virtual XrlCmdError ripng_0_1_set_triggered_update_min_seconds(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv6&	addr,
	const uint32_t&	t_secs) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get minimum period between sending triggered updates from address.
     */
    virtual XrlCmdError ripng_0_1_triggered_update_min_seconds(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv6&	addr,
	// Output values,
	uint32_t&	t_secs) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Set maximum period between sending triggered updates from address.
     */
    virtual XrlCmdError ripng_0_1_set_triggered_update_max_seconds(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv6&	addr,
	const uint32_t&	t_secs) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get maximum period between sending triggered updates from address.
     */
    virtual XrlCmdError ripng_0_1_triggered_update_max_seconds(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv6&	addr,
	// Output values,
	uint32_t&	t_secs) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Set the inter-packet delay between the output of packets from address.
     */
    virtual XrlCmdError ripng_0_1_set_interpacket_delay_milliseconds(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv6&	addr,
	const uint32_t&	t_msecs) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get the inter-packet delay between the output of packets from address.
     */
    virtual XrlCmdError ripng_0_1_interpacket_delay_milliseconds(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv6&	addr,
	// Output values,
	uint32_t&	t_msecs) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get a textual description of the status of address RIP is running upon.
     *
     *  @param ifname the interface that owns vif that has the address.
     *
     *  @param vifname virtual interface owns the address.
     *
     *  @param addr the address to query.
     */
    virtual XrlCmdError ripng_0_1_rip_address_status(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv6&	addr,
	// Output values,
	string&	status) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get the list of peers associated with interface / vif / address.
     */
    virtual XrlCmdError ripng_0_1_get_peers(
	// Input values,
	const string&	ifname,
	const string&	vifname,
	const IPv6&	addr,
	// Output values,
	XrlAtomList&	peers) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Get list of all peers known to RIP. There is a 1-to-1 correspondence
     *  between the items in the lists of peers, ifnames, vifnames, addrs.
     */
    virtual XrlCmdError ripng_0_1_get_all_peers(
	// Output values,
	XrlAtomList&	peers,
	XrlAtomList&	ifnames,
	XrlAtomList&	vifnames,
	XrlAtomList&	addrs) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Add a static route.
     *
     *  @param network route target.
     *
     *  @param nexthop path to direct packets for
     *
     *  @param cost RIP cost [0--15].
     *
     *  @ref network to.
     */
    virtual XrlCmdError ripng_0_1_add_static_route(
	// Input values,
	const IPv6Net&	network,
	const IPv6&	nexthop,
	const uint32_t&	cost) = 0;

    /**
     *  Pure-virtual function that needs to be implemented to:
     *
     *  Remove static route.
     *
     *  @param network route target. This method will fail if network was not
     *  previously added with add_static_route.
     */
    virtual XrlCmdError ripng_0_1_delete_static_route(
	// Input values,
	const IPv6Net&	network) = 0;

private:
    const XrlCmdError handle_common_0_1_get_target_name(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_common_0_1_get_version(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_common_0_1_get_status(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_common_0_1_shutdown(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_finder_event_observer_0_1_xrl_target_birth(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_finder_event_observer_0_1_xrl_target_death(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_ripng_0_1_add_rip_address(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_ripng_0_1_remove_rip_address(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_ripng_0_1_set_rip_address_enabled(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_ripng_0_1_rip_address_enabled(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_ripng_0_1_set_cost(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_ripng_0_1_cost(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_ripng_0_1_set_horizon(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_ripng_0_1_horizon(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_ripng_0_1_set_passive(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_ripng_0_1_passive(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_ripng_0_1_set_accept_non_rip_requests(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_ripng_0_1_accept_non_rip_requests(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_ripng_0_1_set_accept_default_route(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_ripng_0_1_accept_default_route(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_ripng_0_1_set_advertise_default_route(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_ripng_0_1_advertise_default_route(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_ripng_0_1_set_route_expiry_seconds(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_ripng_0_1_route_expiry_seconds(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_ripng_0_1_set_route_deletion_seconds(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_ripng_0_1_route_deletion_seconds(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_ripng_0_1_set_table_request_seconds(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_ripng_0_1_table_request_seconds(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_ripng_0_1_set_unsolicited_response_min_seconds(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_ripng_0_1_unsolicited_response_min_seconds(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_ripng_0_1_set_unsolicited_response_max_seconds(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_ripng_0_1_unsolicited_response_max_seconds(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_ripng_0_1_set_triggered_update_min_seconds(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_ripng_0_1_triggered_update_min_seconds(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_ripng_0_1_set_triggered_update_max_seconds(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_ripng_0_1_triggered_update_max_seconds(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_ripng_0_1_set_interpacket_delay_milliseconds(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_ripng_0_1_interpacket_delay_milliseconds(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_ripng_0_1_rip_address_status(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_ripng_0_1_get_peers(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_ripng_0_1_get_all_peers(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_ripng_0_1_add_static_route(const XrlArgs& in, XrlArgs* out);

    const XrlCmdError handle_ripng_0_1_delete_static_route(const XrlArgs& in, XrlArgs* out);

    void add_handlers()
    {
	if (_cmds->add_handler("common/0.1/get_target_name",
	    callback(this, &XrlRipngTargetBase::handle_common_0_1_get_target_name)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://ripng/common/0.1/get_target_name");
	}
	if (_cmds->add_handler("common/0.1/get_version",
	    callback(this, &XrlRipngTargetBase::handle_common_0_1_get_version)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://ripng/common/0.1/get_version");
	}
	if (_cmds->add_handler("common/0.1/get_status",
	    callback(this, &XrlRipngTargetBase::handle_common_0_1_get_status)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://ripng/common/0.1/get_status");
	}
	if (_cmds->add_handler("common/0.1/shutdown",
	    callback(this, &XrlRipngTargetBase::handle_common_0_1_shutdown)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://ripng/common/0.1/shutdown");
	}
	if (_cmds->add_handler("finder_event_observer/0.1/xrl_target_birth",
	    callback(this, &XrlRipngTargetBase::handle_finder_event_observer_0_1_xrl_target_birth)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://ripng/finder_event_observer/0.1/xrl_target_birth");
	}
	if (_cmds->add_handler("finder_event_observer/0.1/xrl_target_death",
	    callback(this, &XrlRipngTargetBase::handle_finder_event_observer_0_1_xrl_target_death)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://ripng/finder_event_observer/0.1/xrl_target_death");
	}
	if (_cmds->add_handler("ripng/0.1/add_rip_address",
	    callback(this, &XrlRipngTargetBase::handle_ripng_0_1_add_rip_address)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://ripng/ripng/0.1/add_rip_address");
	}
	if (_cmds->add_handler("ripng/0.1/remove_rip_address",
	    callback(this, &XrlRipngTargetBase::handle_ripng_0_1_remove_rip_address)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://ripng/ripng/0.1/remove_rip_address");
	}
	if (_cmds->add_handler("ripng/0.1/set_rip_address_enabled",
	    callback(this, &XrlRipngTargetBase::handle_ripng_0_1_set_rip_address_enabled)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://ripng/ripng/0.1/set_rip_address_enabled");
	}
	if (_cmds->add_handler("ripng/0.1/rip_address_enabled",
	    callback(this, &XrlRipngTargetBase::handle_ripng_0_1_rip_address_enabled)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://ripng/ripng/0.1/rip_address_enabled");
	}
	if (_cmds->add_handler("ripng/0.1/set_cost",
	    callback(this, &XrlRipngTargetBase::handle_ripng_0_1_set_cost)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://ripng/ripng/0.1/set_cost");
	}
	if (_cmds->add_handler("ripng/0.1/cost",
	    callback(this, &XrlRipngTargetBase::handle_ripng_0_1_cost)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://ripng/ripng/0.1/cost");
	}
	if (_cmds->add_handler("ripng/0.1/set_horizon",
	    callback(this, &XrlRipngTargetBase::handle_ripng_0_1_set_horizon)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://ripng/ripng/0.1/set_horizon");
	}
	if (_cmds->add_handler("ripng/0.1/horizon",
	    callback(this, &XrlRipngTargetBase::handle_ripng_0_1_horizon)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://ripng/ripng/0.1/horizon");
	}
	if (_cmds->add_handler("ripng/0.1/set_passive",
	    callback(this, &XrlRipngTargetBase::handle_ripng_0_1_set_passive)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://ripng/ripng/0.1/set_passive");
	}
	if (_cmds->add_handler("ripng/0.1/passive",
	    callback(this, &XrlRipngTargetBase::handle_ripng_0_1_passive)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://ripng/ripng/0.1/passive");
	}
	if (_cmds->add_handler("ripng/0.1/set_accept_non_rip_requests",
	    callback(this, &XrlRipngTargetBase::handle_ripng_0_1_set_accept_non_rip_requests)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://ripng/ripng/0.1/set_accept_non_rip_requests");
	}
	if (_cmds->add_handler("ripng/0.1/accept_non_rip_requests",
	    callback(this, &XrlRipngTargetBase::handle_ripng_0_1_accept_non_rip_requests)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://ripng/ripng/0.1/accept_non_rip_requests");
	}
	if (_cmds->add_handler("ripng/0.1/set_accept_default_route",
	    callback(this, &XrlRipngTargetBase::handle_ripng_0_1_set_accept_default_route)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://ripng/ripng/0.1/set_accept_default_route");
	}
	if (_cmds->add_handler("ripng/0.1/accept_default_route",
	    callback(this, &XrlRipngTargetBase::handle_ripng_0_1_accept_default_route)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://ripng/ripng/0.1/accept_default_route");
	}
	if (_cmds->add_handler("ripng/0.1/set_advertise_default_route",
	    callback(this, &XrlRipngTargetBase::handle_ripng_0_1_set_advertise_default_route)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://ripng/ripng/0.1/set_advertise_default_route");
	}
	if (_cmds->add_handler("ripng/0.1/advertise_default_route",
	    callback(this, &XrlRipngTargetBase::handle_ripng_0_1_advertise_default_route)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://ripng/ripng/0.1/advertise_default_route");
	}
	if (_cmds->add_handler("ripng/0.1/set_route_expiry_seconds",
	    callback(this, &XrlRipngTargetBase::handle_ripng_0_1_set_route_expiry_seconds)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://ripng/ripng/0.1/set_route_expiry_seconds");
	}
	if (_cmds->add_handler("ripng/0.1/route_expiry_seconds",
	    callback(this, &XrlRipngTargetBase::handle_ripng_0_1_route_expiry_seconds)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://ripng/ripng/0.1/route_expiry_seconds");
	}
	if (_cmds->add_handler("ripng/0.1/set_route_deletion_seconds",
	    callback(this, &XrlRipngTargetBase::handle_ripng_0_1_set_route_deletion_seconds)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://ripng/ripng/0.1/set_route_deletion_seconds");
	}
	if (_cmds->add_handler("ripng/0.1/route_deletion_seconds",
	    callback(this, &XrlRipngTargetBase::handle_ripng_0_1_route_deletion_seconds)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://ripng/ripng/0.1/route_deletion_seconds");
	}
	if (_cmds->add_handler("ripng/0.1/set_table_request_seconds",
	    callback(this, &XrlRipngTargetBase::handle_ripng_0_1_set_table_request_seconds)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://ripng/ripng/0.1/set_table_request_seconds");
	}
	if (_cmds->add_handler("ripng/0.1/table_request_seconds",
	    callback(this, &XrlRipngTargetBase::handle_ripng_0_1_table_request_seconds)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://ripng/ripng/0.1/table_request_seconds");
	}
	if (_cmds->add_handler("ripng/0.1/set_unsolicited_response_min_seconds",
	    callback(this, &XrlRipngTargetBase::handle_ripng_0_1_set_unsolicited_response_min_seconds)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://ripng/ripng/0.1/set_unsolicited_response_min_seconds");
	}
	if (_cmds->add_handler("ripng/0.1/unsolicited_response_min_seconds",
	    callback(this, &XrlRipngTargetBase::handle_ripng_0_1_unsolicited_response_min_seconds)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://ripng/ripng/0.1/unsolicited_response_min_seconds");
	}
	if (_cmds->add_handler("ripng/0.1/set_unsolicited_response_max_seconds",
	    callback(this, &XrlRipngTargetBase::handle_ripng_0_1_set_unsolicited_response_max_seconds)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://ripng/ripng/0.1/set_unsolicited_response_max_seconds");
	}
	if (_cmds->add_handler("ripng/0.1/unsolicited_response_max_seconds",
	    callback(this, &XrlRipngTargetBase::handle_ripng_0_1_unsolicited_response_max_seconds)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://ripng/ripng/0.1/unsolicited_response_max_seconds");
	}
	if (_cmds->add_handler("ripng/0.1/set_triggered_update_min_seconds",
	    callback(this, &XrlRipngTargetBase::handle_ripng_0_1_set_triggered_update_min_seconds)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://ripng/ripng/0.1/set_triggered_update_min_seconds");
	}
	if (_cmds->add_handler("ripng/0.1/triggered_update_min_seconds",
	    callback(this, &XrlRipngTargetBase::handle_ripng_0_1_triggered_update_min_seconds)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://ripng/ripng/0.1/triggered_update_min_seconds");
	}
	if (_cmds->add_handler("ripng/0.1/set_triggered_update_max_seconds",
	    callback(this, &XrlRipngTargetBase::handle_ripng_0_1_set_triggered_update_max_seconds)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://ripng/ripng/0.1/set_triggered_update_max_seconds");
	}
	if (_cmds->add_handler("ripng/0.1/triggered_update_max_seconds",
	    callback(this, &XrlRipngTargetBase::handle_ripng_0_1_triggered_update_max_seconds)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://ripng/ripng/0.1/triggered_update_max_seconds");
	}
	if (_cmds->add_handler("ripng/0.1/set_interpacket_delay_milliseconds",
	    callback(this, &XrlRipngTargetBase::handle_ripng_0_1_set_interpacket_delay_milliseconds)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://ripng/ripng/0.1/set_interpacket_delay_milliseconds");
	}
	if (_cmds->add_handler("ripng/0.1/interpacket_delay_milliseconds",
	    callback(this, &XrlRipngTargetBase::handle_ripng_0_1_interpacket_delay_milliseconds)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://ripng/ripng/0.1/interpacket_delay_milliseconds");
	}
	if (_cmds->add_handler("ripng/0.1/rip_address_status",
	    callback(this, &XrlRipngTargetBase::handle_ripng_0_1_rip_address_status)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://ripng/ripng/0.1/rip_address_status");
	}
	if (_cmds->add_handler("ripng/0.1/get_peers",
	    callback(this, &XrlRipngTargetBase::handle_ripng_0_1_get_peers)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://ripng/ripng/0.1/get_peers");
	}
	if (_cmds->add_handler("ripng/0.1/get_all_peers",
	    callback(this, &XrlRipngTargetBase::handle_ripng_0_1_get_all_peers)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://ripng/ripng/0.1/get_all_peers");
	}
	if (_cmds->add_handler("ripng/0.1/add_static_route",
	    callback(this, &XrlRipngTargetBase::handle_ripng_0_1_add_static_route)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://ripng/ripng/0.1/add_static_route");
	}
	if (_cmds->add_handler("ripng/0.1/delete_static_route",
	    callback(this, &XrlRipngTargetBase::handle_ripng_0_1_delete_static_route)) == false) {
	    XLOG_ERROR("Failed to xrl handler finder://ripng/ripng/0.1/delete_static_route");
	}
	_cmds->finalize();
    }

    void remove_handlers()
    {
	_cmds->remove_handler("common/0.1/get_target_name");
	_cmds->remove_handler("common/0.1/get_version");
	_cmds->remove_handler("common/0.1/get_status");
	_cmds->remove_handler("common/0.1/shutdown");
	_cmds->remove_handler("finder_event_observer/0.1/xrl_target_birth");
	_cmds->remove_handler("finder_event_observer/0.1/xrl_target_death");
	_cmds->remove_handler("ripng/0.1/add_rip_address");
	_cmds->remove_handler("ripng/0.1/remove_rip_address");
	_cmds->remove_handler("ripng/0.1/set_rip_address_enabled");
	_cmds->remove_handler("ripng/0.1/rip_address_enabled");
	_cmds->remove_handler("ripng/0.1/set_cost");
	_cmds->remove_handler("ripng/0.1/cost");
	_cmds->remove_handler("ripng/0.1/set_horizon");
	_cmds->remove_handler("ripng/0.1/horizon");
	_cmds->remove_handler("ripng/0.1/set_passive");
	_cmds->remove_handler("ripng/0.1/passive");
	_cmds->remove_handler("ripng/0.1/set_accept_non_rip_requests");
	_cmds->remove_handler("ripng/0.1/accept_non_rip_requests");
	_cmds->remove_handler("ripng/0.1/set_accept_default_route");
	_cmds->remove_handler("ripng/0.1/accept_default_route");
	_cmds->remove_handler("ripng/0.1/set_advertise_default_route");
	_cmds->remove_handler("ripng/0.1/advertise_default_route");
	_cmds->remove_handler("ripng/0.1/set_route_expiry_seconds");
	_cmds->remove_handler("ripng/0.1/route_expiry_seconds");
	_cmds->remove_handler("ripng/0.1/set_route_deletion_seconds");
	_cmds->remove_handler("ripng/0.1/route_deletion_seconds");
	_cmds->remove_handler("ripng/0.1/set_table_request_seconds");
	_cmds->remove_handler("ripng/0.1/table_request_seconds");
	_cmds->remove_handler("ripng/0.1/set_unsolicited_response_min_seconds");
	_cmds->remove_handler("ripng/0.1/unsolicited_response_min_seconds");
	_cmds->remove_handler("ripng/0.1/set_unsolicited_response_max_seconds");
	_cmds->remove_handler("ripng/0.1/unsolicited_response_max_seconds");
	_cmds->remove_handler("ripng/0.1/set_triggered_update_min_seconds");
	_cmds->remove_handler("ripng/0.1/triggered_update_min_seconds");
	_cmds->remove_handler("ripng/0.1/set_triggered_update_max_seconds");
	_cmds->remove_handler("ripng/0.1/triggered_update_max_seconds");
	_cmds->remove_handler("ripng/0.1/set_interpacket_delay_milliseconds");
	_cmds->remove_handler("ripng/0.1/interpacket_delay_milliseconds");
	_cmds->remove_handler("ripng/0.1/rip_address_status");
	_cmds->remove_handler("ripng/0.1/get_peers");
	_cmds->remove_handler("ripng/0.1/get_all_peers");
	_cmds->remove_handler("ripng/0.1/add_static_route");
	_cmds->remove_handler("ripng/0.1/delete_static_route");
    }
};

#endif /* __XRL_INTERFACES_RIPNG_BASE_HH__ */
