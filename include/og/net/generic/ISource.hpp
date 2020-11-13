/*
 * libOG, 2020
 *
 * Name: ISource.hpp
 *
*/

#pragma once

namespace og {

namespace net {

//! Source contains an Handle which can be polled for
//! events.
template<typename T>
class ISource {
public:
	virtual ~ISource() = default;
	
	//! \brief Return the internal handle of the I/O source
	//!
	//! \return The underlying OS descriptor for the I/O source
	//!
	virtual T handle() const = 0;

protected:
	virtual int open() = 0;
	virtual int open(T handle) = 0;
	virtual int close() = 0;

}; // interface ISource

} // namespace net

} // namespace og
