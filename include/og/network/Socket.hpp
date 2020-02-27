/*
 * libOG, 2019
 *
 * Name: Socket.hpp
 *
*/

#pragma once

#include "og/base/NonCopyable.hpp"
#include "og/network/IBaseSocket.hpp"
#include "og/network/SocketHandle.hpp"
#include "og/network/Ipv4.hpp"

#include <stdint.h>

namespace og {

//! \brief User-oriented base class for all the socket types.
//!
class Socket : public IBaseSocket, private NonCopyable {
public:

	//! \brief Status codes which should be returned by
	//!        the socket functions.
	enum Status {
		Success = 0,    //!< Operation has succeeded
		Again = 1,      //!< Operation could not complete at the moment
		Disconnect = 2, //!< Socket was disconnected
		Error = 42      //!< An error occured while preforming the operation
	};

    //! \brief Special port values
	enum Port {
		Any = 0         //!< Let the system pick any available port
	};

	//! \brief Destructor
	//!
	virtual ~Socket();

	//! \brief Indicate if the socket is in blocking or
	//!        non-blocking mode
	//!
	//! \return True if the socket is blocking, false
	//!         if the socket is not blocking
	//!
	bool isBlocking() const;

	//! \brief Set the blocking state of the socket 
	//!
	//! In non-blocking mode I/O operations will 
	//! return immediately. Return code indicates 
	//! if data was available
	//!
	//! In blocking mode system calls do not return
	//! until they receive/send the data.
	//!
	//! \param t_block True to set the socket in 
	//!        blocking mode, false to set it in
	//!        non-blocking mode.
	//!
	void setBlocking(bool blocking);

	//! \brief Bind the socket to a port / address pair
	//!
	//! Manually binding the socket to a port and IP 
	//! address is optional before connecting or 
	//! sending data to a remote host as the 
	//! system would take care of it anyhow.
	//!
	//! However it is mandatory if you need to use a
	//! specific interface or a specific port.
	//!
	//! As the socket can be be bound to a single
	//! port at any given time; calling this 
	//! function will unbind any previously bound 
	//! port.
	//!
	//! You can tell the system to bind to a random
	//! port by specifying Socket::Port::Any as the
	//! port to use.
	//!
	//! You can tell the system to bind the socket
	//! to ALL local interfaces by providing Ipv4::Any
	//! as the address.
	//!
	//! \param port Port to bind the socket to
	//!
	//! \param address Address of the interface to bind to
	//!
	//! \return Status code
	//!
	//! \see unbind
	//!
	virtual Status bind(uint16_t port, const Ipv4& address = Ipv4::Any);
	
	//! \brief Unbind the socket from the port to which it is boud to
	//!
	//! If the socket is not bound this function has no effect.
	//!
	//! \see bind
	//!
	virtual void unbind();

	//! \brief Return the internal handle of the socket
	//!
	//! \return The internal handle of the socket
	//!
	SocketHandle getHandle() const;

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
	Socket(int domain, int type, int protocol);

	//! \brief Create the internal handle of the socket
	//!
	void open();
	
	//! \brief Create the internal handle of the socket
	//!        from a socket handle
	//!
	//! \param handle Wrapper for OS-specific socket
	//!
	void open(SocketHandle handle);

	//! \brief Close properly the socket
	//!
	void close();

	//! \brief Get a suitable error code to return
	//!        to the user in case of operational failure.
	Status getErrorStatus();
	
private:
	SocketHandle m_socket; //!< Internal socket handle
	bool m_blocking;       //!< Blocking mode of the socket
	int m_domain;          //!< Domain used by the socket
	int m_type;            //!< Communication semantics used by the socket
	int m_protocol;        //!< Protocol used by the socket

}; // class Socket

} // namespace og
