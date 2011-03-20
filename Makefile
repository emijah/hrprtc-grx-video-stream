target:camera.o all

include Makefile.VideoStream

LDFLAGS+= `pkg-config --libs opencv` -lueye_api
#WEBCAM
#LDFLAGS+= `pkg-config --libs opencv`
OBJS+=camera.o

camera.o:camera.cpp
	g++ -c $< -I. `pkg-config --cflags opencv` -D__LINUX__
#	g++ -c $< -I. -I/usr/include/ -D__LINUX__

VideoStreamService.jar:
	mkdir -p java/bin
	idlj -fclient -fserver -emitAll -td java/src -I /opt/grx/include/rtm/idl/  VideoStreamService.idl
	javac -d java/bin/ -sourcepath java/src java/src/*.java
	jar cvf VideoStreamService.jar -C java/bin/ .
