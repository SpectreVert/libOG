/*
 * libOG, 2020
 *
 * Name: Poll.hpp
 * 
*/

#pragma once

#include "og/base/NonCopyable.hpp"
#include "og/network/SocketHandle.hpp"
#include "og/network/Event.hpp"
#include "og/network/Registry.hpp"
#include "og/network/Concern.hpp"

namespace og {

//! \brief Polling motor for events on registered I/O sources
//!
class Poll : public NonCopyable {
public:

	//! \brief Default constructor
	//!
	Poll();

	//! \brief Wait and poll readiness events
	//!
	//! The function will block until at least one
	//! readiness event has been received or timeout
	//! has ellapsed.
	//!
	//! \param events The events holder
	//!
	//! \param timeout The maximum time to wait for an event
	//!
	//! \return The number of events polled
	//!
	int poll(Events& events, int timeout);

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
	//!         -1 if an occured. Errno is set accordingly by the
	//!         system
	//!
	int add(SocketHandle socket, Token token, Concern concern);

private:

	Registry m_registry; //!< Holds the OS-based selector

}; // class Poll

} // namespace og
