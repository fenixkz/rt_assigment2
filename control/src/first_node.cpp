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

/* Declaration of essential variables */
float minDistanceFront, minDistanceLeft, minDistanceRight;
float safeDistance = 0.7;
float acceleration = 0;
std::vector<float> d;
std::vector<float> minDistances;
geometry_msgs::Twist msg;
ros::Publisher pub;

/* A simple function to detect the minimal distances in front, on the left, and on the right of the robot
The sides are divided in the following way:
Robot has vision from [-90;90] degrees. So, the frontal vision incorporates all laser measurements from [-45; 45] set of angles
Right is declared as [45;90] degrees
Left is declared as [-90;-45] degrees.
Each of the distance is calculated and an array of three values is returned*/
std::vector<float> calculateMinDistance(std::vector<float> data){
    std::vector<float> distances;
    minDistanceLeft = 30;
    minDistanceFront = 30;
    minDistanceRight = 30;

    /* Calculate the minimal distance on the left of the robot */
    for (int i = 0; i < 4*45; i++){
      if (data[i] < minDistanceLeft){
        minDistanceLeft = data[i];
      }
    }
    distances.push_back(minDistanceLeft);
    /* Calculate the minimal distance in front of the robot */
    for (int i = 4*45; i < 4*135; i++){
      if (data[i] < minDistanceFront){
        minDistanceFront = data[i];
      }
    }
    distances.push_back(minDistanceFront);
    /* Calculate the minimal distance on the right of the robot */
    for (int i = 4*135; i < data.size(); i++){
      if (data[i] < minDistanceRight){
        minDistanceRight = data[i];
      }
    }
    distances.push_back(minDistanceRight);
    return distances;
}

/* Callback of our subscriber, this is the function where the main processes are executed */
void callback(const sensor_msgs::LaserScan::ConstPtr& data) {
  d = data->ranges; // copy the data from the topic to our variable
  minDistances = calculateMinDistance(d); // measure all minimal distances
  // ROS_INFO("Right: %f -- Front: %f -- Left: %f", minDistances[0], minDistances[1], minDistances[2]);
  if (minDistances[1] > safeDistance){ // if the frontal closest obstacle is far enough, we just move forward
    msg.linear.x = 1 + acceleration;
    msg.angular.z = 0;
  }else if(minDistances[0] > minDistances[2]){ // if an obstacle is detected, then we measure if left obstacle is closer
    ROS_INFO("Obstacle is detected, so I am turning to the right");
    msg.linear.x = 0.5;
    msg.angular.z = -2.5;
  }else if(minDistances[0] < minDistances[2]){ // if an obstacle is detected, then we measure if right obstacle is closer
    ROS_INFO("Obstacle is detected, so I am turning to the left");
    msg.linear.x = 0.5;
    msg.angular.z = 2.5;
  }
  pub.publish(msg); // Publish the velocity to the corresponding topic
}

/* This is our service handler to increase/decrease the speed */
bool changeSpeed(control::speed::Request &req,
                 control::speed::Response &res){
      acceleration += req.speed;
      res.response = 1;
      if (acceleration < 0){
        ROS_INFO("Successfully decreased the speed");
      }else{
        ROS_INFO("Successfully increased the speed");
      }
      return true;
}
int main(int argc, char **argv)
{
  ros::init(argc, argv, "Firstnode");
  ros::NodeHandle nh;
  pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
  ros::Subscriber sub = nh.subscribe("/base_scan", 100, callback);
  ros::ServiceServer service = nh.advertiseService("speed", changeSpeed); // Custom created service to increase/decrease speed
  while (ros::ok()){
    ros::spinOnce();
  }
  return 0;
}
