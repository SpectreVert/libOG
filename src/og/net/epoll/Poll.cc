/*
 * Created by Costa Bushnaq
 *
 * 27-03-2021 @ 22:06:38
*/

#include "og/net/epoll/Poll.hpp"

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

	assert(timeout >= -1);

	for (;;)
	{
		/* TODO: when we can use timers in there, make use of
		 * signals & epoll_pwait()
		*/
		nb_events = epoll_wait( \
			m_epoll_fd, events.data(), \
			events.capacity(), timeout \
		);

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
		}
		
		/* Note: user has to make sure he calls
		 * ev::with_capacity() for this to work.
		*/
		events.resize(nb_events);

		break;
	}

	return og::net::Success;
}

int Poll::monitor(Socket& source, core::Tag id, core::Concern concern)
{
	uint32_t bits = EPOLLET;
	epoll_event event{};

	if (concern[og::core::e_write - 1])
		bits |= EPOLLOUT;
	if (concern[og::core::e_read - 1])
		bits = bits | EPOLLRDHUP | EPOLLIN;

	event.events = bits;
	event.data.u32 = id;

	return epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, source.handle(), &event);
}

int Poll::forget(Socket& source)
{
	/* Un-named distrib checks all field */
	epoll_event event{}; 

	return epoll_ctl(m_epoll_fd, EPOLL_CTL_DEL, source.handle(), &event);
}
