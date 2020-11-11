/*
 * libOG, 2020
 *
 * Name: TcpStream.cxx
 *
*/

#include "og/net/TcpStream.hpp"
#include "og/io/Internal.hpp"

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
	return io::intl::connect(m_handle, address);
}

int TcpStream::send(const void* data, std::size_t len)
{
	
}

int TcpStream::send(const void* data, std::size_t len, ssize_t& sent)
{
}

int TcpStream::receive(void* data, std::size_t len)
{
}

int TcpStream::receive(void* data, std::size_t len, ssize_t& received)
{
}
