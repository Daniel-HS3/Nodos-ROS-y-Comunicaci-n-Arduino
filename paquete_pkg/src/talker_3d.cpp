#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Bool.h"
#include "std_msgs/Int16.h"
#include "std_msgs/Float32.h"

#include <sstream>
//------------------------------------------------------------
//variable globales
std_msgs::Bool msgs_bool;     //dato booleano recibido de arduino
std_msgs::Int16 msgs_int;     //dato entero recibido de arduino
std_msgs::Float32 msgs_float; //dato flotante recibido de arduino
//-------------------------------------------------------------

void chatterCallback_bool(const std_msgs::Bool::ConstPtr& msgr_bool) //funcion recepcion dato bool
{
  ROS_INFO("I heard: [%s]", msgr_bool->data ? "true" : "false");
  msgs_bool.data = msgr_bool->data;


}

void chatterCallback_int(const std_msgs::Int16::ConstPtr& msgr_int) //funcion recepcion dato int
{
  ROS_INFO("I heard: [%i]", msgr_int->data);
  msgs_int.data = msgr_int->data;
 
}

void chatterCallback_float(const std_msgs::Float32::ConstPtr& msgr_float)//funcion recepcion dato float
{
  ROS_INFO("I heard: [%f]", msgr_float->data);
  msgs_float.data = msgr_float->data;
}

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "talker_3d"); //inicializacion del nodo talker_3d (nodo A)

  
  ros::NodeHandle n;
//------------------------------------------------------------------------------------------
// suscripcion a los topics del arduino que tienen los datos (bool, int, float) 
  ros::Subscriber bool_sub = n.subscribe("arduino_bool", 1000, chatterCallback_bool);
  ros::Subscriber int_sub = n.subscribe("arduino_int", 1000, chatterCallback_int);
  ros::Subscriber float_sub = n.subscribe("arduino_float", 1000, chatterCallback_float);
//------------------------------------------------------------------------------------------
//creacion de los topic del nodo A que publican los datos bool, int, float a los nodos B, C, D 
//respectivamente   
  ros::Publisher bool_pub = n.advertise<std_msgs::Bool>("d_bool", 1000);
  ros::Publisher int_pub = n.advertise<std_msgs::Int16>("d_int", 1000);
  ros::Publisher float_pub = n.advertise<std_msgs::Float32>("d_float", 1000); 
//------------------------------------------------------------------------------------------

  ros::Rate loop_rate(10);

  
  
  while (ros::ok()) //el while se ejecuta mientras el nodo esta en linea
  {
    


    ROS_INFO("%i", msgs_int.data); // ver información en el terminal

//------------------------------------------------------------------------------------------
//publicar los datos bool, int, float
    bool_pub.publish(msgs_bool);
    int_pub.publish(msgs_int);
    float_pub.publish(msgs_float);
//------------------------------------------------------------------------------------------
    ros::spinOnce(); //verificar si hay datos nuevos en los topics suscritos y ejecuta la o las 
                     //funciones de devolucion de llamada

    loop_rate.sleep();
    
  }


  return 0;
}
