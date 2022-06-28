/*
 * Created by Costa Bushnaq
 *
 * 26-04-2021 @ 21:02:42
 *
 * see LICENSE
*/

#ifndef OG_ERROR_HPP_
#define OG_ERROR_HPP_

#include <cassert>
#include <cerrno>

namespace og {

enum Status {
    e_failure = -1,
    e_success = 0,
    e_again,
    e_closed,
    e_in_progress
};

} // namespace og

#endif /* OG_ERROR_HPP_ */
