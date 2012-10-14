# ccconf copyfile CXXFLAGS=-g -std=c++11
CXXFLAGS = -g -std=c++11  

.PHONY : all clean
all : copyfile
clean :
	rm -f copyfile example.o tags

tags : *.h example.cc 
	ctags *.h example.cc 

copyfile : example.o
	${CXX} ${LDFLAGS} -o copyfile example.o
example.o: example.cc defer.h
