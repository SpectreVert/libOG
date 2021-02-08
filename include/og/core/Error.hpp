/*
 * Created by Costa Bushnaq
 *
 * 07-02-2021 @ 17:41:43
 *
 * see LICENSE
*/

#ifndef _ERROR_HPP_
#define _ERROR_HPP_

// is this X-platform? ¯\_(--')_/¯
#include <cerrno>
#include <cassert>

namespace og {

namespace net {

//! Network specific error codes
//!
enum {
	Success,
	Closed,
	WouldBlock,
	InProgress
};

} // namespace net

} // namspace og

#endif /* _ERROR_HPP_ */
