/*
 * PROJECT_NAME, 2020
 *
 * Name:
 *
 * Description:
 * 
*/


int main()
{
	// one has a socket
	og::UdpSocket so;
	// and a remote address to send messages to
	og::Ipv4 addr ("54.45.54.45");
	og::Socket::Port port = 777;

	// and wants to send a message
	og::Socket::Status stat = so.send_to(msg, addr, port);

	// message could fail because buffer is full
	stat == Socket::Status::RetrySend;

	// therefore, one wants to send it asynchronously
	og::future<og::Socket::Status> fut = so.async_send_to(msg, addr, port);

	// and then get the return from that operation when it has completed
	og::Socket::Status stat = fut.get();
}

int main()
{
	// this is what actually will happen

	// create an instance of an og::Boss (exectutor);

	// with the refresh rate
	og::Boss big_baws = make_shared<DefaultBoss>(milliseconds(10));

	// set the boss as responsible for the current scope
	og::Boss::set_default(big_baws);

	// register a future with a continuation
	// case 1
	og::Future<std::string> error = get_async_connect.and_then(
		[](future<og::Socket::Status> f) {
			switch (f.get()) {
			case Status::Success:
				return "Sent successfully\n"
			case Status::Failure:
				return "Could not send the message\n";
			}
		}
	);

	// print the value
	std::cerr << error.get() << std::endl;
}
