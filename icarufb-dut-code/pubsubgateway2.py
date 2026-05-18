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

"""
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
#sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_TTL, 20)
"""

while True:
	p = icaru_com.readPack()
	if p != None:
		pack = [ord(i) for i in p]
		if(pack[2]==202):
			print pack
			data = ''
			"""
			for i in range(5):
				data = data + chr(0x40 |  (pack[i+3] & 1))
			"""
			data = data + chr(0x40 |  (pack[3] & 1)) + chr(0x40 |  (pack[4] & 1))+ chr(05)+ chr(05)+ chr(05)
			#data = data + chr(0x40 |  (pack[3] & 1)) +  chr(05)+ chr(05)+ chr(05)+ chr(05)

				#data = data + chr(0x51)+ chr(pack[i+3])
			#sock.send(data)
			print "DATA: "+data+' len: %d' % (len(data) )
			print str2hex(data)
			#sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, socket.IPPROTO_UDP)
			sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
			ttl = struct.pack('b',1)
			sock.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_TTL, ttl)
			sock.sendto(data, ("225.0.0.1",61402))
			sock.close()
	
	
	
	
	
	