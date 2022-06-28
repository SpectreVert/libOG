# libOG - socket & event poll abstractions

include config.mk

LIB=libOG.a
TARGET=libOG

OBJ = og/Internal.o\
	og/Ipv4.o\
	og/Socket.o\
	og/SocketAddr.o\
	og/TcpListener.o\
	og/TcpStream.o\
	og/UdpSocket.o

ifeq (${PLATFORM}, linux)
	OBJ += og/epoll/Event.o og/epoll/Poll.o
endif

all: options ${LIB}

${LIB}: ${OBJ}
	${AR} ${LIB} ${OBJ}

.cc.o:
	${CXX} ${CXXFLAGS} -c $< -o ${basename $<}.o

options:
	@echo libOG build options:
	@echo "CXXFLAGS  = ${CXXFLAGS}"
	@echo "LDFLAGS   = ${LDFLAGS}"
	@echo "CXX       = ${CXX}"
	@echo "AR        = ${AR}"

re: clean all

install:

uninstall:

clean:
	rm -f ${LIB} ${OBJ}
