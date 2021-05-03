/* Ilenia D'Angelo 4404721 assignment 1*/
#include "ros/ros.h"
#include "holonomic_robot/Random.h"
/**
* @retval the function randMToN returns a value of type double
* @param M value is the minimum of the interval 
* @param N value is the maximum of the interval 
**/
double randMToN(double M, double N)
{     return M + (rand() / ( RAND_MAX / (N-M) ) ) ; 
}

/**
* @retval the function my random returns a value of type boolen
* @param res is for receiving values of x and y coordinates
* @param req is for broadcasting the minimum and maximum value of the interval to the server
**/

// the callback function of the service server
bool myrandom (holonomic_robot::Random::Request&req, holonomic_robot::Random::Response&res){
	res.x= randMToN(req.min,  req.max);
	res.y= randMToN(req.min,  req.max);
	ROS_INFO("the target is: [%f, %f]", res.x, res.y );
	return true;
}

int main(int argc, char **argv)
{
	//initialization of the node randtarget_server
	ros::init(argc, argv, "randtarget_server");
	ros::NodeHandle n;
	//inizialization of the service server of kind random
	ros::ServiceServer service= n.advertiseService("/random", myrandom);
	ros::spin();

	return 0;
}
