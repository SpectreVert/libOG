/*
 * libOG, 2020
 *
 * Name: Poll.cc
 *
*/

#include "og/net/Poll.hpp"

#if defined(OG_SYSTEM_LINUX)

#include <fcntl.h> // O_CLOEXEC
#include <errno.h> // errno

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
		 * 256 seems like a reasonable value.
		*/
		m_epoll_fd = epoll_create(256);
	}
}


#endif // OG_SYSTEM_LINUX
