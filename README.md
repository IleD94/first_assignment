# first_assignment
First assignment of Research Track I course, Robotics Engineering Unige
Research track 1: Assignment 1 2020/21
Ilenia D’Angelo 4404721

# •	How to run the code:

In order to run the code, follow those steps:
1.	Run the master node with the command: ```roscore```
2.	Run the simulator in the bash with the command: ```rosrun stage_ros stageros $(rospack find holonomic_robot)/world/exercise.world```
3.	Launch the server service for the random number generation with the command: ```rosrun holonomic_robot randomtarget```
4.	Run the second node: ```rosrun holonomic_robot holonomic_robot```

# •	Graph of the system:

 ![rosgraph](https://user-images.githubusercontent.com/80365922/116868912-f2a02300-ac0f-11eb-8b3d-cee87e848d17.png)


# •	Description of the content of the package:
The package is composed of 2 nodes, a custom service and a folder “world”, containing everything necessary to build the environment where our robot moves.
The node “holonomic_robot” is the main node, it calls the service randtarget_server to have random coordinates, it subscribes to the topic “odom” to know the position of the robot and publishes in “cmd_vel” to control the velocity of the robot.

# •	The behaviour of the robot and how to make that

The holonomic robot asks for a random target to the service server “randtarget_server”, this one picks random coordinates (x,y) in the interval (-6.0, 6.0) (min,max), to do this we have created a custom service of this kind:
---
float32 min
float32 max
---
float32 x
float32 y
---
Then the robot reaches the goal with a linear velocity that follows this law:
Linear velocity.x = k*x;
Linear velocity.y = k*y;
Where, in our case k = 0.8.
