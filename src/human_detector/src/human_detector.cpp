#include "ros/ros.h"
#include <sstream>
#include <stdio.h>
#include <iostream>
#include <std_msgs/String.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/highgui/highgui.hpp>
#include <image_transport/image_transport.h>

using namespace std;

void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
    try {
        cv::imshow("view", cv_bridge::toCvShare(msg, "bgr8")->image);
        cv::waitKey(30);
    } catch (cv_bridge::Exception& e) {
        ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "image_listener");
    ros::NodeHandle nh;
    cv::namedWindow("view");

    image_transport::ImageTransport it(nh);
    image_transport::Subscriber sub = it.subscribe("rtsp2/image_raw", 1, imageCallback);

    ros::Publisher human_detected_pub_ = nh.advertise<std_msgs::String>("human", 100);

    ros::spin();
    cv::destroyWindow("view");
}
