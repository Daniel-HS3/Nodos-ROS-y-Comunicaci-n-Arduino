#include "ros/ros.h"
#include "std_msgs/Char.h"
#include "std_msgs/String.h"
#include "std_msgs/Int16.h"
#include <sstream>

//------------------------------------------------------------
//variable globales
std::string msgr_string;  // variable que toma el valor recibido
std_msgs::Char msgs_char; // variable a enviar
std_msgs::Int16 v_alto;   // variable porcentaje alto
std_msgs::Int16 v_medio;  // variable porcentaje medio
std_msgs::Int16 v_bajo;   // variable porcentaje bajo
//-------------------------------------------------------------


void chatterCallback(const std_msgs::String::ConstPtr& msg_string) //funcion recepcion de la cadena
{
  ROS_INFO("I heard: [%s]", msg_string->data.c_str()); // ver informacion en el terminal
  msgr_string=msg_string->data;                        // almacenar informacion recibida
  
  std::stringstream ss(msgr_string); //utilizando la libreria <sstream>, convertimos el string que 
                                     //contiene la informacion recibida a un dato de tipo stringstream
  std_msgs::Int16 count; // contador
  std::string valor;     // variable auxiliar, almacenamiento de partes de la cadena recibida
  std::string valor1;    // variable auxiliar, almacenamiento de partes de la cadena recibida
  std::string valor2;    // variable auxiliar, almacenamiento de partes de la cadena recibida
    

  count.data=1; // inicializacion del contador

//--------------------------------------------------------------------------------------
// separacion de los datos de la cadena recibida

                                     //   ejemplo de cadena recibida: A100%/M0%/B0%
  while(std::getline(ss, valor,'/')) // primera vez -> valor=A100% - segunda vez -> valor=M0% - 
                                     // tercera vez -> valor=B0%
  { 
    if(count.data==1)
      {
        std::stringstream ss1(valor);  //separar cadena
        
        std::getline(ss1, valor1,'A'); //separar cadena - valor1=nada
        std::getline(ss1, valor1,'A'); //separar cadena - valor1=100%
        std::stringstream ss2(valor1); //separar cadena - ss2=100%
        std::getline(ss2, valor2,'%'); //separar cadena - valor2=100
     
        std::stringstream convert(valor2); //convertir string a entero
        convert >> v_alto.data;            //convertir string a entero
      }
    if(count.data==2)
      {
        std::stringstream ss1(valor);  //separar cadena
        
        std::getline(ss1, valor1,'M'); //separar cadena - valor1=nada
        std::getline(ss1, valor1,'M'); //separar cadena - valor1=0%
        std::stringstream ss2(valor1); //separar cadena - ss2=0%
        std::getline(ss2, valor2,'%'); //separar cadena - valor2=0

        std::stringstream convert(valor2); //convertir string a entero
        convert >> v_medio.data;           //convertir string a entero
      }
    if(count.data==3)
      {
        std::stringstream ss1(valor);  //separar cadena
        
        std::getline(ss1, valor1,'B'); //separar cadena - valor1=nada
        std::getline(ss1, valor1,'B'); //separar cadena - valor1=0%
        std::stringstream ss2(valor1); //separar cadena - ss2=0%
        std::getline(ss2, valor2,'%'); //separar cadena - valor2=0

        std::stringstream convert(valor2); //convertir string a entero
        convert >> v_bajo.data;            //convertir string a entero
      }
   count.data=count.data+1; // incrementar el contador
  } // cuando se terminen los "/" en la cadena se termina el ciclo while 
//--------------------------------------------------------------------------------------

  ROS_INFO("dato leido 1: [%i]", v_alto.data);  // ver informacion en el terminal
  ROS_INFO("dato leido 2: [%i]", v_medio.data); // ver informacion en el terminal
  ROS_INFO("dato leido 3: [%i]", v_bajo.data);  // ver informacion en el terminal

//--------------------------------------------------------------------------------------
// seleccion si el dato que llego del arduino es alto, medio o bajo (A, M, B)
  if(v_alto.data>=50)
   {
    msgs_char.data='A'; 
   }
  if(v_medio.data>=50)
   {
    msgs_char.data='M'; 
   }
  if(v_bajo.data>=50)
   {
    msgs_char.data='B'; 
   }
//--------------------------------------------------------------------------------------


}


int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "listener_talker_char_1"); // inicializacion del nodo E
  ros::NodeHandle n;
//-------------------------------------------------------------------------------------------
//el nodo E se suscribe al topic "string_bool" del nodo B
  ros::Subscriber sub = n.subscribe("string_bool", 1000, chatterCallback);
//-------------------------------------------------------------------------------------------
//publica el topic "char_bool" que contiene el caracter que indica la decision (Alto, medio, bajo) 
  ros::Publisher char_pub = n.advertise<std_msgs::Char>("char_bool", 1000); 
//-------------------------------------------------------------------------------------------

  ros::Rate loop_rate(0.5);

  
 while (ros::ok()) //el while se ejecuta mientras el nodo esta en linea
  {
    ros::spinOnce(); //verificar si hay datos nuevos en los topics suscritos y ejecuta la o las 
                     //funciones de devolucion de llamada

    ROS_INFO("%c", msgs_char.data); //ver informacion en el terminal
    char_pub.publish(msgs_char);    //publicar el caracter que contiene la decision

    loop_rate.sleep();

  } 

  return 0;
}
