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

//! \brief Event implementation for epoll
//!
struct Event : IEvent {

    epoll_event event;

	Event(epoll_event t_event) : event(t_event) {}
	virtual ~Event() = default;

	core::Tag id() const { return event.data.u32; }

	bool is_readable() const
	{
	    return (event.events & EPOLLIN) || (event.events & EPOLLPRI) != 0;
	}

	bool is_writable() const
	{
		return event.events & EPOLLOUT;
	}

	bool is_read_closed() const
	{
		return (event.events & EPOLLHUP) != 0 ||
		((event.events & EPOLLOUT) != 0 && (event.events & EPOLLERR) != 0);
	}

	bool is_write_closed() const
	{
		return (event.events & EPOLLHUP) != 0 ||
		((event.events & EPOLLOUT) != 0 && (event.events & EPOLLERR) != 0);
	}

	bool is_error() const
	{
		return (event.events & EPOLLERR) != 0;
	}

}; // struct Event

//! \brief Events implementation for epoll
//!
typedef std::vector<Event> Events;

} // namespace net

} // namespace og
