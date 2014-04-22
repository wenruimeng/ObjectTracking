#include "pathTransfer.h"
#include "ros/ros.h"
#include "std_msgs/UInt32.h"
#include "common.h"


#define pi 3.1415926
#define speed 1

Path currentPath;
Direction currentDirection;
Point currentPosition;

double PathTransfer::getAngle(Point current, Point next){

}

int main(int argc, char **argv) {
  ros::init(argc, argv, "pathTransfer");
  
  ros::Subscriber pathSub = nh.subscribe("/vehicle_path", 1, updatePath);
  ros::Subscriber vehicleDirectionSub = nh.subscribe("/vehicle_direction", 1, UpdateVehicleDirection);
  ros::Subscriber vehiclePositionSub = nh.subscribe("/vehicle_position", 1, UpdateVehiclePosition);

  ros::Publisher velocityPub = nh.advertise<geometry_msgs::Twist>("/cmd_vel",1);	 
  
  ros::Rate r(1);
  while(ros::ok()) {
    ros::spinOnce();
    geometry_msgs::Twist cmd;
    assert(currentPosition.x == currentPath[0].x && currentPosition.y == currentPath[0].y);
    for(int i = 1; i < currentPath.size(); ++i){
      double ang = getAngle(currentPosition, currentPath[i]);
      if(ang == 0){
	cmd.linear.x = speed;
	velocityPub.publish(cmd);
	currentPostion = currentPath[i];
	//our grid is 0.1 x 0.1 grid
	sleep(0.1);
      }
      else{
	cmd.angular.z = ang * 10;
	velocityPub.publish(cmd);
	sleep(0.1);
      }
    r.sleep();
    }
  
  return 0;
}

