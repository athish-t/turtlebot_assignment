#!/usr/bin/env python

import rospy
from visualization_msgs.msg import Marker, MarkerArray
from geometry_msgs.msg import Vector3, Pose
from copy import deepcopy

###############################################
# This script reads the goals from param server
# and created markers in rviz for visualization
###############################################

class GoalViz:
  def __init__(self):
    self.markers_pub = rospy.Publisher("goals", MarkerArray, queue_size=1, latch=True)

  def publish_markers(self):
    goal_points = rospy.get_param('~turtle_goals')
    marker_array = MarkerArray()
    for idx, goal in enumerate(goal_points):
        # goal point cube marker
        goal_point_cube_marker = Marker()
        goal_point_cube_marker.header.frame_id = 'map'
        goal_point_cube_marker.ns = "goal_point_cube"
        goal_point_cube_marker.id = idx
        goal_point_cube_marker.type = Marker().CUBE
        goal_point_cube_marker.action = 0
        pose = Pose()
        pose.position.x = goal['coords'][0]
        pose.position.y = goal['coords'][1]
        goal_point_cube_marker.pose = pose
        goal_point_cube_marker.pose.orientation.w = 1
        goal_point_cube_marker.scale = Vector3(0.2, 0.2, 0.2)
        goal_point_cube_marker.color.g = 1.0
        goal_point_cube_marker.color.a = 1.0
        marker_array.markers.append(goal_point_cube_marker)

        # goal point text marker
        goal_point_text_marker = deepcopy(goal_point_cube_marker)
        goal_point_text_marker.type = Marker().TEXT_VIEW_FACING
        goal_point_text_marker.pose.position.z = 0.2
        goal_point_cube_marker.color.r = 1.0
        goal_point_text_marker.ns = "goal_point_text"
        goal_point_text_marker.text = str(goal['id'])
        marker_array.markers.append(goal_point_text_marker)

    self.markers_pub.publish(marker_array)

if __name__ == '__main__':
    rospy.init_node('goal_viz')
    viz = GoalViz()
    viz.publish_markers()

    try:
        rospy.spin()
    except rospy.ROSInterruptException:
        pass