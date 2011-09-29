#!/opt/grx/bin/hrpsyspy
import os
import time
from java.lang import System
from java.awt import *
from javax.swing import *
from guiinfo import *
import math

FILENAME_ROBOTHOST='.robothost'

def createButton(name, func):
    if not func.__class__.__name__ == 'function':
       return None
    exec('def tmpfunc(e): import time; t1=time.time();'+func.__name__+'(); t2=time.time(); print "['+name+']", t2- t1 ,"[sec]"')
    btn = JButton(label=name, actionPerformed = tmpfunc)
    del tmpfunc
    return btn

frm = JFrame("sample GUI for camera", defaultCloseOperation = JFrame.EXIT_ON_CLOSE)
frm.setAlwaysOnTop(True)
pnl = frm.getContentPane()
pnl.layout = BoxLayout(pnl, BoxLayout.Y_AXIS)
pnl.add(JLabel("HOSTNAME of ROBOT"))

if os.path.isfile(FILENAME_ROBOTHOST):
  f = open(FILENAME_ROBOTHOST, "r")
  txt = JTextField(f.readline())
else:
  txt = JTextField("localhost")
pnl.add(txt)

for func in funcList:
  if func.__class__.__name__ == 'str':
    obj = JLabel(func)
  elif func.__class__.__name__ == 'function':
    obj = createButton(func.__name__, func)
  elif func.__class__.__name__ == 'list':
    obj = createButton(func[0], func[1])
  if obj != None:
    pnl.add(obj)

frm.pack()
frm.show()
