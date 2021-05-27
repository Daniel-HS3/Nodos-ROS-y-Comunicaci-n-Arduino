#include "ros/ros.h"//librerias
#include "std_msgs/Char.h"//librerias

void chatterCallback(const std_msgs::Char::ConstPtr& msg)//funcion para recibir e imprimir en el terminal la informacion que se esta leyendo.se forza a que se reciba una variable del tipo deseado (para este ejemplo "char")y a que sea una variable de punteros
{
  ROS_INFO("I heard: [%c]", msg->data); //imprime el dato recibido en el terminal
}

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "listener");//se inicializa el nodo utilizando el metodo init de la clase ros, donde se debe colocar el nombre al nodo

  ros::NodeHandle n;//permite comunicarse con elementos externos diferentes a los del presente codigo

  
  ros::Subscriber sub = n.subscribe("char", 1000, chatterCallback);//crea un objeto que se va a suscribir especificando el topic con el que se va a susccribir, la funcion suscribe se comunica con el nodo maestro de ros, el cual a su vez tiene registro de los publicadores y suscriptores, y se encarga de recibir informacion del topic al que esta suscrito mediante una devolucion de llamada a la funcion chatterCallback. se especifica el nombre del topic al que se va a suscribir y el buffer de datos deseado para no perder informacion.

  
  ros::spin();//la funcion Spin() o spinOnce() permite que ros lea, estas funciones revisan si ha llegado un dato al topic donde esta suscrito el nodo y ejecuta la funcion callback si hay algun dato. Spin lo hace constantemente, spinonce lo hace una vez y permite que el programa continue.

  return 0;
}
