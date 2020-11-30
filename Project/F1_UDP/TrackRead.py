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

def plotFromArray(trackArray, raceValues, realTimeFlag, raceLineFlag):
    #Reading the data
    centerline = getValuesTrack(trackArray[0])
    innerLimit = getValuesTrack(trackArray[1])
    outerLimit = getValuesTrack(trackArray[2])
    raceLine = getValuesTrack(trackArray[3])
    if(len(raceValues) != 0):
        racingLine = getRaceValues(raceValues)
        plt.plot(racingLine["z"],racingLine["x"], 'r--', label = "Línea carrera")
    #Plotting the track
    plt.plot(centerline["x"],centerline["z"],'k-', label = "Línea central")
    plt.plot(innerLimit["x"],innerLimit["z"],'b-', label = "Límite interno")
    plt.plot(outerLimit["x"],outerLimit["z"], 'g-', label = 'Límite externo')
    #Plotting the raceLine
    if(raceLineFlag):
        plt.plot(raceLine["x"],raceLine["z"],'m-', label = "Línea Carrera")
    plt.legend()
    plt.show()
    retArray = [centerline, innerLimit, outerLimit, raceLine, racingLine] if (len(raceValues)!=0) else [centerline, innerLimit, outerLimit, raceLine]
    return retArray
def silverstoneDefault(raceValues):
    trackArray = ["silverstone_2020_centerline","silverstone_2020_innerlimit", "silverstone_2020_outerlimit","silverstone_2020_racingline"]
    return plotFromArray(trackArray, raceValues, 0,1)
