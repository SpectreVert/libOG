/*
 * libOG, 2020
 *
 * Name: TcpStream.hpp
 *
*/

#pragma once

#include "og/network/Socket.hpp"
#include "og/network/Ipv4.hpp"

namespace og {

//! \brief A non-blocking TCP stream
//!
class TcpStream : public Socket {
public:

    //! Default constructor
    //!
    TcpStream();

    //! \brief Connect the Tcp socket to another Tcp socket
    //!
    //! \param address Address of the socket to connect to
    //!
    //! \param port Port of the socket to connect to
    //!
    //! \return The Status code
    //!
    //! \see disconnect
    //! 
    virtual Socket::Status connect(const Ipv4& address, Port port);

    //! \brief Disconnect the Tcp socket
    //!
    //! \see connect
    //!
    virtual void disconnect();

	virtual Socket::Status send(const void* data, size_t len);

	virtual Socket::Status send(const void* data, std::size_t len, ssize_t& sent);

	virtual Socket::Status receive(void* data, std::size_t len);

	virtual Socket::Status receive(void* data, std::size_t len, ssize_t& received);

protected:

	friend class TcpListener;

}; // class TcpStream

} // namespace og
