/*
 * libOG, 2020
 *
 * Name: Event.hpp
 *
*/

#pragma once

#include "og/net/generic/IEvent.hpp"

#include <vector>

#include <sys/epoll.h>

namespace og {

namespace net {

//! \brief Event implemetation for epoll
//!
struct Event : IEvent {

    Event(epoll_event t_event);
    virtual ~Event() = default;

	virtual core::Tag id() const;

	virtual bool is_readable() const;
	virtual bool is_writable() const;
	virtual bool is_read_closed() const;
	virtual bool is_write_closed() const;
	virtual bool is_error() const;

    epoll_event event;

}; // struct Event

//! \brief Events implementation for epoll
//!
typedef std::vector<Event> Events;

} // namespace net

} // namespace og
