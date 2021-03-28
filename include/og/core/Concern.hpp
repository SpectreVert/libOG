/*
 * libOG, 2020
 *
 * Name: Concern.hpp
 *
*/

#pragma once

#include <bitset>

namespace og {

namespace core {

using Concern = std::bitset<4>;

enum {
	e_write = 1,
	e_read  = 2
};

} // namespace core

} // namespace og
