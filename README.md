# Proyecto Grupo 1 - ELO328 2020.S2
## Sistema de Reconocimiento de Pista de Carreras de F1

### Integrantes
- Mauricio Aravena (Wauro21)
- Diego Badillo (Zimrahin)
- Steev González (steevglez)
- Sebastián Neira (nabway)
- Felipe Villenas (felipeville)
---
## Índice
- [Instalación](#Instalacion)
  * [Instalación en Ubuntu](#instalacion-en-ubuntu)
    + [Pre-requisitos](#prerequisitos)
- [Guía de Uso](#Guia-de-uso)
## 1. Instalación
### 1.1. Instalación en Ubuntu

---

#### 1.1.1. Pre-requisitos
El programa está escrito en el lenguaje de programación **C++**, junto con el uso de librerías de **Qt5** para el desarrollo de la interfaz gráfica. Para el correcto funcionamiento del programa se deben installar las librerías de **Qt5** en el host. Para Ubuntu, se deben ejecutar las siguientes líneas en una terminal:
```
$ sudo apt-get update
$ sudo apt-get install qt5-default
```
Luego, se deberían tener instaladas las librerías requeridas para ejecutar el programa.

#### 1.1.2. Ejecución del Programa
El programa puede ser obtenido en la sección `Releases` del siguiente repositorio de este repositorio. Dentro del `*.zip` descargado se tienen todos los archivos necesarios para el programa. Las librerías de **OpenCV** utilizadas para el procesamiento de imágenes, están incluídas en la carpeta `/lib`. Para correr el programa, se debe ejecutar la siguiente línea en la carpeta raíz del programa:
```
$ ./F1RacingLine.sh
```
Con esto se abrirá la interfaz gráfica del programa y estará listo para ser utilizado.

#### 1.1.3. Dataset
El dataset utilizado para el programa, también puede ser hallado en la sección Releases del repositorio. Dentro de este, están las imágenes, videos, y archivos de telemetría para el correcto funcionamiento del programa.

### 1.2. Instalación desde el Código Fuente

---

#### 1.2.1. Pre-requisito: Qt Creator
De la misma forma que la instalación normal, se deben instalar las librerías de **Qt5** para lograr el funcionamiento del programa:
```
$ sudo apt-get update
$ sudo apt-get install qt5-default
```
Adicionalmente, se debe descargar e instalar el IDE **Qt Creator** para poder *compilar* y ejecutar el programa. Para aquello, se instala de la misma forma desde un terminal con la siguiente línea de código:
```
$ sudo apt install qtcreator
```
La alternativa, es realizar una instalación desde el código fuente el cual puede ser obtenido en el sitio web de Qt.

Luego, con Qt Creator ya instalado es posible poder abrir el archivo `*.pro` contenido en la descarga del código fuente de este programa.

#### 1.2.2. Pre-requisito: OpenCV
Para poder compilar el programa es necesario instalar las librerías de **OpenCV**. Primero, se debe descargar **OpenCV 4.4.0** desde el siguiente [enlace](https://github.com/opencv/opencv/archive/4.4.0.zip). Luego, para instalar OpenCV, se debe seguir los pasos del siguiente [tutorial](https://medium.com/@sb.jaduniv/how-to-install-opencv-4-2-0-with-cuda-10-1-on-ubuntu-20-04-lts-focal-fossa-bdc034109df3).

Luego de completar la instalación, idealmente se debe agregar la ruta de donde están las liberías de OpenCV al **PATH** del sistema, para facilitar el proceso a la hora de incluir las librerías en Qt Creator.

## 2. Guía de Uso
