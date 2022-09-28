/*
 * Created by Costa Bushnaq
 *
 * 29-04-2021 @ 00:19:47
 *
 * see LICENSE
*/

#ifndef OG_SOCKETADDR_HPP_
#define OG_SOCKETADDR_HPP_

#include "og/defs.hpp"
#include "og/Ipv4.hpp"

namespace og {

typedef u16 Port;

//! Ipv4 socket address
//!
struct SocketAddrV4 {
    SocketAddrV4();
    SocketAddrV4(Ipv4 addr, Port port);
    SocketAddrV4(sockaddr_in); //! <sock> is network order

    Ipv4 ip_host_order() const;
    Ipv4 ip_net_order() const;
    SocketAddrV4& set_ip(Ipv4); //! <ip> is host order

    Port port_host_order() const;
    Port port_net_order() const;
    SocketAddrV4& set_port(Port); //! <port> is host order

    sockaddr_in socket_address;

}; // struct SocketAddrV4
/*
struct SocketAddrV6 {
    virtual ~SocketAddrV6() = default;
    SocketAddrV6();
    SocketAddrV6(Ipv6 addr, Port port);
    
    Ipv6 ip() const;
    Ipv6 net_ip() const;
    SocketAddrV6& set_ip(Ipv6 ip);

    Port port() const;
    Port net_port() const;
    SocketAddrV6& set_port(Port port);

}; // struct SocketAddrV6
*/

//! IPv-agnostic socket address
//!
struct SocketAddr {
    SocketAddr() = delete;
    SocketAddr(Ipv4, Port);
    SocketAddr(SocketAddrV4);
    SocketAddr(sockaddr_in);

    enum {
        e_V4,
        /* e_V6 */
    } version;

    union AddrSet {
        AddrSet(Ipv4, Port);
        AddrSet(SocketAddrV4);
        /*
        AddrSet(Ipv6, Port);
        AddrSet(SocketAddrV6);
        */

        SocketAddrV4 v4;
        // SocketAddrV6 v6;
    } addr;

    sockaddr* socket_address();
    sockaddr const* socket_address() const;
    socklen_t socket_address_size() const;

}; // struct SocketAddr

} // namespace og

#endif /* OG_SOCKETADDR_HPP_ */
