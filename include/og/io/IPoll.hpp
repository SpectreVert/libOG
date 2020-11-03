/*
 * libOG, 2020
 *
 * Name: IPoll.hpp
 *
*/

#pragma once

#include "og/io/IEvent.hpp"
#include "og/io/Tag.hpp"
#include "og/io/Concern.hpp"

namespace og {

namespace io {

//! \brief Class template for a Poll object which
//! handles registrations and deregistration, as
//! well as polling for events.
//!
template<typename T, std::size_t N>
class IPoll {
public:
	virtual ~IPoll() = default;

	virtual int poll(Events<N> events, int timeout) = 0;
	virtual int add(T source, io::Tag id, io::Concern concern) = 0;
	virtual int remove(T source) = 0;
	
}; // interface IPoll

} // namespace io

} // namespace og
