/*
 * libOG, 2020
 *
 * Name: Poll.cc
 *
*/

#include "og/net/Internal.hpp"
#include "og/net/Poll.hpp"

#if defined(OG_SYSTEM_LINUX)

#include <fcntl.h>  // O_CLOEXEC
#include <errno.h>  // errno
#include <unistd.h> // close
#include <assert.h>
#include <cstdlib>  // abort



#include <iostream>

using namespace og::net;

Poll::Poll()
{
	m_epoll_fd = epoll_create1(O_CLOEXEC);

	/* epoll_create1() can fail because it's not implemented,
	 * or because it cannot handle O_CLOEXEC flag.
	*/
	if (m_epoll_fd == -1 && (errno == ENOSYS || errno == EINVAL))
	{
		/* Argument should be ignored (> 2.6.8) but if it isn't
		 * this looks like a good compromise.
		*/
		m_epoll_fd = epoll_create(12000);
		
		if (m_epoll_fd != -1)
			intl::set_cloexec(m_epoll_fd, true);
	}
}

Poll::~Poll()
{
	::close(m_epoll_fd);
}

bool Poll::is_valid() const
{
	return m_epoll_fd == -1 ? false : true;
}

int Poll::poll(Events& events, int timeout)
{
	int nb_events;
	epoll_event events_buffer[IPoll::s_poll_event_capacity];
	std::size_t reprompt = s_poll_max_reprompt;
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
		IPoll::s_poll_event_capacity, timeout);

		if (nb_events == 0)
		{
			assert(timeout != -1);

			return 0;
		}

		if (nb_events == -1)
		{
			/* If errno is something else than EINTR,
			 * something is very wrong -- abandon ship!
			*/
			if (errno != EINTR)
				abort();

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

		if (nb_events == s_poll_event_capacity)
			if (--reprompt != 0)
				continue;
		
		break;
	}

	return 0;
}

int Poll::add(SocketHandle source, core::Tag id, core::Concern concern)
{
	uint32_t bits = EPOLLET;
	epoll_event event{};

	if (concern[og::core::Writable - 1])
		bits |= EPOLLOUT;
	if (concern[og::core::Readable - 1])
		bits = bits | EPOLLRDHUP | EPOLLIN;

	event.events = bits;
	event.data.u32 = id;

	return epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, source, &event);
}

int Poll::remove(SocketHandle source)
{
	/* Un-named distrib checks all field */
	epoll_event event{}; 

	return epoll_ctl(m_epoll_fd, EPOLL_CTL_DEL, source, &event);
}

#endif // OG_SYSTEM_LINUX
