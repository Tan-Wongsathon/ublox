#include "ros/ros.h"
#include "std_msgs/String.h"
#include "nav_msgs/Odometry.h"
#include <geometry_msgs/Twist.h>
#include "geometry_msgs/PoseStamped.h"
#include "geometry_msgs/PoseWithCovariance.h"
#include "geometry_msgs/TwistWithCovariance.h"

geometry_msgs::PoseStamped pose_converted;

void ublox_pose_callback(const nav_msgs::Odometry::ConstPtr& msg)
{ 
  pose_converted.header = msg->header;
  pose_converted.pose.position.x = msg->pose.pose.position.x;
  pose_converted.pose.position.y = msg->pose.pose.position.y;
  pose_converted.pose.position.z = msg->pose.pose.position.z;
  pose_converted.pose.orientation.x = msg->pose.pose.orientation.x;
  pose_converted.pose.orientation.x = msg->pose.pose.orientation.y;
  pose_converted.pose.orientation.x = msg->pose.pose.orientation.z;
  pose_converted.pose.orientation.x = msg->pose.pose.orientation.w;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "ublox_posistion_convert");
  ros::NodeHandle node;
  ros::Publisher ublox_pose_convert_pub = node.advertise<geometry_msgs::PoseStamped>("/gnss_pose", 1000);
  ros::Subscriber ublox_pose_sub = node.subscribe("/ublox/pose_converted", 1000, ublox_pose_callback);
  ros::Rate loop_rate(1);
  
  while (node.ok()){
    ublox_pose_convert_pub.publish(pose_converted);
    ros::spinOnce();
    loop_rate.sleep();
  }
};
