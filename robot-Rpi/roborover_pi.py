#!/bin/python3

#	turn on WiFi:
# sudo rfkill unblock all
# sudo ifconfig wlan0 up
#	

import wifi
import os
from bluedot.btcomm import BluetoothClient as btc
import qrcode
from pyngrok import ngrok

#config ngrok
ngrok.set_auth_token('2HaOK69ss6F3oaheISAVSJ9egoN_2ojAtW6FK5HyVJDuNeVy5')

def getPassword(networks_data, name):
    for net_ssid, net_psk in networks_data:
        if net_ssid == name:
            return net_psk
    return ''

def getNetworksInfo():
    conf_file = open('/etc/wpa_supplicant/wpa_supplicant.conf')
    conf_str = conf_file.read()
    conf_str = conf_str.replace('\n', '').replace('\t', '')

    networks = conf_str.split('network=')
    networks = [i for i in networks if 'ssid' in i]
    networks = [i.split('"') for i in networks]


    networks_data = []
    for net in networks:
        ssid, password = '', ''
        for i, elem in enumerate(net):
            if 'ssid' in elem:
                ssid = net[i+1]
            if 'psk' in elem:
                password = net[i+1]
        networks_data.append((ssid, password))
    return networks_data

def data_rec(data):
    global ssid
    global password
    global bluetooth_connection
    global roborover_ip
    print(data)
    if 'ssid' in data:
        bluetooth_connection.send(ssid)
        print('sent ssid via bluetooth')
    if 'password' in data:
        bluetooth_connection.send(password)
        print('sent password via bluetooth')
    if '.' in data:
        roborover_ip = data


# scan available networks:
cell = list(wifi.scan.Cell.all('wlan0'))[0] # note that when WiFi is connected this returns the connected WiFi only

ssid = cell.ssid
networks = getNetworksInfo()
password = getPassword(networks, ssid)
roborover_ip = ''

print("ssid: " + ssid + '\t password: ' + password)
bluetooth_connection = btc('RoboRover', data_rec)

while roborover_ip == '':
    pass

tunnel = ngrok.connect(roborover_ip + ':80')
tunnel_qr = qrcode.make(tunnel.public_url)
tunnel_qr.show()


