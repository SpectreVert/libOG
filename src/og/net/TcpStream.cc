/*
 * Created by Costa Bushnaq
 *
 * 02-05-2021 @ 01:04:20
*/

#include "og/net/Error.hpp"
#include "og/net/TcpStream.hpp"

using namespace og::net;

TcpStream::TcpStream()
	: Socket(AF_INET, SOCK_STREAM, 0)
{
}

TcpStream::TcpStream(Handle handle)
	: Socket(handle)
{
}

std::optional<TcpStream> TcpStream::make_stream(SocketAddr const& address)
{
	Handle handle;

	handle = intl::open(AF_INET, SOCK_STREAM, 0);
	if (handle == k_bad_socket)
		return std::nullopt;

	if (intl::connect(handle, address) == 0 || errno == EINPROGRESS)
		return handle;

	intl::close(handle);

	return std::nullopt;
}

int TcpStream::connect(SocketAddr const& address)
{
	if (intl::connect(m_handle, address) == 0)
		return e_success;

	if (errno == EINPROGRESS)
		return e_in_progress;

	return e_failure;
}

int TcpStream::send(core::RawBufferConst data)
{
	ssize_t res = intl::send(m_handle, data);

	if (res != -1)
		return e_success;

	if (errno == EAGAIN || errno == EWOULDBLOCK)
		return e_would_block;

	return e_failure;
}

int TcpStream::send(core::RawBufferConst data, std::size_t& sent)
{
	ssize_t res = intl::send(m_handle, data);

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

int TcpStream::recv(core::RawBuffer& data)
{
	ssize_t res = intl::recv(m_handle, data);

	if (res > 0)
		return e_success;
	
	if (res == 0)
		return e_closed;
	else if (errno == EAGAIN || errno == EWOULDBLOCK)
		return e_would_block;

	return e_failure;
}

int TcpStream::recv(core::RawBuffer& data, std::size_t& recv)
{
	ssize_t res = intl::recv(m_handle, data);

	if (res > 0)
	{
		recv = static_cast<std::size_t>(res);
		return e_success;
	}

	recv = 0;
	if (res == 0)
		return e_closed;
	else if (errno == EAGAIN || errno == EWOULDBLOCK)
		return e_would_block;

	return e_failure;
}
