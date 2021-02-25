/*
 * Created by Costa Bushnaq
 *
 * 24-02-2021 @ 18:46:52
 *
 * see LICENSE
*/

#ifndef _DRIVER_HPP_
#define _DRIVER_HPP_

#include "og/async/generic/IDriver.hpp"
#include "og/net/Socket.hpp"
#include "og/net/Poll.hpp"

#include <iostream>

namespace og {

namespace async {

class Driver : public IDriver<net::SocketHandle, net::Events> {

	struct Resource {

	};

	net::Poll m_poll;

	int dispatch(core::Tag id, net::Events& events);

public:
	//! FIXME: add a constructor
	//!
	//! Date: 24/02/2021
	//!
	//! Next step now is making the interface final
	//! and writing the required interface for the scheduler,
	//! then probably the Future object and then writing
	//! the code in each of the classes.

	int monitor(net::SocketHandle source, core::Tag id, core::Concern concern);
	
	template<typename C>
	int monitor_then(net::SocketHandle source, core::Tag id, core::Concern concern,
	                 C function)
	{
		std::cout << "I'm here" << std::endl;
		return function(source);
	}

	int step(int timeout);

}; // class Driver

} // namespace aysnc

} // namespace og

#endif /* _DRIVER_HPP_ */

