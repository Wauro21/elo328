import matplotlib.pyplot as plt

#Funcion para obtener puntos x, y, z a partir de archivo .track
def getValuesTrack(name):
    #almacenar la pista
    x = []
    y = []
    z = []
    file = open("silverstone/" + name + ".track", "r")
    retDict = dict()
    #Saltar primeras dos lineas
    next(file)
    next(file)
    #Extraer valores desde archivo
    for i in file:
        i = i.strip().split(",")
        z.append(float(i[1]))
        x.append(float(i[2]))
        y.append(float(i[3]))
    retDict["x"] = x
    retDict["y"] = y
    retDict["z"] = z
    file.close()
    return retDict

def getRaceValues(name):
    x = []
    y = []
    z = []
    file = open(name+".csv", "r")
    retDict = dict()
    next(file)
    #Extraer valores desde archivo
    for i in file:
        i = i.strip().split(",")
        x.append(float(i[0]))
        y.append(float(i[1]))
        z.append(float(i[2]))
    retDict["x"] = x
    retDict["y"] = y
    retDict["z"] = z
    file.close()
    return retDict


#innerBoundaries = getValuesTrack("silverstone_2020_inner_boundaries")
centerline = getValuesTrack("silverstone_2020_centerline")
innerLimit = getValuesTrack("silverstone_2020_innerlimit")
outerLimit = getValuesTrack("silverstone_2020_outerlimit")
racingLine = getValuesTrack("silverstone_2020_racingline")
#plt.plot(centerline["z"],centerline["x"],'k-', label = "Línea central")
#plt.plot(innerBoundaries["x"],innerBoundaries["z"])
plt.plot(innerLimit["z"],innerLimit["x"],'b-', label = "Límite interno")
plt.plot(outerLimit["z"],outerLimit["x"], 'g-', label = 'Límite externo')
#plt.plot(racingLine["z"],racingLine["x"], 'r--', label = "Línea carrera")

#Prueba de concepto
testRace = getRaceValues("testing")
plt.plot(testRace["x"],testRace["z"],'m--', label = "Testing")

plt.legend()
plt.show()
