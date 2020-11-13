/*
 * libOG, 2020
 *
 * Name: RawBuffer
 *
*/

#pragma once

#include <utility>

namespace og {

namespace core {

//! \brief A raw buffer paired with a size mark.
//!
typedef std::pair<void*, std::size_t> RawBuffer;

//! \brief A const raw buffer paired with a size mark.
//!
typedef std::pair<void const*, std::size_t> RawBufferConst;

} // namespace core

} // namespace og
