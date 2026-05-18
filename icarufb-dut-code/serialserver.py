

# Serial Port Server


import socket
import thread
import serial
from flags import *
from time import sleep

USERTS = False

serversocket = socket.socket(
    socket.AF_INET, socket.SOCK_STREAM)
#serversocket.bind((socket.gethostname(), 61494))
serversocket.bind(('localhost', 61900))
serversocket.listen(5)

print 'Server started'


CLIENTS = []
CLIENTSCONFIG = []
OUTBUF=[]
SERIALPORT = None

def printHex(p):
	print [("%X"%(i)) for i in p]
	
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

def readPack(comsock):
	data = []
	data.append(socketget(1,comsock))
	if(data[-1] == 0xAA):
		data.append(socketget(1,comsock))
		if(data[-1] == 0x55):
			for i in range(6):
				data.append(socketget(1,comsock))
			data.append(socketget(1,comsock))
			if(data[-1] == 0x55):
				data.append(0x55)
				return data
	print 'Refused pack: ', printHex(data)
	return None
	
def client_thread(sock):
	try:
		if(socketget(1,sock) == 0x5A):
			if(socketget(1,sock) == 0x55):
				if(socketget(1,sock) == 0x5A):
					if(socketget(1,sock) == 0x55):
						CLIENTS.append(sock)
						print 'App FB connected'
		else:
			CLIENTSCONFIG.append(sock)
			print 'Config tool connected'
	
		while True:		
			#p = readPack(sock)
			data=[]
			v = socketget(1,sock)
			if(v == 0xAA):
				if(socketget(1,sock) == 0x55):
					data = data + [0xAA,0x55]
					for i in range(6):
						data.append(socketget(1,sock))
					if(socketget(1,sock) == 0x55):
						data = data + [0x55]
						OUTBUF.append((data,sock))
						printHex( OUTBUF[-1][0])
			elif v == None:
				return 
			
			#if(p != None):
			#	OUTBUF.append((p,sock))
			#	print 'TOSEND: ' + '.'*len(OUTBUF)
			#else:
			#	return 
	except Exception, e:
		print e
		import traceback
		traceback.print_exc()
	
	
def serialIn_thread():
	while True:
		pack = []
		c = ord(SERIALPORT.read(1))
		if c == 0xAA:
			c = ord(SERIALPORT.read(1))
			if c == 0x55:
				pack.append(0xAA)
				pack.append(0x55)
				for i in range(6):
					pack.append(ord(SERIALPORT.read(1)))
				c = ord(SERIALPORT.read(1))
				if c == 0x55:
					pack.append(0x55)
					if(pack[2] == 0x01 and pack[3] == 0xF1 and pack[4] == 0xF1):
						if(len(OUTBUF) > 0):
							if USERTS:
								SERIALPORT.setRTS(True)
								sleep(0.002)
							SERIALPORT.write(''.join([chr(i) for i in OUTBUF[0][0]]))
							#tk = chr(0xAA) + chr(0x55) + chr(0x01) + chr(0xF1) + chr(0xF1) + chr(0) + chr(0)+ chr(0x55)
							if USERTS:
								while(SERIALPORT.outWaiting()>0):
									i=10
								sleep(0.004)
								SERIALPORT.setRTS(False)
							#OUTBUF[0][1].send(tk)
							del OUTBUF[0]
							print 'WRITE: '+'.'*len(OUTBUF)
					elif(pack[2] in range(0x01,0xB0) and pack[3] == 0xF1 and pack[4] == 0xF1):
						pass
					else:
						#send to all clients
						print "PACK RECEIVED:"
						printHex(pack)
						delc = []
						ind=0
						for c in CLIENTSCONFIG:
							try:
								print 'RESPONDING: '
								printHex(pack)
								c.send(''.join([chr(i) for i in pack]))
							except Exception, e:
								delc.append(ind)
								print e
								import traceback
								traceback.print_exc()
							ind=ind+1
						for i in reversed(delc):
							#---
							del CLIENTSCONFIG[i]
						delc = []
						ind=0
						for c in CLIENTS:
							try:
								#print 'RESPONDING: '
								#printHex(pack)
								c.send(''.join([chr(i) for i in pack]))
							except Exception, e:
								delc.append(ind)
								print e
								import traceback
								traceback.print_exc()
							ind=ind+1
						for i in reversed(delc):
							#---
							del CLIENTS[i]
								
		else:
			print chr(c),
					
					
				
	
	

	

if not flagExist('-p') and not flagExist('-n'):
	print 'Need serial port number: -p <number> or -n <name>'
	exit()
	
SERIALPORT = None
if flagExist('-p'):
	PORTNUM = getPPar('-p')	
	SERIALPORT = serial.Serial(int(PORTNUM)-1)
elif flagExist('-n'):
	PORTNUM = getPPar('-n')	
	SERIALPORT = serial.Serial(PORTNUM)
	
if flagExist('--rts'):
	print 'Using RTS when sending.'
	USERTS = True
else:
	print 'Not using RTS. ICARU connected direct to COM port.'
"""	
PORTNUM = getPPar('-p')	
SERIALPORT = serial.Serial(int(PORTNUM)-1)
"""
SERIALPORT.setRTS(False)
SERIALPORT.setBaudrate(38400)

thread.start_new_thread(serialIn_thread, ())
	
while 1:
	print 'Waiting client...',
	(clientsocket, address) = serversocket.accept()
	print 'OK'
	thread.start_new_thread(client_thread, (clientsocket,))
	#CLIENTS.append(clientsocket)
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
