#include <ros/ros.h>
#include <geometry_msgs/TwistStamped.h>
#include <geometry_msgs/TwistStamped.h>
#include <unitree/robot/go2/sport/sport_client.hpp>
#include <unistd.h>

class SubPubCmd
{
public:
    SubPubCmd()
    {
        // Initialize the ROS node
        ros::NodeHandle nh;

        // Subscribe to the "cmd_vel" topic
        sub_cmd_vel_ = nh.subscribe("cmd_vel", 10, &SubPubCmd::cmdVelCallback, this);

        sport_client.SetTimeout(10.0f); // 超时时间
        sport_client.Init();
    }

    void cmdVelCallback(const geometry_msgs::TwistStamped::ConstPtr &msg)
    {
        sport_client.Move(std::min(msg->twist.linear.x, 0.5), std::min(msg->twist.linear.y, 0.5), msg->twist.angular.z);
        std::cout << "linear.x: " << msg->twist.linear.x << std::endl << "linear.y: " << msg->twist.linear.y << std::endl << "angular.z: " << msg->twist.angular.z << std::endl;
    }

private:
    unitree::robot::go2::SportClient sport_client;
    ros::Subscriber sub_cmd_vel_;
};

int main(int argc, char **argv)
{
    // Initialize the ROS node
    ros::init(argc, argv, "sub_pub_cmd_node");
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " networkInterface" << std::endl;
        exit(-1);
    }
    unitree::robot::ChannelFactory::Instance()->Init(0, argv[1]);
    // Create an instance of the SubPubCmd class
    SubPubCmd sub_pub_cmd;

    // Spin the ROS node
    ros::spin();

    return 0;
}
