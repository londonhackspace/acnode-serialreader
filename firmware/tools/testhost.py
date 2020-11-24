# Test host for the serial protocol written
# requires pyserial and python3

import serial
import os

port = serial.Serial('/dev/ttyUSB0', 115200, timeout=0)

buff = b""

def calculateChecksum(message):
    s = 0
    for i in range(2,len(message)):
        s = s + message[i]
    return s & 0xff

def type2string(t):
    if t == 0x00:
        return "Error"
    if t == 0x01:
        return "Warning"
    if t == 0x02:
        return "Info"
    if t == 0x03:
        return "Debug"
    return "Unknown"

def handleLogMessage(message):
    level = message[4]
    contextLength = message[5]
    context = message[6:(6+contextLength)].decode('utf8')
    messageLength = message[6+contextLength]
    message = message[(7+contextLength):(7+contextLength+messageLength)].decode('utf8')
    print("[%s] %s - %s" % (type2string(level), context, message))

versioncount = 0

def handleVersionMessage(message):
    global versioncount
    versioncount += 1
    if versioncount > 1:
        print("We already got a version message!")
    major = message[4]
    minor = message[5]
    date_length = message[6]
    hash_length = message[7+date_length]
    date = message[7:(7+date_length)].decode('utf8')
    ghash = message[(8+date_length):(8+date_length+hash_length)].decode('utf8')
    print("Reader version %d.%d (%s) built at %s" % (major, minor, ghash, date))

def handleTemperatureMessage(message):
    intpart = message[4]
    fracpart = message[5]
    value = ((intpart << 8) + fracpart)/256
    print("Temperature is %f" % (value,))

def sendVersionRequest():
    buff = bytearray(b"\xff\xdd\x01\x01\xfe")
    port.write(buff)

def sendTemperatureRequest():
    buff = bytearray(b"\xff\xdd\x03\x01\xfc")
    port.write(buff)


def handleMessage():
    global buff
    while len(buff) >= 2:
        if buff[0] == 0xfd and buff[1] == 0x02:
            print("Got ACK")
            buff = buff[2:]
        elif buff[0] == 0xfd and buff[1] == 0x03:
            print("Got NAK")
            buff = buff[2:]
        elif buff[0] == 0xff and buff[1] == 0xdd:
            if len(buff) < 4:
                # incomplete buffer
                print("Incomplete buffer")
                break
            messagetype = buff[2]
            messagelength = buff[3]
            if len(buff) < 4+messagelength:
                # partial message
                break
            s = calculateChecksum(buff[0:(messagelength+4)])
            if s == 0:
                # send ACK
                port.write(b"\xfd\x02")
                print("Sending ACK")
                if messagetype == 0x82:
                    handleLogMessage(buff)
                elif messagetype == 0x81:
                    handleVersionMessage(buff)
                elif messagetype == 0x83:
                    handleTemperatureMessage(buff)
                elif messagetype == 0xff:
                    print("Unknown message type error received")
                else:
                    print("Unknown message received")
            else:
                print(buff.hex())
                print("Invalid checksum 0x%x (last byte 0x%x- sending NAK" % (s, buff[messagelength+3]))
                port.write(b"\xfd\x03")        
            
            port.flush()
            buff = buff[(4+messagelength):]
        else:
            # remove junk
            buffertext = ""
            for i in range(len(buff)):
                if i != 0:
                    buffertext += " "
                buffertext += "%x" % (buff[i],)
            print("Discarded junk 0x%x - buffer is: %s" % (buff[0],buffertext))
            buff = buff[1:]

import time

port.flush()

# send an ack just in case
port.write(b"\xfd\x02")

sendVersionRequest()
port.flush()
sendTemperatureRequest()
port.flush()

while True:
    port.flush()
    buff = buff + port.read(32)
    handleMessage()
    time.sleep(0.05)
