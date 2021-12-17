#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <unistd.h>
#include <sensor_msgs/LaserScan.h>
#include <std_msgs/Float32.h>
#include <iostream>
#include <vector>
#include <geometry_msgs/Twist.h>
#include <control/speed.h>
#include <stdlib.h>
#include "std_srvs/Empty.h"

std_srvs::Empty res_server;
char input;
float speed;
int done = 0;
/* Simple printing function to print the instruction*/
void my_print(){
  system("clear");
  std::cout << "This is a interface with the robot\n";
  std::cout << "There are four commands available: (please press only one button at a time)\n";
  std::cout << "Press W or w to increase the speed \n";
  std::cout << "Press S or s to decrease the speed \n";
  std::cout << "Press R or r to reset the robot \n";
  std::cout << "Press Q or q to quit\n";
}



int main(int argc, char **argv){
  ros::init(argc, argv, "Secondnode");
  ros::NodeHandle nh;
  ros::ServiceClient client = nh.serviceClient<control::speed>("speed"); // Our custom created service
  control::speed srv;
  client.waitForExistence(); // wait for the service to spawn
  my_print();
  while (ros::ok() && !done){
    speed = 0;

    std::cin >> input; // take the input from the keyboard

    switch(input){ // a simple switch function to do the corresponding action
      case 'W': // Increase speed
      case 'w':
              speed = 0.5;
              break;
      case 'S': // Decrease speed
      case 's':
              speed = -0.5;
              break;
      case 'R': // Reset the position
      case 'r':
              ros::service::call("/reset_positions", res_server); // It is done via existing service
              ROS_INFO("The position of the robot is reset\n");
              break;
      case 'Q': // Quit the process
      case 'q':
              ROS_INFO("Farewell!");
              done = 1;
              break;
      default: // Unavailable command
              std::cout << "Unavailable command, please try again: \n";
              break;
    }
    if (speed != 0){
        srv.request.speed = speed;
        if (client.call(srv)){ // send the request and receive status of the response
          ROS_INFO("Successfully changed the speed\n");
        }else{
          ROS_INFO("Unexpected error\n");
        }
    }
  }
  return 0;
}
