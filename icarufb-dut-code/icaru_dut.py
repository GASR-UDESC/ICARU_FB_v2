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
# icaru_dut is a server to receive reconfiguration commands for 
# an ICARU_FB device. 
# 
#

import os
import socket
import xml.etree.ElementTree as ET
import thread
import sys
import icaru_compiler
import icaru_mapper 
from flags import *


serversocket = socket.socket(
    socket.AF_INET, socket.SOCK_STREAM)
#serversocket.bind((socket.gethostname(), 61494))
serversocket.bind(('localhost', 61494))
serversocket.listen(5)

print 'Server started'

TEMP_DIR = 'temp'

mapfname = ''

def createFB(fbname, fbtype):
	global mapfname
	if not icaru_mapper.fbExists(fbtype):
		fbobj = {}
		fbobj['name'] = fbtype
		fbfilename = os.path.join(LIBRARY_DIR,fbtype+'.fbt')
		icaru_compiler.run(fbfilename, TEMP_DIR)
		
		f = open(os.path.join(TEMP_DIR, fbtype+'.hex'))
		c = f.read()
		b = c.split(' ')
		b.remove('')
		bcode = [int(i) for i in b]
		fbobj['bytecode'] = bcode
		print fbobj['bytecode']
		
		f = open(os.path.join(TEMP_DIR, fbtype+'.map'))
		c = f.read()
		c = c.replace('\n','')
		c = c.replace('\r','')
		b = c.split(',')
		vmap={}
		for v in b:
			l = v.split(':')
			if len(l) >2:
				vmap[l[0]] = {'address':int(l[1]), 'size':int(l[2]), 'type':'EVENT'}
		f = open(os.path.join(TEMP_DIR, fbtype+'.vt'))
		c = f.read()
		c = c.replace('\n','')
		c = c.replace('\r','')
		b = c.split(';')	
		for v in b:
			l = v.split(':')
			if len(l) >1:
				vmap[l[0]]['type'] = l[1]
				
		fbobj['varsmap'] = vmap	
		
		icaru_mapper.fbAddType(fbobj)
		print '(dut) FB Type "%s" added.' % (fbtype)
	else:
		print '(dut) FB "%s" already in ICARU_VM.' % (fbtype)
	print 'Adding instance "%s".' % (fbname)
	if(icaru_mapper.fbAddInstance(fbname, fbtype)):
		print "(dut) FB %s (%s) created." % (fbname, fbtype)
		return True
	
	print "(dut) ERROR: FB %s (%s) not created." % (fbname, fbtype)
	return False
		

def client_thread(sock):
	cmd = ''
	received = ''
	
	while 1:
		print 'Waiting for more data...'
		rcv =  sock.recv(2048)
		if rcv == '':
			break
		received = rcv
		#print "RCV: "+received
		#print ord(received[0])
		#print ord(received[1])
		#print ord(received[2])
		#print ord(received[3])
		#print ord(received[4])
		#print ord(received[5])
		
		if ord(received[0]) == 0x50:
			size1 = ((ord(received[1])<<8) | ord(received[2]))
			received = received[3:]
			received = received[size1:]
			if ord(received[0]) == 0x50:
				size = ((ord(received[1])<<8) | ord(received[2]))
				#print 'SIZE: ',size
				while(len(received[3:]) < size):
					received = received + sock.recv(2048)
					
				cmd = ''
				received = received[3:]
				while len(cmd) < size:
					cmd = cmd + received[0]
					received = received[1:]
		
		
		try:
			while  len(cmd)>0 and cmd[0] != '<': 
				#print "CMD: %X" % (ord(cmd[0]))
				cmd = cmd[1:]
			cmd = cmd.replace('\n','')
			cmd = cmd.replace('\r','')
			#cmd = cmd.replace('  ',' ')
			root = ET.fromstring(cmd)
			resp=''
			if root.attrib['Action'] == 'START':
				if not icaru_mapper.writePar('START.COLD','1'):
						print "(dut) ERROR: Can't write parameter %s=%s." %(r,v)
				resp = '<Response ID="%s"/>' % ('')
				icaru_mapper.printTable()
			else:
				if len(root.findall('Parameter'))>0:
					p = root.findall('Parameter')[0]
					r = p.attrib['Reference']
					v = p.attrib['Value']
					if not icaru_mapper.writePar(r,v):
						print "(dut) ERROR: Can't write parameter %s=%s." %(r,v)
					resp = '<Response ID="%s"><Parameter Reference="%s"/></Response>' % (root.attrib['ID'], root.findall('Parameter')[0].attrib["Reference"])
				elif len(root.findall('FB'))>0:
					fb = root.findall('FB')[0]
					if(fb.attrib['Name'] != 'RESM'):
						createFB(fb.attrib['Name'], fb.attrib['Type'])
						resp = '<Response ID="%s"/>' % (root.attrib['ID'])
					else:
						resp = '<Response ID="%s"/>' % (root.attrib['ID'])
				elif len(root.findall('Connection'))>0:
					c = root.findall('Connection')[0]
					fromfbvar = c.attrib['Source']
					tofbvar = c.attrib['Destination']
					if(icaru_mapper.ConnAdd(fromfbvar,tofbvar)):
						print ''
					else:
						print '(dut) ERROR Creating connection %s->%s' % (fromfbvar, tofbvar)
					resp = '<Response ID="%s"/>' % (root.attrib['ID'])
				else:
					resp = '<Response ID="%s"/>' % (root.attrib['ID'])
				
			l = len(resp)	
			#resp = chr(0x50)+chr(0)+chr(0)+chr(0x50)+chr(l>>8)+chr(l&0xFF)+resp
			resp = chr(0x50)+chr(l>>8)+chr(l&0xFF)+resp
			print 'RUN: '+cmd 
			
			print 'RESP: ['+resp+']'
			print ' '
			cmd = ''
			sock.send(resp)
		except Exception, e:
			print 'Parse error... '
			print '['+cmd+']'
			print e
			import traceback
			traceback.print_exc()
			

			
def printUsage():
	print 'Usage: python icaru_dut.py -m map.map -da device_address -dm device_memory_bytes -l library_dir'

	
DEVICE_MEM = 0
DEVICE_ADDR=0
LIBRARY_DIR='.'
MAPFNAME='map.map'

while 1:

	if (not flagExist('-m')) | (not flagExist('-da')) | (not flagExist('-dm')) | (not flagExist('-l')):
		printUsage()
		exit()

	if flagExist('-m'):
		MAPFNAME = getPPar('-m')
	if flagExist('-da'):
		DEVICE_ADDR = int(getPPar('-da'))
	if flagExist('-dm'):
		DEVICE_MEM = int(getPPar('-dm'))	
	if flagExist('-l'):
		LIBRARY_DIR = getPPar('-l')	
		#TEMP_DIR = os.path.join(LIBRARY_DIR,'temp')

	config = {}
	config['memory_len'] = DEVICE_MEM
	config['address'] = DEVICE_ADDR
	icaru_mapper.setMap(MAPFNAME, config)
		
	print 'Waiting client...',
	(clientsocket, address) = serversocket.accept()
	print 'OK'
	thread.start_new_thread(client_thread, (clientsocket,))
	
		
	


