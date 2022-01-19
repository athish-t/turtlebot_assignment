#pragma once

#include <ros/ros.h>
#include <std_msgs/Empty.h>

class WorldModel
{
public:
	void init();
	void reset();
	bool isInterrupted() {return interrupted;}

    static WorldModel& instance();
    virtual ~WorldModel() {}

private:
    WorldModel() {}
	WorldModel(const WorldModel& other);
	WorldModel& operator=(const WorldModel& other);

	ros::NodeHandle nh;
	void interruptCb(const std_msgs::EmptyConstPtr& msg);

	bool interrupted;
	ros::Subscriber interruptSub;
};