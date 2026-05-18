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
#
# usage: icaru_compiler fb.fbt [-o outdir]
#
#

import sys,os
import subprocess
import fb2st
from flags import *

		
def run(argv1, outdir):
	#generate .st
	stname = fb2st.read(argv1,outdir)
	if stname == None:
		print "Invalid FB Type: ", argv1
		exit()
	#compile


	compiler_name = 'ieccomp.exe'
	if os.name == 'posix':
		compiler_name = './ieccomp'

	compdir = os.path.dirname(os.path.realpath(sys.argv[0]))
	comp = os.path.join(compdir, compiler_name)
	print comp
	print os.path.join(outdir,stname)
	r = subprocess.call([comp, '-o','temp',os.path.join(outdir,stname)])
	if int(r) == 0:
		pass
	else:
		print "ERROR compiling: '%s' (%d)" % (stname, r)


if __name__ == '__main__':
	outdir = os.getcwd()
	if flagExist('-o'):
		outdir = getPPar('-o')
	run(sys.argv[1], outdir)

