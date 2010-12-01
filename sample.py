#!/opt/grx/share/hrpsys/jython/hrpsyspy
import sys
import rtm
sys.path.append('VideoStreamService.jar')
import VideoStreamServiceHelper

vs = rtm.findRTC('VideoStream0')
vs.start()
vs_svc = VideoStreamServiceHelper.narrow(vs.service('service0'))

## capture 10 times
##vs_svc.capture(10)

## capture coninuous
vs_svc.capture(-1)
import time 
time.sleep(10)
## stop capture
vs_svc.capture(0)
