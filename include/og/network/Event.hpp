/*
 * libOG, 2020
 *
 * Name: Events.hpp
 *
*/

#pragma once

#include <sys/epoll.h>

#include <vector>

namespace og {

//! \brief A readiness event fetched by poll
//!
class Event {
public:

	//! \brief Default constructor
	//!
	Event(epoll_event event);

	uint32_t token() const;

	bool is_readable() const;

	bool is_writable() const;

	bool is_read_closed() const;

	bool is_write_closed() const;

	bool is_error() const;

private:
	
	epoll_event m_event;

}; // class Event

//! \brief A group of readiness events
//!
class Events {
public:

	//! \brief Initializer constructor
	//!
	//! \param events A std::vector of Event objects
	//!
	Events(std::size_t capacity);
	
	~Events();

	//! \brief Return an std::vector containing the Event objects
	//!        provided by poll
	//!
	std::vector<Event> events() const;

	//! \brief Return the pointer to the events structs
	//!
	epoll_event* epoll_events() const;

	//! \brief Return the capacity of the group
	//!
	std::size_t capacity() const;
	
	//! \brief Set the number of events received
	//!
	void set_length(std::size_t length);

	//! \brief Clear the internal container of event
	//!
	void clear();

private:
	
	epoll_event *m_epoll_events;
	std::size_t m_length = 0;
	std::size_t m_capacity = 0;

}; // class Events

} // namespace og
