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

namespace og {

namespace async {

//! FIXME
//!
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
template<typename T, typename E>
class IDriver {

	// this should be in Driver
    //	struct Resource {
    //		T handle;
    //		E events;
    //	};

	//! Signaling to the scheduler that an event
	//! is there and the operation for id can
	//! be completed
	virtual int dispatch(core::Tag id, E& events) = 0;

public:
	virtual ~IDriver() = default;

	//! Oneshot monitor
	//! also registers to the scheduler instance
	virtual int monitor(T source, core::Tag id, core::Concern concern) = 0;

	//! FIXME: (thought experiment)
	//!
	//! Be sure that the templated way for the callback is
	//! the best (inheritance, wrapper...)
	//!
	//! Also, try to look into std::result::Result from Rust
	//! for similar code in C++
	//!
	//! Also, the monitor functions could be the same. look into
	//! a default argument for Callback.

	//! Oneshot monitor with a subsequent callback that
	//! must have the () operator overloaded. Also a call
	//! to the () operator must take an net::SocketHandle
	//! as argument and return an int.
	//!
	template<typename C>
	int monitor_then(T source, core::Tag id, core::Concern concern, C callback);

	//! Perform a single iteration of the event loop
	//! calls the Poll.poll() which calls one time
	//! the kernel polling function ande dispatches
	//! callbacks if needed
	virtual int step(int timeout) = 0;

	//! FIXME: find a better timeout data type
	//! and for Poll too

}; // class IDriver

} // namespace async

} // namespace og

#endif /* _IDRIVER_HPP_ */

