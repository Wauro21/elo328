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

print("UDP - Reading")

UDP_IP = "255.255.255.255" #loopback
UDP_PORT = 20777 # Puerto defecto F1 - 2018

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

sock.bind((UDP_IP, UDP_PORT))


# 1) Seleccionar packet UDP de interes:
# 2) Desempaquetar informacion importante
# 3) Guardar la informacion en un archivo .csv (Verificar)
# 4) Forma de terminar la lectura UDP de forma sana

# Llega el LSB primero, de todo numero

while True:
    data, addr = sock.recvfrom(2048)
    if(len(data) == 1341): #Tamano motion packet
        damn = packetHeader.from_buffer_copy(data[0:headerSize+1])
        damn_2 = motionPacket.from_buffer_copy(data[headerSize:mPacketSize+1])
        print("{},{},{}".format(damn_2.m_worldPositionX,damn_2.m_worldPositionY,damn_2.m_worldPositionZ))
