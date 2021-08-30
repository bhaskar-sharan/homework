#include "ros/ros.h"
#include "beginner_tutorials/add_int.h"
#include <cstdlib>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "add_int_client");
  if (argc != 2)
  {
    ROS_INFO("usage: add_ints_client_with_previous_number X");
    return 1;
  }

  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<beginner_tutorials::add_int>("add_int");

  beginner_tutorials::add_int srv;
  srv.request.a = atoll(argv[1]);
  if (client.call(srv))
  {
    ROS_INFO("Sum: %ld", (long int)srv.response.sum);
  }
  else
  {
    ROS_ERROR("Failed to call service add_int");
    return 1;
  }

  return 0;
}
