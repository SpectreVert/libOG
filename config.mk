PREFIX = /usr/local/libOG
#MAPREFIX = ${PREFIX}/share/man

VERSION = 1
PLATFORM = linux
#PLATFORM = bsd

CXXFLAGS  = -I. -std=c++14 -pedantic -Wall -Wextra -O3
CXX       = clang++
AR        = ar rc
