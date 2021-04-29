/*
 * Created by Costa Bushnaq
 *
 * 27-04-2021 @ 02:30:20
 *
 * see LICENSE
*/

#ifndef _SOCKET_HPP
#define _SOCKET_HPP

#include "og/core/RawFd.hpp"
#include "og/net/generic/ISource2.hpp"
#include "og/net/Internal2.hpp"

namespace og {

namespace net {

class Socket : public ISource<core::RawFd> {
public:
	using Handle = ISource::Handle;

	virtual ~Socket() = default;

	virtual Handle handle() const;
	virtual void set_handle(Handle);
	virtual int make_handle(int dom, int type, int prot);
	virtual int close();

	virtual int bind(SocketAddr const& addr);

protected:
	Handle m_handle = k_bad_socket;

}; // class Socket

} // namespace core

} // namespace og

#endif /* _SOCKET_HPP */
