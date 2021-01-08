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
- [Instalación](#1-instalación)
  * [Instalación desde Código Fuente](#11-instalación-desde-el-código-fuente)
    + [Pre-requisito: Qt Creator](#111-pre-requisito-qt-creator)
    + [Pre-requisito: OpenCV](#112-pre-requisito-opencv)
    + [Compilación y Ejecución](#113-compilación-y-ejecución)
    + [Dataset](#114-dataset)
- [Guía de Uso](#2-guía-de-uso)
## 1. Instalación

### 1.1. Instalación (Linux)

---

#### 1.1.1. Pre-requisito: Qt Creator
El programa está escrito en el lenguaje de programación **C++**, junto con el uso de librerías de **Qt5** para el desarrollo de la interfaz gráfica. Para el correcto funcionamiento del programa se deben installar las librerías de **Qt5** en el host. Para Ubuntu, se deben ejecutar las siguientes líneas en una terminal:
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

#### 1.1.2. Pre-requisito: OpenCV
Para poder compilar el programa es necesario instalar las librerías de **OpenCV**. Primero, se debe descargar **OpenCV 4.4.0** desde el siguiente [enlace](https://github.com/opencv/opencv/archive/4.4.0.zip). Luego, para instalar OpenCV, se debe seguir los pasos del siguiente [tutorial](https://medium.com/@sb.jaduniv/how-to-install-opencv-4-2-0-with-cuda-10-1-on-ubuntu-20-04-lts-focal-fossa-bdc034109df3).

Luego de completar la instalación, idealmente se debe agregar la ruta de donde están las liberías de OpenCV al **PATH** del sistema, para facilitar el proceso a la hora de incluir las librerías en Qt Creator.

#### 1.1.3. Compilación y Ejecución
El programa está ubicado en la sección [Releases](https://github.com/Wauro21/elo328/releases/tag/v0.1-alpha) del repositorio. Para compilar y ejecutar el programa, se debe abrir el archivo `*.pro` incluido en la descarga con Qt Creator. En el archivo `*.pro`, se debe cerciorarse que la variable `INCLUDEPATH` tenga la ruta correcta de donde se encuentran los *headers* de OpenCV. 

Luego, en la siguiente figura se muestra como compilar y ejecutar el programa dentro del IDE.
<details>
 <summary>Imagen</summary>
 
  ![Vista de interfaz del IDE Qt Creator](/Project/zImagenesDoc/qt_run.png)
</details>

#### 1.1.4. Dataset
Dentro de los archivos del release vienen incluídas las imágenes y video de prueba, junto con los respectivos archivos de telemetría en formato `*.csv` y `*.txt`. Las imágenes de prueba están enumeradas del 0 hacia adelante, y también se incluyen sus respectivas versiones con la línea de carrera mostrada dentro del videojuego para realizar comparaciones con el funcionamiento del algoritmo de procesamiento. Dichos archivos con la línea tienen una `w` después del número. Los archivos de telemetría correspondientes poseen el mismo número de la imagen a la cual le corresponden, por ejemplo, imagen `0.jpg` y su archivo de telemetría `0.csv`. En el caso del video de prueba, este se llama `redbull.mp4` y su archivo de telemetría `redbull.txt`.

---

## 2. Guía de Uso
