import serial
import os
import serial.tools.list_ports
import sys
from PIL import Image

#####################################################
# connect to serial port
#####################################################
if os.name == 'posix':
    ser = serial.Serial('/dev/ttyUSB0')
elif os.name == 'nt':
    print("choose device index:")
    comlist = serial.tools.list_ports.comports()
    for i, elem in enumerate(comlist):
        print(str(i) + ":" + elem.device)
        sys.stdout.flush()
    idx = int(input())
    ser = serial.Serial(comlist[idx].device, 230400)

#####################################################
# port config
#####################################################
ser.baudrate = 230400
ser.bytesize = 8
ser.parity = 'N'
print(
    "open " + ser.name + "\nbaud: " + str(ser.baudrate) + "\ndata format:" + str(ser.bytesize) + str(ser.parity) + str(
        ser.stopbits))

#####################################################
# prepare file
#####################################################

#####################################################
# pic format config
#####################################################
picSize160x120 = 38400
picSize320x240 = 153600
picSize = picSize320x240

raw_img_postfix = ".raw"
data_buffer = []

print("Enter number of frame, you want to convert: ")
num_pics = int(input())

for i in range(0, num_pics):
    #####################################################
    # get data from uart-usb
    #####################################################
    print("reading data...")
    picData = []
    for pixel in range(picSize):
        bit = ser.read()
        print('\n ' + str(pixel))
        picData.append(bit)
    data_buffer.append(picData)

    print('\n' + 'Total size: ' + str(len(picData)) + ' bytes')

count = 0
for data in data_buffer:
    fileName = "image"
    count += 1;
    fileName = fileName + str(count) + raw_img_postfix
    fileRaw = open(fileName, "wb+")
    for bit in data:
        fileRaw.write(bit)
    fileRaw.close()

#####################################################
# convert raw data
#####################################################
# require: installed imagemagick

# print ("Enter number of frame, you want to convert: ")
# num_pics = int(input())

command = "convert"
raw_img_postfix = ".raw"
bmp_img_postfix = ".bmp"
fileName = "image"
outputName = "image_out"

flag160x120 = "160x120"
flag320x240 = "320x240"

flagsize = flag320x240

flags = ["-size " + flagsize, "-sampling-factor 4:2:2", "-depth 8"]
for i in range(0, num_pics):
    inputfile = "yuv:" + fileName + str(i + 1) + raw_img_postfix
    outputFile = outputName + str(i + 1) + bmp_img_postfix

    os.system(command + " " + ' '.join(flags) + " " + inputfile + " " + outputFile)
    print(inputfile + " => " + outputFile + " \n")
    #####################################################
    # Image open
    #####################################################
    img = Image.open(outputFile)
    img.show()
