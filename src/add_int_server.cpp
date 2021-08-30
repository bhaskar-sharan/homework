#include "ros/ros.h"
#include "beginner_tutorials/add_int.h"

bool add(beginner_tutorials::add_int::Request  &req, beginner_tutorials::add_int::Response &res)
{
  // how to get variable from another node ?
  res.sum = req.a;
  ROS_INFO("request: x=%ld", (long int)req.a);
  ROS_INFO("sending back response: [%ld]", (long int)res.sum);
  return true;
}
int main(int argc, char **argv)
{
   ros::init(argc, argv, "add_int_server");
   ros::NodeHandle n;


   ros::ServiceServer service = n.advertiseService("add_int", add);
   ROS_INFO("Ready to add int.");
   ros::spin();
   return 0;
}
