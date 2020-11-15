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

typedef std::bitset<4> Concern;

enum {
	Writable = 1,
	Readable = 2
};

} // namespace core

} // namespace og
