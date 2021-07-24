/*
 * Created by Costa Bushnaq
 *
 * 04-02-2021 @ 23:36:49
 *
 * see LICENSE
*/

#ifndef _TCPLISTENER_HPP_
#define _TCPLISTENER_HPP_

#include "og/net/SocketAddr.hpp"
#include "og/net/TcpStream.hpp"

#include <optional>

namespace og {

namespace net {

class TcpListener : public Socket {
public:
	virtual ~TcpListener() = default;
	TcpListener();
	TcpListener(Handle handle);

	virtual int listen(int backlog);
	std::optional<TcpStream> try_accept();
	std::optional<TcpStream> try_accept(SocketAddr&);

}; // class TcpListener

} // namespace net

} // namespace og

#endif /* _TCPLISTENER_HPP_ */
