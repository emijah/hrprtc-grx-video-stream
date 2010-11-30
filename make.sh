#!/bin/sh
export PATH=/opt/grx/bin/:$PATH
export LD_LIBRARY_PATH=/opt/grx/lib:/opt/grx/lib/OpenRTM-aist:$LD_LIBRARY_PATH
make -f Makefile.VideoStream
