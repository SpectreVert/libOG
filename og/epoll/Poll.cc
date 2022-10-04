/*
 * Created by Costa Bushnaq
 *
 * 27-04-2021 @ 15:47:57
*/

#include "og/Poll.hpp"
#include "og/epoll/Event.hpp"
#include "og/internal.hpp"

#include <sys/epoll.h>

#include <cstring>
#include <fcntl.h>

using namespace og;

Poll::~Poll()
{
    intl::close(m_pollfd);
}

Poll::Poll()
{
    m_pollfd = epoll_create1(O_CLOEXEC);

    if (m_pollfd != -1)
        return;

    /* epoll_create1 can fail because it's not implemented,
     * or because it cannot handle O_CLOEXEC flag */
    if (errno == ENOSYS || errno == EINVAL)
    {
        /* see kernel 2.6.8 patch notes */
        m_pollfd = epoll_create(1024);
    }

    assert(m_pollfd != -1);
    assert(intl::set_cloexec(m_pollfd, true) != -1);
}

s32 Poll::poll(Events& events, s32 timeout)
{
    s32 nb;
    
    assert(timeout >= -1);
    std::memset((void*) events.data(), 0, events.size() * sizeof(og::Event));

    for (;;)
    {
        nb = epoll_wait(m_pollfd, events.data(), events.size(), timeout);
        
        if (nb == 0)
        {
            assert(timeout != -1);
            return e_success;
        }

        if (nb == -1)
        {
            if (errno != EINTR)
                return e_failure;

            if (timeout)
                continue;
        }

        break;
    }

    return e_success;
}

s32 Poll::add(s32 socketfd, u64 id, u16 concern)
{
    u32 bits{0};
    epoll_event event{0, {0}};

    /* if the fd we're using needs to be shared, we're
     * staying in level-triggered mode so as to dodge
     * starvation with multiple incoming events.
    */
    if (concern & e_shared)
        bits = EPOLLEXCLUSIVE;
    else
        bits = EPOLLET;

    if (concern & e_write)
        bits |= EPOLLOUT;
    if (concern & e_read)
        bits |= EPOLLIN;

    event.events = bits;
    event.data.u64 = id;

    return epoll_ctl(m_pollfd, EPOLL_CTL_ADD, socketfd, &event);

}

s32 Poll::add(Socket& socket, u64 id, u16 concern)
{
    return add(socket.handle(), id, concern);
}

s32 Poll::refresh(s32 socketfd, u64 id, u16 concern)

{
    u32 bits{EPOLLET};
    epoll_event event{0, {0}};

    if (concern & e_shared)
    {
        errno = EINVAL;
        return e_failure;
    }

    if (concern & e_write)
        bits |= EPOLLOUT;
    if (concern & e_read)
        bits |= EPOLLIN;

    event.events = bits;
    event.data.u64 = id;

    return epoll_ctl(m_pollfd, EPOLL_CTL_MOD, socketfd, &event);
}

s32 Poll::refresh(Socket& socket, u64 id, u16 concern)
{
    return refresh(socket.handle(), id, concern);
}

int Poll::forget(s32 socketfd)
{
    epoll_event event{0, {0}};

    return epoll_ctl(m_pollfd, EPOLL_CTL_DEL, socketfd, &event);
}

int Poll::forget(Socket& socket)
{
    return forget(socket.handle());
}
