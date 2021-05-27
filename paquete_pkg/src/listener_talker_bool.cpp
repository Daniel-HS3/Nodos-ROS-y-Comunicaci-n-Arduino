#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Bool.h"

//------------------------------------------------------------
//variable globales
std_msgs::Bool msgr_bool;     //variable que toma el valor recibido
std_msgs::String msgs_string; // variable a enviar
//-------------------------------------------------------------

void chatterCallback(const std_msgs::Bool::ConstPtr& msg_bool) //funcion recepcion dato bool
{
  ROS_INFO("I heard: [%s]", msg_bool->data ? "true" : "false");
  msgr_bool.data=msg_bool->data;
//-------------------------------------------------------------------------------------------
// selección de la cadena que se debe enviar dependiedo del valor boleano recibido del nodo A
  if(msgr_bool.data==true)
   { 
     msgs_string.data= "A100%/M0%/B0%";
   }
  if(msgr_bool.data==false)
   {
     msgs_string.data= "A0%/M0%/B100%";
   }
//-------------------------------------------------------------------------------------------
}

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "listener_talker_bool");//inicialización del nodo listener_talker_bool (nodo B)
  ros::NodeHandle n;
//-------------------------------------------------------------------------------------------
//el nodo B se suscribe al topic "d_bool" del nodo A
  ros::Subscriber bool_sub = n.subscribe("d_bool", 1000, chatterCallback); 
//-------------------------------------------------------------------------------------------
//publica el topic "string_bool" que contiene el porcentaje de pertenencia a cada funcion 
//(Alto, medio, bajo) 
  ros::Publisher string_pub = n.advertise<std_msgs::String>("string_bool", 1000);
  ros::Rate loop_rate(1);
//-------------------------------------------------------------------------------------------

  while (ros::ok()) //el while se ejecuta mientras el nodo esta en linea
  {

    ROS_INFO("%s", msgs_string.data.c_str()); //ver informacion en el terminal

    string_pub.publish(msgs_string); //publicar la cadena que contiene el porcentaje de pertenencia

    ros::spinOnce();//verificar si hay datos nuevos en los topics suscritos y ejecuta la o las 
                    //funciones de devolucion de llamada

    loop_rate.sleep();

  }

  
  

  return 0;
}
