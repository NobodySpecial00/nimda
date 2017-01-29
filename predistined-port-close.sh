#!/bin/bash
iptables -A INPUT -p tcp -s 0/0 -d 0/0 --dport 7100 -j DROP       
iptables -A INPUT -p tcp -s 0/0 -d 0/0 --dport 515 -j DROP        
iptables -A INPUT -p udp -s 0/0 -d 0/0 --dport 515 -j DROP        
iptables -A INPUT -p tcp -s 0/0 -d 0/0 --dport 111 -j DROP        
iptables -A INPUT -p udp -s 0/0 -d 0/0 --dport 111 -j DROP       
iptables -A INPUT -p all -s localhost -i eth0 -j DROP 
iptables -A INPUT -p tcp -s 0/0 -d 0/0 --dport 23 -j DROP         
iptables -A INPUT -p tcp -s 0/0 -d 0/0 --dport 2049 -j DROP       
iptables -A INPUT -p udp -s 0/0 -d 0/0 --dport 2049 -j DROP       
iptables -A INPUT -p tcp -s 0/0 -d 0/0 --dport 6000:6009 -j DROP  
ufw enable
ufw deny 2049
ufw deny 111
ufw deny 515
ufw deny 23
