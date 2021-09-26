/*
 * Created by Costa Bushnaq
 *
 * 26-04-2021 @ 20:38:49
 *
 * see LICENSE
*/

#include <utility>

#ifndef _RAWBUFFER_HPP
#define _RAWBUFFER_HPP

namespace og {

//! a `read/write` raw buffer paired with a size mark
typedef std::pair<void*, std::size_t> RawBuffer;

//! a `read only` raw buffer paired with a size mark
typedef std::pair<void const*, std::size_t> RawBufferConst;

} // namespace og

#endif /* _RAWBUFFER_HPP */
