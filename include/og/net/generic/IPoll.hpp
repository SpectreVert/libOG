/*
 * libOG, 2020
 *
 * Name: IPoll.hpp
 *
*/

#pragma once

#include "og/core/Tag.hpp"
#include "og/core/Concern.hpp"
#include "og/net/generic/ISource.hpp"

namespace og {

namespace net {

//! \brief Interface for an object which handles registration
//!        and deregistration of ISource derivates. Events
//!        on the sources can then be polled for.
//!
template<typename TSource, typename TEvents>
class IPoll {
public:

	//! \brief The size of kernel-specific buffer for event
	//!        polling
	//!
	//! While increasing this value might bring down
	//! the number of system calls performed it also
	//! implies a bigger buffer and therefore a bigger
	//! memory footprint.
	//!
	//static std::size_t constexpr k_poll_event_capacity = 1024;

	virtual ~IPoll() = default;

	int poll(TEvents& events, int timeout);

	int monitor(TSource& source, core::Tag id, core::Concern concern);
	
	int forget(TSource& source);
	
}; // interface IPoll

} // namespace net

} // namespace og
