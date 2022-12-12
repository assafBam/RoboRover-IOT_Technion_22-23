#!/bin/python

#	turn on WiFi:
# sudo rfkill unblock all
# sudo ifconfig wlan0 up
#	

import wifi
import os

# turn on wifi:
os.system('sudo rfkill unblock all')
os.system('sudo ifconfig wlan0 up')
#	check if both returns 0. if not then the command failed

# scan available networks:
cells = wifi.scan.Cell.all('wlan0')

# get ssid from user:
ssid = raw_input('please enter the wifi\'s name: ')

# check if there exists a network with the provided ssid:
#	sort the cells list (move the cell with the provided ssid to the begginig of the list)
cells.sort(key=lambda x: x.ssid!=ssid)
if cells[0].ssid != ssid:
	raise IndexError('no network with provided ssid') # decide what to do later, possibly do a while loop

# get password from user:
password = raw_input('please enter the wifi\'s password: ')

# connect to wifi:
scheme = wifi.Scheme.for_cell('wlan0', ssid, cells[0], password)
scheme.activate() # does not work. need to find something else.


