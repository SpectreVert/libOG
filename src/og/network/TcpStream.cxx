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

TcpStream::TcpStream() :
    Socket(PF_INET, SOCK_STREAM, false)
{

}

Socket::Status TcpStream::connect(const Ipv4& raddress, uint16_t rport)
{
    sockaddr_in addr = impl::SocketHelper::build_ipv4_sockaddr(raddress, rport);

    if (::connect(handle(),
                  reinterpret_cast<sockaddr*>(&addr),
                  sizeof(addr)) == -1)
    {
        // If socket hasn't finished connecting ; that's alright
        if (errno == EINPROGRESS)
            return Socket::Status::Connecting;

        return Socket::Status::Error;
    }

    return Socket::Status::Success;
}

void TcpStream::disconnect()
{
    close();
}

Socket::Status TcpStream::send(const void* data, std::size_t len)
{
    ssize_t sent;

    return send(data, len, sent);
}

Socket::Status TcpStream::send(const void* data, std::size_t len, ssize_t& sent)
{
    ssize_t delivered = 0;

    // We'll try to send all of the data
    for (sent = 0; sent < len; sent += delivered)
    {
        delivered = ::send(handle(),
                           static_cast<const char*>(data) + sent,
                           static_cast<size_t>(len - sent),
                           impl::SocketHelper::MSG_FLAG);

        if (delivered < 0)
        {
            // We already sent data but the socket can't send more for now
            if ((errno == EAGAIN || errno == EWOULDBLOCK) && sent)
            {
                return Socket::Status::PartialSend;
            }
            else if (!sent) // No data was sent ; the socket is not ready
            {
                return Socket::Status::RetrySend;
            }

            return Socket::Status::Error;
        }
    }

    return Socket::Status::Success;
}

Socket::Status TcpStream::receive(void* data, std::size_t len)
{
    ssize_t received = 0;

    return receive(data, len, received);
}

Socket::Status TcpStream::receive(void* data, std::size_t len, ssize_t& received)
{
    received = ::recv(handle(),
                                    data,
                                    len,
                                    impl::SocketHelper::MSG_FLAG);

    if (received < 0)
    {
        received = 0;

        if (errno == EAGAIN || errno == EWOULDBLOCK)
            return Socket::Status::RetryReceive;

        return Socket::Status::Error;
    }

    return Socket::Status::Success;
}
