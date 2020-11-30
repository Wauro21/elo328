from udpReader import listenUDP
from TrackRead import *
from math import sqrt

def minDistance(trackArray, borderIndex, xFinal, zFinal, tolerance):
    xUpper = xFinal + ((tolerance/100)*abs(xFinal))
    xLower = xFinal - ((tolerance/100)*abs(xFinal))
    zUpper = zFinal + ((tolerance/100)*abs(zFinal))
    zLower = zFinal - ((tolerance/100)*abs(zFinal))
    xTrack = trackArray[borderIndex]["x"]
    zTrack = trackArray[borderIndex]["z"]
    size = len(xTrack)
    minDistance = 1000
    for i in range(size):
        if((zTrack[i] <= xUpper) and (zTrack[i] > xLower) and (xTrack[i] <= zUpper) and (xTrack[i] > zLower)):
            aDiff = (zTrack[i] - xFinal)**2
            bDiff = (xTrack[i] - zFinal)**2
            tempDistance = sqrt(aDiff + bDiff)
            minDistance = tempDistance if sqrt(aDiff + bDiff) < minDistance else minDistance
    print(minDistance)
#listenUDP("255.255.255.255", "mainScript")
valoresPista = silverstoneDefault("mainScript")

xFinal = valoresPista[4]["x"][0]
zFinal = valoresPista[4]["z"][0]
print("x: {}    z:{}".format(valoresPista[4]["x"][0], valoresPista[4]["z"][0]))
minDistance(valoresPista, 2, xFinal, zFinal, 10.0)
