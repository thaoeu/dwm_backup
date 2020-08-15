#include <X11/XF86keysym.h>

/******
appearance
******/
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "Source Code Pro:size=17" };
static const char dmenufont[]       = "Source Code Pro:size=17";
static const char col_gray1[]       = "#282a36";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#f1f1f0";
static const char col_cyan[]        = "#66ccff";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_gray1,  col_cyan  },
};

static const char *const autostart[] = {
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "\uf120", "\uf121", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "",      tile },    /* first entry is default */
	{ "<(_ _)>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
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

/******
commands
******/
static char dmenumon[2]			=	"0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]		=	{ "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char scratchpadname[] 	=	"scratchpad";
static const char *scratchpadcmd[]	=	{ "st", "-t", scratchpadname, "-g", "56x35", NULL };
static const char *termcmd[]		=	{ "st", NULL };
static const char *konsole[]		=	{ "konsole", NULL };
static const char *screenshot[]		=	{ "deepin-screenshot", NULL };
//static const char *krunner[]		=	{ "krunner", NULL };
static const char *firefox[]		=	{ "firefox", NULL };
static const char *anki[]		=	{ "anki", NULL };
static const char *oud[]		=	{ "electron-netease-cloud-music", NULL};
static const char *vivaldi[]		=	{ "vivaldi-stable", NULL };

/******
Scripts
******/
static const char *keynav[]		=	{ "/home/qj/Script/keynav.sh", NULL };
static const char *ranger[]		=	{ "/home/qj/Script/st-ranger.sh", NULL };
static const char *trayer[]		=	{ "/home/qj/Script/trayer.sh", NULL };
static const char *fcitx[]		=	{ "/home/qj/Script/fcitx.sh", NULL };
static const char *WpCh[]		=	{ "/home/qj/Script/wp-change.sh", NULL };
static const char *VolUp[]		=	{ "/home/qj/Script/vol-up.sh", NULL };
static const char *VolDown[]		=	{ "/home/qj/Script/vol-down.sh", NULL };
static const char *Mute[]		=	{ "/home/qj/Script/VolMute.sh", NULL };
static const char *PlNext[]		=	{ "/home/qj/Script/Play-Next.sh", NULL };
static const char *PlPrev[]		=	{ "/home/qj/Script/Play-Prev.sh", NULL };
static const char *Pause[]		=	{ "/home/qj/Script/Play-pause.sh", NULL };
static const char *Stop[]		=	{ "/home/qj/Script/Play-Stop.sh", NULL };
static const char *Up1[]		=	{ "/home/qj/Script/vol1u.sh", NULL };
static const char *Dn1[]		=	{ "/home/qj/Script/vol1d.sh", NULL };
static const char *LigInc[]		=	{ "/home/qj/Script/LightInc.sh", NULL };
static const char *LigDec[]		=	{ "/home/qj/Script/LightDec.sh", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,			XK_Return,	spawn,		{.v = termcmd } },
	{ MODKEY,                       XK_space,	spawn,		{.v = dmenucmd } },
	{ MODKEY|ShiftMask,		XK_space,	spawn,		{.v = fcitx } },
	{ MODKEY,			XK_Insert,	spawn,		{.v = WpCh   } },
	{ MODKEY,			XK_t,		spawn,		{.v = konsole } },
	{ MODKEY,                       XK_h,		focusstack,	{.i = -1 } },
	{ MODKEY|ShiftMask,             XK_h,		zoom,		{0} },
	{ MODKEY,                       XK_l,		focusstack,	{.i = +1 } },
	{ MODKEY|ShiftMask,             XK_l,		zoom,		{0} },
	{ MODKEY,			XK_e,		spawn,		{.v = ranger } },
	{ MODKEY,			XK_m,		spawn,		{.v = anki } },
	{ MODKEY|ShiftMask,		XK_m,		spawn,		{.v = oud } },
	{ MODKEY,                       XK_a,		setlayout,	{.v = &layouts[1]} },
	{ MODKEY,                       XK_o,		setlayout,	{.v = &layouts[0]} },
	{ MODKEY,                       XK_b,		togglebar,	{0} },
	{ MODKEY,			XK_f,		spawn,		   {.v = firefox } },
	{ MODKEY,			XK_v,		spawn,		   {.v = vivaldi } },
	{ MODKEY|ShiftMask,             XK_w,	    	killclient,	{0} },
	{ MODKEY,                       XK_j,		setmfact,	{.f = -0.05} },
	{ MODKEY,                       XK_k,		setmfact,	{.f = +0.05} },
	{ MODKEY,                       XK_Tab,     	view,           {0} },
	{ MODKEY|ShiftMask,             XK_s,	    	spawn,		{.v = screenshot } },
	{ MODKEY,			XK_d,		spawn,		{.v = trayer } },
	{ MODKEY,			XK_i,		spawn,		{.v = keynav } },
	{ MODKEY,                       XK_u,		fullscreen,     {0} },
	{ MODKEY,                       XK_g,		incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_g,		incnmaster,     {.i = -1 } },
	{ MODKEY,			XK_apostrophe,	togglescratch,  {.v = scratchpadcmd } },
	/******
	Media operation
	******/

	{ 0,				XF86XK_AudioRaiseVolume,	spawn,		{.v = VolUp   } },
	{ MODKEY,			XF86XK_AudioRaiseVolume,	spawn,		{.v = Up1 } },
	{ 0,				XF86XK_AudioLowerVolume,	spawn,		{.v = VolDown } },
	{ MODKEY,			XF86XK_AudioLowerVolume,	spawn,		{.v = Dn1 } },
	{ 0,				XF86XK_AudioMute,		spawn,		{.v = Mute } } ,
	{ 0,				XF86XK_AudioPause,		spawn,		{.v = Pause } } ,
	{ 0,				XF86XK_AudioNext,		spawn,		{.v = PlNext } },
	{ 0,				XF86XK_AudioPrev,		spawn,		{.v = PlPrev } },
	{ 0,				XF86XK_AudioStop,		spawn,		{.v = Stop } },
//	{ MODKEY,                   	XK_backslash,spawn,				{.v = volup   } },

	/******
	BackLight
	******/
	{ 0,				XF86XK_MonBrightnessUp,		spawn,		{.v = LigInc } },
	{ 0,				XF86XK_MonBrightnessDown,	spawn,		{.v = LigDec } },

	/*
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
//	{ MODKEY,                       XK_space,  setlayout,      {0} },
//	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	*/
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

