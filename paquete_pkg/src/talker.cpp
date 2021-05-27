#include "ros/ros.h"// librerias
#include "std_msgs/String.h"// librerias

#include <sstream>// librerias


int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "talker"); //se inicializa el nodo utilizando el metodo init de la clase ros, donde se debe colocar el nombre al nodo
  
  ros::NodeHandle n; //permite comunicarse con elementos externos diferentes a los del presente codigo 

  
  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);//crea un objeto que publica el topic con el nombre deseado, la funcion Publisher se comunica con el nodo maestro de ros, el cual a su vez tiene registro de los publicadores y suscriptores, y se encarga de hacer visible el topic para que un nodo pueda suscribirse. se forza a que se publique una variable del tipo deseado (para este ejemplo "string"), se define el nombre dl topic y el buffer de datos deseado para no perder informacion.

  ros::Rate loop_rate(10); //se define el periodo de muestreo  

  
  
  while (ros::ok())// mientras el nodo este activo va a ejecutar lo que esta dentro del while
  {
    
    std_msgs::String msg;// se crea un objeto del tipo String, el cual va a contener la informacion que se va a publicar

    
    msg.data= "Prueba";// se escribe el mensaje o la informacion que se va a publicar
    ROS_INFO("%s", msg.data.c_str());//se utiliza para ver en el terminal lo que se está enviando, se utiliza %s porque es un string. la funcion c_str() regresa un puntero de clase c-style de la cadena invocada.

   
    chatter_pub.publish(msg);//utilizando el objeto creado de la clase publisher, se publica la informacion que se quiere compartir mediante el metodo llamado "publish" de dicho objeto

   
    loop_rate.sleep(); //espera que se cumpla el tiempo definido anteriormente (periodo de muestreo)
   
  }


  return 0;
}
