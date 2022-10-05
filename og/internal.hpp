/*
 * Created by Costa Bushnaq
 *
 * 27-09-2022 @ 18:37:53
 *
 * see LICENSE
*/

/* You should not have to #include this file by hand */

#ifndef OG_INTERNAL_HPP_
#define OG_INTERNAL_HPP_

#include "og/defs.hpp"
#include "og/Buffer.hpp"
#include "og/SocketAddr.hpp"

#include <arpa/inet.h>
#include <cassert>
#include <cerrno>
#include <sys/ioctl.h>
#include <unistd.h>

namespace og {

namespace intl {

constexpr s32 k_message_flag{ MSG_NOSIGNAL };

s32 open(s32 domain, s32 type, s32 protocol);
s32 close(s32 socketfd);
s32 bind(s32 socketfd, SocketAddr const& addr);
s32 connect(s32 socketfd, SocketAddr const& addr);
s32 listen(s32 socketfd, s32 backlog);
s32 accept(s32 socketfd, SocketAddr& new_address);

s64 recv(s32 socketfd, Buffer &buf);
s64 recv_from(s32 socketfd, SocketAddr& address, Buffer &buf);
s64 send(s32 socketfd, Buffer const &buf);
s64 send_to(s32 socketfd, SocketAddr const& address, Buffer const& buf);

s32 set_cloexec(s32 socketfd, s32 on);
s32 set_nonblock(s32 socketfd, s32 on);

} // namespace intl

} // namespace og

#endif /* OG_INTERNAL_HPP_ */
