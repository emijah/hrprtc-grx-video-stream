target:all
camera.o:camera.cpp
	g++ -c camera.cpp -I. `pkg-config --cflags opencv`

include Makefile.VideoStream

LDFLAGS+= `pkg-config --libs opencv`
OBJS+=camera.o

VideoStreamService.jar:
	idlj -fclient -fserver -emitAll -td src -I /opt/grx/include/rtm/idl/  VideoStreamService.idl
	javac src/*.java
	jar cvf VideoStreamService.jar src/*.class -C src
