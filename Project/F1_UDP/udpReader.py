import socket

print("UDP - Reading")

UDP_IP = "192.168.0.13" #loopback
UDP_PORT = 20777 # Puerto defecto F1 - 2018

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

sock.bind((UDP_IP, UDP_PORT))

while True:
    data, addr = sock.recvfrom(2048)
    print("Recibido: {}",format(data))
