/*
 * Created by Costa Bushnaq
 *
 * 27-04-2021 @ 02:30:20
 *
 * see LICENSE
*/

#ifndef OG_SOCKET_HPP_
#define OG_SOCKET_HPP_

#include "og/internal.hpp"

namespace og {

struct Socket {
    s32 m_handle{ k_bad_socketfd };

    virtual ~Socket();
    Socket() = default;
    Socket(s32 domain, s32 type, s32 protocol);
    Socket(s32 socketfd);

    s32 close();
    s32 mk_handle(int dom, int type, int prot);
    void set_handle(s32 socketfd);
    s32 handle() const;

    int bind(SocketAddr const& addr);

}; // struct Socket

} // namespace og

#endif /* OG_SOCKET_HPP_ */
