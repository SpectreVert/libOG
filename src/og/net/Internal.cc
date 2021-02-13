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
	sockaddr const* addr_ptr = address.socket_address();
	socklen_t addr_size = address.socket_address_size();

	return ::bind(socket, addr_ptr, addr_size);
}

int intl::connect(SocketHandle socket, SocketAddr const& address)
{
	sockaddr const* addr_ptr = address.socket_address();
	socklen_t addr_size = address.socket_address_size();
	int res;

	do {
		errno = 0;
		res = ::connect(socket, addr_ptr, addr_size);
	} while (res == -1 && errno == EINTR);

	return res;
}

int intl::listen(SocketHandle socket, int backlog)
{ 
	/* Backlog serves as a hint so it shouldn't really be a concern,
	 * but we're checking for negative values anyway. I'd like to
	 * keep the int type for compatibility reasons.
	*/
	if (backlog < 0)
		backlog = 128;

	return ::listen(socket, backlog);
}

// TODO: check naming of SocketHandle argument
//       
int intl::accept(SocketHandle socket, SocketHandle &new_socket,
                 SocketAddr& new_address, int flags)
{
	SocketHandle sock;

#if defined(SOCK_NONBLOCK) && defined(SOCK_CLOEXEC)
	do
		sock = accept4(socket, 0x0, 0x0, flags);
	while (sock == intl::bad_socket && errno == EINTR);
	if (sock != intl::bad_socket)
	{
		new_socket = sock;
		return 0;
	}
	else if (errno != EINVAL && errno != ENOSYS)
		return -1;
#endif
	int res;

	do
		sock = ::accept(socket, 0x0, 0x0);
	while (sock == intl::bad_socket && errno == EINTR);
	if (sock == intl::bad_socket)
		return intl::bad_socket;

	res = intl::set_cloexec(sock, true);
	if (res == 0)
		res = intl::set_nonblock(sock, true);
	
	if (res)
	{
		close(sock);
		return -1;
	}

	new_socket = sock;
	return 0;
}

ssize_t intl::send(SocketHandle socket, core::RawBufferConst data)
{
	ssize_t res;

	do
		res = ::send(socket, data.first, data.second, intl::MSG_FLAG);
	while (res == -1 && errno == EINTR);

	return res;
}

ssize_t intl::send_to(SocketHandle socket, core::RawBufferConst data,
                      SocketAddr const& address)
{
	ssize_t res;
	sockaddr const* addr_ptr = address.socket_address();
	socklen_t addr_size = address.socket_address_size();

	do
		res = ::sendto( \
		socket, data.first, data.second, \
		intl::MSG_FLAG, addr_ptr, addr_size);
	while (res == -1 && errno == EINTR);

	return res;
}

ssize_t intl::recv(SocketHandle socket, core::RawBuffer const& data)
{
	ssize_t res;

	do
		res = ::recv(socket, data.first, data.second, intl::MSG_FLAG);
	while (res == -1 && errno == EINTR);

	return res;	
}

ssize_t intl::recv_from(SocketHandle socket, core::RawBuffer const& data,
                        SocketAddr& address)
{
	ssize_t res;
	sockaddr* addr_ptr = address.socket_address();
	socklen_t addr_size = address.socket_address_size();

	do
		res = ::recvfrom( \
		socket, data.first, data.second, \
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
