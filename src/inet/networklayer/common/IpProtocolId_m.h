//
// Generated file, do not edit! Created by nedtool 5.6 from inet/networklayer/common/IpProtocolId.msg.
//

#ifndef __INET_IPPROTOCOLID_M_H
#define __INET_IPPROTOCOLID_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0506
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif

// dll export symbol
#ifndef INET_API
#  if defined(INET_EXPORT)
#    define INET_API  OPP_DLLEXPORT
#  elif defined(INET_IMPORT)
#    define INET_API  OPP_DLLIMPORT
#  else
#    define INET_API
#  endif
#endif


namespace inet {

} // namespace inet

#include "inet/common/INETDefs_m.h" // import inet.common.INETDefs


namespace inet {

/**
 * Enum generated from <tt>inet/networklayer/common/IpProtocolId.msg:29</tt> by nedtool.
 * <pre>
 * //
 * // Protocol field: taken from RFC 1700.
 * // Replacing old RFC1700 with newer (28/06/01) Protocol Numbers
 * //
 * enum IpProtocolId
 * {
 *     //  IP_PROT_HOPOPT    = 0;
 *     IP_PROT_ICMP = 1;
 *     IP_PROT_IGMP = 2;
 *     IP_PROT_IP = 4; // used for IP tunneling. FIXME: RFC1700 specifies =3 (old IPSuite) ???
 *     IP_PROT_TCP = 6;
 *     IP_PROT_EGP = 8;
 *     IP_PROT_IGP = 9;
 *     IP_PROT_UDP = 17;
 *     IP_PROT_XTP = 36;
 *     IP_PROT_IPv6 = 41;
 *     IP_PROT_RSVP = 46;
 *     IP_PROT_IPv6_ICMP = 58;
 *     IP_PROT_NONE = 59;
 *     IP_PROT_EIGRP = 88;
 *     IP_PROT_OSPF = 89;
 *     IP_PROT_OSPFv3 = 90;
 *     IP_PROT_PIM = 103;
 *     IP_PROT_VRRP = 112;
 *     IP_PROT_SCTP = 132;
 *     IP_PROT_DSR = 48;
 *     IP_PROT_MANET = 138;
 * 
 *     IP_PROT_IPv6EXT_HOP = 0;       // Hop-by-hop option header.
 *     IP_PROT_IPv6EXT_DEST = 60;     // Destination options header.
 *     IP_PROT_IPv6EXT_ROUTING = 43;  // Routing header.
 *     IP_PROT_IPv6EXT_FRAGMENT = 44; // Fragmentation/reassembly header.
 *     IP_PROT_IPv6EXT_AUTH = 51;     // Authentication header.
 *     IP_PROT_IPv6EXT_ESP = 50;      // Encapsulating security payload.
 *     IP_PROT_IPv6EXT_MOB = 135;      // Mobility Header for MIPv6 support.
 * 
 *     IP_PROT_FLOODING = 250;    // INET specific: Probabilistic Network Protocol
 *     IP_PROT_PROBABILISTIC = 251;    // INET specific: Probabilistic Network Protocol
 *     IP_PROT_WISE = 252;    // INET specific: Probabilistic Network Protocol
 *     IP_PROT_NEXT_HOP_FORWARDING = 253; // INET specific: Next Hop Forwarding
 *     IP_PROT_ECHO = 254; // INET specific: Echo Protocol
 * }
 * </pre>
 */
enum IpProtocolId {
    IP_PROT_ICMP = 1,
    IP_PROT_IGMP = 2,
    IP_PROT_IP = 4,
    IP_PROT_TCP = 6,
    IP_PROT_EGP = 8,
    IP_PROT_IGP = 9,
    IP_PROT_UDP = 17,
    IP_PROT_XTP = 36,
    IP_PROT_IPv6 = 41,
    IP_PROT_RSVP = 46,
    IP_PROT_IPv6_ICMP = 58,
    IP_PROT_NONE = 59,
    IP_PROT_EIGRP = 88,
    IP_PROT_OSPF = 89,
    IP_PROT_OSPFv3 = 90,
    IP_PROT_PIM = 103,
    IP_PROT_VRRP = 112,
    IP_PROT_SCTP = 132,
    IP_PROT_DSR = 48,
    IP_PROT_MANET = 138,
    IP_PROT_IPv6EXT_HOP = 0,
    IP_PROT_IPv6EXT_DEST = 60,
    IP_PROT_IPv6EXT_ROUTING = 43,
    IP_PROT_IPv6EXT_FRAGMENT = 44,
    IP_PROT_IPv6EXT_AUTH = 51,
    IP_PROT_IPv6EXT_ESP = 50,
    IP_PROT_IPv6EXT_MOB = 135,
    IP_PROT_FLOODING = 250,
    IP_PROT_PROBABILISTIC = 251,
    IP_PROT_WISE = 252,
    IP_PROT_NEXT_HOP_FORWARDING = 253,
    IP_PROT_ECHO = 254
};

} // namespace inet

#endif // ifndef __INET_IPPROTOCOLID_M_H

