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
# icaru_mapper manages the memory of a ICARU_FB device.
# ICARU_FB device is only responsive for running code
# (avoid management tasks on ICARU_FB device)
#

import os,sys
from flags import *
from saveload import *
#import com


DEVICE_MAP = {}

devicemapfilename='dev.mem'

def setMap(mapfilename, newmap=None):
	global DEVICE_MAP
	devicemapfilename = mapfilename
	if not os.path.exists(mapfilename):
		DEVICE_MAP["device_config"] = newmap["device_config"]
		DEVICE_MAP["table"] = [{'name':'','address':0,'size':newmap['memory_len'],'valid':False, 'type':'', 'obj':None, 'loaded':False}] #name, address, size, valid, type, obj, loaded : list of dict
		DEVICE_MAP["connections"] = [] #fromfbvar, tofbvar, size, event, valid : list of dict
		DEVICE_MAP["memory"]=[] #list of byte
		DEVICE_MAP["memory_len"] = newmap["memory_len"]
		save_obj(DEVICE_MAP, devicemapfilename)
	else:
		DEVICE_MAP = load_obj(devicemapfilename)

def getConnectionsLen():
	return len(DEVICE_MAP['connections'])*7
		
def getIndexOfFreeSpace(size):
	i = len(DEVICE_MAP['table']) -1
	while i>= 0:
		if DEVICE_MAP['table'][i]['valid']==False and DEVICE_MAP['table'][i]['size'] >= size:
			if(i == 0):
				cl = getConnectionsLen()
				if DEVICE_MAP['table'][i]['size']-size < cl:
					print '(icaru_mapper) Error: No memory for connections.'
					return -1
			return i
		i = i - 1
	print '(icaru_mapper) Error: No memory.'
	return -1
	
	
	"""
	for l in DEVICE_MAP['table']:
		if l['valid'] == False and l['size'] >= size:
			return i
		i = i + 1
	return -1
	"""


def alloc(name, size, otype, obj):
	i = getIndexOfFreeSpace(size)
	if i == -1:
		return False
	if DEVICE_MAP['table'][i]['size'] > size:
		#ns = DEVICE_MAP['table'][i]['size'] - size
		nadd = DEVICE_MAP['table'][i]['address']+DEVICE_MAP['table'][i]['size']-size
		DEVICE_MAP['table'][i]['size'] = DEVICE_MAP['table'][i]['size'] - size		
		nline = {'name': name, 'address': nadd, 'size':size, 'valid':True, 'type':otype, 'obj':obj,'loaded':False}
		DEVICE_MAP['table'].insert(i+1,nline)
		return i
	elif DEVICE_MAP['table'][i]['size'] >= size:
		DEVICE_MAP['table'][i]['name'] = name
		DEVICE_MAP['table'][i]['valid'] = True
		DEVICE_MAP['table'][i]['type'] = otype
		DEVICE_MAP['table'][i]['obj'] = obj
		DEVICE_MAP['table'][i]['loaded'] = False
	else:
		print '(icaru_mapper) Unknow Error 1.'
		return False
	save_obj(DEVICE_MAP, devicemapfilename)
	return True
	
		
def fbTypeExists(fbname):
	for l in DEVICE_MAP["table"]:
		if(l["type"] == 'FBTYPE' and l["name"] == fbname):
			return True
	return False
	
def fbInstanceExists(fbname):
	for l in DEVICE_MAP["table"]:
		if(l["type"] == 'FBINSTANCE' and l["name"] == fbname):
			return True
	return False
	
def ConnExists(fromfbvar,tofbvar):
	for c in DEVICE_MAP["connections"]:
		if(c["from"] == fromfbvar and c["tofbvar"] == tofbvar):
			return True
	return False
	
def getMemoryToWrite(fbname):
	buf=[]
	for l in DEVICE_MAP["table"]:
		if(l["name"] == fbname):
			return {'address':l['address'], 'hex': l['obj']['hex']}
	return None
	
def CreateFbType(fbobj):
	if fbTypeExists(fbobj['name']):
		print "Error: FBType '%s' already exists." % (fbobj['name'])
		return False
	if alloc(fbobj['name'], fbobj['size'], 'FBTYPE', fbobj):
		mwrite = getMemoryToWrite(fbobj['name'])
		#if com.write(mwrite['address'],mwrite['hex'])
		return True
	return False
	
def getAddressOfFb(fbname):
	for l in DEVICE_MAP["table"]:
		if(l["name"] == fbname):
			return l['address']
	print '(icaru_mapper) Error: Address of %s not founded.' % (fbname)
	return 0
	
def getFb(fbname):
	for l in DEVICE_MAP["table"]:
		if(l["name"] == fbname):
			return l
	return None

def CreateFbInstance(fbobj):
	ad = getAddressOfFb(fbobj['type'])
	fbobj['hex'].insert(0,ad & 0xFF)
	fbobj['hex'].insert(0,ad >> 8)
	if fbInstanceExists(fbobj['name']):
		print "Error: FBInstance '%s' already exists." % (fbobj['name'])
		return False
	if alloc(fbobj['name'], fbobj['size'], 'FBINSTANCE', fbobj):
		return True
	return False
	
	
def DeleteFbInstance(fbname):
	fb = getFb(fbname)
	if(fb['type'] == 'FBINSTANCE'):
		DeleteAllConnWith(fbname)
		fb['valid'] = False
		return True
	return False
	
def DeleteFbType(fbname):
	for l in DEVICE_MAP["table"]:
		if(l['type']=='FBINSTANCE' and l['fbtype']==fbname):
			DeleteFbInstance(l['name'])
	fb = getFb(fbname)
	fb['valid'] = False
	return True
			
	
	
def DeleteFb(fbname):
	fb = getFb(fbname)
	if(fb['type'] == 'FBINSTANCE'):
		return DeleteFbInstance(fbname)		
	elif(fb['type'] == 'FBTYPE'):
		return DeleteFbType(fbname)
		
def breakFbVar(fv):
	return fv.split('.')
	
def DeleteAllConnWith(fbname):
	for c in DEVICE_MAP["connections"]:
		if breakFbVar(c['fromfbvar'])[0] == fbname or breakFbVar(c['fromfbvar'])[1] == fbname:
			DeleteConn(breakFbVar(c['fromfbvar'])[0],
			breakFbVar(c['fromfbvar'])[1])
		
	
def CreateConn(fromfbvar,tofbvar,size,evt):
	if getConnectionsLen() +7 >= DEVICE_MAP['table'][0]['size']:
		print '(icaru_mapper) Error: no memory for more connections.'
		return False
	for c in DEVICE_MAP["connections"]:
		if not c['valid']:
			c['fromfbvar'] = fromfbvar
			c['tofbvar'] = tofbvar
			c['size'] = size
			c['event'] = evt
			c['valid'] = True
			return True
	c = {'fromfbvar':fromfbvar, 'tofbvar':tofbvar,'size':size,'event':evt,'valid':True}
	DEVICE_MAP['connections'].append(c)
	return True
	
	
def DeleteConn(fromfbvar,tofbvar):
	for c in DEVICE_MAP["connections"]:
		if c['fromfbvar'] == fromfbvar and c['tofbvar'] == tofbvar:
			c['valid'] = False
			return True
	return False
	
def WritePar(tofbvar,value):
	s = tofbvar.split('.')
	fbname = s[0]
	v = s[1]
	fb = getFb(fbname)
	
	#if byte
	addr = fb['obj']['vars'][v]['address']
	fb['obj']['hex'][addr] = value & 0xFF
	return True
	


	
if __name__ == "__main__":
	print 'Initing map'
	nm = {'device_config':{}, 'memory_len':4000}
	setMap('testmap', nm)
	
	fbobj = {}
	fbobj['vars'] = {'EO1':{'address':5}}
	fbobj['hex'] = [0,0,0,0,0]
	fbobj['name'] = 'fbtest'
	fbobj['size'] = len(fbobj['hex'])
	
	fbobj2 = {}
	fbobj2['vars'] = {'EI1':{'address':5}}
	fbobj2['hex'] = [0,0,0,0,0]
	fbobj2['name'] = 'fbtest2'
	fbobj2['size'] = len(fbobj2['hex'])
	
	CreateFbType(fbobj)
	
	CreateFbType(fbobj2)
	for l in DEVICE_MAP['table']:
		print l
	




	
	




