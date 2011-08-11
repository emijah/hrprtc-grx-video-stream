#!/opt/grx/bin/hrpsyspy
import sys
sys.path.append('VideoStreamService.jar')
import rtm
import OpenHRP.VideoStreamServiceHelper

vs = rtm.findRTC('VideoStream0')
vs.start()
vs_svc = OpenHRP.VideoStreamServiceHelper.narrow(vs.service('service0'))

## capture 10 times
##vs_svc.capture(10)

## capture coninuous
vs_svc.capture(-1)
import time 
time.sleep(10)
## stop capture
vs_svc.capture(0)
