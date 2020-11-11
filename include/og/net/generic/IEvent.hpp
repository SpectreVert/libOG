/*
 * PROJECT_NAME, 2020
 *
 * Name:
 *
*/

#pragma once

#include "og/core/Tag.hpp"

namespace og {

namespace net {

struct IEvent {
	virtual ~IEvent() = default;

	virtual core::Tag id() const = 0;

	virtual bool is_readable() const = 0;
	virtual bool is_writable() const = 0;
	virtual bool is_read_closed() const = 0;
	virtual bool is_write_closed() const = 0;
	virtual bool is_error() const = 0;

}; // interface IEvent

} // namespace net

} // namespace og