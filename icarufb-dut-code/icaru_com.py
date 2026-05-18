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

#
# icaru_com communicates with ICARU network
# 
#
#

import socket
from time import sleep

comsock = None

def connect(isfb=False):
	global comsock
	comsock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	comsock.connect(("localhost", 61900))
	if isfb:
		comsock.send(chr(0x5A)+chr(0x55)+chr(0x5A)+chr(0x55))
	else:
		comsock.send(chr(0xAA))
	
#connect()

def sendIdentify(ident):
	global comsock
	comsock.send(ident)

def disconnect():
	global comsock
	comsock.close()


ENTER_PROGRAMMING = 0x20
EXIT_PROGRAMMING = 0x40
WRITE_MEMORY = 0x60
WRITE_MEMORY_SIZE = 0x80
READ_MEMORY = 0xA0
WRITE_CHECK = 0xC0
def setId(iid):
	if (iid & 0xE0) > 0:
		print 'Error, id must be "0 < id < 32".' 
		return False
	global ENTER_PROGRAMMING
	global EXIT_PROGRAMMING
	global WRITE_MEMORY
	global WRITE_MEMORY_SIZE
	global READ_MEMORY
	global WRITE_CHECK
	
	ENTER_PROGRAMMING = 0x20 | iid
	EXIT_PROGRAMMING = 0x40 | iid
	WRITE_MEMORY = 0x60 | iid
	WRITE_MEMORY_SIZE = 0x80 | iid
	READ_MEMORY = 0xA0 | iid
	WRITE_CHECK = 0xC0 | iid

def createPacksWriteMemory(data):
	packs = []
	while(len(data) >= 5):
		packs.append(chr(0xAA) + chr(0x55) + chr(WRITE_MEMORY) + ''.join([chr(i) for i in data[:5]]) + chr(0x55))
		data = data[5:]
	if(len(data) > 0):
		d2 = ''.join([chr(i) for i in data])
		while len(d2) < 4:
			d2 = d2 + chr(0)
		packs.append(chr(0xAA) + chr(0x55) + chr(WRITE_MEMORY_SIZE) + chr(len(data)) + d2 + chr(0x55))
	return packs


def writePack(pack):
	global comsock
	comsock.send(pack)
	print 'WRITING: ',
	print [("%X"%(ord(i))) for i in pack]
	
def getChecksum(pack):
	cs = 0;
	for d in pack:
		cs = cs + d
	return cs & 0xFFFF

def writeIcaruMemory(address, data, iid):
	#connect()
	packs = createPacksWriteMemory(data)
	pe = [chr(0xAA) + chr(0x55) + chr(ENTER_PROGRAMMING) + chr(iid>>8) + chr(iid & 0xFF) + chr(address>>8) + chr(address & 0xFF)+chr(0)+ chr(0x55)]
	px = [chr(0xAA) + chr(0x55) + chr(EXIT_PROGRAMMING) + chr(iid>>8) + chr(iid & 0xFF) + chr(0) + chr(0)+ chr(0) +  chr(0x55)]
	#writePack(pe)
	packs = pe+packs+px
	for p in packs:
		writePack(p)
		
	cs = getChecksum(data)
	rcs = None
	
	print "Waiting Checksum (%d)..." % (cs)
	
	#comment to avoid checksum
	"""
	while rcs != cs:
		strpack = readPack()
		
		if strpack != None:
			rp = list(strpack)
			print [("%X"%(ord(i))) for i in rp]
			p = [ord(i) for i in rp]
			print [("%X"%(i)) for i in p]
			if(p[2] == WRITE_CHECK):
				rcs = (p[3]<<8) | p[4]
			print "%X == %X"%(p[2], WRITE_CHECK)
			print rcs
			
	print " (%d) OK" % (rcs)
	"""
	###
	
	#writePack(px)
	#sleep(0.3)
	#disconnect()
	return True
	


"""
def packCS(pack):
	cs = 0
	for i in range(len(pack)):
		cs = cs + ord(pack[i])
	return cs 
"""

"""
def writePackConf(address,data):
	writePack(address,data)
	start_time = time.time()
	et = start_time - time.time()

	while et < 10:
		p = readPack()
"""	
	
_socketgetbytes=[]
def socketget(bytes, sock):
	global _socketgetbytes
	while(len(_socketgetbytes) < bytes):
		_socketgetbytes = _socketgetbytes + list(sock.recv(4096))
		#print "SOCKBYTES: ",printHex([ord(i) for i in _socketgetbytes])
		if _socketgetbytes == '' or _socketgetbytes == None or len(_socketgetbytes)==0:
			return None
	r= _socketgetbytes[:bytes]
	for i in range(bytes):
		del _socketgetbytes[0]
	if len(r)>1:
		return [ord(i) for i in r]
	return ord(r[0])

def readPack():
	global comsock
	data = chr(0xAA) + chr(0x55)
	c = socketget(1,comsock)
	if(c == 0xAA):
		c = socketget(1,comsock)
		if(c == 0x55):
			for i in range(6):
				c = socketget(1,comsock) 
				data = data + chr(c)
			c = socketget(1,comsock)
			if(c == 0x55):
				return data + chr(0x55)
	
	print "%X" % (c)
		
	return None












