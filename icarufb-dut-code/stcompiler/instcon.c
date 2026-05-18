


#include "instcon.h"
#include "algcode.h"
#include <stdio.h>

FILE *f;
FILE *xml;
int idcount;

void ic_init(){
    //f = fopen("asmhex/system.txt","w");
    idcount = 0;
}

void ic_openxml(char *device, char*resource){
    char filename[100];
    sprintf(filename, "%s/%s%s.xml", alg_getOutput(), device, resource);
    xml = fopen(filename,"w");
    idcount = 0;
}
void ic_closexml(){
    fclose(xml);
}

void ic_newInstance(char *iname, char *type, char *init, char *device, char *resource){
    if(init == NULL){
       // fprintf(f, "INST, %s, %s, 0, %s, %s\n", iname, type, device, resource);
    }else{
       // fprintf(f, "INST, %s, %s, %s, %s, %s\n", iname, type, init, device, resource);
    }

    fprintf(xml, "<Request ID='%d' Action='CREATE'>\n",idcount);
    fprintf(xml, "  <FB Name='%s' Type='%s'/>\n</Request>\n\n", iname, type);

    idcount++;
}
void ic_newConnection(char *fromInstance, char *fromVar, char *toInstance, char *toVar, char *device, char *resource){
       // fprintf(f, "CONN, %s, %s, %s, %s, %s, %s\n", fromInstance, fromVar, toInstance, toVar, device, resource);
        fprintf(xml, "<Request ID='%d' Action='CREATE'>\n", idcount);
        fprintf(xml, "  <Connection Source='%s.%s' Destination='%s.%s'/>\n</Request>\n\n", fromInstance, fromVar, toInstance, toVar);
        idcount++;
}
