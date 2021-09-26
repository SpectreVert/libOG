PREFIX = /usr/local/libOG
#MAPREFIX = ${PREFIX}/share/man

VERSION = 1
PLATFORM = linux
#PLATFORM = bsd

CXXFLAGS  = -I. -std=c++20 -pedantic -Wall -Wextra -g3
CXX       = clang++
AR        = ar rc
