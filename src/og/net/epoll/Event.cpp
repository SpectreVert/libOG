/*
 * Created by Costa Bushnaq
 *
 * 27-03-2021 @ 22:03:12
*/

#include "og/net/epoll/Event.hpp"

using namespace og::net;

Events ev::with_capacity(std::size_t cap)
{
	Events ev;

	ev.resize(cap);
	return ev;
}

og::core::Tag id(Event event)
{
	return event.data.u32;
}

bool ev::is_readable(Event event)
{
    return (event.events & EPOLLIN) || (event.events & EPOLLPRI) != 0;
}

bool ev::is_writable(Event event)
{
	return event.events & EPOLLOUT;
}

bool ev::is_read_closed(Event event)
{
	return (event.events & EPOLLHUP) != 0 ||
	((event.events & EPOLLOUT) != 0 && (event.events & EPOLLERR) != 0);
}

bool ev::is_write_closed(Event event)
{
	return (event.events & EPOLLHUP) != 0 ||
	((event.events & EPOLLOUT) != 0 && (event.events & EPOLLERR) != 0);
}

bool ev::is_error(Event event)
{
	return (event.events & EPOLLERR) != 0;
}
