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

#include <sys/epoll.h>

namespace og {

//! \brief Special values for poll timeout
//!
enum PollTimeout {
	None = -1,
};

//! \brief Unix-specific selector using epoll
//!
class Selector : public NonCopyable {
public:

	//! \brief Default constructor
	//!
	Selector();

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

	//! \brief Poll pending epoll_events
	//!
	//! \param events The events container
	//!
	//! \param timeout The number of milliseconds to block for
	//!                waiting for events.
	//!
	//! \return The number of file descriptors ready for I/O ; zero if
	//!         no file descriptors became ready during before timeout ; 
	//!         -1 if an error occured. Errno is set accordingly by the
	//!         system
	//!         
	int select(Events& events, int timeout);

	//! \brief Check if the object was correctly constructed
	//!
	//! \return True if the object is valid ; false if not.
	//!
	inline bool is_valid() const;

private:

	int m_poll_fd; //!< The file descriptor

}; // class Selector

} // namespace og
