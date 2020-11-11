/*
 * libOG, 2020
 *
 * Name: TcpStream.cxx
 *
*/

#include "og/net/Internal.hpp"
#include "og/net/TcpStream.hpp"

using namespace og::net;

TcpStream::TcpStream() :
	Socket(AF_INET, SOCK_STREAM)
{
}

TcpStream::~TcpStream()
{
	close();
}

int TcpStream::connect(const SocketAddr& address)
{
	return intl::connect(m_handle, address);
}

int TcpStream::send(core::RawBuffer const data)
{
	return 0;
}

int TcpStream::send(core::RawBuffer const data, ssize_t& sent)
{
	return 0;
}

int TcpStream::recv(core::RawBuffer& data)
{
	return 0;
}

int TcpStream::recv(core::RawBuffer& data, ssize_t& received)
{
	return 0;
}
