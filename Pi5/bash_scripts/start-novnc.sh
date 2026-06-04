#!/usr/bin/env bash

export USER=root

mkdir -p ~/.vnc

cat > ~/.vnc/xstartup <<'EOF'
#!/usr/bin/env bash
unset SESSION_MANAGER
unset DBUS_SESSION_BUS_ADDRESS
exec startxfce4
EOF

chmod +x ~/.vnc/xstartup

# Kill old sessions if they exist
vncserver -kill :1 2>/dev/null || true

# Start TigerVNC
vncserver :1 -geometry 1280x800 -depth 24

# Start noVNC proxy
/usr/share/novnc/utils/novnc_proxy \
    --vnc localhost:5901 \
    --listen 8080
