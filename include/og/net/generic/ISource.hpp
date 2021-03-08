/*
 * libOG, 2020
 *
 * Name: ISource.hpp
 *
*/

#pragma once

namespace og {

namespace net {

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
	virtual int close() = 0;

}; // interface ISource

} // namespace net

} // namespace og
