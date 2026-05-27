#Building an Ubuntu Environment containing: ROS2, NAV2, RVIZ, noVNC and thats it 

#Installs Ubuntu24.04 with Ros2-jazzy-desktop
FROM osrf/ros:jazzy-desktop

ENV DEBIAN_FRONTEND=noninteractive

#All the installs needed for Nav2 and noVNC
RUN apt update && apt install -y \
    ros-jazzy-navigation2 \
    ros-jazzy-nav2-bringup \
    python3-pip \
    python3-colcon-common-extensions \
    git \
    xfce4 \
    xfce4-goodies \
    tigervnc-standalone-server \
    novnc \
    websockify \
    dbus-x11 \
    && rm -rf /var/lib/apt/lists/*

#THIS WILL AUTO SOURCE ROS2
RUN echo "source /opt/ros/jazzy/setup.bash" >> ~/.bashrc

#THIS WILL AUTO SOURCE MY WORKSPACE
RUN echo "source /workspace/AutonomousRC/Pi5/ros2_ws/install/setup.bash" >> ~/.bashrc

WORKDIR /workspace

#For noVNC
EXPOSE 8080 

CMD ["bash"] 
