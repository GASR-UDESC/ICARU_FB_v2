"""
import socket

UDP_IP = "localhost"
UDP_PORT = 61401

sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP
sock.bind((UDP_IP, UDP_PORT))

while True:
	data, addr = sock.recvfrom(1024) # buffer size is 1024 bytes
	print "received message:", data
"""

import socket
import struct
#import iecvmnet as inet

def str2hex(str):
	h = ""
	for c in str:
		h = h + "%02X" % (ord(c))
	return h

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
sock.bind(('', 61401))
# wrong: mreq = struct.pack("sl", socket.inet_aton("224.51.105.104"), socket.INADDR_ANY)
mreq = struct.pack("=4sl", socket.inet_aton("225.0.0.1"), socket.INADDR_ANY)

sock.setsockopt(socket.IPPROTO_IP, socket.IP_ADD_MEMBERSHIP, mreq)

#inet.init("localhost", 5200)

while True:
	d = sock.recv(1024)
	print d
	print str2hex(d)
#	inet.send("#FFA1"+str2hex(chr(71))+str2hex(d[3])+str2hex(d[1])+"$")
	
	
	
	
	
	