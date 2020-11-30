import socket
import ctypes
import sys
#Variables globales

headerSize = 21 # en bytes
mPacketSize = 60 # en bytes
#Clase para el desempaquetado del Header usando ctypes, littleEndian
class packetHeader(ctypes.LittleEndianStructure):
    _pack_ = 1
    _fields_ = [    ("m_packetFormat",ctypes.c_uint,16),
                    ("m_packetVersion",ctypes.c_uint8,8),
                    ("m_packetId",ctypes.c_uint8,8),
                    ("m_sessionUID",ctypes.c_uint64,64),
                    ("m_sessionTime",ctypes.c_float),
                    ("m_frameIdentifier",ctypes.c_uint32,32),
                    ("m_playerCarIndex",ctypes.c_uint8,8),
    ]

#Clase para el desempaquetado del motionPacket usando ctypes, littleEndian
class motionPacket(ctypes.LittleEndianStructure):
    _pack_ = 1
    _fields_ = [    ("m_worldPositionX", ctypes.c_float),
                    ("m_worldPositionY", ctypes.c_float),
                    ("m_worldPositionZ", ctypes.c_float),

    ]

#Funcion escucha puerto 20777
def listenUDP(ip, outFile):
    if(len(outFile) == 0 ):
        outFile = "hamilton"
    file = open(outFile+".csv", "w")
    UDP_IP = ip
    UDP_PORT = 20777
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind((UDP_IP, UDP_PORT))
    print("UDP - Reading")
    file.write("UDP - Reading \n")
    while True:
        try:
            data, addr = sock.recvfrom(2048)
            if(len(data) == 1341): #Tamano motion packet
                damn = packetHeader.from_buffer_copy(data[0:headerSize+1])
                damn_2 = motionPacket.from_buffer_copy(data[headerSize:mPacketSize+1])
                print("{},{},{}".format(damn_2.m_worldPositionX,damn_2.m_worldPositionY,damn_2.m_worldPositionZ))
                file.write("{},{},{} \n".format(damn_2.m_worldPositionX,damn_2.m_worldPositionY,damn_2.m_worldPositionZ))
        except KeyboardInterrupt:
            break
    sock.close()
    file.close()

#listenUDP("255.255.255.255","")
