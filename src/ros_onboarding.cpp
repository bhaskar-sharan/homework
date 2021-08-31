#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include "beginner_tutorials/add_int.h"
#include <cstdlib>

std_msgs::Int32 msg;

bool add(beginner_tutorials::add_int::Request  &req, beginner_tutorials::add_int::Response &res)
{
  msg.data = req.a + msg.data;
  res.sum = msg.data;
  ROS_INFO("request: x=%ld", (long int)req.a);
  ROS_INFO("sending back response: [%ld]", (long int)res.sum);
  return true;
}

void chatterCallback(const std_msgs::Int32::ConstPtr& msg)
{
  ROS_INFO("Integer being published currently: [%i]", msg->data);
}

int main(int argc, char **argv){

	ros::init(argc, argv, "masternode");
  	ros::NodeHandle n;
  	ros::Publisher chatter_pub = n.advertise<std_msgs::Int32>("chatter", 1000);

  	msg.data = 0;
	int frequency;
    n.getParam("/frequency", frequency);
	ROS_INFO("%i", frequency);
    ros::Rate loop_rate(frequency);

  	ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);
    

	// call service using 'rosservice call /add_int 5
	ros::ServiceServer service = n.advertiseService("add_int", add);

  	while (ros::ok())
  	{
    	chatter_pub.publish(msg);

    	ros::spinOnce();

    	loop_rate.sleep();
  	}
  	return 0;
}

/* Syntax */



/* using config files
<rosparam file="$(find beginner_tutorials)/config/params.yaml"/>

without using config files
<launch>
    <rosparam param="frequency">5</rosparam>
</launch>
*/