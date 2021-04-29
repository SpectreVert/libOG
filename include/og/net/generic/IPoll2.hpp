/*
 * Created by Costa Bushnaq
 *
 * 27-04-2021 @ 14:22:37
 *
 * see LICENSE
*/

#ifndef _IPOLL_HPP
#define _IPOLL_HPP

#include "og/net/generic/ISource2.hpp"
#include "og/net/generic/IEvent.hpp"

#include "og/core/Concern.hpp"
#include "og/core/Tag.hpp"

#include <array>

namespace og {

namespace net {

//! interface for registering a derivate of ISource
//!
template<typename TSource, typename TEvent>
class IPoll {
public:
	static std::size_t constexpr k_events_size{1024};

	using Source = TSource;
	using Event  = TEvent;
	using Events = std::array<Event, k_events_size>;

	virtual ~IPoll() = default;

	virtual int poll(Events& events, int timeout) = 0;

	virtual int monitor(Source&, core::Tag, core::Concern)= 0;
	virtual int re_monitor(Source&, core::Tag, core::Concern) = 0;
	virtual int forget(Source&) = 0;

}; // class IPoll

} // namespace net

} // namespace og

#endif /* _IPOLL_HPP */
