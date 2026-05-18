"""
    Copyright 2015 Leandro Israel Pinto
	
	This file is part of ICARU_FB.

    ICARU_FB is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    ICARU_FB is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with ICARU_FB.  If not, see <http://www.gnu.org/licenses/>.
"""

"""

# python pubsubgateway -a <address>

"""


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
import icaru_com
icaru_com.connect(True)
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
	p = list(d)
	p = [ord(i) for i in p]
	pack=[]
	while len(p)>0:
		if(p[0] == 0x51):
			pack.append(p[1])
			del p[0]
			del p[0]
		elif(p[0] & 0x40) == 0x40:
			if((p[0] & 0x40) >0):
				pack.append(p[0] & 0x01)
			else:
				pack.append(0)
			del p[0]
		elif(p[0] == 0x05):
			pack.append(0)
			del p[0]
		else:
			print 'Not recognized: %X' % (p[0])
			
	while len(pack)<5:
		pack.append(0)
	if len(pack)>5:
		pack = pack[:5]
	"""
	for i in range(5):
		if((p[i] & 0x40) >0):
			pack.append(p[i] & 0x01)
		else:
			pack.append(0)
	"""		
	pack = [0xAA,0x55,201]+pack+[0x55]
	icaru_com.writePack(''.join([chr(i) for i in pack]))
#	inet.send("#FFA1"+str2hex(chr(71))+str2hex(d[3])+str2hex(d[1])+"$")
	
	
	
	
	
	