/*
 * libOG, 2020
 *
 * Name: TcpStream.cxx
 *
*/

#include "og/network/TcpStream.hpp"
#include "og/network/SocketImplementation.hpp"
#include "og/base/SystemException.hpp"

using namespace og;

#ifdef _WIN_32
constexpr int MSG_FLAG = 0;
#else
constexpr int MSG_FLAG = MSG_NOSIGNAL;
#endif

TcpStream::TcpStream() :
    Socket(PF_INET, SOCK_STREAM, false)
{

}

Socket::Status TcpStream::connect(const Ipv4& raddress, uint16_t rport)
{
    sockaddr_in addr = impl::SocketHelper::build_ipv4_sockaddr(raddress, rport);

    if (::connect(handle(), reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) == -1) {
        // If connect hasn't finished ; that's alright
        if (errno == EINPROGRESS) return Status::Partial;
		// Else it should have failed
        return Status::Error;
    }

	// Everything is alright
    return Status::Success;
}

void TcpStream::disconnect()
{
    close();
}

Socket::Status TcpStream::send(const void* data, std::size_t len)
{
    std::size_t sent;

    return send(data, len, sent);
}

Socket::Status TcpStream::send(const void* data, std::size_t len, std::size_t& sent)
{
    if (!len || !data)
        return Error;

    // We'll need to perform the send over a loop -- so that everything is sent correctly.
    ssize_t delivered = 0;

    for (sent = 0; sent < len; sent += delivered) {
        delivered = ::send(handle(), static_cast<const char*>(data) + sent,
        static_cast<size_t>(len - sent), MSG_FLAG);

        if (delivered < 0)
            return get_error_status();

    }

    return Success;
}

Socket::Status TcpStream::receive(void* data, std::size_t len)
{
    size_t received = 0;

    return receive(data, len, received);
}

Socket::Status TcpStream::receive(void* data, std::size_t len, std::size_t& received)
{
    if (!data)
        return Error;

    int bytes_received = recv(handle(), data, len, MSG_FLAG);
    received = 0;

    if (bytes_received > 0) {
        received = static_cast<std::size_t>(bytes_received);
        return Success;
    }

    return get_error_status();
}
