/*
 * Created by Costa Bushnaq
 *
 * 28-04-2021 @ 23:40:27
 *
 * see LICENSE
*/

#ifndef OG_INTERNAL_HPP_
#define OG_INTERNAL_HPP_

#include "og/RawBuffer.hpp"
#include "og/SocketAddr.hpp"

namespace og {

int constexpr k_bad_socket = -1;

namespace intl {

int constexpr k_message_flag = MSG_NOSIGNAL;

using Handle = int;

Handle open(int dom, int type, int prot);
int close(Handle);
int bind(Handle, SocketAddr const&);
int connect(Handle, SocketAddr const&);
int listen(Handle, int);
Handle accept(Handle, SocketAddr&);

ssize_t recv(Handle, RawBuffer&);
ssize_t recv_from(Handle, SocketAddr&, RawBuffer&);
ssize_t send(Handle, RawBuffer const&);
ssize_t send_to(Handle, SocketAddr const&, RawBuffer const&);

int set_cloexec(Handle, bool);
int set_nonblock(Handle, bool);

} // namespace intl

} // namespace og

#endif /* OG_INTERNAL_HPP_ */
