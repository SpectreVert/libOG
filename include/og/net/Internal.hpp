/*
 * Created by Costa Bushnaq
 *
 * 28-04-2021 @ 23:40:27
 *
 * see LICENSE
*/

#ifndef _INTERNAL_HPP
#define _INTERNAL_HPP

#include "og/core/RawBuffer.hpp"
#include "og/core/RawFd.hpp"
#include "og/net/SocketAddr.hpp"

namespace og {

namespace net {

core::RawFd constexpr k_bad_socket = -1;

namespace intl {

int constexpr k_message_flag = MSG_NOSIGNAL;

using Handle = core::RawFd;

Handle open(int dom, int type, int prot);
int close(Handle);
int bind(Handle, SocketAddr const&);
int connect(Handle, SocketAddr const&);
int listen(Handle, int);
Handle accept(Handle, SocketAddr&);

ssize_t send(Handle, core::RawBufferConst);
ssize_t send_to(Handle, SocketAddr const&, core::RawBufferConst);
ssize_t recv(Handle, core::RawBuffer&);
ssize_t recv_from(Handle, SocketAddr&, core::RawBuffer&);

int set_nonblock(Handle, bool);
int set_cloexec(Handle, bool);

} // namespace intl

} // namespace net

} // namespace og

#endif /* _INTERNAL_HPP */
