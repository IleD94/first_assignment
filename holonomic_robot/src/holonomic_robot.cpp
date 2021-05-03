/*Ilenia D'Angelo 4404721, assignment 1*/ 

#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "holonomic_robot/Random.h"
#include "nav_msgs/Odometry.h"
#include <math.h>

// Definition of the publisher
ros::Publisher pub;
// Definition of the client
ros::ServiceClient client;

//global definition of the random target variables
float x2 = 0;
float y2 = 0;

/**
* @retval the function positionRobotCallback returns a void
* @param pointer to the message
**/
void positionRobotCallback(const nav_msgs::Odometry::ConstPtr& msg)
	{ROS_INFO("Robot position [%f, %f]", msg->pose.pose.position.x, msg->pose.pose.position.y);

	geometry_msgs::Twist vel;
	holonomic_robot:: Random target;
	//current position x of the robot
	float x1 = msg-> pose.pose.position.x;
	//current position y of the robot
	float y1 = msg -> pose.pose.position.y;

	float x = x2-x1;
	float y = y2-y1;
	//distance between the position of the robot and its target
	double dist = sqrt (pow (x,2) + pow (y,2));
	
	if ( dist <= 0.1) {
		holonomic_robot:: Random target;
		target.request.min = -6.0;
		target.request.max = 6.0;
		client.call (target);
		x2 = target.response.x;
		y2 = target.response.y;
	}
	// robot's velocity along axis x
	vel.linear.x = 0.8*x;
	//velocity along axis y
	vel.linear.y = 0.8*y;	
	pub.publish (vel);
}

int main(int argc, char **argv)
{
	//initialization of the node holonomic_robot
	ros::init(argc, argv, "holonomic_robot");
	ros::NodeHandle n;
	
	//client of the service Random
	client = n.serviceClient<holonomic_robot::Random>("random");
	//publisher for the topic cmd_vel
	pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);
	// initialization of the subscriber of the topic /odom
	ros::Subscriber sub = n.subscribe("/odom", 1000, positionRobotCallback);
	ros::spin();

	return 0;
}
