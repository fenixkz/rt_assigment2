# Research Track Assignment 2


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
It is done by calculating the closest obstacle to the left and to the right. Then, based on the closest obstacle, the turn is taken in the opposite direction
The frontal side is considered the value of the angles in the range: [-45°; 45°]
The left side is considered the value of the angles in the range: [-90°; -45°]
The right side is considered the value of the angles in the range: [45°; 90°]

The flowchart:
