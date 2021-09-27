/*
 * Created by Costa Bushnaq
 *
 * 27-04-2021 @ 14:22:37
 *
 * see LICENSE
*/

#ifndef _IPOLL_HPP
#define _IPOLL_HPP

#include "og/generic/ISource.hpp"
#include "og/generic/IEvent.hpp"

#include <array>

namespace og {

template<typename TSource, typename TEvent>
class IPoll {
public:
	std::size_t static constexpr k_events_size{1024};

	enum {
		e_read   = 1,
		e_write  = 2,
		e_shared = 4
	};

	using Source = TSource;
	using Event  = TEvent;
	using Events = std::array<Event, k_events_size>;
	using Concern = short;
	using Tag    = IEvent::Tag;

	virtual ~IPoll() = default;

	virtual int poll(Events& events, int timeout) = 0;

	virtual int monitor(Source&, Tag, Concern) = 0;
	virtual int re_monitor(Source&, Tag, Concern) = 0;
	virtual int forget(Source&) = 0;

}; // class IPoll

} // namespace og

#endif /* _IPOLL_HPP */
