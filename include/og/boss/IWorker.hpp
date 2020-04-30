/*
 * libOG, 2020
 *
 * Name: IWorker.hpp
 * 
*/

#pragma once

#include "og/base/NonCopyable.hpp"

#include <functional>

namespace og {

//! \brief An interface for a Worker object; which is responsible
//!        for executing tasks
//!
class IWorker : public NonCopyable {
public:

	//! \brief Default destructor
	//!
	virtual ~IWorker() = default;

	//! \brief Begin the worker operations
	//!
	virtual void start() = 0;

	//! \brief Halt the worker operations
	//!
	virtual void stop() = 0;

	//! \brief Schedule a task for execution
	//!
	//! Note to self: try with void for now. Could add a temapleted
	//! signature or use an std::any object as return value.
	//!
	//! \param task The function that represents the
	//!        task to execute
	//!
	virtual void push(std::function<void()> task)

}; // class IWorker

} // namespace og
