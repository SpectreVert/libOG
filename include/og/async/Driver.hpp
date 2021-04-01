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

#include <vector>

namespace og {

namespace async {

class Driver : public IDriver<net::Socket, net::Events> {
	std::vector<std::packaged_task<int()>> m_tasks;
	net::Poll m_poll;
	net::Events m_events;

public:

	virtual ~Driver() = default;
	Driver()
	{
		m_events = net::ev::with_capacity(1024);
	}

	std::future<int>
	monitor_then(net::Socket& source, core::Tag id, std::function<int()>& fn)
	{
		(void) source;
		(void) id;

		std::packaged_task<int()> task(fn);
		auto fut = task.get_future();

		m_tasks.push_back(std::move(task));
		return fut;
	}

	void run_all()
	{
		for (auto& task : m_tasks)
		{
			std::thread thr(std::move(task));
			thr.detach();
		}
	}

	// TODO: explicity core::Tag
	int dispatch(core::Tag id, net::Events& events)
	{
		return 0;
	}

	int step(int timeout)
	{
		return 0;
	}

}; // class Driver

} // namespace aysnc

} // namespace og

#endif /* _DRIVER_HPP_ */

