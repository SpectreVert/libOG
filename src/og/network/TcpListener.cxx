/*
 * libOG, 2019
 *
 * Name: TcpListener.cxx
 *
 * Description:
 * 
*/

#include "og/network/TcpListener.hpp"
#include "og/network/SocketImplementation.hpp"

namespace og {

class TcpSocket;

TcpListener::TcpListener() :
	Socket(PF_INET, SOCK_STREAM, 0)
{
	
}

Socket::Status TcpListener::listen(uint16_t lport, const Ipv4& laddress)
{
	// Reset connection
	disconnect();
	open();

	// Comparison operator not implemented yet
	/* if ((laddress == Ipv4::Broadcast || laddress == Ipv4::Any))
		return Error; */

	sockaddr_in addr = impl::SocketHelper::build_ipv4_sockaddr(laddress, lport);

	if (::bind(handle(), reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) == -1)
		return Error;

	if (::listen(handle(), 0) == -1) {
		return Error;
	}

	return Success;
}

void TcpListener::disconnect()
{
	close();
}

Socket::Status TcpListener::accept(TcpStream& stream)
{
	if (handle() == impl::SocketHelper::bad_socket)
		return Error;

	sockaddr_in addr;
	impl::Addrlen addrlen = sizeof(addr);
	SocketHandle accepted = ::accept(handle(), reinterpret_cast<sockaddr*>(&addr), &addrlen);

	if (accepted == impl::SocketHelper::bad_socket)
		return Error;

	stream.disconnect();
	stream.open(accepted);

	return Success;
}

} // namespace og
