/*
 * libOG, 2020
 *
 * Name: Concern.hpp
 *
*/

#pragma once

namespace og {

namespace io {

enum Concern
{
	Writable = 0x1,
	Readable = 0x2,
	Both = Writable | Readable
};

} // namespace io

} // namespace og
