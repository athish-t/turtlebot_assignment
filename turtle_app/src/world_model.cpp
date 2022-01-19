#include "world_model.h"


WorldModel& WorldModel::instance()
{
	static WorldModel singleton;
	return singleton;
}

void WorldModel::init()
{
	reset();
	interruptSub = nh.subscribe("/interrupt", 1, &WorldModel::interruptCb, this);
}

void WorldModel::reset()
{
	interrupted = false;
}

void WorldModel::interruptCb(const std_msgs::EmptyConstPtr& msg)
{
	interrupted = true;
}

