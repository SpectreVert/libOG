/*
 * Created by Costa Bushnaq
 *
 * 28-04-2021 @ 23:43:24
*/

#include "og/net/Error.hpp"
#include "og/net/Internal.hpp"

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

int intl::connect(intl::Handle handle, SocketAddr const& addr)
{
	sockaddr const* addr_ptr = addr.socket_address();
	socklen_t addr_size = addr.socket_address_size();
	int res;

	do
		res = ::connect(handle, addr_ptr, addr_size);
	while (res == -1 && errno == EINTR);

	return res;
}

int intl::listen(intl::Handle handle, int backlog)
{
	return ::listen(handle, backlog);
}

intl::Handle intl::accept(intl::Handle handle, SocketAddr& new_address)
{
	intl::Handle new_handle;
	sockaddr addr;
	socklen_t addr_size;

	do
		new_handle = ::accept(handle, &addr, &addr_size);
	while (new_handle == k_bad_socket && errno == EINTR);

	if (new_handle == k_bad_socket)
		return new_handle;

	int res = intl::set_cloexec(new_handle, true);
	if (!res)
		res = intl::set_nonblock(new_handle, true);

	if (res)
	{
		// could not set the socket parameters -- get out
		close(new_handle);
		return k_bad_socket;
	}

	// Ipv6 not yet implemented
	assert(addr_size == sizeof(sockaddr_in));
	new_address = SocketAddr(*reinterpret_cast<sockaddr_in*>(&addr));
	
	return new_handle;
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

ssize_t intl::send(intl::Handle handle, core::RawBufferConst data)
{
	ssize_t res;

	do
		res = ::send(handle, data.first, data.second, intl::k_message_flag);
	while (res == -1 && errno == EINTR);

	return res;
}

ssize_t intl::send_to(intl::Handle handle, SocketAddr const& address,
                      core::RawBufferConst data)
{
	ssize_t res;
	sockaddr const* addr_ptr = address.socket_address();
	socklen_t addr_size = address.socket_address_size();

	do
		res = ::sendto(
			handle, data.first, data.second,
		    intl::k_message_flag, addr_ptr, addr_size
		);
	while (res == -1 && errno == EINTR);

	return res;
}

ssize_t intl::recv(intl::Handle handle, core::RawBuffer& data)
{
	ssize_t res;

	do
		res = ::recv(handle, data.first, data.second, intl::k_message_flag);
	while (res == -1 && errno == EINTR);

	return res;
}

ssize_t intl::recv_from(intl::Handle handle, SocketAddr& address,
                        core::RawBuffer& data)
{
	ssize_t res;
	sockaddr* addr_ptr = address.socket_address();
	socklen_t addr_size{0};

	do
		res = ::recvfrom(
			handle, data.first, data.second,
			intl::k_message_flag, addr_ptr, &addr_size
		);
	while (res == -1 && errno == EINTR);

	assert(addr_size == address.socket_address_size());

	return res;
}
