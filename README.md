#XinCheJian Gate Project

## Overview
This project use a motor controlled screw to drive a bold/latch to lock and unlock a gate.

The lowest level circuit consist of a motor driver and a diode + switch based end stop machanism. So in case of arduino failure, the motor won't go crazy and distroys the screw.

On top of that, we have an arduino react to manual button press and listens on the USB Serial port for commands to do the locking/unlocking of the door.

Then there is the high level TPlink 703n router which is connected to arduino through a USB hub and runs a web service which presents the login screen on web browsers.

## Circuit
See circuit/gate.pdf

## Arduino Program
Arduino listens to the status of the 2 physical buttons and keeps its internal status which is if it is openning or closing the gate based on the command giver over the serial port to decide if it should send any output to the motor driver.

See arduino/gate.ino

The protocol could not be simpler. When gate openning is needed, a single lower case character 'o' is sent over the usb-serial port to arduino. And 'c' is sent when closing is needed.

## Setup 703N router

### Installing of OpenWRT firmware
Download the factory upgrade file from OpenWRT website

http://wiki.openwrt.org/toh/tp-link/tl-wr703n

Download Link: http://downloads.openwrt.org/attitude_adjustment/12.09/ar71xx/generic/openwrt-ar71xx-generic-tl-wr703n-v1-squashfs-factory.bin

You can choose the trunk version if you need some more advanced features of openwrt.

http://downloads.openwrt.org/snapshots/trunk/ar71xx/

Once you have downloaded the firmware, power up your 703n, use your computer to connect to this network (wireless or cable) and navigate to its admin page (usually http://192.168.1.1/) and login using the default login (admin/admin or written on the router). Then navigate to the system menu and choose upgrade and choose the file you have downloaded just now as the upgrade file. Once you are upgraded, the router would restart and then you need to follow the instructions to setup the password for root.

Instructions from OpenWRT : http://wiki.openwrt.org/doc/howto/firstlogin

Warning: as 703n has only limited storage, luci is not installed by default, and you'll need to have some Linux console operation experience to continue.

### Setup the WIFI on 703n 
Depends what you need, you can choose one of the following 3 modes:

1. Standalone WiFi network (ap mode)
2. Join existing WiFi network (sta mode)
3. Create its own WiFi network as well as join existing WiFi network (not stable, requires using the trunk version of OpenWrt firmware, not mentioned in official documentation) (2 wifi networks, one ap, one sta)

There are 2 files you need to edit to enable wifi network

````
/etc/config/wireless
/etc/config/network
````

Offical documentation: http://wiki.openwrt.org/doc/uci/wireless
More details coming ...

### Setup the webservice
Install lua on 703n by running the following commands:
````
opkg update
opkg install lua
opkg install luasocket
````

Then install md5sum
````
opkg install coreutils-md5sum
````

Then copy serve.lua to /usr/bin/, copy config/gate to /etc/init.d/ then run 

````
chmod +x /etc/init.d/gate
/etc/init.d/gate enable
/etc/init.d/gate start
````

Now navigate to the router's IP address (e.g. http://192.168.1.1/) you should see the login screen.


