# Research Track Assignment 2

## Problem statement
The robot is spawned inside a circle. The idea is to implement an algorithm that will autonomously navigate the robot along the circle.

Also, an another process should be done that simulates an interface. It takes a command from the user: to increase or decrease the speed of the robot, and to reset the position of the robot.

Problem details: the robot is equipped with laser scanner that gives a measurement of the distance to the closest obstacle in the range of approximately [-90°; 90°]. This interval is sampled with approximately 0.25° step. 

## Installing 
In order to be able to use that project, first you need to have a catkin workspace, then git clone this repository into your workspsace, and execute the following commands:

`
$ catkin_make
`

## Running 
There are three main processes that need to be launched, each in different terminals:
```
$ roscore
$ rosrun stage_ros stageros $(rospack find second_assignment)/world/my_wld.world
$ rosrun control first_node 
$ rosrun control second_node
```

## Solution implementation details

In general, the robot moves along the circle until an obstacle is found in front of the robot. After that, the algorithm decided with turn to take: right or left.
It is done by calculating the closest obstacle to the left and to the right. Then, based on the closest obstacle, the turn is taken in the opposite direction.

The frontal side is considered the value of the angles in the range: [-45°; 45°]

The left side is considered the value of the angles in the range: [-90°; -45°]

The right side is considered the value of the angles in the range: [45°; 90°]

There are two .cpp files in the *control* package. 

*first_node.cpp* is responsible for robot control and navigation

*second_node.cpp* is responsible for receiving an input from the user and executing the corresponding action.

The flowchart: 

![text](https://github.com/fenixkz/rt_assigment2/blob/master/images/Graph.svg)
