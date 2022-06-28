/*
 * Created by Costa Bushnaq
 *
 * 27-04-2021 @ 14:22:37
 *
 * see LICENSE
*/

#ifndef OG_IPOLL_HPP_
#define OG_IPOLL_HPP_

#include "og/generic/ISource.hpp"
#include "og/generic/IEvent.hpp"

#include <array>

namespace og {

template<typename TSource, typename TEvent>
class IPoll {
public:
    // TODO: have k_events_size be a template argument instead
    static constexpr std::size_t k_events_size{ 1024 };

    enum {
        e_read   = 1,
        e_write  = 2,
        e_shared = 4
    };

    using Event   = TEvent;
    using Events  = std::array<TEvent, k_events_size>;
    using Concern = short;
    using Source  = TSource;
    using Tag     = IEvent::Tag;

    virtual ~IPoll() = default;

    virtual int poll(Events& events, int timeout) = 0;

    virtual int add(Source&, Tag, Concern) = 0;
    virtual int refresh(Source&, Tag, Concern) = 0;
    virtual int forget(Source&) = 0;

}; // class IPoll

} // namespace og

#endif /* OG_IPOLL_HPP_ */
