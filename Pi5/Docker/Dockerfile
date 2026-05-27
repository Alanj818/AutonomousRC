#Building an Ubuntu Environment containing: ROS2, NAV2, RVIZ, noVNC and thats it 

#Installs Ubuntu24.04 with Ros2-jazzy-desktop
FROM arm64v8/ros:jazzy-perception

ENV DEBIAN_FRONTEND=noninteractive

#All the installs needed for Nav2 and noVNC
RUN apt update && apt install -y \
    ros-jazzy-navigation2 \
    ros-jazzy-nav2-bringup \
    ros-jazzy-rviz2 \
    ros-jazzy-slam-toolbox \
    python3-pip \
    python3-colcon-common-extensions \
    git \
    xfce4 \
    xfce4-goodies \
    tigervnc-standalone-server \
    xvfb \
    x11vnc \
    novnc \
    websockify \
    dbus-x11 \
    && rm -rf /var/lib/apt/lists/*

#THIS WILL AUTO SOURCE ROS2
RUN echo "source /opt/ros/jazzy/setup.bash" >> ~/.bashrc

#COPY ../bash_scripts/start-novnc.sh /start-novnc.sh

#RUN chmod +x /start-novnc.sh

WORKDIR /workspace

#For noVNC
EXPOSE 8080 

#CMD ["/start-novnc.sh"]
CMD ["bash"]
