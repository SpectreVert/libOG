/*
 * Created by Costa Bushnaq
 *
 * 27-04-2021 @ 15:22:07
 *
 * see LICENSE
*/

#ifndef OG_IEVENT_HPP_
#define OG_IEVENT_HPP_

#include "og/defs.hpp"

namespace og {

struct IEvent {
    virtual ~IEvent() = default;

    virtual u64 id() const = 0;

    virtual bool is_error() const = 0;
    virtual bool is_readable() const = 0;
    virtual bool is_read_closed() const = 0;
    virtual bool is_writable() const = 0;
    virtual bool is_write_closed() const = 0;

}; // struct IEvent

} // namespace og

#endif /* OG_IEVENT_HPP_ */
