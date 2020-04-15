/*
 * libOG, 2020
 *
 * Name: Socket.hpp
 *
*/

#pragma once

#include "og/network/IBaseSocket.hpp"
#include "og/network/SocketHandle.hpp"
#include "og/network/Ipv4.hpp"
#include "og/base/NonCopyable.hpp"

#include <stdint.h>

namespace og {

//! \brief Base class for non-blocking socket
//!
class Socket : public IBaseSocket {
public:

	//! \brief Warper for port values
	//!
	typedef uint16_t Port;

    //! \brief Port value to let system chose port
	//!
	static constexpr Port any_port = 0;

	//! \brief Status codes returned by Socket functions
	//!
	enum class Status
	{
		Success = 0,	//!< Operation has succeeeded
		Error,			//!< Operation has failed

		Connecting,		//!< The connect operation is not done yet
		
		RetrySend,		//!< Socket unavailable for writing data
		PartialSend,	//!< Data was partially sent (TCP only)

		RetryReceive,	//!< No data to be read from the socket

		RetryAccept		//!< No connections are currently pending
	};

	//! \brief Destructor
	//!
	virtual ~Socket();

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
	//! \param address Address of the interface to bind to
	//!
	//! \param port Port to bind the socket to
	//!
	//! \return Status code
	//!
	//! \see unbind
	//!
	virtual Status bind(const Ipv4& address, Port port);
	
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
	SocketHandle handle() const;

protected:

	//! \brief Default constructor
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
	Socket(int domain, int type, int protocol = 0);

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

private:
	SocketHandle m_socket; //!< Internal socket handle
	int m_domain;          //!< Domain used by the socket
	int m_type;            //!< Communication semantics used by the socket
	int m_protocol;        //!< Protocol used by the socket

}; // class Socket

} // namespace og
