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

    //! \brief Issue a non-blocking connect to the specified address
    //!
    //! \param raddress Address of the remote peer to connect to
    //!
    //! \param rport Port of the remote peer to connect to
    //!
    //! \return The status code
    //!
    //! \see disconnect
    //! 
    virtual Socket::Status connect(const Ipv4& raddress, uint16_t rport);

    //! \brief Disconnect the TcpStream from the remote peer
    //!
    //! \see connect
    //!
    virtual void disconnect();

	virtual Socket::Status send(const void* data, std::size_t len);

	virtual Socket::Status send(const void* data, std::size_t len, std::size_t& sent);

	virtual Socket::Status receive(void* data, std::size_t len);

	virtual Socket::Status receive(void* data, std::size_t len, size_t& received);

protected:

	friend class TcpListener;

}; // class TcpStream

} // namespace og
