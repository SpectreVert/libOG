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
//! handles registrations and deregistration, as
//! well as polling for events.
//!
template<typename T, typename E>
class IPoll {
public:
	virtual ~IPoll() = default;

	virtual int poll(E& events, int timeout) = 0;
	virtual int add(T source, core::Tag id, core::Concern concern) = 0;
	virtual int remove(T source) = 0;
	
}; // interface IPoll

} // namespace net

} // namespace og
