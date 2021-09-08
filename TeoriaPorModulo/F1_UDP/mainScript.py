from udpReader import listenUDP
from TrackRead import *
from math import sqrt

## DEBUG:
import matplotlib.pyplot as plt

NOTVALID = 100000

def minDistance(trackArray, borderIndex, xFinal, zFinal, tolerance):
    xUpper = xFinal + ((tolerance/100)*abs(xFinal))
    xLower = xFinal - ((tolerance/100)*abs(xFinal))
    zUpper = zFinal + ((tolerance/100)*abs(zFinal))
    zLower = zFinal - ((tolerance/100)*abs(zFinal))
    xTrack = trackArray[borderIndex]["z"]
    zTrack = trackArray[borderIndex]["x"]
    size = len(xTrack)
    minDistance = NOTVALID

    #Almacenar puntos
    xA = NOTVALID
    zA = NOTVALID
    xB = NOTVALID
    zB = NOTVALID
    iA = NOTVALID
    #Almacenar distancias
    dA = NOTVALID
    dB = NOTVALID
    for i in range(size):
        if((xTrack[i] <= xUpper) and (xTrack[i] > xLower) and (zTrack[i] <= zUpper) and (zTrack[i] > zLower)):
            aDiff = (xTrack[i] - xFinal)**2
            bDiff = (zTrack[i] - zFinal)**2
            tempDistance = sqrt(aDiff + bDiff)
            if tempDistance < dA:
                dB = dA
                xB = xA
                zB = zA
                dA = tempDistance
                xA = xTrack[i]
                zA = zTrack[i]
                iA = i
            elif tempDistance < dB:
                dB = tempDistance
                xB = xTrack[i]
                zB = zTrack[i]
    #BORRAR PRINTS
    print("xA: {}, zA: {}, dA: {} \n".format(xA,zA,dA))
    print("xB: {}, zB: {}, dB: {} \n".format(xB,zB,dB))

    #DISTANCIA SUCIA
    dTransversal = NOTVALID
    jFinal = NOTVALID
    for j in range(len(trackArray[2]["x"])):
        D1 = (trackArray[1]["x"][iA]  -trackArray[2]["x"][j])**2
        D2 = (trackArray[1]["z"][iA]  -trackArray[2]["z"][j])**2
        if (D1+D2) < dTransversal:
            dTransversal = D1+D2
            jFinal = j

    DT = sqrt(dTransversal)
    print("Distancia transversal {} \n".format(DT))
    # FIN PRINTS

    #Distancia punto a recta:
    m = (zB - zA)/(xB - xA)
    b = zB - (xB*m)
    dNumerador = abs(m*xFinal - zFinal + b)
    dDenominador = sqrt((m**2) + 1)
    dFinal = dNumerador/dDenominador
    print("m:{}, b:{}, dNumerador:{}, dDenominador: {}, dFinal {}".format(m,b,dNumerador, dDenominador, dFinal))




#listenUDP("255.255.255.255", "test4")
valoresPista = silverstoneDefault("test3")

xFinal = valoresPista[4]["x"][-1]
zFinal = valoresPista[4]["z"][-1]
print("x: {}    z:{}".format(valoresPista[4]["x"][-1], valoresPista[4]["z"][-1]))
minDistance(valoresPista, 2, xFinal, zFinal, 10.0)
