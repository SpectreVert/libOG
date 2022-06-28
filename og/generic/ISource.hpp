/*
 * Created by Costa Bushnaq
 *
 * 26-04-2021 @ 23:40:51
 *
 * see LICENSE
*/

#ifndef OG_ISOURCE_HPP_
#define OG_ISOURCE_HPP_

namespace og {

//! interface for an arbitrary source that can
//! be registered to an arbitrary poller.
//!
template<typename THandle>
class ISource {
public:
    using Handle = THandle;

    virtual ~ISource() = default;

    virtual Handle handle() const = 0;
    virtual void set_handle(Handle) = 0;
    virtual int close() = 0;

}; // class ISource

} // namespace og

#endif /* OG_ISOURCE_HPP_ */
