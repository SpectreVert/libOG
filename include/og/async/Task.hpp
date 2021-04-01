/*
 * Created by Costa Bushnaq
 *
 * 02-03-2021 @ 14:56:19
 *
 * see LICENSE
*/

// FIXME: _TASK_HPP_ is a reserved identifier...
#ifndef _ATASK_HPP_
#define _ATASK_HPP_

#include <functional>
#include <future>

// XXX Heh well sorry but we won't be using
// that header. We'll go with packaged_task
// instead my man.

namespace og {

namespace aysnc {

template<typename> class Task;

//! \brief A class template that wraps a callable object
//!        to be called asynchronously. Its return value
//!        can be accessed through a std::future object.
//!
template<typename R, typename ...Args>
class Task<R(Args...)> {
	std::function<R(Args...)> m_func;
	std::promise<R> m_promise;

public:
	template<typename ...Ts>
	explicit Task(Ts&&... ts) : m_func(std::forward<Ts>(ts)...)
	{}
	virtual ~Task() = default;

	template<typename ...Ts>
	void operator()(Ts&&... ts)
	{
		m_promise.set_value(m_func(std::forward<Ts>(ts)...));
	}

	std::future<R> get_future() { return m_promise.get_future(); }

	// FIXME: disable copy, default move

}; // class Task

} // namespace async

} // namespace og

#endif /* _ATASK_HPP_ */

