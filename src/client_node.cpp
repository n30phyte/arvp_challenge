//
// Created by Michael on 26/05/2018.
//
#include <iostream>
#include <string>

#include "ros/ros.h"
#include "std_msgs/Int16.h"

void messageCallback(const std_msgs::Int16::ConstPtr &message)
{
    std::cout << message->data << std::endl;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "client");

    ros::NodeHandle hThisNode;
    ros::Publisher channelPublisher = hThisNode.advertise<std_msgs::Int16>("challenge_test", 2);
    ros::Subscriber channelSubscriber = hThisNode.subscribe("challenge_reply", 1, &messageCallback);

    int messageCount = 0;

    std_msgs::Int16 message;
    std::string input;

    std::vector<int> values;

    while (ros::ok()) // Main program loop
    {

        std::cout << "Please input a number between 0 and 1000" << std::endl;

        std::cin >> input;

        message.data = std::stoi(input);
        // Converts the message from string to integer

        if (message.data > 0 && message.data < 1000)
        {
            channelPublisher.publish(message);
            values.push_back(std::stoi(input));

            ros::spinOnce();

            messageCount++;
        }
        else
        {
            std::cout << "Invalid number" << std::endl;
        }

        if(messageCount == 2)
        {
            std::cout << values[0] << " + " << values[1] << " = ";

            ros::spin();
            
            return 0;
        }
    }
}