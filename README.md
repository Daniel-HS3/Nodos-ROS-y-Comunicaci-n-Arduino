# Nodos-ROS-y-Comunicaci-n-Arduino
==============

## Introducción

*Este proyecto consiste en el control de un servomotor en función de 3 datos (un booleano, un entero y un flotante) de entrada que son enviados por el arduino a través de 3 tópics diferentes y siendo estos recibidos por los nodos de ROS creados que se encargarán de procesar esta información con un control difuso y un árbol de decisión, por lo que habrán ciertas funciones de pertenencia para definir cuál es el porcentaje de pertenencia de los datos una clase (alto, medio, bajo); Dependiendo de las clases a las que pertenezcan los 3 datos, se envía un cierto valor de grados al arduino y que asía sea controlado el servo*

![alt text](https://github.com/Daniel-HS3/Nodos-ROS-y-Comunicaci-n-Arduino/blob/dcf73b7f1c697c23026679bbdcc199a3630fa927/Im%C3%A1genes%20-%20Nodos%20ROS/Diagrama%20nodos.jpeg)

*-------------------------------------------------------------------------------------------------------------------------------------------------------*

## Nodos

**NODO "talker_3d.cpp":**
*Este nodo se encarga de recibir los tres datos del arduino (bool, int, float) por tres diferentes topics y volverlos a enviar por un topic diferente cada uno para que el nodo al que corresponda cada uno lo reciba.*

**NODO "listener_talker_bool.cpp":**
*Este nodo se encarga de recibir el dato booleano que es publicado por el nodo "talker_3d.cpp"; si el dato recibido es "true" publicará en un topic que este tiene un porcentaje de pertenencia de 100% para alto, por el contrario si el dato es "false" publicará en el topic que este tiene un porcentaje de pertenencia de 100% para bajo*

**NODO "listener_talker_int.cpp":**
*Este nodo se encarga de recibir el dato entero que es publicado por el nodo "talker_3d.cpp"; Define su valor de pertenencia a cada una de ellas y publica el resultado en un topic diferente*

**NODO "listener_talker_float.cpp":**
*Este nodo se encarga de recibir el dato flotante que es publicado por el nodo "talker_3d.cpp"; Define su valor de pertenencia a cada una de ellas y publica el resultado en un topic diferente*

![alt text](https://github.com/Daniel-HS3/Nodos-ROS-y-Comunicaci-n-Arduino/blob/7ae80b332ae113597b6aa1a5be279ba060d403b4/Im%C3%A1genes%20-%20Nodos%20ROS/Funciones%20de%20pertenencia%20-%20Nodos%20ROS.jpeg)

*--------------------------------*

***Nota:** para los tres nodos anteriores los topics en los que estos publican, están enviando cadenas con el porcentaje de pertenencia a cada clase (bajo, medio, alto), por ejemplo: "A100%/M0%/B0%" (La cadena enviada por el nodo "listener_talker_bool.cpp" Siempre tendrá el porcentaje de la clase "medio" en 0% debido a que el dato que este analiza es el booleano)*

*--------------------------------*

**NODO "listener_talker_char_1.cpp":**
*Este nodo se encarga de recibir la cadena que viene del nodo "listener_talker_bool.cpp", separa la misma y según el porcentaje de pertenencia (si para una clase es mayor a 50% se dice que pertenece a esa clase) asigna una letra que representa a la clase a la cual pertenece (B-A -> bajo-alto), esta letra se publica como un caracter en un topic*

**NODO "listener_talker_char_2.cpp":**
*Este nodo se encarga de recibir la cadena que viene del nodo "listener_talker_int.cpp", separa la misma y según el porcentaje de pertenencia (si para una clase es mayor a 50% se dice que pertenece a esa clase) asigna una letra que representa a la clase a la cual pertenece (B-M-A -> bajo-medio-alto), esta letra se publica como un caracter en un topic*

**NODO "listener_talker_char_3.cpp":**
*Este nodo se encarga de recibir la cadena que viene del nodo "listener_talker_float.cpp", separa la misma y según el porcentaje de pertenencia (si para una clase es mayor a 50% se dice que pertenece a esa clase) asigna una letra que representa a la clase a la cual pertenece (B-M-A -> bajo-medio-alto), esta letra se publica como un caracter en un topic*

**NODO "listener_char_123.cpp":**
*Este nodo se encarga de recibir los caracteres que publican los tres nodos anteriores y dependiento de los caracteres que lleguen, mediante un arbol de decisiones se le asigna un valor de 0° a 180° a la variable que se va a publicar (la cual corresponde a los grados que se le envian a un servomotor). Este nodo se comunica con el arduino para enviar la informacion procesada (grados del servo)*

![alt text](https://github.com/Daniel-HS3/Nodos-ROS-y-Comunicaci-n-Arduino/blob/7ae80b332ae113597b6aa1a5be279ba060d403b4/Im%C3%A1genes%20-%20Nodos%20ROS/%C3%81rbol%20de%20decisi%C3%B3n%20-%20Nodos%20ROS.jpeg)

**NODO "serial_node.py" (nodo arduino):**
*Este nodo corresponde al nodo de arduino, el cual se implementa descargando la biblioteca rosserial de arduino. En el código de arduino se coloca a que topics se va a suscribir y se definen los topics que van a publicar; el nodo de arduino se encarga de tomar los datos boleano, entero y flotante de un interruptor y dos potenciomentros. Igualmente el nodo de arduino recibe un valor entero del topic publicador del nodo "listener_char_123.cpp", el cual contiene la informacion de los grados a los que se va a llevar el servomotor*

*-------------------------------------------------------------------------------------------------------------------------------------------------------*

## Implementación

*--------------------------------*

### Para el nodo de arduino:

<https://biorobotics.fi-p.unam.mx/wp-content/uploads/Courses/contrucci%C3%B3n_de_robots_moviles/2017-1/practicas/prac03.pdf>

*--------------------------------*

### Descargar Paquete:

*1. El paquete debe descargarse dentro de un workspace; por ejemplo: "/home/workspace/src/paquete_pkg"*

*2. Utilizando el terminal se abre el archivo ".bashrc" y se agrega el workspace:*

```
$ cd # nos dirigimos a home

$ sudo gedit .bashrc # con esto abrimos el archivo ".bashrc" para editarlo
```

- *Al final del archivo .bashrc agregamos la siguiente linea:*

```
source ~/workspace/devel/setup.bash
```

- *luego en una ventana de terminal ubicados en "/home" nos dirigimos al workspace y compilamos:*

```
$ cd workspace # "workspace" hace referencia al nombre del mismo

$ catkin_make
```
*--------------------------------*

### Ejecución:

1. *En una ventana del terminal inicializamos roscore:*

```
$ roscore
```

2. *Con el arduino conectado al computador y habiendo identificado el puerto al que se ha conectado, se ejecuta el nodo de arduino:*

```
$ rosrun rosserial_python serial_node.py /dev/ttyACM0
```

3. *Se ejecuta cada uno de los 8 nodos de Ros en una ventana de terminal diferente:*

```
$ rosrun paquete_pkg talker_3d
$ rosrun paquete_pkg listener_talker_bool
$ rosrun paquete_pkg listener_talker_int
$ rosrun paquete_pkg listener_talker_float
$ rosrun paquete_pkg listener_talker_char_1
$ rosrun paquete_pkg listener_talker_char_2
$ rosrun paquete_pkg listener_talker_char_3
$ rosrun paquete_pkg listener_char_123
```

4. *Habiendo realizado los pasos anteriores podremos ver las conexiones de los nodos ejecutando la siguiente instrucción en otra ventana del terminal:*

```
$ rosrun rqt_graph rqt_graph
```
![alt text](https://github.com/Daniel-HS3/Nodos-ROS-y-Comunicaci-n-Arduino/blob/6916df171dca74fa7c2649ea116cec093d246964/Im%C3%A1genes%20-%20Nodos%20ROS/rqt_graph.jpeg)

*--------------------------------*

**Autores**

*Elian Andrés Díaz Vargas*

*Camilo Andrés Sosa Gutierrez*

*Daniel Alberto Cruz Porras*
