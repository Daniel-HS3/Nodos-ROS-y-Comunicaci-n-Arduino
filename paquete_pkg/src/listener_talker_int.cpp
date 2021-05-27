#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Int16.h"
#include <sstream>



//------------------------------------------------------------
//variable globales
std_msgs::Int16 msgr_int;     //variable que toma el valor recibido
std_msgs::String msgs_string; // variable a enviar
std_msgs::Int16 v_alto;       // variable porcentaje alto
std_msgs::Int16 v_medio;      // variable porcentaje medio
std_msgs::Int16 v_bajo;       // variable porcentaje bajo
//-------------------------------------------------------------


void chatterCallback_int(const std_msgs::Int16::ConstPtr& msg_int)//funcion recepcion dato int
{
  ROS_INFO("I heard: [%i]", msg_int->data); // ver informacion en el terminal
  msgr_int.data=msg_int->data;              // almacenar el dato recibido

//--------------------------------------------------------------------------------------------
// evaluar el dato recibido en las funciones de pertenencia (Alto, medio, bajo)
  if(msgr_int.data<=250)
   {
     v_alto.data=0;
     v_medio.data=0;
     v_bajo.data=100;
   }
  if(msgr_int.data>250 && msgr_int.data<=500)
    {
     v_alto.data=0;
     v_medio.data=0.4*(msgr_int.data)-100;
     v_bajo.data=-0.4*(msgr_int.data)+200;
   }
  if(msgr_int.data>500 && msgr_int.data<=750)
    {
     v_alto.data=0.4*(msgr_int.data)-200;
     v_medio.data=-0.4*(msgr_int.data)+300;
     v_bajo.data=0;
   }
  if(msgr_int.data>750 && msgr_int.data<=1000)
    {
     v_alto.data=100;
     v_medio.data=0;
     v_bajo.data=0;
   }
//-------------------------------------------------------------------------------------------
}

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "listener_talker_int"); //inicializacion del nodo C
  ros::NodeHandle n;
//-------------------------------------------------------------------------------------------
//el nodo C se suscribe al topic "d_int" del nodo A
  ros::Subscriber int_sub = n.subscribe("d_int", 1000, chatterCallback_int);
//-------------------------------------------------------------------------------------------
//publica el topic "string_int" que contiene el porcentaje de pertenencia a cada funcion 
//(Alto, medio, bajo) 
  ros::Publisher string_pub = n.advertise<std_msgs::String>("string_int", 1000); 
//-------------------------------------------------------------------------------------------
 
 ros::Rate loop_rate(1);
  
  while (ros::ok()) //el while se ejecuta mientras el nodo esta en linea
  {

//-------------------------------------------------------------------------------------------
// concatenacion de la cadena con la informacion de la pertenencia a cada funcion (alto, medio, bajo)
    std::stringstream ss;
    ss <<"A" << v_alto.data << "%/M" << v_medio.data << "%/B" << v_bajo.data << "%"  ;
    msgs_string.data = ss.str();
//-------------------------------------------------------------------------------------------
    ROS_INFO("%s", msgs_string.data.c_str()); //ver informacion en el terminal

    string_pub.publish(msgs_string); //publicar la cadena que contiene el porcentaje de pertenencia

    ros::spinOnce(); //verificar si hay datos nuevos en los topics suscritos y ejecuta la o las 
                     //funciones de devolucion de llamada
    loop_rate.sleep();
    

  }

  
  

  return 0;
}
