#include "ros/ros.h"
#include "std_msgs/Char.h"
#include "std_msgs/Int16.h"
#include "std_msgs/Float32.h"
//------------------------------------------------------------
//variable globales
std_msgs::Int16 msgs;   // grados del servo
std_msgs::Char v_bool;  // variable recibida (char de bool)
std_msgs::Char v_int;   // variable recibida (char de int)
std_msgs::Char v_float; // variable recibida (char de float)
//-------------------------------------------------------------

void chatterCallback_bool(const std_msgs::Char::ConstPtr& msg_bool) // funcion recepcion del caracter 
                                                                    // de la parte boleana
{
  ROS_INFO("bool: [%c]", msg_bool->data); // ver informacion en el terminal
  v_bool.data=msg_bool->data;             // almacenar informacion recibida 
}

void chatterCallback_int(const std_msgs::Char::ConstPtr& msg_int) // funcion recepcion del caracter 
                                                                  // de la parte entera
{
  ROS_INFO("int: [%c]", msg_int->data); // ver informacion en el terminal
  v_int.data=msg_int->data;             // almacenar informacion recibida   
}

void chatterCallback_float(const std_msgs::Char::ConstPtr& msg_float)//funcion recepcion del caracter 
                                                                     //de la parte flotante
{
  ROS_INFO("float: [%c]", msg_float->data); // ver informacion en el terminal
  v_float.data=msg_float->data;             // almacenar informacion recibida   
}

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "listener_char_123"); // inicializacion del nodo H

  ros::NodeHandle n;
//------------------------------------------------------------------------------------------
// suscripcion a los topics "char_bool", "char_int" y "char_float" de los nodos E, F y G  que tienen 
// las decisiones (A, M, B) de los datos (bool, int, float) 
  ros::Subscriber sub = n.subscribe("char_bool", 1000, chatterCallback_bool);
  ros::Subscriber sub1 = n.subscribe("char_int", 1000, chatterCallback_int);
  ros::Subscriber sub3 = n.subscribe("char_float", 1000, chatterCallback_float);
//------------------------------------------------------------------------------------------
// se crea el topic "grados_servo" el cual va a publicar un valor entero que corresponde a los grados 
// del servo
  ros::Publisher grados_pub = n.advertise<std_msgs::Int16>("grados_servo", 1000); 
//------------------------------------------------------------------------------------------

  ros::Rate loop_rate(0.2);

    while (ros::ok()) //el while se ejecuta mientras el nodo esta en linea
  {
    ros::spinOnce(); //verificar si hay datos nuevos en los topics suscritos y ejecuta la o las 
                     //funciones de devolucion de llamada

//------------------------------------------------------------------------------------------
//implementacion de las decisiones de los tres datos (bool, int, float) en grados del potenciometro (0° - 180°)
    if(v_int.data=='A' && v_float.data=='A' && v_bool.data=='A')
      {
       msgs.data=180; 
      }
    if(v_int.data=='A' && v_float.data=='A' && v_bool.data=='B')
      {
       msgs.data=169; 
      }
    if(v_int.data=='A' && v_float.data=='M' && v_bool.data=='A')
      {
       msgs.data=159; 
      }
    if(v_int.data=='A' && v_float.data=='M' && v_bool.data=='B')
      {
       msgs.data=148; 
      }
    if(v_int.data=='A' && v_float.data=='B' && v_bool.data=='A')
      {
       msgs.data=138; 
      }
    if(v_int.data=='A' && v_float.data=='B' && v_bool.data=='B')
      {
       msgs.data=127; 
      }
    if(v_int.data=='M' && v_float.data=='A' && v_bool.data=='A')
      {
       msgs.data=116; 
      }
    if(v_int.data=='M' && v_float.data=='A' && v_bool.data=='B')
      {
       msgs.data=106; 
      }
    if(v_int.data=='M' && v_float.data=='M' && v_bool.data=='A')
      {
       msgs.data=95; 
      }
    if(v_int.data=='M' && v_float.data=='M' && v_bool.data=='B')
      {
       msgs.data=85; 
      }
    if(v_int.data=='M' && v_float.data=='B' && v_bool.data=='A')
      {
       msgs.data=74; 
      }
    if(v_int.data=='M' && v_float.data=='B' && v_bool.data=='B')
      {
       msgs.data=64; 
      }
    if(v_int.data=='B' && v_float.data=='A' && v_bool.data=='A')
      {
       msgs.data=53; 
      }
    if(v_int.data=='B' && v_float.data=='A' && v_bool.data=='B')
      {
       msgs.data=42; 
      }
    if(v_int.data=='B' && v_float.data=='M' && v_bool.data=='A')
      {
       msgs.data=32; 
      }
    if(v_int.data=='B' && v_float.data=='M' && v_bool.data=='B')
      {
       msgs.data=21; 
      }
    if(v_int.data=='B' && v_float.data=='B' && v_bool.data=='A')
      {
       msgs.data=11; 
      }
    if(v_int.data=='B' && v_float.data=='B' && v_bool.data=='B')
      {
       msgs.data=0; 
      }
//------------------------------------------------------------------------------------------
    ROS_INFO("%i", msgs.data); //ver informacion en el terminal
    grados_pub.publish(msgs);  //publicar los grados a los que se llevara el servo

    loop_rate.sleep();


  }

  return 0;
}
