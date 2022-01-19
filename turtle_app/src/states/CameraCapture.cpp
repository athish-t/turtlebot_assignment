#include "fsm/FiniteStateMachine.h"
#include "states/Navigate.h"
#include "states/CameraCapture.h"

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
	success = std::nullopt;
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
    ROS_INFO_STREAM_NAMED(__func__, "Image saved successfully");
    return true;
}

void CameraCapture::run(FiniteStateMachine* fsm)
{
	const std::string fileName = std::to_string(std::any_cast<int>(fsm->getUserData().at("last_checkpoint_id"))) + ".jpg";
	const std::string& imageSaveDir = std::any_cast<std::string&>(fsm->getUserData().at("image_save_path"));

	ROS_INFO_STREAM_NAMED(__func__, "Saving image to " << fileName);

	// Get ROS Image message from camera
	ros::NodeHandle nh;
	ros::ServiceClient cameraClient = nh.serviceClient<turtle_app::CameraCapture>("camera_server/get_image");
	sensor_msgs::ImageConstPtr imagePtr;
	turtle_app::CameraCapture captureRequest;
	bool serviceSuccess = cameraClient.call(captureRequest);

	if (!serviceSuccess || !captureRequest.response.success) {
		ROS_ERROR_STREAM_NAMED(__func__, "Unable to get image from camera");
		success = false;
		return;
	}
	else if (captureRequest.response.success && !saveImage(boost::make_shared<sensor_msgs::Image>(captureRequest.response.image), imageSaveDir, fileName)) {
		ROS_ERROR_STREAM_NAMED(__func__, "Unable to save image");
		success = false;
		return;
	}

	success = true;
}

void CameraCapture::evaluateTransitions(FiniteStateMachine* fsm)
{
	// Transition regardless of whether capturing successed or failed
	if (success.has_value()) {
		fsm->setState(Navigate::getInstance());
	}
}

} // end namespace fsm