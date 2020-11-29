import socket

print("UDP - Reading")

UDP_IP = "255.255.255.255" #loopback
UDP_PORT = 20777 # Puerto defecto F1 - 2018

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

sock.bind((UDP_IP, UDP_PORT))


# 1) Seleccionar packet UDP de interes:
# 2) Desempaquetar información importante
# 3) Guardar la información en un archivo .csv (Verificar)
# 4) Forma de terminar la lectura UDP de forma sana

# Llega el LSB primero, de todo numero

while True:
    data, addr = sock.recvfrom(2048)
    if(len(data) == 1341): #Tamaño motion packet
        #print("Recibido: {!r}",format(data))
        print(data[0:2])
