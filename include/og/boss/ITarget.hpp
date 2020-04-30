/*
 * libOG, 2020
 *
 * Name: ITarget.hpp
 *
*/

#pragma once

// #include "og/boss/TargetException.hpp"

#include <chrono>
#include <exception>

namespace og {

//! \brief An interface for a Target object; which can be
//!        waited on and get executed.
//!
class ITarget {
public:

	//! \brief Default destructor
	//!
	virtual ~ITarget() = default;

	//! \brief Wait, at most, the given amount of time to deternmine
	//!        whether the object is ready or not
	//!
	//! \param timeout The maximum time to wait
	//!
	//! \return true if the object is ready ; false otherwise 
	//!
	virtual bool wait(const std::chrono::microseconds& timeout) = 0;

	//! \brief Execute the object - setting it to a finished state
	//!
	//! \param error The optional exception that occured during 
	//!        execution of the target
	//!
	virtual void execute(std::exception_ptr error = nullptr) = 0;

}; // class ITarget

} // namespace og
