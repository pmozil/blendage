#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include "config.h"

void tohex(char *inp, float *f) {
    char *a = inp + (inp[0]=='#'), c[2];
    int i, j = 0, k;

    for(i = 0; a[i]!='\0'; i++) {
        k = (i%2);
        c[k]=a[i];
        if(k) {
            float v =  ldexpf( (float)strtol(c, NULL, 16), -8);
            *(&f[j]) = *(&v);
            j++;
        }
    }
}

int set_var(lua_State *L) {
    char name[64];
    strcpy(name, lua_tostring(L, 1));
    var_list var;
    int set = 0;
    for(int i = 0; i < LENGTH(links); i++) {
        if(!strcmp(links[i].name, name)) {
            var = links[i];        
            set = 1;
        }
    }

    if (!set)
        return 1;

    if(!strcmp(var.type, "int")) {
        *(int *) var.link = lua_tointeger(L, 2);
        return 0;
    }

    if(!strcmp(var.type, "double")) {
        *(double *) var.link = lua_tonumber(L, 2);
        return 0;
    }

    if(!strcmp(var.type, "char")) {
        strcpy((char *) var.link, lua_tostring(L, 2));
        return 0;
    }

    if(!strcmp(var.type, "hex")) {
        char hex[10];
        strcpy(hex, lua_tostring(L, 2));
        tohex(hex, (float *)var.link);
        return 0;
    }
}
