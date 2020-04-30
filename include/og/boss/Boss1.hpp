/*
 * libOG, 2020
 *
 * Name: Boss1.hpp
 *
*/

#pragma once

#include "og/network.hpp"
#include "og/boss/IBoss.hpp"

#include <chrono>
#include <mutex>
#include <queue>
#include <utility>

namespace og {

//! \brief An implementation of the Boss class that supervises readiness
//!        on sockets and executes optional callbacks.
//!
//! \note TPollWorker and TExecuteWorker shall be implementations
//!       of IWorker. TPollWorker will only receive a single task.
//!       TExecuteWorker can receive multiple tasks.
//!
template<class TPollWorker, class TExecuteWorker>
class Boss1 : public IBoss {
public:

	//! \brief Constructor
	//!
	//! \param timeout The polling interval
	//!
	Boss1(std::chrono::milliseconds t_timeout,
	      TPollWorker&& t_poll_worker,
		  TExecuteWorker&& t_execute_worker) :
		m_timeout(t_timeout),
		m_poll_worker(std::forward<TPollWorker>(t_poll_worker)),
		m_execute_worker(std::forward<TExecuteWorker>(t_execute_worker))
	{
		m_poll_worker.start();
		m_execute_worker.start();

		m_poll_worker.push([this]() {
			while (1)
			{
				m_poll.poll(
			}
		});
	}

	~Boss1();
	
	//! \brief Marks the given Target for monitoring and enventually
	//!        executes if when is is ready
	//!
	//! \param target The target instance to monitor and execute when
	//!        it is ready
	//!
	void mark(std::unique_ptr<ITarget> target) override final
	{

	}

	void stop() override final;

private:

	std::chrono::milliseconds m_timeout; //!< the polling interval
	std::mutex m_mutex; //!< the critical section mutex
	og::Poll m_poll;

	bool m_is_active = true;

	std::queue<std::unique_ptr<ITarget>> m_targets; //!< the internal holder of targets

	TPollWorker m_poll_worker; //!< the worker that does the polling
	TExecuteWorker m_execute_worker; //!< the worker that executes the callback

}; // class Boss1

} // namespace og
