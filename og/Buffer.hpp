/*
 * Created by Costa Bushnaq
 *
 * 26-04-2021 @ 20:38:49
 *
 * see LICENSE
*/

#include <utility>

#ifndef OG_BUFFER_HPP_
#define OG_BUFFER_HPP_

#include "../og.config.hpp"
#include "og/defs.hpp"

namespace og {

template<u32 N>
struct BasicBuffer {
    static constexpr auto k_capacity = N;

    char data[N];
    u32 size;
};

using Buffer = BasicBuffer<OG_BUFFER_SIZE>;

} // namespace og

#endif /* OG_BUFFER_HPP_ */
