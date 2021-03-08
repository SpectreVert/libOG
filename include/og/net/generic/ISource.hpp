/*
 * libOG, 2020
 *
 * Name: ISource.hpp
 *
*/

#pragma once

namespace og {

namespace net {

class ISource {
public:
	virtual ~ISource() = default;
	
	//! \brief Return the internal handle of the I/O source
	//!
	//! \return The underlying OS descriptor for the I/O source
	//!
	template<typename T>
	T handle() const;

protected:
	virtual int close() = 0;

}; // interface ISource

} // namespace net

} // namespace og
