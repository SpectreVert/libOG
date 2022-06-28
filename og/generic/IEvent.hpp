/*
 * Created by Costa Bushnaq
 *
 * 27-04-2021 @ 15:22:07
 *
 * see LICENSE
*/

#ifndef _IEVENT_HPP
#define _IEVENT_HPP

#include <utility>

namespace og {

struct IEvent {
    using Tag = std::size_t;

    virtual ~IEvent() = default;

    virtual Tag id() const = 0;

    virtual bool is_error() const = 0;
    virtual bool is_readable() const = 0;
    virtual bool is_read_closed() const = 0;
    virtual bool is_writable() const = 0;
    virtual bool is_write_closed() const = 0;
};

} // namespace og

#endif /* _IEVENT_HPP */
