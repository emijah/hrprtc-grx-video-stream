target:all
camera.o:camera.cpp
	g++ -c camera.cpp -I. `pkg-config --cflags opencv`

include Makefile.VideoStream

OBJS+=camera.o

VideoStreamService.jar:
	idlj -I /opt/grx/include/rtm/idl/  VideoStreamService.idl
	javac *.java
	jar cvf VideoStreamService.jar *.class
