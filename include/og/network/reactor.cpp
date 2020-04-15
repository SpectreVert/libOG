/*
 * PROJECT_NAME, 2020
 *
 * Name:
 *
 * Description:
 * 
*/

//
// https://docs.rs/tokio/0.1.22/tokio/reactor/index.html
//
//
// 1. I want to connect to a remote Tcp server
//
// og::async::TcpStream st;
//
// 2. I try to connect using asynchronous connection
//
// auto future = st.connect(og::Ipv4::Loopback, 69);
//
// Actually is something like:
//
// og::future<og::Socket::Status> future = st.connect(og::Ipv4::Loopback, 69);
//
// 3. What is does behind the scene, before returning the future, is registering
//    the socket with a « Reactor » instance. At this point it starts monitoring
//    for events on that socket.
//
// 4. The future needs to be registerd onto a thread pool that awaits to
//    be able to perform the operation.
// 
// 5. When the connection is established the reactor receives an event from the
//    OS and forwards that event as a notification to the thread pool, telling it
//    that the future can complete.
//
// 6. The thread poll schedules a task to run on one of its worker. When it is done
//    the future is gettable.
//
//// Instead of returing a connect status it returns a future that
//
//
//
//
//
//
