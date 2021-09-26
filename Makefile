# libOG - socket & event poll abstractions

include config.mk

LIB=libOG.a
TARGET=libOG

OBJFILES = og/Internal.o\
	og/Ipv4.o\
	og/Socket.o\
	og/SocketAddr.o\
	og/TcpListener.o\
	og/TcpStream.o\
	og/UdpSocket.o

ifeq (${PLATFORM}, linux)
	OBJFILES += og/epoll/Event.o\
				og/epoll/Poll.o
endif

all: options ${LIB}

options:
	@echo libOG build options:
	@echo "CXXFLAGS  = ${CXXFLAGS}"
	@echo "LDFLAGS   = ${LDFLAGS}"
	@echo "CXX       = ${CXX}"
	@echo "AR        = ${AR}"

install:

uninstall:

${LIB}: ${OBJFILES}
	${AR} ${LIB} ${OBJFILES}

.cc.o:
	${CXX} ${CXXFLAGS} -c $< -o ${basename $<}.o

clean:
	rm -f ${OBJFILES} ${LIB}
