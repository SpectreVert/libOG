/*
 * Created by Costa Bushnaq
 *
 * 04-02-2021 @ 23:36:49
 *
 * see LICENSE
*/

#ifndef _TCPLISTENER_HPP_
#define _TCPLISTENER_HPP_

#include "og/SocketAddr.hpp"
#include "og/TcpStream.hpp"

#include <memory>

namespace og {

class TcpListener : public Socket {
public:
	virtual ~TcpListener() = default;
	TcpListener();
	TcpListener(Handle handle);

	virtual int listen(int backlog);
	std::unique_ptr<TcpStream> virtual try_accept();
	std::unique_ptr<TcpStream> virtual try_accept(SocketAddr &peer_address);

}; // class TcpListener

} // namespace og

#endif /* _TCPLISTENER_HPP_ */
