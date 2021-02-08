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

namespace og {

namespace net {

class TcpListener : public Socket {
public:
	TcpListener();
	virtual ~TcpListener();

	virtual int listen(int backlog);
	virtual int accept(TcpStream& socket);

}; // class TcpListener

} // namespace net

} // namespace og

#endif /* _TCPLISTENER_HPP_ */
