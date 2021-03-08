/*
 * libOG, 2020
 *
 * Name: Poll.cc
 *
*/

#include "og/core/Error.hpp"
#include "og/net/Internal.hpp"
#include "og/net/Poll.hpp"

#if defined(OG_SYSTEM_LINUX)

#include <fcntl.h>  // O_CLOEXEC
#include <unistd.h> // close

#include <iostream>

using namespace og::net;

Poll::Poll()
{
	m_epoll_fd = epoll_create1(O_CLOEXEC);

	if (m_epoll_fd != -1)
		return;
	
	/* epoll_create1() can fail because it's not implemented,
	 * or because it cannot handle O_CLOEXEC flag.
	*/
	if (errno == ENOSYS || errno == EINVAL)
	{
		/* Argument should be ignored (> 2.6.8) but if it isn't
		 * this looks like a good compromise.
		*/
		m_epoll_fd = epoll_create(12000);
	}

	assert(m_epoll_fd != -1);
	assert(intl::set_cloexec(m_epoll_fd, true) != -1);
}

Poll::~Poll()
{
	::close(m_epoll_fd);
}

int Poll::poll(Events& events, int timeout)
{
	int nb_events;
	epoll_event events_buffer[S_POLL_EVENT_CAPACITY];
	std::size_t reprompt = S_POLL_MAX_REPROMPT;
	std::size_t hint = 1024;

	assert(timeout >= -1);

	events.clear();

	if (events.capacity() < hint)
		events.reserve(hint);

	for (;;)
	{
		/* TODO: when we can use timers in there, make use of
		 * signals & epoll_pwait()
		*/
		nb_events = epoll_wait( \
		m_epoll_fd, events_buffer, \
		S_POLL_EVENT_CAPACITY, timeout);

		if (nb_events == 0)
		{
			assert(timeout != -1);

			return og::net::Success;
		}

		if (nb_events == -1)
		{
			/* If errno is something else than EINTR,
			 * something is most likely wrong.
			*/
			if (errno != EINTR)
				return -errno;

			/* Otherwise, we've just been interrupted by a signal.
			 * Either redo a loop -- not taking into account time
			 * lost in the first poll, for now -- or return.
			*/
			if (timeout != 0)
				continue;

			break;
		}

		for (int i = 0; i != nb_events; ++i)
			events.push_back(events_buffer[i]);

		if (nb_events == S_POLL_EVENT_CAPACITY)
			if (--reprompt != 0)
				continue;
		
		break;
	}

	return og::net::Success;
}

/* TODO: return -errno rather than the return value from epoll_ctl
 * which is either 0 or -1
*/
int Poll::monitor(SocketFd socket, core::Tag id, core::Concern concern)
{
	uint32_t bits = EPOLLET;
	epoll_event event{};

	if (concern[og::core::Writable - 1])
		bits |= EPOLLOUT;
	if (concern[og::core::Readable - 1])
		bits = bits | EPOLLRDHUP | EPOLLIN;

	event.events = bits;
	event.data.u32 = id;

	return epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, socket, &event);
}

int Poll::forget(SocketFd socket)
{
	/* Un-named distrib checks all field */
	epoll_event event{}; 

	return epoll_ctl(m_epoll_fd, EPOLL_CTL_DEL, socket, &event);
}

#endif // OG_SYSTEM_LINUX
