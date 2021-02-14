# Snap

This code is my ongoing attempt to turn my M5Camera model A into a remotely controlled camera. 
The goal is to have a very simple webserver running that upon a GET request does the following:

1. Turn on an LED (I salvaged a bulb from a cheap torch that I drive with a ULN2803 (I had many laying around and my transistor circuit didn't work.) 
2. Take a picture in high quality.
3. Turn off the LED
4. Return the picture as a JPEG image.

The purpose is to request an image from a computer at a regular interval to take pictures of our energy meter, but that's for later.
