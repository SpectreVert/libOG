/*
 * Created by Costa Bushnaq
 *
 * 27-04-2021 @ 02:30:20
 *
 * see LICENSE
*/

#ifndef OG_SOCKET_HPP_
#define OG_SOCKET_HPP_

#include "og/generic/ISource.hpp"
#include "og/Internal.hpp"

namespace og {

class Socket : public ISource<intl::Handle> {
public:
	virtual ~Socket();
	Socket() = default;
	Socket(int dom, int type, int prot);
	Socket(Handle);

	virtual Handle handle() const;
	virtual int mk_handle(int dom, int type, int prot);
	virtual void set_handle(Handle);
	virtual int close();

	virtual int bind(SocketAddr const& addr);

protected:
	Handle m_handle = k_bad_socket;

}; // class Socket

} // namespace og

#endif /* OG_SOCKET_HPP_ */
