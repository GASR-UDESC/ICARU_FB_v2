
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
import icaru_com
icaru_com.connect()

"""
DEVICE_MAP:
	table: memory allocation
		name, type, address, size, valid, obj, bytecode
	address:
	memory_len:


"""

DEVICE_MAP = {}

devicemapfilename='dev.mem'


def setMap(mapfilename, device_config):
	"""
	device_config: {'address':(int), 'memory_len': (int)}
	
	"""
	global DEVICE_MAP
	devicemapfilename = mapfilename
	print '(icaru_mapper) Always creating a new map.'
	if not os.path.exists(mapfilename) or True:
		startfb = {'name':'START','fbtype':'E_RESTART'}
		startfb['varsmap'] = {'COLD': {'address':0, 'size':1, 'type':'EVENT'}, 'WARM': {'address':1, 'size':1, 'type':'EVENT'}, 'STOP': {'address':2, 'size':1, 'type':'EVENT'},'SUBMAP': {'address':3, 'size':2,'type':'UINT'}}
		DEVICE_MAP['table'] = [{'name':'START','fbtype':'E_RESTART','type':'FBINSTANCE','address':0,'size':9,'valid':True,'obj':startfb,'bytecode':[0,0,0,0]+getByteCodeForVarMap(startfb['varsmap']),'varsmap':startfb['varsmap']},{'name':'','type':'','address':9,'size':device_config['memory_len']-9,'valid':False,'obj':None,'bytecode':[]}]
		DEVICE_MAP['address'] = device_config['address']
		DEVICE_MAP['memory_len'] = device_config['memory_len']
		save_obj(DEVICE_MAP, devicemapfilename)
	else:
		DEVICE_MAP = load_obj(devicemapfilename)
	icaru_com.setId(DEVICE_MAP['address'])
	
		
def getIndexOfFreeSpace(size):
	i = len(DEVICE_MAP['table']) -1
	while i>= 0:
		if DEVICE_MAP['table'][i]['valid']==False and DEVICE_MAP['table'][i]['size'] >= size:
			return i
		i = i - 1
	print '(icaru_mapper) Error: No memory.'
	return -1
	
def alloc(size):
	i = getIndexOfFreeSpace(size)
	
	if i == -1:
		return -1
	if DEVICE_MAP['table'][i]['size'] > size:
		#ns = DEVICE_MAP['table'][i]['size'] - size
		nadd = DEVICE_MAP['table'][i]['address']+DEVICE_MAP['table'][i]['size']-size
		DEVICE_MAP['table'][i]['size'] = DEVICE_MAP['table'][i]['size'] - size		
		nline = {'address': nadd, 'size':size, 'valid':True}
		DEVICE_MAP['table'].insert(i+1,nline)
		DEVICE_MAP['table'][i+1]['name']=''
		if(DEVICE_MAP['table'][i+1]['address'] + DEVICE_MAP['table'][i+1]['size'] > DEVICE_MAP['memory_len']):
			print 'Error: (mapper) address outside max memory'
			print 'Memory: ',DEVICE_MAP['memory_len']
			print DEVICE_MAP['table'][i+1]
			exit()
		return i+1
	elif DEVICE_MAP['table'][i]['size'] == size:
		DEVICE_MAP['table'][i]['valid'] = True
		DEVICE_MAP['table'][i]['name']=''
	else:
		print '(icaru_mapper) No memory space.'
		return -2
	#save_obj(DEVICE_MAP, devicemapfilename)
	return i
	
def extend(i, nsize):
	pass

def printTable():
	for r in DEVICE_MAP['table']:
		print '%10d %10d %15s %15s' % (r['address'],r['size'], r['name'],r['valid'])
		if('connections' in r):
			e = getElement('__conn_'+r['name'])
			if e != None:
				print 'C AT:', e['address']
			for c in r['connections']:					
				print '        ',
				print [("%X"%(i)) for i in c]
				
		
		

builtintypes = {
'E_RESTART': 
  {'name':'E_RESTART','address':65500, 'varsmap': {'COLD': {'address':0, 'size':1,'type':'EVENT'}, 'WARM': {'address':1, 'size':1,'type':'EVENT'}, 'STOP': {'address':2, 'size':1,'type':'EVENT'}, 'SUBMAP': {'address':3, 'size':2,'type':'UINT'}} },
}

builtintypes['DIGITAL_READ'] = {'name':'DIGITAL_READ','address':65501}
builtintypes['DIGITAL_READ']['varsmap'] = {'REQ':{'address':0, 'size':1, 'type':'EVENT'}, 'PIN':{'address':1, 'size':1, 'type':'BYTE'}, 'CNF':{'address':2, 'size':1, 'type':'EVENT'}, 'VAL':{'address':3, 'size':1, 'type':'BYTE'}}

builtintypes['DIGITAL_WRITE'] = {'name':'DIGITAL_WRITE','address':65502}
builtintypes['DIGITAL_WRITE']['varsmap'] = {'REQ':{'address':0, 'size':1, 'type':'EVENT'}, 'PIN':{'address':1, 'size':1, 'type':'BYTE'}, 'CNF':{'address':2, 'size':1, 'type':'EVENT'}, 'VAL':{'address':3, 'size':1, 'type':'BYTE'}}

builtintypes['ANALOG_READ'] = {'name':'ANALOG_READ','address':65511}
builtintypes['ANALOG_READ']['varsmap'] = {'REQ':{'address':0, 'size':1, 'type':'EVENT'}, 'PIN':{'address':1, 'size':1, 'type':'BYTE'}, 'CNF':{'address':2, 'size':1, 'type':'EVENT'}, 'VAL':{'address':3, 'size':2, 'type':'UINT'}}

builtintypes['E_MERGE'] = {'name':'E_MERGE','address':65503}
builtintypes['E_MERGE']['varsmap'] = {'a':{'address':0, 'size':1, 'type':'BYTE'},'EO':{'address':1, 'size':1, 'type':'EVENT'},'EI1':{'address':2, 'size':1, 'type':'EVENT'}, 'EI2':{'address':3, 'size':1, 'type':'EVENT'}}

builtintypes['E_SPLIT'] = {'name':'E_SPLIT','address':65504}
builtintypes['E_SPLIT']['varsmap'] = {'EI':{'address':0, 'size':1, 'type':'EVENT'},'ne':{'address':1, 'size':1, 'type':'BYTE'},'EO1':{'address':2, 'size':1, 'type':'EVENT'}, 'EO2':{'address':3, 'size':1, 'type':'EVENT'}}

builtintypes['SUBL_5'] = {'name':'SUBL_5','address':65505}
builtintypes['SUBL_5']['varsmap'] = {'INIT':{'address':0, 'size':1, 'type':'EVENT'},'INITO':{'address':1, 'size':1, 'type':'EVENT'}, 'IND':{'address':2, 'size':1, 'type':'EVENT'},  'ID':{'address':3, 'size':1, 'type':'BYTE'},   'RD_1':{'address':4, 'size':1, 'type':'BYTE'}, 'RD_2':{'address':5, 'size':1, 'type':'BYTE'}, 'RD_3':{'address':6, 'size':1, 'type':'BYTE'}, 'RD_4':{'address':7, 'size':1, 'type':'BYTE'}, 'RD_5':{'address':8, 'size':1, 'type':'BYTE'}}

builtintypes['PUBL_5'] = {'name':'PUBL_5','address':65508}
builtintypes['PUBL_5']['varsmap'] = {'INIT':{'address':0, 'size':1, 'type':'EVENT'},'INITO':{'address':1, 'size':1, 'type':'EVENT'}, 'REQ':{'address':2, 'size':1, 'type':'EVENT'}, 'CNF':{'address':3, 'size':1, 'type':'EVENT'}, 'ID':{'address':4, 'size':1, 'type':'BYTE'},   'SD_1':{'address':5, 'size':1, 'type':'BYTE'}, 'SD_2':{'address':6, 'size':1, 'type':'BYTE'}, 'SD_3':{'address':7, 'size':1, 'type':'BYTE'}, 'SD_4':{'address':8, 'size':1, 'type':'BYTE'}, 'SD_5':{'address':9, 'size':1, 'type':'BYTE'}, 'resend':{'address':10, 'size':1, 'type':'BYTE'}}

builtintypes['LCD_MSG'] = {'name':'LCD_MSG','address':65509}
builtintypes['LCD_MSG']['varsmap'] = {'INIT':{'address':0, 'size':1, 'type':'EVENT'},'REQ':{'address':1, 'size':1, 'type':'EVENT'}, 'INITO':{'address':2, 'size':1, 'type':'EVENT'}, 'CNF':{'address':3, 'size':1, 'type':'EVENT'}, 'MSG':{'address':4, 'size':1, 'type':'BYTE'},   'VAR1':{'address':5, 'size':2, 'type':'UINT'}, 'VAR2':{'address':7, 'size':2, 'type':'UINT'}, 'VAR3':{'address':9, 'size':2, 'type':'UINT'}, 'VAR4':{'address':11, 'size':2, 'type':'UINT'}}

builtintypes['SD_CARD_WRITE'] = {'name':'SD_CARD_WRITE','address':65510}
builtintypes['SD_CARD_WRITE']['varsmap'] = {'INIT':{'address':0, 'size':1, 'type':'EVENT'},'REQ':{'address':1, 'size':1, 'type':'EVENT'}, 'INITO':{'address':2, 'size':1, 'type':'EVENT'}, 'CNF':{'address':3, 'size':1, 'type':'EVENT'}, 'SEP':{'address':4, 'size':1, 'type':'BYTE'},   'VAR1':{'address':5, 'size':2, 'type':'UINT'}, 'VAR2':{'address':7, 'size':2, 'type':'UINT'}, 'VAR3':{'address':9, 'size':2, 'type':'UINT'}, 'VAR4':{'address':11, 'size':2, 'type':'UINT'}}

builtintypes['E_DELAY'] = {'name':'E_DELAY','address':65506}
builtintypes['E_DELAY']['varsmap'] = {'START':{'address':0, 'size':1, 'type':'EVENT'},'STOP':{'address':1, 'size':1, 'type':'EVENT'},'EO':{'address':2, 'size':1, 'type':'EVENT'}, 'DT':{'address':3, 'size':4, 'type':'UDINT'}, 'CT':{'address':7, 'size':4, 'type':'UDINT'}, 'started':{'address':11, 'size':1, 'type':'BYTE'}, 'told':{'address':12, 'size':1, 'type':'BYTE'}}

builtintypes['E_PERMIT'] = {'name':'E_PERMIT','address':65507}
builtintypes['E_PERMIT']['varsmap'] = {'EI':{'address':0, 'size':1, 'type':'EVENT'},'EO':{'address':1, 'size':1, 'type':'EVENT'},'PERMIT':{'address':2, 'size':1, 'type':'BOOL'}}

builtintypes['MILLIS'] = {'name':'MILLIS','address':65512}
builtintypes['MILLIS']['varsmap'] = {'REQ':{'address':0, 'size':1, 'type':'EVENT'}, 'CNF':{'address':1, 'size':1, 'type':'EVENT'}, 'MS':{'address':2, 'size':2, 'type':'UINT'}}


"""
builtintypes['START'] = {'name':'START','address':0,'type':'E_RESTART'}
builtintypes['START']['varsmap'] = {'COLD': {'address':0, 'size':1, 'type':'EVENT'}, 'WARM': {'address':1, 'size':1, 'type':'EVENT'}, 'STOP': {'address':3, 'size':1, 'type':'EVENT'}}
"""


def getElement(fbName):
	for l in DEVICE_MAP["table"]:
		if(l["name"] == fbName and l['valid']):
			return l
	if fbName in builtintypes:
		return builtintypes[fbName]
	return None

def getFb(fbName):
	return getElement(fbName)
	
def fbExists(fbName):
	global builtintypes
	fb = getFb(fbName)
	if(fb != None):
		return True
	if fbName in builtintypes:
		return True
	return False
	

def fbAddType(fbobj):
	"""
	fbobj:
		name:
		bytecode:
		varsmap: 
	"""
	global builtintypes
	

	if fbExists(fbobj['name']):
		return False

	if fbobj['name'] in builtintypes:
		print '(icaru_mapper) INFO: FB type "%s" already is in ICARU_VM, is a builtin type.' % (fbobj['name'])
		
		#print '(icaru_mapper) Returning True.'
		return True

	
	i = alloc(len(fbobj['bytecode']))
	if(i < 0):
		return False

	DEVICE_MAP['table'][i]['name'] = fbobj['name']
	DEVICE_MAP['table'][i]['bytecode'] = fbobj['bytecode']	
	DEVICE_MAP['table'][i]['varsmap'] = fbobj['varsmap']	
	DEVICE_MAP['table'][i]['type'] = 'FBTYPE'	

	#Write on real device
	icaru_com.writeIcaruMemory(DEVICE_MAP['table'][i]['address'], DEVICE_MAP['table'][i]['bytecode'], DEVICE_MAP['address'])
	return True
	

	return False
	

	
def getByteCodeForVarMap(map):
	bcode = []
	for v in map.iterkeys():
		for i in range(map[v]['size']):
			bcode.append(0)
	return bcode

def fbAddInstance(fbname, fbtype):
	global builtintypes
	if fbExists(fbname):
		print "(icaru_mapper) FB Instance '%s' already in ICARU_VM." % (fbname)
		return False
	if not fbExists(fbtype):
		print "(icaru_mapper) Error: FBTYPE '%s' doesn't exists." % (fbtype)
		return False
	fb = getFb(fbtype)
	
	cp_msb = (fb['address']>>8 & 0xFF)
	cp_lsb = fb['address'] & 0xFF
	fbbcode = getByteCodeForVarMap(fb['varsmap'])
	bytecode = [cp_msb, cp_lsb, 0, 0] + fbbcode
	
	i = alloc(len(bytecode))
	if(i < 0):
		return False

	DEVICE_MAP['table'][i]['name'] = fbname
	DEVICE_MAP['table'][i]['bytecode'] = bytecode
	DEVICE_MAP['table'][i]['varsmap'] = fb['varsmap']	
	DEVICE_MAP['table'][i]['type'] = 'FBINSTANCE'	
	DEVICE_MAP['table'][i]['fbtype'] = fbtype
	DEVICE_MAP['table'][i]['conpointer'] = 0

	#Write on real device
	if(fbtype == 'E_MERGE'):
		DEVICE_MAP['table'][i]['bytecode'][4] = 2
		print 'Setting E_MERGE with 2 input events.'
	if(fbtype == 'E_SPLIT'):
		DEVICE_MAP['table'][i]['bytecode'][5] = 2
		print 'Setting E_MERGE with 2 input events.'
		
	icaru_com.writeIcaruMemory(DEVICE_MAP['table'][i]['address'], DEVICE_MAP['table'][i]['bytecode'], DEVICE_MAP['address'])
	return True
	
	return False

def ConnAdd(fromfbvar,tofbvar):
	"""
	fromfbvar | tofbvar = ('fbname','varname')
	"""
	
	l = tofbvar.split('.')
	fb = getFb(l[0])
	pto = fb['address']+4 + fb['varsmap'][l[1]]['address']
	psize = fb['varsmap'][l[1]]['size']
	pfb = int(fb['address'])
	
	l = fromfbvar.split('.')
	fb = getFb(l[0])
	pfrom = fb['address']+4 + fb['varsmap'][l[1]]['address']
	
	
	conn = [pfrom>>8, pfrom & 0XFF, pto >> 8, pto & 0xFF, psize & 0xFF, (pfb >> 8) &0xFF, pfb & 0xFF]
	conn0 = [0,0,0,0,0,0,0]
	if(fb['varsmap'][l[1]]['type'] == 'EVENT'):
		conn[4]=0
	
	
	if not 'connections' in fb:
		fb['connections'] = []
		fb['connections'].append(conn)
		fb['connections'].append(conn0)
		i = alloc(len(conn)*2)
		if(i < 0):
			return False
		DEVICE_MAP['table'][i]['name'] = '__conn_'+fb['name']
		DEVICE_MAP['table'][i]['bytecode'] = sum(fb['connections'], [])
		DEVICE_MAP['table'][i]['type'] = 'CONNECTION'

		fb['conpointer'] = i

		#write to device
		icaru_com.writeIcaruMemory(DEVICE_MAP['table'][i]['address'], DEVICE_MAP['table'][i]['bytecode'], DEVICE_MAP['address'])
		newpointer = [DEVICE_MAP['table'][i]['address']>>8, DEVICE_MAP['table'][i]['address']&0xFF]
		icaru_com.writeIcaruMemory(fb['address']+2, newpointer, DEVICE_MAP['address'])
		return True
	else:
		del fb['connections'][-1]
		fb['connections'].append(conn)
		fb['connections'].append(conn0)
		
		cf = getElement('__conn_'+fb['name'])
		

		i = alloc(len(fb['connections'])*7)
		if(i < 0):
			return False
		DEVICE_MAP['table'][i]['name'] = '__conn_'+fb['name']
		DEVICE_MAP['table'][i]['bytecode'] = sum(fb['connections'], [])
		DEVICE_MAP['table'][i]['type'] = 'CONNECTION'

		fb['conpointer'] = i

		#write to device
		icaru_com.writeIcaruMemory(DEVICE_MAP['table'][i]['address'], DEVICE_MAP['table'][i]['bytecode'], DEVICE_MAP['address'])
		newpointer = [DEVICE_MAP['table'][i]['address']>>8, DEVICE_MAP['table'][i]['address']&0xFF]
		icaru_com.writeIcaruMemory(fb['address']+2, newpointer, DEVICE_MAP['address'])
		cf['valid'] = False
		return True
	return False
	
def ConnDel(fromfbvar,tofbvar):
	l = tofbvar.split('.')
	fb = getFb(l[0])
	pto = fb['address']+4 + fb['varsmap'][l[1]]['address']
	psize = fb['varsmap'][l[1]]['size']
	pfb = int(fb['address'])
	
	l = fromfbvar.split('.')
	fb = getFb(l[0])
	pfrom = fb['address']+4 + fb['varsmap'][l[1]]['address']
	
	
	conn = [pfrom>>8, pfrom & 0XFF, pto >> 8, pto & 0xFF, psize & 0xFF, (pfb >> 8) &0xFF, pfb & 0xFF]
	conn0 = [0,0,0,0,0,0,0]
	
	if not 'connections' in fb:
		print 'No connections in'+l[0]
	else:
		i = 0
		count =0
		for c in fb['connections']:
			if c == conn:
				i = count
				break;
			count=count+1
		del fb['connections'][i]
		
		
			

def getTypeOfVar(fbtype, varname):
	fb = getFb(fbtype)
	return fb['varsmap'][varname]['type']
	
def addToSublList(id, address):
	subl = [id, address>>8, address & 0xFF]
	if not 'subls' in DEVICE_MAP:
		DEVICE_MAP['subls'] = [[0,0,0]]
	del DEVICE_MAP['subls'][-1]
	DEVICE_MAP['subls'].append(subl)
	DEVICE_MAP['subls'].append([0,0,0])
	i = getElement('__subls_')
	if(i != None):
		i['valid']=False
	i = alloc(len(DEVICE_MAP['subls'])*3)
	if(i < 0):
		return False
	DEVICE_MAP['table'][i]['name'] = '__subls_'
	DEVICE_MAP['table'][i]['bytecode'] = sum(DEVICE_MAP['subls'], [])
	DEVICE_MAP['table'][i]['type'] = 'SUBLS'
	icaru_com.writeIcaruMemory(DEVICE_MAP['table'][i]['address'], DEVICE_MAP['table'][i]['bytecode'], DEVICE_MAP['address'])
	writePar('START.SUBMAP', DEVICE_MAP['table'][i]['address'])
		
		
def writePar(tofbvar, value):
	l = tofbvar.split('.')
	t = getTypeOfVar(l[0], l[1])
	val = None
	value = str(value)
	if 'T#' in value.upper():
		value = value.upper()
		if 'MS' in value:
			value = value.replace('T#','')
			value = value.replace('MS','')
		else:
			print "'%s' not supported, only ms."
	print 'T::',t,
	if(t == 'BYTE' or t=='EVENT' or t == 'BOOL'):
		val = int(value) & 0xFF
		fb = getFb(l[0])
		vp = fb['varsmap'][l[1]]['address']+4
		fb['bytecode'][vp] = val
		print 'pos: ',fb['address']+vp
		#write to device		
		icaru_com.writeIcaruMemory(fb['address']+vp, [val], DEVICE_MAP['address'])
		
		tfb = fb['fbtype']
		print 'tfb: ',tfb
		print l[1]
		if(tfb == 'SUBL_5' and l[1]=='ID'):
			addToSublList(val, fb['address'])
		return True
	elif(t == 'UINT'):
		val = int(value) & 0xFFFF
		fb = getFb(l[0])
		vp = fb['varsmap'][l[1]]['address']+4
		fb['bytecode'][vp] = val>>8
		fb['bytecode'][vp+1] = val & 0xFF
		icaru_com.writeIcaruMemory(fb['address']+vp, [val>>8,val & 0xFF], DEVICE_MAP['address'])
	elif(t == 'UDINT'):
		val = int(value) & 0xFFFFFFFF
		fb = getFb(l[0])
		vp = fb['varsmap'][l[1]]['address']+4
		fb['bytecode'][vp] = (val>>24) & 0xFF
		fb['bytecode'][vp+1] = (val>>16) & 0xFF
		fb['bytecode'][vp+2] = (val>>8) & 0xFF
		fb['bytecode'][vp+3] = val & 0xFF
		icaru_com.writeIcaruMemory(fb['address']+vp, [fb['bytecode'][vp],fb['bytecode'][vp+1],fb['bytecode'][vp+2],fb['bytecode'][vp+3]], DEVICE_MAP['address'])
	return False
		
		

		







