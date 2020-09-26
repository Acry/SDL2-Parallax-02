#!/usr/bin/env bash

# Test if process is not running
if ! pidof parallax
then
  # start it
  ./parallax </dev/null &>/dev/null &
fi

# Set up watcher
while inotifywait -e close_write parallax.c
do
  sleep .1
  make > /dev/null
  kill -9 $(pidof parallax)
  ./parallax </dev/null &>/dev/null &
  date +%X
done

# One Line
# while inotifywait -e close_write ./parallax.c; do make > /dev/null; kill -9 $(pidof parallax); ./parallax </dev/null &>/dev/null &; date +%X; done

# get pid
# pidof parallax

# get X-Window ID from PID:
# xdotool search --any --pid $pid

# get window geometry
# xdotool getwindowgeometry
# or
# xwininfo -id $pid

# set window position
# xdotool windowmove $id $x $y