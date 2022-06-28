/*
 * Created by Costa Bushnaq
 *
 * 26-04-2021 @ 20:38:49
 *
 * see LICENSE
*/

#include <utility>

#ifndef OG_RAWBUFFER_HPP_
#define OG_RAWBUFFER_HPP_

namespace og {

struct RawBuffer {
    static constexpr std::size_t k_capacity{ 2048 };
    
    char data[k_capacity];
    std::size_t size;
};

} // namespace og

#endif /* OG_RAWBUFFER_HPP_ */
