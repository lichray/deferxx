# ccconf example CXXFLAGS=-g -std=c++11
CXXFLAGS = -g -std=c++11  

.PHONY : all clean
all : example
clean :
	rm -f example example.o tags

tags : *.h example.cc 
	ctags *.h example.cc 

example : example.o
	${CXX} ${LDFLAGS} -o example example.o
example.o: example.cc defer.h
