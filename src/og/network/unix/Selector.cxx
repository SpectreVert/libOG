/*
 * libOG, 2020
 *
 * Name: Selector.cxx
 *
*/

#include "og/network/unix/Selector.hpp"
#include "og/base/SystemException.hpp"

#include <unistd.h> // close

using namespace og;

Selector::Selector()
{
	m_poll_fd = epoll_create1(EPOLL_CLOEXEC);

	if (m_poll_fd == -1)
		throw SystemException("epoll_create1");
}

Selector::~Selector()
{
	if (m_poll_fd != -1)
		close(m_poll_fd);
}

int Selector::add(SocketHandle handle, Token token, Concern concern)
{
	uint32_t events = EPOLLET;
	epoll_event event = { 0 };

	if (concern & Readable)
		events = events | EPOLLRDHUP | EPOLLIN;
	if (concern & Writable)
		events |= EPOLLOUT;

	event.events = events;
	event.data.u32 = token;

	return epoll_ctl(m_poll_fd, EPOLL_CTL_ADD, handle, &event);
}

int Selector::remove(SocketHandle handle)
{
	epoll_event event = { 0 }; // for portability reasons
	
	return epoll_ctl(m_poll_fd, EPOLL_CTL_DEL, handle, &event);
}

int Selector::select(Events& events, int64_t timeout)
{
	events.clear();

	int n = epoll_wait(m_poll_fd, events.epoll_events(), events.capacity(), timeout);

	// Take note of the number of file descriptors ready for I/O 
	if (n > -1)
		events.set_length(n);
	else
		throw SystemException("epoll_wait");

	return n;
}
