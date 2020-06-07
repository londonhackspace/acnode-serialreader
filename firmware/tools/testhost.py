# Test host for the serial protocol written
# requires pyserial and python3

import serial
import os

port = serial.Serial('/dev/ttyACM0', 115200, timeout=0.1)

buff = b""

def calculateChecksum(message):
    s = 0
    print("Checksumming %d bytes" % (len(message),))
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


def handleMessage():
    global buff
    while len(buff) >= 2:
        if buff[0] == 0xfd and buff[1] == 0x02:
            print("Got ACK")
        elif buff[0] == 0xfd and buff[1] == 0x03:
            print("Got NAK")
        elif buff[0] == 0xff and buff[1] == 0xdd:
            if len(buff) < 4:
                # incomplete buffer
                print("Incomplete buffer")
                break
            messagetype = buff[2]
            messagelength = buff[3]
            if len(buff) < 4+messagelength:
                # partial message
                print("Partial message - have %d bytes of %d" % (len(buff), 4+messagelength))
                print(buff.hex())
                break
            print("Got message of type 0x%x" % (messagetype,))
            s = calculateChecksum(buff[0:(messagelength+4)])
            if s == 0:
                print(buff.hex())
                # send ACK
                port.write(b"\xfd\x02")
                if messagetype == 0x82:
                    handleLogMessage(buff)
            else:
                print(buff.hex())
                print("Invalid checksum 0x%x (last byte 0x%x- sending NAK" % (s, buff[messagelength+3]))
                port.write(b"\xfd\x03")        
            
            port.flush()
            buff = buff[(4+messagelength):]
            print("Discarded %d - remaining %d" % (4+messagelength, len(buff)))
        else:
            # remove junk
            print("Discarded junk 0x%x" % (buff[0],))
            buff = buff[1:]


while True:
    port.flush()
    buff = buff + port.read(256)
    handleMessage()
