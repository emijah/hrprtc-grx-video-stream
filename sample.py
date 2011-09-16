#!/opt/grx/bin/hrpsyspy
import sys
sys.path.append('Img.jar')
import rtm
import Img.CameraCaptureServiceHelper

vs = rtm.findRTC('VideoStream0')
vs.start()
vs_svc = Img.CameraCaptureServiceHelper.narrow(vs.service('service0'))

## capture coninuous
vs_svc.take_one_frame()
#import time 
#time.sleep(10)
## stop capture
#vs_svc.capture(0)
