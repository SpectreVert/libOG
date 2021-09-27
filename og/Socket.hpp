/*
 * Created by Costa Bushnaq
 *
 * 27-04-2021 @ 02:30:20
 *
 * see LICENSE
*/

#ifndef _SOCKET_HPP
#define _SOCKET_HPP

#include "og/generic/ISource.hpp"
#include "og/Internal.hpp"

namespace og {

class Socket : public ISource<intl::Handle> {
public:
	using Handle = ISource::Handle;

	virtual ~Socket();
	Socket() = default;
	Socket(int dom, int type, int prot);
	Socket(Handle);

	virtual Handle handle() const;
	virtual void set_handle(Handle);
	virtual int make_handle(int dom, int type, int prot);
	virtual int close();

	virtual int bind(SocketAddr const& addr);

protected:
	Handle m_handle = k_bad_socket;

}; // class Socket

} // namespace og

#endif /* _SOCKET_HPP */
