/*
 * libOG, 2019
 *
 * Name: Socket.hpp
 *
 * Description:
 * Base class for all socket types.
*/

#pragma once

#include <og/base/NonCopyable.hpp>
#include <og/network/IBaseSocket.hpp>
#include <og/network/SocketHandle.hpp>

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
		Error = 42,     //!< An error occured while preforming the operation
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
	//! \param t_domain Specify a communication domain;
	//!        the protocol family which will be used
	//!        for communication
	//!
	//! \param t_type Specify the communication semantics
	//!
	//! \param t_protocol Specify a particular protocol
	//!        to be used with the socket. Normally, a
	//!        single protocol exists to support a particular
	//!        socket type in which caes protocol can be
	//!        set to 0.
	//!
	Socket(int t_domain, int t_type, int t_protocol);

	//! \brief Create the internal handle of the socket
	//!
	void open();
	
	//! \brief Create the internal handle of the socket
	//!        from a socket handle
	//!
	//! \param t_handle Wrapper for OS-specific socket
	//!
	void open(SocketHandle t_socket);

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
