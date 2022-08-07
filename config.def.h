#ifndef DWL_CONFIG
#define DWL_CONFIG
/* tagging */
static char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static Rule rules[1];// = {
	/* app_id     title       tags mask     isfloating   monitor */
	/* examples:
	{ "Gimp",     NULL,       0,            1,           -1 },
	*/
//};

/* layout(s) */
static Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]_",      dynamictilereverse },
	{ "[]=",      dynamictile },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* monitors */
static MonitorRule monrules[] = {
	/* name             mfact   nmaster scale   layout       rotate/reflect 
    *    examples: 
    *    { "eDP-1",          0.5,    1,      1,      &layouts[3], WL_OUTPUT_TRANSFORM_NORMAL }, 
	*    { "HDMI-A-1",       0.5,    1,      1,      &layouts[3], WL_OUTPUT_TRANSFORM_NORMAL }, 
    */
    { NULL,             0.5,    1,      1,      &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL },
};


/* keyboard */
static char kbrules[64];
static char kbmodel[64];
static char kbvariant[64];
static char kblayout[64] = "us";
static char kboptions[64] = "grp:alt_space_toggle";

/* You can choose between:
LIBINPUT_CONFIG_SCROLL_NO_SCROLL
LIBINPUT_CONFIG_SCROLL_2FG
LIBINPUT_CONFIG_SCROLL_EDGE
LIBINPUT_CONFIG_SCROLL_ON_BUTTON_DOWN
*/
static enum libinput_config_scroll_method scroll_method = LIBINPUT_CONFIG_SCROLL_2FG;

/* You can choose between:
LIBINPUT_CONFIG_CLICK_METHOD_NONE       
LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS       
LIBINPUT_CONFIG_CLICK_METHOD_CLICKFINGER 
*/
static enum libinput_config_click_method click_method = LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS;

/* You can choose between:
LIBINPUT_CONFIG_SEND_EVENTS_ENABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED
LIBINPUT_CONFIG_SEND_EVENTS_DISABLED_ON_EXTERNAL_MOUSE
*/
static uint32_t send_events_mode = LIBINPUT_CONFIG_SEND_EVENTS_ENABLED;

/* You can choose between:
LIBINPUT_CONFIG_ACCEL_PROFILE_FLAT
LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE
*/

static enum libinput_config_accel_profile accel_profile = LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE;

/* If you want to use the windows key change this to WLR_MODIFIER_LOGO */
#define MODKEY WLR_MODIFIER_LOGO
#define TAGKEYS(KEY,SKEY,TAG) \
	{ MODKEY,                    KEY,            view,            {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL,  KEY,            toggleview,      {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_SHIFT, SKEY,           tag,             {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL|WLR_MODIFIER_SHIFT,SKEY,toggletag, {.ui = 1 << TAG} }

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char *termcmd[] = { "alacritty", NULL };
static char *menucmd[] = { "wofi", "--show", "drun", NULL };
static char *browsercmd[] = { "firefox-bin", NULL };
static char *wallcmd[] = {"~/.local/bin/scripts/select-background.sh", NULL};

static Key keys[] = {
	/* Note that Shift changes certain key codes: c -> C, 2 -> at, etc. */
	/* modifier                  key                 function        argument */
	{ MODKEY,                    XKB_KEY_r,          spawn,          {.v = menucmd} },
	{ MODKEY,                    XKB_KEY_t,          spawn,          {.v = termcmd} },
	{ MODKEY,                    XKB_KEY_b,          spawn,          {.v = browsercmd} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_W,          spawn,          {.v = wallcmd} },
	{ MODKEY,                    XKB_KEY_j,          focusstack,     {.i = +1} },
	{ MODKEY,                    XKB_KEY_k,          focusstack,     {.i = -1} },
	{ MODKEY,                    XKB_KEY_o,          incnmaster,     {.i = +1} },
	{ MODKEY,                    XKB_KEY_p,          incnmaster,     {.i = -1} },
	{ MODKEY,                    XKB_KEY_h,          setmfact,       {.f = -0.05} },
	{ MODKEY,                    XKB_KEY_l,          setmfact,       {.f = +0.05} },
	{ MODKEY,                    XKB_KEY_Return,     zoom,           {0} },
	{ MODKEY,                    XKB_KEY_Tab,        view,           {0} },
	{ MODKEY,                    XKB_KEY_q,          killclient,     {0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_R,          setlayout,      {.v = &layouts[0]} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_T,          setlayout,      {.v = &layouts[1]} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_F,          setlayout,      {.v = &layouts[2]} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_M,          setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                    XKB_KEY_space,      setlayout,      {0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_space,      togglefloating, {0} },
	{ MODKEY,                    XKB_KEY_e,          togglefullscreen, {0} },
	{ MODKEY,                    XKB_KEY_0,          view,           {.ui = ~0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_parenright, tag,            {.ui = ~0} },
	{ MODKEY,                    XKB_KEY_comma,      focusmon,       {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY,                    XKB_KEY_period,     focusmon,       {.i = WLR_DIRECTION_RIGHT} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_less,       tagmon,         {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_greater,    tagmon,         {.i = WLR_DIRECTION_RIGHT} },
	TAGKEYS(          XKB_KEY_1, XKB_KEY_exclam,                     0),
	TAGKEYS(          XKB_KEY_2, XKB_KEY_at,                         1),
	TAGKEYS(          XKB_KEY_3, XKB_KEY_numbersign,                 2),
	TAGKEYS(          XKB_KEY_4, XKB_KEY_dollar,                     3),
	TAGKEYS(          XKB_KEY_5, XKB_KEY_percent,                    4),
	TAGKEYS(          XKB_KEY_6, XKB_KEY_asciicircum,                5),
	TAGKEYS(          XKB_KEY_7, XKB_KEY_ampersand,                  6),
	TAGKEYS(          XKB_KEY_8, XKB_KEY_asterisk,                   7),
	TAGKEYS(          XKB_KEY_9, XKB_KEY_parenleft,                  8),
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_A,          restart,        {0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Q,          quit,           {0} },

	/* Ctrl-Alt-Backspace and Ctrl-Alt-Fx used to be handled by X server */
	{ WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_Terminate_Server, quit, {0} },
#define CHVT(n) { WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_XF86Switch_VT_##n, chvt, {.ui = (n)} }
	CHVT(1), CHVT(2), CHVT(3), CHVT(4), CHVT(5), CHVT(6),
	CHVT(7), CHVT(8), CHVT(9), CHVT(10), CHVT(11), CHVT(12),
};

static Button buttons[] = {
	{ MODKEY, BTN_LEFT,   moveclient,     {.ui = CurMove} },
	{ MODKEY, BTN_MIDDLE, togglefloating, {0} },
	{ MODKEY, BTN_RIGHT,  resizeclient,   {.ui = CurResize} },
};

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
static double accel_speed = 0.0;

typedef struct var_list {
    char name[64];
    char type[8];
    long link;
} var_list;

static var_list links[] = {
    { "sloppyfocus",                "int",      (long) &sloppyfocus },
    { "borderpx",                   "int",      (long) &borderpx },
    { "gappx",                      "int",      (long) &gappx },
    { "lockfullscreen",             "int",      (long) &lockfullscreen },
    { "rootcolor",                  "hex",      (long) &rootcolor },
    { "bordercolor",                "hex",      (long) &bordercolor },
    { "focuscolor",                 "hex",      (long) &focuscolor },
    { "repeat_rate",                "int",      (long) &repeat_rate },
    { "repeat_delay",               "int",      (long) &repeat_delay },
    { "tap_to_click",               "int",      (long) &tap_to_click },
    { "tap_and_drag",               "int",      (long) &tap_and_drag },
    { "drag_lock",                  "int",      (long) &drag_lock },
    { "natural_scrolling",          "int",      (long) &natural_scrolling },
    { "disable_while_typing",       "int",      (long) &disable_while_typing },
    { "left_handed",                "int",      (long) &left_handed },
    { "middle_button_emulation",    "int",      (long) &middle_button_emulation },
    { "accel_speed",                "double",   (long) &accel_speed },
    { "kbrules",                    "char",     (long) &kbrules },
    { "kbmodel",                    "char",     (long) &kbmodel },
    { "kbvariant",                  "char",     (long) &kbvariant },
    { "kblayout",                   "char",     (long) &kblayout },
    { "kboptions",                  "char",     (long) &kboptions },
};

static var_list kbd_props[] = {
    { "rules",                      "char",     (long) &kbrules},
    { "model",                      "char",     (long) &kbmodel },
    { "variant",                    "char",     (long) &kbvariant },
    { "layout",                     "char",     (long) &kblayout },
    { "options",                    "char",     (long) &kboptions },
};

static lua_State *lua;
#endif
