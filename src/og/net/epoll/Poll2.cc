/*
 * Created by Costa Bushnaq
 *
 * 27-04-2021 @ 15:47:57
*/

#include "og/net/epoll/Poll2.hpp"
#include "og/net/Error.hpp"
#include "og/net/Internal2.hpp"

#include <fcntl.h> // O_CLOEXEC

using namespace og::net;

Poll::~Poll()
{
	intl::close(m_epoll_fd);
}

Poll::Poll()
{
	m_epoll_fd = epoll_create(O_CLOEXEC);

	if (m_epoll_fd != -1)
		return;

	/* epoll_create1 can fail because it's not implemented,
	 * or because it cannot handle O_CLOEXEC flag */
	if (errno == ENOSYS || errno == EINVAL)
	{
		/* see kernel 2.6.8 patch notes */
		m_epoll_fd = epoll_create(1024);
	}

	assert(m_epoll_fd != -1);
	//assert(intl::set_cloexec(m_epoll_fd, true) != -1);
}

int Poll::poll(Events& events, int timeout)
{
	int nb;
	
	assert(timeout >= -1);

	for (;;)
	{
		nb = epoll_wait(
			m_epoll_fd, events.data(),
			events.size(), timeout
		);
		
		if (nb == 0)
		{
			assert(timeout != -1);
			return e_success;
		}

		if (nb == -1)
		{
			if (errno != EINTR)
				return e_failure;

			if (timeout)
				continue;
		}

		break;
	}

	return e_success;
}

int Poll::monitor(Source& src, core::Tag tag, core::Concern concern)
{
	uint32_t bits{0};
	epoll_event event{0, {0}};

	/* if the fd we're using needs to be shared, we're
	 * staying in level-triggered mode so as to dodge
	 * starvation with multiple incoming events.
	*/
	if (concern & core::e_shared)
		bits = EPOLLEXCLUSIVE;
	else
		bits = EPOLLET;

	if (concern & core::e_write)
		bits |= EPOLLOUT;
	if (concern & core::e_read)
		bits |= EPOLLIN;

	event.events = bits;
	event.data.u64 = tag;

	return epoll_ctl(m_epoll_fd, EPOLL_CTL_ADD, src.handle(), &event);
}

//! this function re_registers an fd/concern pair; but
//! cannot take e_shared as concern.
int Poll::re_monitor(Source& src, core::Tag tag, core::Concern concern)
{
	uint32_t bits{EPOLLET};
	epoll_event event{0, {0}};

	if (concern & core::e_shared)
	{
		errno = EINVAL;
		return e_failure;
	}

	if (concern & core::e_write)
		bits |= EPOLLOUT;
	if (concern & core::e_read)
		bits |= EPOLLIN;

	event.events = bits;
	event.data.u64 = tag;

	return epoll_ctl(m_epoll_fd, EPOLL_CTL_MOD, src.handle(), &event);
}

int Poll::forget(Source& src)
{
	epoll_event event{0, {0}};

	return epoll_ctl(m_epoll_fd, EPOLL_CTL_DEL, src.handle(), &event);
}
