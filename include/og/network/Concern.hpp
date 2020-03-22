/*
 * libOG, 2020
 *
 * Name: Concern.hpp
 *
*/

#pragma once

namespace og {

//! \brief Description of what should be monitored
//!
enum Concern {
	
	Writable = 1,
	Readable = 2,
	Both = Writable | Readable

}; // enum Concern

} // namespace og
