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

using namespace og::net;

Poll::Poll()
{
	m_epoll_fd = epoll_create1(O_CLOEXEC);

	/* epoll_create1() can fail because it's not implemented,
	 * or because it cannot handle to O_CLOEXEC flag.
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

int Poll::add(SocketHandle source, core::Tag id, core::Concern concern)
{
	return 0;
}

#endif // OG_SYSTEM_LINUX
