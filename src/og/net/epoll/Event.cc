/*
 * Created by Costa Bushnaq
 *
 * 28-04-2021 @ 16:06:00
*/

#include "og/net/epoll/Event.hpp"

#include <iostream>

using namespace og::net;

Event::Event(epoll_event event)
{
	data = event.data;
	events = event.events;
}

og::core::Tag Event::id() const
{
	return data.u64;
}

bool Event::is_error() const
{
	return (events & EPOLLERR) != 0;
}

bool Event::is_readable() const
{
	return (events & EPOLLIN) || (events & EPOLLPRI) != 0;
}

bool Event::is_read_closed() const
{
	return (events & EPOLLHUP) != 0 ||
	((events & EPOLLIN) != 0 && (events & EPOLLERR) != 0);
}

bool Event::is_writable() const
{
	return events & EPOLLOUT;
}

bool Event::is_write_closed() const
{
	return (events & EPOLLHUP) != 0 ||
	((events & EPOLLOUT) != 0 && (events & EPOLLERR) != 0);
}
