#include <iostream>

#include <cstdlib>

#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "geometry_msgs/Twist.h"


class ReactiveController
{
private:
    ros::NodeHandle n;
    ros::Publisher cmd_vel_pub;
    ros::Subscriber laser_sub_0;
    ros::Subscriber laser_sub_1;
    ros::Subscriber laser_sub_2;

    double obstacle_distance_F, obstacle_distance_R, obstacle_distance_L;
    bool robot_stopped;

    geometry_msgs::Twist calculateCommand()
    {
        auto msg = geometry_msgs::Twist();
        
        if(obstacle_distance_F > 0.5){
            if(obstacle_distance_R > 0.2){
                msg.linear.x = 1.0;
                msg.angular.z = -2.0;
            }
            else{
                msg.linear.x = 1.0;
            }
        }else{
            msg.angular.z = 1.0;
        }
        
        return msg;
    }

    void laserCallbackF(const sensor_msgs::LaserScan::ConstPtr& msg)
    {
        obstacle_distance_F = *std::min_element(msg->ranges.begin(), msg->ranges.end());
        ROS_INFO("Min distance front to obstacle: %f", obstacle_distance_F);
    }
    
    void laserCallbackR(const sensor_msgs::LaserScan::ConstPtr& msg)
    {
        obstacle_distance_R = *std::min_element(msg->ranges.begin(), msg->ranges.end());
        ROS_INFO("Min distance right to obstacle: %f", obstacle_distance_R);
    }

    void laserCallbackL(const sensor_msgs::LaserScan::ConstPtr& msg)
    {
        obstacle_distance_L = *std::min_element(msg->ranges.begin(), msg->ranges.end());
        ROS_INFO("Min distance left to obstacle: %f", obstacle_distance_L);
    }

public:
    ReactiveController(){
        this->n = ros::NodeHandle();

        this->cmd_vel_pub = this->n.advertise<geometry_msgs::Twist>("cmd_vel", 5);

        this->laser_sub_0 = n.subscribe("base_scan_0", 10, &ReactiveController::laserCallbackF, this);
        this->laser_sub_1 = n.subscribe("base_scan_1", 10, &ReactiveController::laserCallbackL, this);
        this->laser_sub_2 = n.subscribe("base_scan_2", 10, &ReactiveController::laserCallbackR, this);
    }

    void run(){
        ros::Rate loop_rate(10);
        while (ros::ok())
        {
            auto msg = calculateCommand();

            this->cmd_vel_pub.publish(msg);

            ros::spinOnce();

            loop_rate.sleep();
        }
    }
};

int main(int argc, char **argv){
    ros::init(argc, argv, "reactive_controller");

    auto controller = ReactiveController();
    controller.run();

    return 0;
}
