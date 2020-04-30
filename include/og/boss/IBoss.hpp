/*
 * libOG, 2020
 *
 * Name: IBoss.hpp
 *
*/

#pragma once

#include "og/base/NonCopyable.hpp"
#include "og/boss/ITarget.hpp"

#include <memory>

namespace og {
	
class ITarget;

//! \brief An interface for a Boss class; which is the equivalent
//! of an executor.
//!
class IBoss : public NonCopyable {
public:

	virtual ~IBoss() = default;

	//! \brief Marks the given Target for monitoring and eventually
	//!        executes it when it is ready
	//!
	//! \param target The target instance to monitor and execute when
	//!        it is ready
	//!
	virtual void mark(std::unique_ptr<ITarget> target) = 0;

	//! \brief Stops the Boss instance and attempts to stop all pending
	//!        operations
	//!
	virtual void stop() = 0;

}; // class IBoss

} // namespace og
