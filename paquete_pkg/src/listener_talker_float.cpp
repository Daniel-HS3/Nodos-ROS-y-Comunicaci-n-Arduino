#include "ros/ros.h"
#include "std_msgs/Float32.h"
#include "std_msgs/String.h"
#include <sstream>



//------------------------------------------------------------
//variable globales
std_msgs::Float32 msgr_float; // variable que toma el valor recibido
std_msgs::String msgs_string; // variable a enviar
std_msgs::Float32 v_alto;     // variable porcentaje alto
std_msgs::Float32 v_medio;    // variable porcentaje medio
std_msgs::Float32 v_bajo;     // variable porcentaje bajo
//-------------------------------------------------------------

void chatterCallback(const std_msgs::Float32::ConstPtr& msg_float) //funcion recepcion dato float
{
  ROS_INFO("I heard: [%f]", msg_float->data); // ver informacion en el terminal
  msgr_float.data=msg_float->data;            // almacenar el dato recibido

//--------------------------------------------------------------------------------------------
// evaluar el dato recibido en las funciones de pertenencia (Alto, medio, bajo)
  if(msgr_float.data<=250)
   {
     v_alto.data=0;
     v_medio.data=0;
     v_bajo.data=100;
   }
  if(msgr_float.data>250 && msgr_float.data<=500)
    {
     v_alto.data=0;
     v_medio.data=0.4*(msgr_float.data)-100;
     v_bajo.data=-0.4*(msgr_float.data)+200;
   }
  if(msgr_float.data>500 && msgr_float.data<=750)
    {
     v_alto.data=0.4*(msgr_float.data)-200;
     v_medio.data=-0.4*(msgr_float.data)+300;
     v_bajo.data=0;
   }
  if(msgr_float.data>750 && msgr_float.data<=1000)
    {
     v_alto.data=100;
     v_medio.data=0;
     v_bajo.data=0;
   }
//--------------------------------------------------------------------------------------------
}

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "listener_talker_float"); // inicializacion del nodo D
  ros::NodeHandle n;
//-------------------------------------------------------------------------------------------
//el nodo D se suscribe al topic "d_float" del nodo A
  ros::Subscriber float_sub = n.subscribe("d_float", 1000, chatterCallback);
//-------------------------------------------------------------------------------------------
//publica el topic "string_float" que contiene el porcentaje de pertenencia a cada funcion 
//(Alto, medio, bajo) 
  ros::Publisher string_pub = n.advertise<std_msgs::String>("string_float", 1000); 
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
