# turtlebot_assignment

This project has been developed and tested with Ubunutu 20.04 Focal and ROS1 Noetic.

Ideally, there shouldn't be any issues running with earlier versions, however steps to installing dependencies may differ.

### Install

		export CATKIN_WS=~/catkin_ws
		mkdir -p $CATKIN_WS/src
		cd $CATKIN_WS

		git clone https://github.com/athish-t/turtlebot_fsm.git
		git submodule update --init --recursive

		rosdep install --from-paths src --ignore-src -r -y
		sudo apt install ros-noetic-amcl # not released in rosdep yet for noetic

		catkin build turtle_bringup

### Run
		export TURTLEBOT3_MODEL=burger # only support burger
		roslaunch turtle_bringup sim.launch