
#ifndef _INSTCON_H_
#define _INSTCON_H_ 1

void ic_init();

void ic_newInstance(char *iname, char *type, char *init, char *device, char *resource);
void ic_newConnection(char *fromInstance, char *fromVar, char *toInstance, char *toVar, char *device, char *resource);

void ic_openxml(char *device, char*resource);
void ic_closexml();

#endif

