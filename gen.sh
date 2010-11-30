#!/bin/sh
export RTM_ROOT="/opt/grx"
export PATH=/opt/grx/bin/:$PATH
export LD_LIBRARY_PATH=/opt/grx/lib:/opt/grx/lib/OpenRTM-aist:$LD_LIBRARY_PATH
/opt/grx/bin/rtc-template -bcxx \
    --module-name=VideoStream \
	--module-type='SequenceInComponent' \
    --module-desc='Sequence InPort component' \
    --module-version=1.0 \
	--module-vendor='General Robotix,Inc.' \
    --module-category=example \
    --module-comp-type=DataFlowComponent \
	--module-act-type=SPORADIC \
    --module-max-inst=1 \
    --outport=DoubleSeq:MultiCameraImages \
    --service=VideoStreamService:service0:VideoStreamService \
    --service-idl=VideoStreamService.idl
