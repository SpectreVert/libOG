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

	//! \brief The size of kernel-specific buffer for event
	//!        polling
	//!
	//! An important caveat to note is that this size
	//! serves only to allocate statically the buffer
	//! for polling events from the kerne.
	//!
	//! The ::poll() method will ask the kernel for more
	//! events if it thinks there are more available for
	//! as much as s_poll_max_reprompt times; returing
	//! a maximum total of s_poll_event_capacity *
	//! s_poll_max_prompt envents to the user.
	//!
	//! While increasing this value might bring down
	//! the number of system calls performed it also
	//! implies a bigger buffer and therefore a bigger
	//! memory footprint.
	//!
	//! The casual user should leave the value as is.
	//!
	//! \see s_poll_max_repromt
	//!
	static constexpr std::size_t s_poll_event_capacity = 1024;

	//! \brief The amount of times ::poll() will prompt
	//!        the kernel for events
	//!
	//! If the kernel event polling function returns with
	//! a full buffer, ::poll() is allowed to poll for
	//! events up to s_poll_max_reprompt times; returning
	//! a maximum total of s_poll_event_capacity *
	//! s_poll_max_prompt events to the user.
	//!
	//! The casual user should leave the value as is.
	//!
	//! \see s_poll_event_capacity
	//! 
	static constexpr std::size_t s_poll_max_reprompt = 24;

	virtual ~IPoll() = default;
	
	virtual bool is_valid() const = 0;

	virtual int poll(E& events, int timeout) = 0;
	virtual int add(T source, core::Tag id, core::Concern concern) = 0;
	virtual int remove(T source) = 0;
	
}; // interface IPoll

} // namespace net

} // namespace og
