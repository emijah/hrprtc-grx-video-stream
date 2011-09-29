#!/opt/grx/bin/hrpsyspy
import sys
sys.path.append('Img.jar')
import rtm
import Img.CameraCaptureServiceHelper

def init():
  global vs_svc
  vs = rtm.findRTC('VideoStream0')
  vs.start()
  vs_svc = Img.CameraCaptureServiceHelper.narrow(vs.service('service0'))

  # if you setup MultiDisp RTC (OpenVGR)
  md = rtm.findRTC('MultiDisp0')
  if md != None:
    rtm.connectPorts(vs.port('MultiCameraImages'), md.port('images'))
    md.start()

def take_one_frame():
  vs_svc.take_one_frame()

if __name__ == '__main__' or __name__ == 'main':
  init()
  take_one_frame()
