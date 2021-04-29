/*
 * Created by Costa Bushnaq
 *
 * 28-04-2021 @ 23:40:27
 *
 * see LICENSE
*/

#ifndef _INTERNAL_HPP
#define _INTERNAL_HPP

#include "og/core/RawFd.hpp"
#include "og/net/SocketAddr2.hpp"

namespace og {

namespace net {

core::RawFd constexpr k_bad_socket = -1;

namespace intl {

using Handle = core::RawFd;

Handle open(int dom, int type, int prot);
int close(Handle);
int bind(Handle, SocketAddr const& addr);

int set_nonblock(Handle, bool);
int set_cloexec(Handle, bool);

} // namespace intl

} // namespace net

} // namespace og

#endif /* _INTERNAL_HPP */
