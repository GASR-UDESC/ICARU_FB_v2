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
# icaru_ccg
# CCG: Configuration Command Generator
#
# A tool to generate configuration commands to configure a system. 
#
# usage:
# python icaru_ccg.py system.sys [-o out.config]
#                            (or .xml)

import xml.etree.ElementTree as ET
from flags import *

tree = ET.parse(sys.argv[1])
root = tree.getroot()

#out = ET.Element('systemconfig')

outfilename = 'out.config'
if flagExist('-o'):
	outfilename = getPPar('-o')
	
outfile= open(outfilename,'w')
	
id = 1
for d in root.findall('Device'):
	#outd = ET.SubElement(out, 'Device')
	for r in d.findall('Resource'):
		fbn = r.find('FBNetwork')
		for fb in fbn.findall('FB'):
			outfile.write('%s.%s:<Request ID="%d" Action="CREATE"><FB Name="%s" Type="%s" /></Request>\n' % (d.attrib['Name'], r.attrib['Name'], id, fb.attrib['Name'], fb.attrib['Type']))
			id=id+1
			for p in fb.findall('Parameter'):
				outfile.write('%s.%s: <Request ID="%d" Action="WRITE" ><Parameter Reference="%s.%s" Value="%s" /></Request>\n' % (d.attrib['Name'], r.attrib['Name'], id, fb.attrib['Name'],p.attrib['Name'],p.attrib['Value']))
				id=id+1
		
		for c in fbn.findall('EventConnections'):
			for e in c.findall('Connection'):
				outfile.write('%s.%s: <Request ID="%d" Action="CREATE" ><Connection Source="%s" Destination="%s" /></Request>\n' % (d.attrib['Name'], r.attrib['Name'], id, e.attrib['Source'], e.attrib['Destination']))
				id=id+1
		for c in fbn.findall('DataConnections'):
			for e in c.findall('Connection'):
				outfile.write('%s.%s: <Request ID="%d" Action="CREATE" ><Connection Source="%s" Destination="%s" /></Request>\n' % (d.attrib['Name'], r.attrib['Name'], id, e.attrib['Source'], e.attrib['Destination']))
				id=id+1
				
outfile.close()
			


