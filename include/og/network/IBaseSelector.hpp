/*
 * libOG, 2020
 *
 * Name: Selector.hpp
 *
*/

#pragma once

#include "og/base/NonCopyable.hpp"
#include "og/network/SocketHandle.hpp"
#include "og/network/Event.hpp"
#include "og/network/Token.hpp"
#include "og/network/Concern.hpp"



namespace og {

//! \brief A base template for all selector types.
//!
class IBaseSelector : public NonCopyable {
public:

	//! \brief Destructor
	//!
	virtual ~IBaseSelector() = default;

protected:

	//! \brief Default constructor
	//!
	IBaseSelector() = default;

	//! \brief Add a new socket to the poll list
	//!
	//! \param handle The raw socket handle to register
	//!
	//! \param token Token to retrieve the events of the socket
	//!        handle descriptor
	//!
	//! \param concern The readiness that should be monitored
	//!
	//! \return zero if the socket handle was registered ;
	//!         -1 if an occured
	//!
	virtual int add(SocketHandle handle, Token token, Concern concern) = 0;

	//! \brief Remove a socket from the poll list
	//!
	//! \param The raw socket handle to deregister
	//!
	//! \return zero if the socket handle was deregistered ;
	//!         -1 if an error occured
	//!
	virtual int remove(SocketHandle handle) = 0;

	//! \brief Poll pending events
	//!
	//! \param events The events container
	//!
	//! \param timeout The number of milliseconds to block for
	//!                waiting for events.
	//!
	//! \return The number of file descriptors ready for I/O ; zero if
	//!         no file descriptors became ready during before timeout ; 
	//!         -1 if an error occured
	//!         
	virtual int select(Events& events, int64_t timeout) = 0;

}; // class Selector

} // namespace og
