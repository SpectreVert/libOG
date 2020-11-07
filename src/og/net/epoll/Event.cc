/*
 * libOG, 2020
 *
 * Name: Event.cc
 *
*/

#include "og/net/Poll.hpp"

#if defined(OG_SYSTEM_LINUX)

using namespace og;
using namespace og::net;

Event::Event(epoll_event t_event) :

    event(t_event)
{
}

io::Tag Event::id() const
{
    return event.data.u32;
}

bool Event::is_readable() const
{
    return (event.events & EPOLLIN) || (event.events & EPOLLPRI) != 0;
}

bool Event::is_writable() const
{
	return event.events & EPOLLOUT;
}

bool Event::is_read_closed() const
{
	return (event.events & EPOLLHUP) != 0 ||
	((event.events & EPOLLOUT) != 0 && (event.events & EPOLLERR) != 0);
}

bool Event::is_write_closed() const
{
	return (event.events & EPOLLHUP) != 0 ||
	((event.events & EPOLLOUT) != 0 && (event.events & EPOLLERR) != 0);
}

bool Event::is_error() const
{
	return (event.events & EPOLLERR) != 0;
}

#endif // OG_SYSTEM_LINUX