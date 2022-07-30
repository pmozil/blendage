#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

#ifndef LENGTH
#define LENGTH(X)               (sizeof X / sizeof X[0])
#endif

#ifndef CONF_VARS
#define CONF_VARS
static void tohex(char *inp, float *f);
int set_var(lua_State *L);

static int sloppyfocus = 1;
static int borderpx = 0;
static int gappx = 2;
static int lockfullscreen = 1;
static float rootcolor[4] = {1.0, 1.0, 1.0, 0.0};
static float bordercolor[4] = {1.0, 1.0, 1.0, 0.0};
static float focuscolor[4] = {1.0, 1.0, 1.0, 0.0};
static int repeat_rate = 25;
static int repeat_delay = 600;
static int tap_to_click = 1;
static int tap_and_drag = 1;
static int drag_lock = 1;
static int natural_scrolling = 0;
static int disable_while_typing = 1;
static int left_handed = 0;
static int middle_button_emulation = 0;

typedef struct var_list {
    char name[64];
    char type[8];
    long link;
} var_list;

static var_list links[] = {
    { "sloppyfocus",                "int", (long) &sloppyfocus },
    { "borderpx",                   "int", (long) &borderpx },
    { "gappx",                      "int", (long) &gappx },
    { "lockfullscreen",             "int", (long) &lockfullscreen },
    { "rootcolor",                  "hex", (long) &rootcolor },
    { "bordercolor",                "hex", (long) &bordercolor },
    { "focuscolor",                 "hex", (long) &focuscolor },
    { "repeat_rate",                "int", (long) &repeat_rate },
    { "repeat_delay",               "int", (long) &repeat_delay },
    { "tap_to_click",               "int", (long) &tap_to_click },
    { "tap_and_drag",               "int", (long) &tap_and_drag },
    { "drag_lock",                  "int", (long) &drag_lock },
    { "natural_scrolling",          "int", (long) &natural_scrolling },
    { "disable_while_typing",       "int", (long) &disable_while_typing },
    { "left_handed",                "int", (long) &left_handed },
    { "middle_button_emulation",    "int", (long) &middle_button_emulation },
};

static lua_State *lua;
#endif
