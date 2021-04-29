/*
 * Created by Costa Bushnaq
 *
 * 28-04-2021 @ 23:43:24
*/

#include "og/net/Internal2.hpp"

#include <sys/ioctl.h>
#include <unistd.h> // close

using namespace og::net;

intl::Handle intl::open(int dom, int type, int prot)
{
	return ::socket(dom, type, prot);
}

int intl::close(intl::Handle handle)
{
	return ::close(handle);
}

int intl::bind(intl::Handle handle, SocketAddr const& addr)
{
	sockaddr const* addr_ptr = addr.socket_address();
	socklen_t addr_size = addr.socket_address_size();

	return ::bind(handle, addr_ptr, addr_size);
}

int intl::set_nonblock(intl::Handle handle, bool on)
{
	int res;

	do
		res = ioctl(handle, FIONBIO, &on);
	while (res == -1 && errno == EINTR);

	return res;
}

int intl::set_cloexec(intl::Handle handle, bool on)
{
	int res;

	do
		res = ioctl(handle, on ? FIOCLEX : FIONCLEX);
	while (res == -1 && errno == EINTR);

	return res;
}
