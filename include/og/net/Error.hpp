/*
 * Created by Costa Bushnaq
 *
 * 26-04-2021 @ 21:02:42
 *
 * see LICENSE
*/

#ifndef _ERROR_HPP
#define _ERROR_HPP

#include <cerrno>
#include <cassert>

namespace og {

namespace net {

enum Status {
	e_failure = -1,
	e_success = 0,
	e_closed,
	e_would_block,
	e_in_progress
};

} // namespace net

} // namespace og

#endif /* _ERROR_HPP */
