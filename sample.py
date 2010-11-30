#!/opt/grx/share/hrpsys/jython/hrpsyspy
import sys
import rtm
sys.path.append('VideoStreamService.jar')
import VideoStreamServiceHelper

vs = rtm.findRTC('VideoStream0')
vs.start()
vs_svc = VideoStreamServiceHelper.narrow(vs.service('service0'))
vs_svc.capture(0)
