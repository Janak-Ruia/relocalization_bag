#include <ros/ros.h>
#include <rosbag/bag.h>
#include <rosbag/view.h>
#include <std_msgs/Int32.h>
#include <std_msgs/String.h>

#include <boost/foreach.hpp>
#include <sensor_msgs/PointCloud2.h>




ros::init (argc, argv, "bag");
ros::NodeHandle nh;
ros::Publisher pcl_pub_bag = nh.advertise<sensor_msgs::PointCloud2> ("/bag", 1);

#define foreach BOOST_FOREACH
rosbag::Bag bag;
bag.open("/home/janak/Downloads/new_kitti.bag", rosbag::bagmode::Read);

std::vector<std::string> topics;
//topics.push_back(std::string("chatter"));
topics.push_back(std::string("sensor_msgs/PointCloud2"));

rosbag::View view(bag, rosbag::TopicQuery(topics));

    foreach(rosbag::MessageInstance const m, view)
    {
        /*std_msgs::String::ConstPtr s = m.instantiate<std_msgs::String>();
        if (s != NULL)
            std::cout << s->data << std::endl;

        std_msgs::Int32::ConstPtr i = m.instantiate<std_msgs::Int32>();
        if (i != NULL)
            std::cout << i->data << std::endl;*/
        std_msgs::String::ConstPtr s = m.instantiate<sensor_msgs::PointCloud2>();
        sensor_msgs::PointCloud2 scan = s->data;
        pcl_pub_bag.publish(scan);
        // now publish it



    }

bag.close();