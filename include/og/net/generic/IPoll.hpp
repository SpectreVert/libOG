/*
 * libOG, 2020
 *
 * Name: IPoll.hpp
 *
*/

#pragma once

#include "og/core/Tag.hpp"
#include "og/core/Concern.hpp"

namespace og {

namespace net {

//! \brief Class template for a Poll object which
//!        handles registrations and deregistration, as
//!        well as polling for events
//!
//! To limit overhead and leave more freedom to the user,
//! pre-made Poll implementations do not keep track of what
//! handles are currently monitored: only the kernel keeps
//! a list.
//!
template<typename T, typename E>
class IPoll {
public:

	//! FIXME: decide where the declaration of these values
	//! is best: here or in Poll.hpp headers.
	//!
	//! \brief The size of kernel-specific buffer for event
	//!        polling
	//!
	//! An important caveat to note is that this size
	//! serves only to allocate statically the buffer
	//! for polling events from the kerne.
	//!
	//! The ::poll() method will ask the kernel for more
	//! events if it thinks there are more available for
	//! as much as S_POLL_MAX_REPROMPT times; returing
	//! a maximum total of S_POLL_EVENT_CAPACITY *
	//! s_poll_max_prompt envents to the user.
	//!
	//! While increasing this value might bring down
	//! the number of system calls performed it also
	//! implies a bigger buffer and therefore a bigger
	//! memory footprint.
	//!
	//! The casual user should leave the value as is.
	//!
	//! \see S_POLL_MAX_REPROMPT
	//!
	static std::size_t constexpr S_POLL_EVENT_CAPACITY = 1024;

	//! \brief The amount of times ::poll() will prompt
	//!        the kernel for events
	//!
	//! If the kernel event polling function returns with
	//! a full buffer, ::poll() is allowed to poll for
	//! events up to S_POLL_MAX_REPROMPT times; returning
	//! a maximum total of S_POLL_EVENT_CAPACITY *
	//! s_poll_max_prompt events to the user.
	//!
	//! The casual user should leave the value as is.
	//!
	//! \see S_POLL_EVENT_CAPACITY
	//! 
	static std::size_t constexpr S_POLL_MAX_REPROMPT = 24;

	virtual ~IPoll() = default;

	virtual int poll(E& events, int timeout) = 0;
	virtual int monitor(T source, core::Tag id, core::Concern concern) = 0;
	virtual int forget(T source) = 0;
	
}; // interface IPoll

} // namespace net

} // namespace og
