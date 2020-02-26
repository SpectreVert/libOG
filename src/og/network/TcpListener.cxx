/*
 * libOG, 2019
 *
 * Name: TcpListener.cxx
 *
 * Description:
 * 
*/

#include <og/network/TcpListener.hpp>
#include <og/network/SocketImplementation.hpp>

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

	sockaddr_in addr = impl::SocketHelper::fill_ipv4_sockaddr(laddress, lport);

	if (bind(getHandle(), reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) == -1)
		return Error;

	if (::listen(getHandle(), 0) == -1) {
		return Error;
	}

	return Success;
}

void TcpListener::disconnect()
{
	close();
}

Socket::Status TcpListener::accept(TcpSocket& socket)
{
	if (getHandle() == impl::SocketHelper::bad_socket)
		return Error;

	sockaddr_in addr;
	impl::Addrlen addrlen = sizeof(addr);
	SocketHandle accepted = ::accept(getHandle(), reinterpret_cast<sockaddr*>(&addr), &addrlen);
	//SocketHandle accepted = ::accept(getHandle(), 0x0, 0x0);

	// TODO Return a useful error status
	if (accepted == impl::SocketHelper::bad_socket)
		return Error;

	socket.disconnect();
	socket.open(accepted);

	return Success;
}

} // namespace og
