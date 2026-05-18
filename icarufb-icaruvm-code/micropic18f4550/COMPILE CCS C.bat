@echo off
cd ..
ccsc "main.c"  +FH +DF +LN -A +M -Z +Y=9 +EA I+="micropic18f4550"
FOR /F "delims=|" %%f in (main.err) DO echo %%f
move main.cof micropic18f4550\bin
move main.err micropic18f4550\bin
move main.esym micropic18f4550\bin
move main.hex micropic18f4550\bin
move main.PJT micropic18f4550\bin
move main.sym micropic18f4550\bin
move main.lst micropic18f4550\bin
PAUSE
cd micropic18f4550
cd bin
REGRAVAR.bat