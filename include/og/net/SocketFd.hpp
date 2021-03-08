/*
 * Created by Costa Bushnaq
 *
 * 08-03-2021 @ 22:19:42
 *
 * see LICENSE
*/

#ifndef _SOCKETFD_HPP_
#define _SOCKETFD_HPP_

#include "og/core/RawFd.hpp"

namespace og {

namespace net {

//! \brief A wrapper around the unix file descriptor type.
//!
typedef core::RawFd SocketFd;

} // namespace net

} // namespace og

#endif /* _SOCKETFD_HPP_ */
