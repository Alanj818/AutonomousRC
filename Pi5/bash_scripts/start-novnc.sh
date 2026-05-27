#!/usr/bin/env bash

export DISPLAY=:1

Xvfb :1 -screen 0 1280x800x24 &

startxfce4 &

x11vnc -display :1 -nopw -forever -shared -rfbport 5900 &

novnc_proxy --vnc localhost:5900 --listen 8080 &

sleep infinity
