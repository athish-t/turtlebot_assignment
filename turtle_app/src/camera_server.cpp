#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <image_transport/image_transport.h>

#include "turtle_app/CameraCapture.h"

class CameraServer
{
public:
	CameraServer()
	: nh()
	, rpnh("~")
	, it(nh)
	{
		imageSub = it.subscribe("kinect/color/image_raw", 1, &CameraServer::imageCb, this);
		cameraServer = rpnh.advertiseService("get_image", &CameraServer::serviceCb, this);
	}

private:
	void imageCb(const sensor_msgs::ImageConstPtr& msg)
	{
		imagePtr = msg;
	}

	bool serviceCb(turtle_app::CameraCaptureRequest& req, turtle_app::CameraCaptureResponse& res)
	{
		if (imagePtr != nullptr) {
			res.success = true;
			res.image = *imagePtr;
		} else {
			res.success = false;
		}

		return true;
	}

	ros::NodeHandle nh;
	ros::NodeHandle rpnh;
	ros::ServiceServer cameraServer;
	image_transport::ImageTransport it;
	image_transport::Subscriber imageSub;
	sensor_msgs::ImageConstPtr imagePtr;
};


int main(int argc, char** argv)
{
	ros::init(argc, argv, "camera_server");
	ros::NodeHandle nh;

	ROS_INFO_STREAM_NAMED(__func__, "Starting camera server");

	CameraServer server;
	ros::spin();

	return 0;
}
