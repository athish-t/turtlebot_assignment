#include "fsm/State.h"
#include "world_model.h"

#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/highgui/highgui.hpp>
#include <image_transport/image_transport.h>
#include "boost/filesystem.hpp"
#include "turtle_app/CameraCapture.h"

namespace fsm
{

class CameraCapture : public State
{
public:
	virtual void run(FiniteStateMachine* fsm) override;
	virtual void init(FiniteStateMachine* fsm) override;
	virtual void evaluateTransitions(FiniteStateMachine* fsm) override;

	/*
	* Get singleton instance of state
	*/
	static State& getInstance();

protected:
	/*
	* Save ROS Image message as image file to filesystem
	*/
	bool saveImage(const sensor_msgs::ImageConstPtr& msg, std::string dir, std::string filename);

private:
	/*
	* Disallow default construction to get state instance as singleton
	*/
	CameraCapture() {}
	CameraCapture(const CameraCapture& other);
	CameraCapture& operator=(const CameraCapture& other);

	std::optional<bool> success;
};

} // end namespace fsm