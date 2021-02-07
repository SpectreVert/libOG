/*
 * libOG, 2020
 *
 * Name: Internal.cc
 *
*/

#include "og/core/Error.hpp"
#include "og/net/Internal.hpp"

#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>  // for BSD friends
#include <unistd.h>     // close(2)

using namespace og::net;

SocketHandle intl::open(int domain, int type, int protocol)
{
	SocketHandle sock;

#if defined(SOCK_NONBLOCK) && defined(SOCK_CLOEXEC)
	sock = socket(domain, type | SOCK_NONBLOCK | SOCK_CLOEXEC, protocol);
	if (sock != intl::bad_socket)
		return sock;
	else if (errno != EINVAL)
		return intl::bad_socket;
#endif
	
	int res;

	/* There's no support for the shortcut flags.
	 * -> the socket fd might leak to a forked program
	 *    before set_cloexec is set.
	*/
	sock = socket(domain, type, protocol);
	if (sock == intl::bad_socket)
		return intl::bad_socket;

	res = intl::set_cloexec(sock, true);
	if (res == 0)
		res = intl::set_nonblock(sock, true);
	
	if (res)
	{
		close(sock);
		return intl::bad_socket;
	}

	return sock;
}

/* https://sourceware.org/bugzilla/show_bug.cgi?id=14627
 * https://stackoverflow.com/questions/33114152/what-to-do-if-a-posix-close-call-fails
 *TODO: check all cases for close() - based on man page HP-UX does weird stuff,
 * so can other OS too
*/
int intl::close(SocketHandle socket)
{
	int res;

	res = ::close(socket);
	if (res)
		return -1;

	return 0;	
}

int intl::bind(SocketHandle socket, SocketAddr const& address)
{
	sockaddr const* addr_ptr = get_sockaddr_ptr(address);
	std::size_t addr_size = get_sockaddr_size(address.version);

	if (::bind(socket, addr_ptr, addr_size))
		return -1;

	return 0;	
}

int intl::connect(SocketHandle socket, SocketAddr const& address)
{
	sockaddr const* addr_ptr = get_sockaddr_ptr(address);
	std::size_t addr_size = get_sockaddr_size(address.version);
	int res;

	do {
		errno = 0;
		res = ::connect(socket, addr_ptr, addr_size);
	} while (res == -1 && errno == EINTR);

	return res;
}

ssize_t intl::send(SocketHandle handle, core::RawBufferConst data)
{
	ssize_t res;

	do
		res = ::send(handle, data.first, data.second, intl::MSG_FLAG);
	while (res == -1 && errno == EINTR);

	return res;
}

ssize_t intl::send_to(SocketHandle handle, core::RawBufferConst data,
                      SocketAddr const& address)
{
	ssize_t res;
	sockaddr const* addr_ptr = get_sockaddr_ptr(address);
	socklen_t addr_size = get_sockaddr_size(address.version);

	do
		res = ::sendto( \
		handle, data.first, data.second, \
		intl::MSG_FLAG, addr_ptr, addr_size);
	while (res == -1 && errno == EINTR);

	return res;
}

ssize_t intl::recv(SocketHandle handle, core::RawBuffer const& data)
{
	ssize_t res;

	do
		res = ::recv(handle, data.first, data.second, intl::MSG_FLAG);
	while (res == -1 && errno == EINTR);

	return res;	
}

ssize_t intl::recv_from(SocketHandle handle, core::RawBuffer const& data,
                        SocketAddr& address)
{
	ssize_t res;
	sockaddr* addr_ptr = get_sockaddr_ptr(address);
	socklen_t addr_size = get_sockaddr_size(address.version);

	do
		res = ::recvfrom( \
		handle, data.first, data.second, \
		intl::MSG_FLAG, addr_ptr, &addr_size);
	while (res == -1 && errno == EINTR);

	return res;
}

/* TODO: using ioctl() for now because it's only a single
 * syscall. Linux source code says it's best to use fcntl()
 * TODO: check where ioctl() is not implemented/complete
 * BTW: who can tell me where to find these values - FIOBIO
 * and FIOCLEX - in the linux man pages? Only found them in
 * BSD ioctl(2)...
*/
int intl::set_nonblock(SocketHandle socket, bool set)
{
	int res;

	do
		res = ioctl(socket, FIONBIO, &set);
	while (res == -1 && errno == EINTR);

	return res;
}

// TODO: ditto
int intl::set_cloexec(SocketHandle socket, bool set)
{
	int res;

	do
		res = ioctl(socket, set ? FIOCLEX : FIONCLEX);
	while (res == -1 && errno == EINTR);

	return res;
}

/* NOTE: Ipv6 and SockAddrV6 aren't implemented yet,
 * so these two functions can only return Ipv4 related values.
*/
inline sockaddr* intl::get_sockaddr_ptr(SocketAddr& address)
{
	if (address.version == SocketAddr::V4)
		return reinterpret_cast<sockaddr*>(&address.addr.v4.socket_addr);

	return 0x0;
}

inline sockaddr const* intl::get_sockaddr_ptr(SocketAddr const& address)
{
	if (address.version == SocketAddr::V4)
		return reinterpret_cast<sockaddr const*>(&address.addr.v4.socket_addr);

	return 0x0;
}

inline std::size_t intl::get_sockaddr_size(int version)
{
	if (version == SocketAddr::V4)
		return sizeof(sockaddr_in);

	return 0;
}
