#!/opt/grx/bin/hrpsyspy
import sys
sys.path.append('Img.jar')
import rtm
import Img.CameraCaptureServiceHelper

def init():
  global vs_svc, vs_port, md_port
  vs = rtm.findRTC('VideoStream0')
  vs.start()
  vs_svc = Img.CameraCaptureServiceHelper.narrow(vs.service('service0'))
  vs_port = vs.port('MultiCameraImages')

  # if you setup MultiDisp RTC (OpenVGR)
  md = rtm.findRTC('MultiDisp0')
  if md != None:
    md_port = md.port('images')
    #rtm.connectPorts(vs_port, md_port)
    md.start()

def take_one_frame():
  vs_svc.take_one_frame()
  dat = rtm.readDataPort(vs_port, classname='Img.TimedMultiCameraImageHolder')
  print dat.data
  if md_port != None:
    rtm.writeDataPort(md_port, dat)

if __name__ == '__main__' or __name__ == 'main':
  init()
  take_one_frame()
