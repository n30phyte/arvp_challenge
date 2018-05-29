//
// Created by Michael on 26/05/2018.
//
#include <iostream>
#include <string>
#include <functional>

#include "ros/ros.h"
#include "std_msgs/Int16.h"

class Values
{
  public:
    void messageCallback(const std_msgs::Int16::ConstPtr &recv_message)
    {
        if (count != 2)
        {
            value += recv_message->data;
            count++;
            if (count == 1)
            {
                std::cout << value << std::endl
                          << "What would you like to add to that?" << std::endl;
            }
        }

        if (count == 2)
        {
            std_msgs::Int16 message;
            message.data = value;

            channelPublisher.publish(message);

            std::cout << "Added!" << std::endl;
            count = 0;
        }
    }

  private:
    int value = 0;
    int count = 0;

    ros::NodeHandle hThisNode;

    ros::Publisher channelPublisher = hThisNode.advertise<std_msgs::Int16>("challenge_reply", 1);
};

int main(int argc, char **argv)
{
    ros::init(argc, argv, "server");

    ros::NodeHandle hThisNode;

    Values test;

    ros::Subscriber channelSubscriber = hThisNode.subscribe("challenge_test", 2, &Values::messageCallback, &test);

    ros::spin();
}