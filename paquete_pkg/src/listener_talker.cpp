#include "ros/ros.h"//librerias
#include "std_msgs/String.h"//librerias
#include "std_msgs/Char.h"//librerias

void chatterCallback(const std_msgs::String::ConstPtr& msg)//funcion para recibir e imprimir en el terminal la informacion que se esta leyendo.se forza a que se reciba una variable del tipo deseado (para este ejemplo "string")y a que sea una variable de punteros
{
  ROS_INFO("I heard: [%s]", msg->data.c_str());//imprime el dato recibido en el terminal
}

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "listener_talker");//se inicializa el nodo utilizando el metodo init de la clase ros, donde se debe colocar el nombre al nodo
  ros::NodeHandle n;//permite comunicarse con elementos externos diferentes a los del presente codigo

  ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);//crea un objeto que se va a suscribir especificando el topic con el que se va a susccribir, la funcion suscribe se comunica con el nodo maestro de ros, el cual a su vez tiene registro de los publicadores y suscriptores, y se encarga de recibir informacion del topic al que esta suscrito mediante una devolucion de llamada a la funcion chatterCallback. se especifica el nombre del topic al que se va a suscribir y el buffer de datos deseado para no perder informacion.

  ros::NodeHandle nn;//permite comunicarse con elementos externos diferentes a los del presente codigo

  ros::Publisher char_pub = nn.advertise<std_msgs::Char>("char", 1000); //crea un objeto que publica el topic con el nombre deseado, la funcion Publisher se comunica con el nodo maestro de ros, el cual a su vez tiene registro de los publicadores y suscriptores, y se encarga de hacer visible el topic para que un nodo pueda suscribirse. se forza a que se publique una variable del tipo deseado (para este ejemplo "char"), se define el nombre del topic y el buffer de datos deseado para no perder informacion.

  ros::Rate loop_rate(1);//se define el periodo de muestreo  

  
  //int count = 0;
  while (ros::ok()) // mientras el nodo este activo va a ejecutar lo que esta dentro del while
  {

    std_msgs::Char msg1;// se crea un objeto del tipo char, el cual va a contener la informacion que se va a publicar

    msg1.data ='e' ;// se escribe el mensaje o la informacion que se va a publicar

    ROS_INFO("%c", msg1.data);//se utiliza para ver en el terminal lo que se está enviando, se utiliza %c porque es un char

    char_pub.publish(msg1);//utilizando el objeto creado de la clase publisher, se publica la informacion que se quiere compartir mediante el metodo llamado "publish" de dicho objeto

    ros::spinOnce();//la funcion Spin() o spinOnce() permite que ros lea, estas funciones revisan si ha llegado un dato al topic donde esta suscrito el nodo y ejecuta la funcion callback si hay algun dato. Spin lo hace constantemente, spinonce lo hace una vez y permite que el programa continue.

    loop_rate.sleep();//espera que se cumpla el tiempo definido anteriormente (periodo de muestreo)
   
    //++count;

  }

  
  

  return 0;
}
