#include "Navigate.h"
#include "CameraCapture.h"
#include "fsm/FiniteStateMachine.h"

namespace fsm
{

State& CameraCapture::getInstance()
{
	static CameraCapture singleton;
	return singleton;
}

void CameraCapture::init(FiniteStateMachine* fsm)
{
	ROS_INFO_STREAM_NAMED(__func__, "In CameraCapture state");
}

bool CameraCapture::saveImage(const sensor_msgs::ImageConstPtr& image_msg, std::string dir, std::string filename)
{
	// Convert to cv image
	cv::Mat image;
    try{
		image = cv_bridge::toCvShare(image_msg, "bgr8")->image;
    } catch(cv_bridge::Exception){
		ROS_WARN_NAMED(__func__, "Unable to convert %s image to bgr8", image_msg->encoding.c_str());
		return false;
    }

    if (image.empty()) {
    	ROS_WARN_NAMED(__func__, "Couldn't save image, no data!");
    	return false;
    }

    // Create directories and paths
    boost::filesystem::path dirPath = boost::filesystem::path(dir);
	boost::filesystem::create_directories(dir);
    boost::filesystem::path filePath = dirPath / boost::filesystem::path(filename);

    // Save
    cv::imwrite((boost::filesystem::path(dir) / boost::filesystem::path(filename)).string(), image);
    return true;
}

void CameraCapture::run(FiniteStateMachine* fsm)
{
	const std::string fileName = std::to_string(std::any_cast<int>(fsm->getUserData().at("last_checkpoint_id"))) + ".jpg";
	const std::string& imageSaveDir = std::any_cast<std::string&>(fsm->getUserData().at("image_save_path"));

	ROS_INFO_STREAM_NAMED(__func__, "Saving image to " << fileName);

	// Wait for ROS message from camera
	sensor_msgs::ImageConstPtr imagePtr = ros::topic::waitForMessage<sensor_msgs::Image>("kinect/color/image_raw");

	if (imagePtr == nullptr) {
		ROS_ERROR_STREAM_NAMED(__func__, "Unable to get image from camera");
	}
	else if (!saveImage(imagePtr, imageSaveDir, fileName)) {
		ROS_ERROR_STREAM_NAMED(__func__, "Unable to save image");
	}
	else {
		ROS_INFO_STREAM_NAMED(__func__, "Captured and saved image successfully");
	}

	// Transition
	fsm->setState(Navigate::getInstance());
}

} // end namespace fsm