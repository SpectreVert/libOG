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

#include <vector>

namespace og {

namespace net {

template<typename THandle, typename TEventType>
class IPoll {
public:
	using Source = ISource<THandle>;
	using Event  = IEvent<TEventType>;
	using Events = std::vector<Event>;

	virtual ~IPoll() = default;

	virtual int poll(Events& events) = 0;

	virtual int monitor(Source&, core::Tag, core::Concern)= 0;
	virtual int re_monitor(Source&, core::Tag, core::Concern) = 0;
	virtual int forget(Source&) = 0;

}; // class IPoll

} // namespace net

} // namespace og

#endif /* _IPOLL_HPP */
