# wifi_analyzer
PS project

lecture:

https://www.cs.put.poznan.pl/mkalewski/edu/ps/doc/filtracja-ramek-nasluchiwanych-biblioteka-libpcap.pdf


https://www.tcpdump.org/manpages/pcap.3pcap.html
https://lynxbee.com/sniffex-c-program-to-capture-wifi-packets-using-libpcap/#.Yn_iQ-hByUk


http://recursos.aldabaknocking.com/libpcapHakin9LuisMartinGarcia.pdf
https://www.tcpdump.org/manpages/pcap_datalink.3pcap.html
https://www.tcpdump.org/linktypes.html


IEE80211 headers struct:
https://elixir.bootlin.com/linux/latest/source/include/linux/ieee80211.h


setting monitor mode
```bash
sudo iw phy phy0 interface add mon0 type monitor
sudo iw dev wlan0 del
sudo ifconfig mon0 up
sudo iw dev mon0 set freq 5180 # for 5G
iwconfig mon0 # to check if works
```
or
```bash
airmon-ng check kill
airmon-ng start wlan0
iwconfig
```

cleaning
```bash
sudo iw dev mon0 del
sudo iw phy phy0 interface add wlan0 type managed
iwconfig wlan0
```
or
```bash
airmon-ng stop wlan0mon #wlan0mon may be different
systemctl start NetworkManager
##############################################################
#### in case of problem with DNS
rm /etc/resolv.conf && systemctl restart NetworkManager.service
```
