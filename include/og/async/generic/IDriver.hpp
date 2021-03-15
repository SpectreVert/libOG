/*
 * Created by Costa Bushnaq
 *
 * 23-02-2021 @ 12:36:31
 *
 * see LICENSE
*/

#ifndef _IDRIVER_HPP_
#define _IDRIVER_HPP_

#include "og/core/Tag.hpp"
#include "og/core/Concern.hpp"
#include "og/net/Poll.hpp"

#include <functional>
#include <future>

namespace og {

namespace async {

//! \brief Driver is the event loop that monitors
//! network I/O resources. It receives events from
//! the kernel and forward them to the Scheduler.
//!
//! Asynchronous I/O (connect, accept, read, write) is
//! not performed on call (synchronously). The socket is
//! first registered to a Driver, which will wait for an
//! event that indicates that the resource is usable.
//!
//! When it detects such events, the Driver forwards them
//! to the scheduler to perform the I/O operation and
//! notify the user that the operation has been performed.
//!
//! By default, a runtime's default reactor runs on a
//! background thread. This ensures that application code
//! cannot significantly impact the reactor's responsiveness.
//!
class IDriver {

	// this should be in Driver
    //	struct Resource {
    //		T handle;
    //		E events;
    //	};

	//! Signaling to the scheduler that an event
	//! is there and the operation for id can
	//! be completed
	//!
	//! Here we have two (maybe more) solutions:
	//!
	//! - a thread-agnostic list of ressources; that
	//!   is modified by the Driver receives an event.
	//!   The Scheduler should receive an event when the
	//!   corresponding resource is awoken.
	//!
	//! - the Scheduler receives a call from the Driver,
	//!   indicating that XXX resource is available.
	//!
	//! - the Scheduler receives a hint from a message channel
	//!   it has been waiting on that a resource is ready
	//!   for polling.
	//!
	template<typename E>
	int dispatch(core::Tag id, E& events);

public:
	virtual ~IDriver() = default;

	//! Perform a single iteration of the event loop
	//! calls the Poll.poll() which calls one time
	//! the kernel polling function ande dispatches
	//! callbacks if needed
	//!
	virtual int step(int timeout) = 0;

	template<typename T, typename R, typename ...Args>
	std::future<R> monitor_for(T& source, core::Tag id, core::Concern concern,
	                           std::packaged_task<R(Args...)>& callback);

	template<typename T>
	int forget(T& source);

}; // class IDriver

} // namespace async

} // namespace og

#endif /* _IDRIVER_HPP_ */

