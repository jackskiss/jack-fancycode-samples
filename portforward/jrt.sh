#!/bin/bash

if [ $# -lt 2 ];then
	echo "Need more parameters"
	echo "jrt.sh [LOCAL IP Adress] [ PORT TO CONNECT]"
	exit 0
fi

LOCAL_IP="$1"
CONNECT_PORT="$2"

sudo apt-get install rinetd
sudo adb forward tcp:$2 tcp:$2
sudo echo -e "${LOCAL_IP} ${CONNECT_PORT} 127.0.0.1 ${CONNECT_PORT}" | sudo tee /etc/rinetd.conf 
sudo echo -e "logfile /var/log/rinetd.log" | sudo tee -a /etc/rinetd.conf
sudo service rinetd restart
netstat -lntp

echo "Completed!!!"





