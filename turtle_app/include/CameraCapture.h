#include "fsm/State.h"

#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/highgui/highgui.hpp>
#include <image_transport/image_transport.h>
#include "boost/filesystem.hpp"

namespace fsm
{

class CameraCapture : public State
{
public:
	virtual void run(FiniteStateMachine* fsm) override;
	virtual void init(FiniteStateMachine* fsm);

	static State& getInstance();

private:
	CameraCapture() {}
	CameraCapture(const CameraCapture& other);
	CameraCapture& operator=(const CameraCapture& other);

	bool saveImage(const sensor_msgs::ImageConstPtr& msg, std::string dir, std::string filename);
};

} // end namespace fsm