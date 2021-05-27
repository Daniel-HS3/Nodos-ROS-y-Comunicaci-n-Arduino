#include <ros.h>

#include <std_msgs/Float32.h>
#include <std_msgs/Int16.h>
#include <std_msgs/Bool.h>
#include <Servo.h>

//-------------------------------------------------
//declaracion de pines arduino
const int pin_bool=3; // pin de la entrada boolean
const int pot_int=A0; //entrada analogica potenciometro entero
const int pot_float=A1; //entrada analogica potenciometro flotante
const int pin_pwm=5;  // pin pwm para el control del servo
bool v_bool;          //valor que se lee en pin_bool
int v_int;            //valor que se lee en pot_int
int v_float;        //valor que se lee en pot_float
//servo
Servo servo;
//-------------------------------------------------
std_msgs::Int16 msgr; // se declara como global la variable donde se va a recibir el dato entero
void chatterCallback(std_msgs::Int16& msg) //funcion para leer y guardar el dato recibido
{
  msgr.data=msg.data;  
}

//configuracion ros
ros::NodeHandle  nh;

std_msgs::Bool msg_bool;     //Variable donde dato bolleano a enviar
std_msgs::Int16 msg_int;     //Variable donde dato entero a enviar
std_msgs::Float32 msg_float; //Variable donde dato flotante a enviar


ros::Publisher chatter_bool("arduino_bool", &msg_bool);  
ros::Publisher chatter_int("arduino_int", &msg_int);
ros::Publisher chatter_float("arduino_float", &msg_float);
ros::Subscriber<std_msgs::Int16> arduino_sub("grados_servo",chatterCallback);
//---------------------------------------------------

void setup()
{
  nh.initNode();
  nh.advertise(chatter_bool);
  nh.advertise(chatter_int);
  nh.advertise(chatter_float);
  nh.subscribe(arduino_sub);
//servo
servo.attach(pin_pwm); // asignacion del pin del servo
//--------------------------------------------------
}

void loop()
{
  v_bool=digitalRead(pin_bool); // dato booleno leido del dip-switch
  v_int=analogRead(pot_int)*0.9775171065; // dato entero leido del potenciometro 1
  v_float=analogRead(pot_float)*0.9775171065; // dato flotante leido del potenciometro 2

  msg_bool.data = v_bool; // dato boleano a enviar
  msg_int.data = v_int; // dato entero a enviar
  msg_float.data = (float)v_float+(float)v_float/1000; // dato flotante a enviar
  if(msg_float.data>1000) // condicion para evitar que el dato flotante supere 1000
  {
    msg_float.data = 1000;
  }
  chatter_bool.publish( &msg_bool );
  chatter_int.publish( &msg_int );
  chatter_float.publish( &msg_float );
  nh.spinOnce();
  servo.write(msgr.data); // se envia el valor recibido (grados) al servomotor (mediante la libreria Servo.h)
  delay(100);
}
