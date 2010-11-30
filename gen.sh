#!/bin/sh
export RTM_PATH=/opt/grx
export PATH=$RTM_PATH/bin/:$PATH
export LD_LIBRARY_PATH=$RTM_PATH/lib:$RTM_PATH/lib/OpenRTM-aist:$LD_LIBRARY_PATH
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
    --outport=MultiCameraImages:MultiCameraImages \
    --service=VideoStreamService:service0:VideoStreamService \
    --service-idl=VideoStreamService.idl
