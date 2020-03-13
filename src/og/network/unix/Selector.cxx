/*
 * libOG, 2020
 *
 * Name: Selector.cxx
 *
*/

#include "og/network/unix/Selector.hpp"
#include "og/base/SystemException.hpp"

using namespace og;

Selector::Selector()
{
	m_poll_fd = epoll_create1(EPOLL_CLOEXEC);

	if (m_poll_fd == -1)
		throw SystemException("epoll_create1");
}

int Selector::add(SocketHandle socket, Token token, Concern concern)
{
	uint32_t events = EPOLLET;
	epoll_event event { 0 };

	if (concern & READABLE)
		events = events | EPOLLRDHUP | EPOLLIN;
	if (concern & WRITABLE)
		events |= EPOLLOUT;

	event.events = events;
	event.data.u32 = token;

	return epoll_ctl(m_poll_fd, EPOLL_CTL_ADD, socket, &event);
}

#include <iostream>

int Selector::select(Events& events, int timeout)
{
	events.clear();

	int n = epoll_wait(m_poll_fd, events.epoll_events(), events.capacity(), timeout);

	// Take note of the number of file descriptors ready for I/O 
	if (n > -1)
		events.set_length(n);
	else
		throw SystemException("epoll_wait");

	// Need to push each events on the queue

	return n;
}

inline bool Selector::is_valid() const
{
	return m_poll_fd;
}
