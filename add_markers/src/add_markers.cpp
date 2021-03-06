#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle nh;
  ros::Rate r(1);
  ros::Publisher marker_pub = nh.advertise<visualization_msgs::Marker>("visualization_marker", 1);

  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;
  bool robot_is_at_pickup_loc = false;
  bool robot_is_at_drop_off_loc = false;

  visualization_msgs::Marker marker;
  // Set the frame ID and timestamp.  See the TF tutorials for information on these.
  marker.header.frame_id = "map";
  marker.header.stamp = ros::Time::now();

  // Set the namespace and id for this marker.  This serves to create a unique ID
  // Any marker sent with the same namespace and id will overwrite the old one
  marker.ns = "add_markers";
  marker.id = 0;

  // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
  marker.type = shape;

  // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
  marker.action = visualization_msgs::Marker::ADD;

  // Set the marker at the pickup location at middle of the bottom hallway
  marker.pose.position.x = 2.68486404419;
  marker.pose.position.y = -2.00983738899;
  marker.pose.position.z = 0;
  marker.pose.orientation.x = 0.0;
  marker.pose.orientation.y = 0.0;
  marker.pose.orientation.z = 0.0;
  marker.pose.orientation.w = 1.0;

  // Set the scale of the marker -- 1x1x1 here means 1m on a side
  marker.scale.x = 0.25;
  marker.scale.y = 0.25;
  marker.scale.z = 0.25;

  // Set the color -- be sure to set alpha to something non-zero!
  marker.color.r = 0.1f;
  marker.color.g = 0.5f;
  marker.color.b = 1.0f;
  marker.color.a = 1.0;

  marker.lifetime = ros::Duration();
  while (ros::ok()) {
    // Publish the marker
    while (marker_pub.getNumSubscribers() < 1) {
      if (!ros::ok()) {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }
    ROS_INFO("publishing marker at pickup location: x: %f, y: %f, z: %f",
        marker.pose.position.x, marker.pose.position.y, marker.pose.position.z);
    marker_pub.publish(marker);

    nh.getParam("robot_is_at_pickup_loc", robot_is_at_pickup_loc);
    while( ! robot_is_at_pickup_loc ) {
        sleep(0.25);
        nh.getParam("robot_is_at_pickup_loc", robot_is_at_pickup_loc);
        ROS_INFO("add_markers verified robot is at pickup location");
    }

    // Sending message to 'delete' the marker
    marker.action = visualization_msgs::Marker::DELETE;
    marker_pub.publish(marker);

    // Setting up marker to be added to the drop-off location
    // Top of the middle hallway (left of the top hallway)
    marker.pose.position.x = -0.133507564664;
    marker.pose.position.y = 4.03573846817;
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;
    marker.action = visualization_msgs::Marker::ADD;

    nh.getParam("robot_is_at_drop_off_loc", robot_is_at_drop_off_loc);
    while( ! robot_is_at_drop_off_loc ) {
        sleep(0.25);
        nh.getParam("robot_is_at_drop_off_loc", robot_is_at_drop_off_loc);
        ROS_INFO("add_markers verified robot is at drop-off location");
    }

    // sending message to add the marker to the drop-off location
    ROS_INFO("publishing marker at drop-ff location: x: %f, y: %f, z: %f",
            marker.pose.position.x, marker.pose.position.y, marker.pose.position.z);
    marker_pub.publish(marker);

    r.sleep();
  }
}













