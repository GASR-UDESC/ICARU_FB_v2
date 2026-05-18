

#ifndef _ERRORS_H_
#define _ERRORS_H_ 1

void err_init();
void err_lineInc();
void err_lineReset();
void err_setFile(char *filename);
void err_printWarm(char *info);
void err_printError(char *info);
void err_printFatalError(char *info);
int err_getLine();

#endif // _ERRORS_H_
