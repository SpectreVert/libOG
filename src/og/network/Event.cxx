/*
 * libOG, 2020
 *
 * Name: Event.hpp
 *
*/

#include "og/network/Event.hpp"

#include <iostream>
#include <cstring>

using namespace og;

///////////////////////////////////////
/// Event
///////////////////////////////////////

Event::Event(epoll_event t_event) :
	m_event(t_event)
{

}

uint32_t Event::token() const
{
	return m_event.data.u32;
}

bool Event::is_readable() const
{
	return (m_event.events & EPOLLIN) ||
			(m_event.events & EPOLLPRI != 0);
}

bool Event::is_writable() const
{
	return m_event.events & EPOLLOUT;
}

bool Event::is_read_closed() const
{
	return m_event.events & EPOLLHUP != 0 ||
			(m_event.events & EPOLLIN != 0 &&
			 m_event.events & EPOLLRDHUP != 0);
}

bool Event::is_write_closed() const
{
	return m_event.events & EPOLLHUP != 0 ||
			(m_event.events & EPOLLOUT != 0 &&
			 m_event.events & EPOLLERR != 0);
}

bool Event::is_error() const
{
	return (m_event.events & EPOLLERR != 0);
}

///////////////////////////////////////
/// Events
///////////////////////////////////////

// TODO: free up the events storage during destruction

Events::Events(std::size_t t_capacity)
{
	m_capacity = t_capacity;
	m_epoll_events = new epoll_event[t_capacity];
}

Events::~Events()
{
	delete m_epoll_events;
}

std::vector<Event> Events::events() const
{
	std::vector<Event> events;

	for (std::size_t i = 0; i != m_length; ++i)
		events.push_back( Event(m_epoll_events[i]) );

	return events;
}

epoll_event* Events::epoll_events() const
{
	return m_epoll_events;
}

std::size_t Events::capacity() const
{
	return m_capacity;
}

void Events::set_length(std::size_t t_length)
{
	m_length = t_length;
}

void Events::clear()
{
	m_length = 0;
}
