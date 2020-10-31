/*
 * libOG, 2020
 *
 * Name: SourceHandle.hpp
 *
*/

#pragma once

#include "og/core/config.hpp"

namespace og {

namespace io {

//! Source contains an Handle which can be polled for
//! events.
template<typename THandle>
class Source {
public:
	virtual ~Source() = default;
	
	//! \brief Return the internal handle of the I/O source
	//!
	//! \return The underlying OS descriptor for the I/O source
	//!
	virtual THandle handle() const = 0;

protected:
	virtual int open() = 0;
	virtual int open(THandle handle) = 0;
	virtual int close();

}; // class Source

} // namespace io

} // namespace og
