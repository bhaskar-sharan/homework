#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include "beginner_tutorials/add_int.h"

std_msgs::Int32 msg;
bool add(beginner_tutorials::add_int::Request  &req, beginner_tutorials::add_int::Response &res)
{
  msg.data = req.a + msg.data;
  res.sum = msg.data;
  ROS_INFO("request: x=%ld", (long int)req.a);
  ROS_INFO("sending back response: [%ld]", (long int)res.sum);
  return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "talker");
  ros::NodeHandle n;
  ros::Publisher chatter_pub = n.advertise<std_msgs::Int32>("chatter", 1000);
  
  msg.data = 0;
  ros::Rate loop_rate(1);

  ros::init(argc, argv, "add_int_server");
  ros::ServiceServer service = n.advertiseService("add_int", add);
  while (ros::ok())
  {
    chatter_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
  }
  return 0;
}
