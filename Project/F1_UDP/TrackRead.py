import matplotlib.pyplot as plt

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

#innerBoundaries = getValuesTrack("silverstone_2020_inner_boundaries")
centerline = getValuesTrack("silverstone_2020_centerline")
innerLimit = getValuesTrack("silverstone_2020_innerlimit")
outerLimit = getValuesTrack("silverstone_2020_outerlimit")
racingLine = getValuesTrack("silverstone_2020_racingline")
plt.plot(centerline["x"],centerline["z"])
#plt.plot(innerBoundaries["x"],innerBoundaries["z"])
plt.plot(innerLimit["x"],innerLimit["z"])
plt.plot(outerLimit["x"],outerLimit["z"])
plt.plot(racingLine["x"],racingLine["z"])
plt.show()
