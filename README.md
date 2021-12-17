# Research Track Assignment 2


## Installing 
In order to be able to use that project, first you need to have a catkin workspace, then git clone this repository into your workspsace, and execute the following commands:

`
$ catkin_make
`

## Running 
There are three main processes that need to be launched, each in different terminals:
`
$ roscore
$ rosrun stage_ros stageros $(rospack find second_assignment)/world/my_wld.world
$ rosrun control first_node 
$ rosrun control second_node
`
