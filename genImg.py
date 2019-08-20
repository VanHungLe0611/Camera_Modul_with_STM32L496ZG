import serial
import os
import serial.tools.list_ports
import sys
from PIL import Image

#####################################################
# connect to serial port
#####################################################
if os.name=='posix':
    ser = serial.Serial('/dev/ttyUSB0')
elif os.name=='nt':
    print("choose device index:")
    comlist = serial.tools.list_ports.comports()
    for i, elem in enumerate(comlist):
        print(str(i) + ":" + elem.device)
        sys.stdout.flush()
    idx = int(input())
    ser = serial.Serial(comlist[idx].device, 115200)

#####################################################
# port config
#####################################################
ser.baudrate=115200
ser.bytesize=8
ser.parity='N'
print("open " + ser.name + "\nbaud: " + str(ser.baudrate) + "\ndata format:" + str(ser.bytesize) + str(ser.parity) + str(ser.stopbits))


#####################################################
# prepare file
#####################################################
fileName="image.raw"
fileRaw=open(fileName,"wb+")

#####################################################
# pic format config 
#####################################################
picSize160x120=38400
picSize = picSize160x120


#####################################################
# get data from uart-usb
#####################################################
print("reading data...")
for pixel in range(picSize):
    test = ser.read()
    fileRaw.write(test)

fileRaw.close()
print('\n'+'Total size: '+str(pixel+1) + ' bytes')


#####################################################
# convert raw data
#####################################################
# require: installed imagemagick
command = "convert"
flags = ["-size 160x120", "-sampling-factor 4:2:2", "-depth 8"]
inputFormat = "yuv:" + fileName
outputFile = "image_out.bmp"

os.system(command + " " + ' '.join(flags)+ " " + inputFormat + " " + outputFile)

#####################################################
# Image open
#####################################################
img = Image.open('image_out.bmp')
img.show()

