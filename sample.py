#!/opt/grx/bin/hrpsyspy
import sys
sys.path.append('Img.jar')
import rtm
import Img.CameraCaptureServiceHelper

vs = rtm.findRTC('VideoStream0')
vs.start()
vs_svc = Img.CameraCaptureServiceHelper.narrow(vs.service('service0'))

vs_svc.take_one_frame()
