/*
 * libOG, 2020
 *
 * Name: ISource.hpp
 *
*/

#pragma once

#include "og/core/Concern.hpp"
#include "og/core/Tag.hpp"

namespace og {


// TODO: maybe move this to og::core

// TODO: XXX: make this be a wrapper/interface around RawFd!!!!
namespace net {

//! \brief Interface for a I/O source that can be registered
//!        with a IPoll derivate and be monitored for I/O events.
//!
class ISource {
public:
	virtual ~ISource() = default;
	
	//! \brief Return the internal handle of the I/O source
	//!
	//! \return The underlying OS descriptor for the I/O source
	//!
	//! FIXME: rename this raw_fd() or something
	//!
	template<typename T>
	T handle() const;

	template<typename P>
	int monitor(P& poll, core::Tag id, core::Concern concern);

	template<typename P>
	int forget(P& poll);

protected:
	virtual int close() = 0;

}; // interface ISource

} // namespace net

} // namespace og
