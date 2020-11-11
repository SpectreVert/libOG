/*
 * libOG, 2020
 *
 * Name: Concern.hpp
 *
*/

#pragma once

namespace og {

namespace core {

enum Concern
{
	Writable = 0x1,
	Readable = 0x2,
	Both = Writable | Readable
};

} // namespace core

} // namespace og
