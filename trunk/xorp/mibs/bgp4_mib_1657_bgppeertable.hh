/*
 * Note: this file originally auto-generated by mib2c using
 *        : mib2c.iterate.conf,v 5.5 2002/12/16 22:50:18 hardaker Exp $
 */
#ifndef BGP4_MIB_1657_BGPPEERTABLE_H
#define BGP4_MIB_1657_BGPPEERTABLE_H

/* function declarations */
void init_bgp4_mib_1657_bgppeertable(void);
void initialize_table_bgpPeerTable(void);
Netsnmp_Node_Handler bgpPeerTable_handler;

Netsnmp_First_Data_Point  bgpPeerTable_get_first_data_point;
Netsnmp_Next_Data_Point   bgpPeerTable_get_next_data_point;

/* column number definitions for table bgpPeerTable */
       #define COLUMN_BGPPEERIDENTIFIER		1
       #define COLUMN_BGPPEERSTATE		2
       #define COLUMN_BGPPEERADMINSTATUS		3
       #define COLUMN_BGPPEERNEGOTIATEDVERSION		4
       #define COLUMN_BGPPEERLOCALADDR		5
       #define COLUMN_BGPPEERLOCALPORT		6
       #define COLUMN_BGPPEERREMOTEADDR		7
       #define COLUMN_BGPPEERREMOTEPORT		8
       #define COLUMN_BGPPEERREMOTEAS		9
       #define COLUMN_BGPPEERINUPDATES		10
       #define COLUMN_BGPPEEROUTUPDATES		11
       #define COLUMN_BGPPEERINTOTALMESSAGES		12
       #define COLUMN_BGPPEEROUTTOTALMESSAGES		13
       #define COLUMN_BGPPEERLASTERROR		14
       #define COLUMN_BGPPEERFSMESTABLISHEDTRANSITIONS		15
       #define COLUMN_BGPPEERFSMESTABLISHEDTIME		16
       #define COLUMN_BGPPEERCONNECTRETRYINTERVAL		17
       #define COLUMN_BGPPEERHOLDTIME		18
       #define COLUMN_BGPPEERKEEPALIVE		19
       #define COLUMN_BGPPEERHOLDTIMECONFIGURED		20
       #define COLUMN_BGPPEERKEEPALIVECONFIGURED		21
       #define COLUMN_BGPPEERMINASORIGINATIONINTERVAL		22
       #define COLUMN_BGPPEERMINROUTEADVERTISEMENTINTERVAL		23
       #define COLUMN_BGPPEERINUPDATEELAPSEDTIME		24
#endif /* BGP4_MIB_1657_BGPPEERTABLE_H */
