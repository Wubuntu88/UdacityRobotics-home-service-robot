# UdacityRobotics-home-service-robot
Project 5 of term 1 of the Udacity Robotics Nanodegree

To bring the workspace up and running, execute the following commands in the terminal:
```bash
mkdir -p /home/workspace/catkin_ws/src
cd /home/workspace/catkin_ws/src
catkin_init_workspace
cd ..
catkin_make
sudo apt-get update
cd /home/workspace/catkin_ws/src
git clone https://github.com/ros-perception/slam_gmapping
git clone https://github.com/turtlebot/turtlebot
git clone https://github.com/turtlebot/turtlebot_interactions
git clone https://github.com/turtlebot/turtlebot_simulator
cd /home/workspace/catkin_ws/
source devel/setup.bash
rosdep -i install gmapping
rosdep -i install turtlebot_teleop
rosdep -i install turtlebot_rviz_launchers
rosdep -i install turtlebot_gazebo
catkin_make
source devel/setup.bash
```

Copy these lines into the /home/workspace/.student_bashrc file and run `source /home/workspace/.student_bashrc`
This will eliminate the `No module named rospkg` when starting gazebo.
```bash
export PATH=/usr/bin:$PATH
source /opt/ros/kinetic/setup.bash
alias ss="source devel/setup.bash"
```
