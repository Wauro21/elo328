# Actividad 1 - ELO328 - 2020/2

Nombres:

Mauricio Aravena
Diego Badillo
Steev Gonz�lez
Sebasti�n Neira
Felipe Villenas

## Notas

Para una secci�n de 200x200 pixeles, se calcula el promedio de los tiempos
obtenidos por los cinco integrantes.

imagen:
m1 150[us]
m2 2436[us]

video:
m1 164[us]
m2 2861[us]

## Compilaci�n

Use

g++ -o GAMMA Actividad1_ELO328.cpp `pkg-config --cflags --libs opencv4`


## Uso

```C++

Para ejecutar el archivo creado, use

./GAMMA [-m1 | -m2] -v gamma [-f x y w h] [-c r g b]
./GAMMA [-m1 | -m2] -i imagen gamma [-f x y w h] [-c r g b]
	-v:    usar webcam.
	-i:    usar imagen.
	image: Ruta de imagen a procesar.
	gamma: Nivel de Gamma. Debe ser un valor real, mayor que 0.
	-f:    (Optional) Define �rea a la que aplica gamma. Resto es borde.
			  Se define rect �ngulo posicion (x,y) y tama�o w X h.
                          Si no se define, se usa imagen completa.
	-c:    (Optional) Color (r,g,b) del borde. Si no se define,
			  se usa negro.

```
