#include "ros/ros.h"
#include "std_msgs/Bool.h"

void chatterCallback(const std_msgs::Bool::ConstPtr& msg)
{
  ROS_INFO("I heard: [%s]", msg->data ? "true" : "false");
}

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "listener_bool");

  ros::NodeHandle n;

  
  ros::Subscriber sub = n.subscribe("d_bool", 1000, chatterCallback);

  
  ros::spinOnce();

  return 0;
}
