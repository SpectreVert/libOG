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
	
	WRITABLE = 1,
	READABLE = 2,
	BOTH = 4

}; // enum Concern

} // namespace og
