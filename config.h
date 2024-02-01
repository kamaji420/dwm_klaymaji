/* See LICENSE file for copyright and license details. */

/* constants */
#define TERMINAL "urxvt"
#define TERMOPS "-e"
#define BROWSER "io.gitlab.librewolf-community"
/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const int startwithgaps	    = 1;	/* 1 means gaps are used by default */
static const unsigned int gappx     = 8;        /* default gap between windows in pixels */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Terminess Nerd Font:size=13", "Symbols Nerd Font" };
static const char dmenufont[]       = "Terminess Nerd Font:size=13";
static const char col_gray1[]       = "#362c34";
static const char col_gray2[]       = "#f3c6c6";
static const char col_purple[]      = "#d9a2fb";
static const char col_pink[]        = "#f77ce6";
static const char *colors[][3]      = {
	/*               fg         bg          border   */
	[SchemeNorm] = { col_gray2, col_gray1,  col_pink },
	[SchemeSel]  = { col_gray1, col_purple, col_purple  },
};

/* tagging */
static const char *tags[] = { "", "", "", "󰊗", "󰄛", "", "󰗃", "󰵅", "󰎆" };
static const char *defaulttagapps[] = { "NULL", BROWSER, "com.valvesoftware.Steam", "net.lutris.Lutris", "NULL", "org.gimp.GIMP", "io.freetubeapp.FreeTube", "dev.vencord.Vesktop", "NULL", NULL }; 
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
};

/* layout(s) */
static const float mfact     = 0.60; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "",      tile },    /* first entry is default */
	{ "",      NULL },    /* no layout function means floating behavior */
	{ "[M]",    monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */

static const char dmenuprompt[] = "klaymaji<3";
static const char n3sort[] = "v";

static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_pink, "-sb", col_purple, "-sf", col_gray1, "-i", "-p", dmenuprompt, NULL };
static const char *termcmd [] = { TERMINAL, NULL };
static const char *pmixer[] = { TERMINAL, TERMOPS, "pulsemixer", NULL };
static const char *n3[] = { TERMINAL, TERMOPS, "nnn", "-T", n3sort, NULL };
static const char *shotgun[] = { "shotgun-selection", NULL };
static const char *up_vol[] = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "+1%",   NULL };
static const char *down_vol[] = { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "-1%",   NULL };
static const char *mute_vol[] = { "pactl", "set-sink-mute",   "@DEFAULT_SINK@", "toggle", NULL };

#include <X11/XF86keysym.h>
static const Key keys[] = {
	/* modifier                     key                      function        argument */
	{ MODKEY,                       XK_r,                    spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_t,                    spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_v,                    spawn,          {.v = pmixer } },
	{ MODKEY,                       XK_e,                    spawn,          {.v = n3 } },
	{ MODKEY,                       XK_p,                    spawn,          {.v = shotgun } },
	{ MODKEY,                       XK_s,                    spawndefault,   {0} },
	{ MODKEY,                       XK_b,                    togglebar,      {0} },
	{ MODKEY,                       XK_j,                    focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,                    focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_h,                    incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_l,                    incnmaster,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_h,                    setmfact,       {.f = -0.05} },
	{ MODKEY|ControlMask,           XK_l,                    setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_space,                zoom,           {0} },
	{ MODKEY,                       XK_Tab,                  view,           {0} },
	{ MODKEY,                       XK_d,                    killclient,     {0} },
	{ MODKEY|ControlMask,           XK_comma,                setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ControlMask,           XK_period,               setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ControlMask,           XK_slash,                setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_KP_Delete,            togglefloating, {0} },
	{ MODKEY,                       XK_KP_Insert,            togglefullscr,  {0} },
	{ MODKEY|ControlMask,           XK_KP_Delete,            view,           {.ui = ~0 } },
	{ MODKEY|ControlMask,           XK_KP_Insert,            tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,                focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,               focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,                tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,               tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_equal,                setgaps,        {.i = -5 } },
	{ MODKEY,                       XK_minus,                setgaps,        {.i = +5 } },
	{ MODKEY|ControlMask,           XK_0,                    setgaps,        {.i = GAP_RESET } },
	{ MODKEY,                       XK_0,                    setgaps,        {.i = GAP_TOGGLE} },
	{ 0,                            XF86XK_AudioMute,        spawn,          {.v = mute_vol } },
	{ 0,                            XF86XK_AudioLowerVolume, spawn,          {.v = down_vol } },
	{ 0,                            XF86XK_AudioRaiseVolume, spawn,          {.v = up_vol } },
	TAGKEYS(                        XK_1,                    0)
	TAGKEYS(                        XK_2,                    1)
	TAGKEYS(                        XK_3,                    2)
	TAGKEYS(                        XK_4,                    3)
	TAGKEYS(                        XK_5,                    4)
	TAGKEYS(                        XK_6,                    5)
	TAGKEYS(                        XK_7,                    6)
	TAGKEYS(                        XK_8,                    7)
	TAGKEYS(                        XK_9,                    8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions 3 */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = TERMINAL } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

