/*
 * Created by Costa Bushnaq
 *
 * 26-04-2021 @ 23:40:51
 *
 * see LICENSE
*/

#ifndef _ISOURCE_HPP
#define _ISOURCE_HPP

namespace og {

namespace net {

//! interface for an arbitrary source that can
//! be registered to an arbitrary poller.
//!
template<typename THandle>
class ISource {
public:
	virtual ~ISource() noexcept = default;

	virtual void set_handle(THandle) = 0;
	virtual THandle handle() const = 0;
	virtual int close() = 0;

}; // class ISource

} // namespace net

} // namespace og

#endif /* _ISOURCE_HPP */
