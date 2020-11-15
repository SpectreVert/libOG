/*
 * libOG, 2020
 *
 * Name: Errors.hpp
 *
*/

#pragma once

#include "og/core/Errors.hpp"

namespace og {

namespace net {

enum {
	Error = og::core::Error,
	Success,
	WouldBlock,
	Closed
};

} // namespace net

} // namespace og
