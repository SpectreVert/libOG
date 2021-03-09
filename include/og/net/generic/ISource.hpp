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

namespace net {

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
