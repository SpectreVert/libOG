/*
 * libOG, 2020
 *
 * Name: IBaseSocket.hpp
 *
*/

#pragma once

#include <og/network/SocketHandle.hpp>

#include <sys/types.h>  // BSD compatibility
#include <sys/socket.h>

namespace og {

//! \brief Base template interface for all socket types
//!
class IBaseSocket {
public:

	//! \brief Destructor
	//!
	virtual ~IBaseSocket()
	{

	}

	//! \brief Indicate if the socket is in blocking or
	//!        non-blocking mode
	//!
	//! \return True if the socket is blocking, false
	//!         if the socket is not blocking
	//!
	virtual bool isBlocking() const = 0;

	//! \brief Set the blocking state of the socket 
	//!
	//! In non-blocking mode I/O operations will 
	//! return immediately. Return code indicates 
	//! if data was available
	//!
	//! In blocking mode system calls do not return
	//! until they receive/send the data.
	//!
	//! \param block True to set the socket in 
	//!        blocking mode, false to set it in
	//!        non-blocking mode.
	//!
	virtual void setBlocking(bool block) = 0;

	//! \brief Return the internal handle of the socket
	//!
	//! \return The internal handle of the socket
	//!
	virtual SocketHandle getHandle() const = 0;

protected:

	//! \brief Constructor
	//!
	//! Construct the socket and store its
	//! internal parameters.
	//!
	//! Consult socket(2) for details.
	//!
	//! \param domain Specify a communication domain;
	//!        the protocol family which will be used
	//!        for communication
	//!
	//! \param type Specify the communication semantics
	//!
	//! \param protocol Specify a particular protocol
	//!        to be used with the socket. Normally, a
	//!        single protocol exists to support a particular
	//!        socket type in which caes protocol can be
	//!        set to 0.
	//!
	IBaseSocket(int domain, int type, int protocol)
	{

	}

	//! \brief Create the internal handle of the socket
	//!
	virtual void open() = 0;

	//! \brief Create the internal handle of the socket
	//!        from a socket handle
	//!
	//! \param handle Wrapper for OS-specific socket
	//!
	virtual void open(SocketHandle handle) = 0;

	//! \brief Close properly the socket
	//!
	virtual void close() = 0;

}; // class IBaseSocket

} // namespace og
