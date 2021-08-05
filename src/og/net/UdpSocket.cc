/*
 * Created by Costa Bushnaq
 *
 * 04-08-2021 @ 15:40:31
*/

#include "og/net/Error.hpp"
#include "og/net/UdpSocket.hpp"

using namespace og::net;

UdpSocket::UdpSocket()
	: Socket(AF_INET, SOCK_DGRAM, 0)
{}

UdpSocket::UdpSocket(Handle handle)
	: Socket(handle)
{}

int UdpSocket::send_to(SocketAddr const& addr, core::RawBufferConst data)
{
	ssize_t res = intl::send_to(m_handle, addr, data);

	if (res != -1)
		return e_success;

	if (errno == EAGAIN || errno == EWOULDBLOCK)
		return e_would_block;

	return e_failure;
}

int UdpSocket::send_to(SocketAddr const& addr, core::RawBufferConst data,
                       std::size_t& sent)
{
	ssize_t res = intl::send_to(m_handle, addr, data);

	if (res != -1)
	{
		sent = static_cast<std::size_t>(res);
		return e_success;
	}

	sent = 0;
	if (errno == EAGAIN || errno == EWOULDBLOCK)
		return e_would_block;

	return e_failure;
}

int UdpSocket::recv_from(SocketAddr& addr, core::RawBuffer& data)
{
	ssize_t res = intl::recv_from(m_handle, addr, data);

	if (res != -1)
		return e_success;

	if (errno == EAGAIN || errno == EWOULDBLOCK)
		return e_would_block;

	return e_failure;
}

int UdpSocket::recv_from(SocketAddr& addr, core::RawBuffer& data,
                         std::size_t& received)
{
	ssize_t res = intl::recv_from(m_handle, addr, data);

	if (res != -1)
	{
		received = static_cast<std::size_t>(res);
		return e_success;
	}

	received = 0;
	if (errno == EAGAIN || errno == EWOULDBLOCK)
		return e_would_block;

	return e_failure;
}
