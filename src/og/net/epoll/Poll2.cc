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
	}

	return 0;
}

int Poll::monitor(Source& src, core::Tag tag, core::Concern concern)
{
	(void) src;
	(void) tag;
	(void) concern;

	return 0;
}

// this basically is a monitor but cannot take
// shared as concern
int Poll::re_monitor(Source& src, core::Tag tag, core::Concern concern)
{
	(void) src;
	(void) tag;
	(void) concern;

	return 0;
}

int Poll::forget(Source& src)
{
	(void) src;

	return 0;
}
