/*===[[ START ]]==============================================================*/
#include    "ySTR.h"
#include    "ySTR_priv.h"



static int ySTR_tmin  =     0;
static int ySTR_cmin  =     0;
static int ySTR_rmin  =     0;


static int ySTR_tmax  =    37;
static int ySTR_cmax  =   702;    /*  ·a to zz        */
static int ySTR_rmax  =  9998;    /*   100000 rows    */


static char *ySTR_tvalid  = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ®¯";
static char *ySTR_cvalid  = "abcdefghijklmnopqrstuvwxyz";
static char *ySTR_rvalid  = "0123456789";


static char    (*zSTR_checker)   (int a_tab, int a_col, int a_row, char a_check) = NULL;

static char s_func      =    0;
static char s_label     [LEN_LABEL] = "-----";
static char s_check     =  -10;
static int  s_tab       =  -10;
static int  s_col       =  -10;
static int  s_row       =  -10;
static int  s_abs       =  -10;
static int  s_def       =  -10;



/*====================------------------------------------====================*/
/*===----                          configuration                       ----===*/
/*====================------------------------------------====================*/
static void      o___CONFIG__________________o (void) {;}

char
str0gyges          (void *a_checker)
{
   zSTR_checker = a_checker;
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        common support                        ----===*/
/*====================------------------------------------====================*/
static void      o___SUPPORT_________________o (void) {;}

char
ystr_gyges__check     (int a_tab, int a_col, int a_row, int a_abs)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;           /* return code for errors        */
   /*---(defense: theoretical range)-----*/
   DEBUG_YSTR   yLOG_complex ("a_tab"     , "%4d,  abs range %d to %d", a_tab, ySTR_tmin, ySTR_tmax);
   --rce;  if (a_tab  < ySTR_tmin || a_tab  > ySTR_tmax) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR   yLOG_complex ("a_col"     , "%4d,  abs range %d to %d", a_col, ySTR_cmin, ySTR_cmax);
   --rce;  if (a_col  < ySTR_cmin || a_col  > ySTR_cmax) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR   yLOG_complex ("a_row"     , "%4d,  abs range %d to %d", a_row, ySTR_rmin, ySTR_rmax);
   --rce;  if (a_row  < ySTR_rmin || a_row  > ySTR_rmax) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR   yLOG_complex ("abs"       , "%4d,  abs range %d to %d", a_abs, 0, 7);
   --rce;  if (a_abs < 0 || a_abs > 7) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char         /*-> convert and check if legal ---------[ leaf   [ge.#HB.1B#.Z0]*/ /*-[01.0000.K44.W]-*/ /*-[--.---.---.--]-*/
ystr_gyges__legal       (int a_tab, int a_col, int a_row, char a_check)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         = -10;           /* return code for errors         */
   char        rc          = 0;             /* generic return code            */
   /*---(defense)------------------------*/
   if (a_check == YSTR_CHECK)  return 0;
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_enter   (__FUNCTION__);
   /*---(verify checker)-----------------*/
   DEBUG_YSTR   yLOG_point   ("checker"   , zSTR_checker);
   if (zSTR_checker == NULL) {
      DEBUG_YSTR   yLOG_note    ("no checker configured");
      DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(verify check type)--------------*/
   --rce;  if (a_check == YSTR_LEGAL) {
      DEBUG_YSTR   yLOG_note    ("conduct legal check");
   } else if  (a_check == YSTR_ADAPT) {
      DEBUG_YSTR   yLOG_note    ("grow/adapt to include");
   } else {
      DEBUG_YSTR   yLOG_note    ("a_check flag not understood");
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(host check)---------------------*/
   DEBUG_YSTR   yLOG_note    ("let host application check specifics");
   rc = zSTR_checker (a_tab, a_col, a_row, a_check);
   DEBUG_YSTR   yLOG_value   ("checker"   , rc);
   if (rc < 0) {
      DEBUG_YSTR   yLOG_note    ("position out of legal range");
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
   return  0;
}



/*====================------------------------------------====================*/
/*===----                 convert labels to positions                  ----===*/
/*====================------------------------------------====================*/
static void      o___TO_POS__________________o (void) {;}

char
ystr__gyges2prep        (char *a_src, int *a_tab, int *a_col, int *a_row, char *a_abs, int a_def, char a_check)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;           /* return code for errors        */
   int         x_len       =    0;           /* length of label               */
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_enter   (__FUNCTION__);
   /*---(default values)-----------------*/
   if (a_col != NULL)  *a_col = -2;
   if (a_row != NULL)  *a_row = -2;
   if (a_tab != NULL)  *a_tab = -2;
   if (a_abs != NULL)  *a_abs =  0;
   /*---(defense: empty label)-----------*/
   DEBUG_YSTR   yLOG_point   ("a_src"     , a_src);
   --rce;  if (a_src == NULL) {
      DEBUG_YSTR   yLOG_note    ("aborting, no a_src means no point");
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR   yLOG_info    ("a_src"     , a_src);
   /*---(shortcut saved)-----------------*/
   if (s_func == 2 && strcmp (a_src, s_label) == 0 && a_def == s_def && a_check == s_check) {
      DEBUG_YSTR   yLOG_note    ("shortcut, same as last request");
      /*---(return values)------------------*/
      if (a_tab != NULL)  *a_tab = s_tab;
      if (a_col != NULL)  *a_col = s_col;
      if (a_row != NULL)  *a_row = s_row;
      if (a_abs != NULL)  *a_abs = s_abs;
      /*---(complete)-----------------------*/
      DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
      return  1;
   }
   /*---(display)------------------------*/
   DEBUG_YSTR   yLOG_point   ("*a_tab"    , a_tab);
   DEBUG_YSTR   yLOG_point   ("*a_col"    , a_col);
   DEBUG_YSTR   yLOG_point   ("*a_row"    , a_row);
   DEBUG_YSTR   yLOG_point   ("*a_abs"    , a_abs);
   DEBUG_YSTR   yLOG_value   ("a_def"     , a_def);
   /*---(check for root)-----------------*/
   if (strcmp (a_src, "ROOT") == 0) {
      DEBUG_YSTR   yLOG_note    ("handling root");
      if (a_tab != NULL)  *a_tab = -1;
      if (a_col != NULL)  *a_col = -1;
      if (a_row != NULL)  *a_row = -1;
      if (a_abs != NULL)  *a_abs =  0;
      DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
      return 1;
   }
   /*---(check sizes)--------------------*/
   x_len = strllen (a_src, LEN_LABEL);
   DEBUG_YSTR   yLOG_value   ("x_len"       , x_len);
   --rce;  if (x_len <=  0) {
      DEBUG_YSTR   yLOG_note    ("aborting, a_src contains nothing, no point");
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (x_len >  12) {  /* a1 to $Z$ab$12345 */
      DEBUG_YSTR   yLOG_note    ("aborting, a_src too long for legal address");
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(defense: check special)---------*/
   --rce;  if (x_len == 1 && strchr (",.-", a_src [0]) != NULL) {
      DEBUG_YSTR   yLOG_note    ("aborting, no need to parse special char (,.-)");
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
   return  0;
}

char
ystr__gyges2tab         (char *a_src, char *a_pos, int *a_val, char *a_abs, char a_def)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;           /* return code for errors        */
   char       *p           = NULL;
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_senter  (__FUNCTION__);
   DEBUG_YSTR   yLOG_sint    (*a_pos);
   DEBUG_YSTR   yLOG_sint    (a_def);
   DEBUG_YSTR   yLOG_sint    (a_src [*a_pos]);
   /*---(check for full abs)-------------*/
   if (a_src [*a_pos] == '@') {
      DEBUG_YSTR   yLOG_snote   ("found full abs");
      *a_abs  = 7;
      ++*a_pos;
   }
   /*---(check for tab abs)--------------*/
   else if (a_src[*a_pos] == '$') {
      DEBUG_YSTR   yLOG_snote   ("found tab abs");
      *a_abs  = 4;
      ++*a_pos;
   }
   /*---(if found)-----------------------*/
   --rce;  if (a_src [*a_pos] == '\0') {
      DEBUG_YSTR   yLOG_snote   ("null, failed");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(search for tab chars)-----------*/
   DEBUG_YSTR   yLOG_schar   (a_src [*a_pos]);
   p = strchr (ySTR_tvalid, a_src [*a_pos]);
   /*---(if found)-----------------------*/
   if (p != NULL) {
      DEBUG_YSTR   yLOG_snote   ("found tab");
      *a_val = p - ySTR_tvalid;
      ++*a_pos;
   }
   /*---(if missing)---------------------*/
   else {
      DEBUG_YSTR   yLOG_snote   ("defaulting tab");
      *a_val = a_def;
      if (*a_abs == 4)  *a_abs = 1;  /* shift abs tab to abs col */
   }
   /*---(summary)------------------------*/
   DEBUG_YSTR   yLOG_sint    (*a_pos);
   DEBUG_YSTR   yLOG_sint    (*a_val);
   DEBUG_YSTR   yLOG_sint    (*a_abs);
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_sexit   (__FUNCTION__);
   return  0;
}

char
ystr__gyges2col         (char *a_src, char *a_pos, int *a_val, char *a_abs)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;           /* return code for errors        */
   char        x_pos       =    0;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_senter  (__FUNCTION__);
   DEBUG_YSTR   yLOG_sint    (*a_pos);
   DEBUG_YSTR   yLOG_sint    (a_src [*a_pos]);
   /*---(look for absolute)--------------*/
   if (a_src [*a_pos] == '$') {
      DEBUG_YSTR   yLOG_snote   ("found abs marker");
      *a_abs += 1;
      ++*a_pos;
      DEBUG_YSTR   yLOG_sint    (*a_pos);
      DEBUG_YSTR   yLOG_sint    (*a_abs);
   }
   /*---(parse characters)---------------*/
   *a_val = 0;
   x_pos  = *a_pos;
   for (i = x_pos; i < x_pos + 2; ++i) {
      DEBUG_YSTR   yLOG_sint    (a_src [i]);
      if (a_src [i] == '\0')                         break;
      DEBUG_YSTR   yLOG_schar   (a_src [i]);
      if (strchr (ySTR_cvalid, a_src [i]) == NULL)   break;
      if (i > x_pos)   *a_val *= 26;
      *a_val += a_src [i] - 'a' + 1;
      DEBUG_YSTR   yLOG_sint    (*a_val);
      ++*a_pos;
   }
   /*---(check for failure)--------------*/
   --rce;  if (*a_pos == x_pos) {
      DEBUG_YSTR   yLOG_snote   ("no column found");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(adjust value)-------------------*/
   --*a_val;
   /*---(summary)------------------------*/
   DEBUG_YSTR   yLOG_sint    (*a_pos);
   DEBUG_YSTR   yLOG_sint    (*a_val);
   DEBUG_YSTR   yLOG_sint    (*a_abs);
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_sexit   (__FUNCTION__);
   return  0;
}

char
ystr__gyges2row         (char *a_src, char *a_pos, int *a_val, char *a_abs)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;           /* return code for errors        */
   char        x_pos       =    0;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_senter  (__FUNCTION__);
   DEBUG_YSTR   yLOG_sint    (*a_pos);
   DEBUG_YSTR   yLOG_sint    (a_src [*a_pos]);
   /*---(look for absolute)--------------*/
   if (a_src [*a_pos] == '$') {
      DEBUG_YSTR   yLOG_snote   ("found abs marker");
      *a_abs += 2;
      ++*a_pos;
      DEBUG_YSTR   yLOG_sint    (*a_pos);
      DEBUG_YSTR   yLOG_sint    (*a_abs);
   }
   /*---(parse characters)---------------*/
   *a_val = 0;
   x_pos  = *a_pos;
   for (i = x_pos; i < x_pos + 4; ++i) {
      DEBUG_YSTR   yLOG_sint    (a_src [i]);
      if (a_src [i] == '\0')                         break;
      DEBUG_YSTR   yLOG_schar   (a_src [i]);
      if (strchr (ySTR_rvalid, a_src [i]) == NULL)   break;
      if (i >  x_pos)  *a_val *= 10;
      *a_val += a_src[i] - '0';
      DEBUG_YSTR   yLOG_sint    (*a_val);
      ++*a_pos;
   }
   /*---(check for failure)--------------*/
   --rce;  if (*a_pos == x_pos) {
      DEBUG_YSTR   yLOG_snote   ("no row found");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(adjust value)-------------------*/
   --*a_val;
   /*---(summary)------------------------*/
   DEBUG_YSTR   yLOG_sint    (*a_pos);
   DEBUG_YSTR   yLOG_sint    (*a_val);
   DEBUG_YSTR   yLOG_sint    (*a_abs);
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_sexit   (__FUNCTION__);
   return  0;
}

char         /*-> convert label into coordinates -----[ leaf   [ge.#HB.1B#.Z0]*/ /*-[01.0000.K44.W]-*/ /*-[--.---.---.--]-*/
str2gyges         (char *a_src, int *a_tab, int *a_col, int *a_row, char *a_abs, int a_def, char a_check)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;           /* return code for errors        */
   char        rc          =    0;           /* generic return code           */
   int         x_len       =    0;           /* length of label               */
   char        x_pos       =    0;
   int         x_tab       =    0;
   int         x_col       =    0;
   int         x_row       =    0;
   char        x_abs       =    0;
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   rc = ystr__gyges2prep  (a_src, a_tab, a_col, a_row, a_abs, a_def, a_check);
   --rce;  if (rc >  0) {
      DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   --rce;  if (rc <  0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(parse tab)----------------------*/
   rc = ystr__gyges2tab  (a_src, &x_pos, &x_tab, &x_abs, a_def);
   --rce;  if (rc <  0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(parse col)----------------------*/
   rc = ystr__gyges2col  (a_src, &x_pos, &x_col, &x_abs);
   --rce;  if (rc <  0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(parse row)----------------------*/
   rc = ystr__gyges2row  (a_src, &x_pos, &x_row, &x_abs);
   --rce;  if (rc <  0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check length)-------------------*/
   x_len = strllen (a_src, LEN_LABEL);
   DEBUG_YSTR   yLOG_value   ("x_pos"       , x_pos);
   DEBUG_YSTR   yLOG_value   ("x_len"       , x_len);
   --rce;  if (x_len != x_pos) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(fix abs)------------------------*/
   if (x_abs > 7)  x_abs = 7;
   /*---(check theoretical range)--------*/
   rc = ystr_gyges__check (x_tab, x_col, x_row, x_abs);
   --rce;  if (rc < 0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check theoretical range)--------*/
   rc = ystr_gyges__legal (x_tab, x_col, x_row, a_check);
   --rce;  if (rc < 0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save for shortcut)--------------*/
   DEBUG_YSTR   yLOG_note    ("save shortcuts");
   s_func  = 2;
   strlcpy (s_label, a_src, LEN_LABEL);
   s_tab   = x_tab;
   s_col   = x_col;
   s_row   = x_row;
   s_abs   = x_abs;
   s_def   = a_def;
   s_check = a_check;
   /*---(return values)------------------*/
   DEBUG_YSTR   yLOG_note    ("save return values");
   if (a_tab != NULL)  *a_tab = x_tab;
   if (a_col != NULL)  *a_col = x_col;
   if (a_row != NULL)  *a_row = x_row;
   if (a_abs != NULL)  *a_abs = x_abs;
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
   return  0;
}




/*====================------------------------------------====================*/
/*===----                 convert positions to labels                  ----===*/
/*====================------------------------------------====================*/
static void      o___TO_LABEL________________o (void) {;}

char
ystr__gyges4prep        (int a_tab, int a_col, int a_row, char a_abs, char *a_out, char a_check)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;           /* return code for errors        */
   int         x_len       =    0;           /* length of label               */
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_enter   (__FUNCTION__);
   /*---(defense: empty output)----------*/
   DEBUG_YSTR   yLOG_point   ("a_out"     , a_out);
   --rce;  if (a_out == NULL) {
      DEBUG_YSTR   yLOG_note    ("aborting, no a_out means no point");
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   strlcpy (a_out  , "n/a", LEN_LABEL);
   DEBUG_YSTR   yLOG_info    ("a_out"     , a_out);
   /*---(shortcut saved)-----------------*/
   if (s_func == 4 && a_tab == s_tab && a_col == s_col && a_row == s_row  && a_abs == s_abs && a_check == s_check) {
      DEBUG_YSTR   yLOG_note    ("shortcut, same as last request");
      /*---(return values)------------------*/
      if (a_out != NULL)  strlcpy (a_out, s_label, LEN_LABEL);
      /*---(complete)-----------------------*/
      DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
      return  1;
   }
   /*---(defense: root)------------------*/
   DEBUG_YSTR   yLOG_value   ("a_tab"     , a_tab);
   DEBUG_YSTR   yLOG_value   ("a_col"     , a_col);
   DEBUG_YSTR   yLOG_value   ("a_row"     , a_row);
   if (a_col == -1 && a_row == -1 && a_tab == -1) {
      DEBUG_YSTR   yLOG_note    ("requested ROOT");
      strlcpy (a_out  , "ROOT", LEN_LABEL);
      DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
      return 1;
   }
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
   return  0;
}

char         /*-> convert position into label --------[ leaf   [ge.IB4.5B#.B0]*/ /*-[02.0000.200.!]-*/ /*-[--.---.---.--]-*/
str4gyges         (int a_tab, int a_col, int a_row, char a_abs, char *a_out, char a_check)
{
   /*---(locals)-----------+-----+-----+-*/
   char        x_cname     [100]       = "";
   char        x_tref      [5]         = "";
   char        x_cref      [5]         = "";
   char        x_rref      [5]         = "";
   char        rce         = -10;           /* return code for errors         */
   char        rc          = 0;             /* generic return code            */
   char        x_tab       =  '0';
   char        x_label     [LEN_LABEL];
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   rc = ystr__gyges4prep  (a_tab, a_col, a_row, a_abs, a_out, a_check);
   --rce;  if (rc >  0) {
      DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   --rce;  if (rc <  0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check if valid)-----------------*/
   rc = ystr_gyges__check (a_tab, a_col, a_row, a_abs);
   --rce;  if (rc < 0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check if legal)-----------------*/
   rc = ystr_gyges__legal (a_tab, a_col, a_row, a_check);
   --rce;  if (rc < 0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(figure out tab name)------------*/
   x_tab = ySTR_tvalid [a_tab];
   DEBUG_YSTR   yLOG_char    ("x_tab"     , x_tab);
   /*---(figure out column name)---------*/
   if   (a_col < 26)  {
      x_cname[0] = a_col + 'a';
   } else  {
      x_cname[0] = (a_col / 26) - 1 + 'a';
      x_cname[1] = (a_col % 26) + 'a';
   }
   x_cname[2] = '\0';
   DEBUG_YSTR   yLOG_char    ("x_tab"     , x_tab);
   /*---(figure out reference markers)---*/
   switch (a_abs) {
   case 0 :                                                                   break;
   case 1 :                       strcpy (x_cref, "$");                       break;
   case 2 :                                             strcpy (x_rref, "$"); break;
   case 3 :                       strcpy (x_cref, "$"); strcpy (x_rref, "$"); break;
   case 4 : strcpy (x_tref, "$");                                             break;
   case 5 : strcpy (x_tref, "$"); strcpy (x_cref, "$");                       break;
   case 6 : strcpy (x_tref, "$");                       strcpy (x_rref, "$"); break;
   default: strcpy (x_tref, "@");                                             break;
   }
   /*---(create label)-------------------*/
   sprintf (x_label, "%s%c%s%s%s%d", x_tref, x_tab, x_cref, x_cname, x_rref, a_row + 1);
   strlcpy  (a_out, x_label, LEN_LABEL);
   DEBUG_YSTR   yLOG_info    ("a_out"     , a_out);
   /*---(save for shortcut)--------------*/
   DEBUG_YSTR   yLOG_note    ("save shortcuts");
   s_func  = 4;
   strlcpy (s_label, a_out, LEN_LABEL);
   s_tab   = a_tab;
   s_col   = a_col;
   s_row   = a_row;
   s_abs   = a_abs;
   s_def   = 0;
   s_check = a_check;
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
   return  0;
}



/*====================------------------------------------====================*/
/*===----                   pretty/update labels                       ----===*/
/*====================------------------------------------====================*/
static void      o___COMBOS__________________o (void) {;}

char         /*-> make label pretty ------------------[ leaf   [gc.420.353.30]*/ /*-[00.0000.000.!]-*/ /*-[--.---.---.--]-*/
str6gyges         (char *a_src, int a_def, char *a_out, char a_check)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   int         x_col, x_row, x_tab;
   int         x_abs       =    0;
   /*---(default)------------------------*/
   if (a_out != NULL)    strlcpy (a_out  , "n/a", LEN_LABEL);
   /*---(get coordinates)----------------*/
   rc = str2gyges (a_src, &x_tab, &x_col, &x_row, &x_abs, a_def, a_check);
   if (rc < 0)   return rc;
   /*---(make new label)-----------------*/
   rc = str4gyges (x_tab, x_col, x_row, x_abs, a_out, a_check);
   if (rc < 0)   return rc;
   /*---(complete)-----------------------*/
   return 0;
}

char         /*-> adjust address using offsets -------[ leaf   [gc.660.553.40]*/ /*-[00.0000.000.!]-*/ /*-[--.---.---.--]-*/
str8gyges         (char *a_src, int a_toff, int a_coff, int a_roff, char *a_out, char a_check)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   int         x_col, x_row, x_tab;
   int         x_abs       =    0;
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   if (a_out != NULL)    strlcpy (a_out  , "n/a", LEN_LABEL);
   /*---(get coordinates)----------------*/
   rc = str2gyges (a_src, &x_tab, &x_col, &x_row, &x_abs, 0, a_check);
   DEBUG_YSTR   yLOG_value   ("str2gyges" , rc);
   if (rc < 0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   DEBUG_YSTR   yLOG_complex ("starting"      , "%s, tab = %d, col = %d, row = %d", a_src, x_tab, x_col, x_row);
   /*---(update coordinates)-------------*/
   DEBUG_YSTR   yLOG_complex ("offset"        , "abs = %d, tab = %d, col = %d, row = %d", x_abs, a_toff, a_coff, a_roff);
   switch (x_abs) {
   case 0 :  x_col += a_coff; x_row += a_roff; x_tab += a_toff;  break;
   case 1 :                   x_row += a_roff; x_tab += a_toff;  break;
   case 2 :  x_col += a_coff;                  x_tab += a_toff;  break;
   case 3 :                                    x_tab += a_toff;  break;
   case 4 :  x_col += a_coff; x_row += a_roff;                   break;
   case 5 :  x_col += a_coff;                                    break;
   case 6 :                   x_row += a_roff;                   break;
   case 7 :                                                      break;
   }
   /*---(make new label)-----------------*/
   rc = str4gyges (x_tab, x_col, x_row, x_abs, a_out, a_check);
   DEBUG_YSTR   yLOG_value   ("str4gyges" , rc);
   if (rc < 0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   DEBUG_YSTR   yLOG_complex ("updated"       , "%s, tab = %d, col = %d, row = %d", a_out, x_tab, x_col, x_row);
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       unit testing helper                    ----===*/
/*====================------------------------------------====================*/
static void      o___UNIT_TEST_______________o (void) {;}

char
ystr_gyges__unit_check  (int a_tab, int a_col, int a_row, char a_check)
{
   char        rc          =    0;
   if (a_check == YSTR_ADAPT)  return 0;
   if (a_check != YSTR_LEGAL)  return 0;
   DEBUG_YSTR   yLOG_senter  (__FUNCTION__);
   DEBUG_YSTR   yLOG_sint    (a_tab);
   DEBUG_YSTR   yLOG_sint    (a_col);
   DEBUG_YSTR   yLOG_sint    (a_row);
   if (a_tab < 5) {
      DEBUG_YSTR   yLOG_snote   ("numeric (0-4) tab");
      if (a_col >  22)  rc = -1;
      if (a_row >  99)  rc = -1;
   }
   else if (a_tab < 10) {
      DEBUG_YSTR   yLOG_snote   ("numeric (5-9) tab");
      if (a_col >  40)  rc = -2;
      if (a_row > 499)  rc = -2;
   }
   else if (a_tab < 20) {
      DEBUG_YSTR   yLOG_snote   ("alpha (A-J) tab");
      if (a_col <  22)  rc = -3;
      if (a_row <  99)  rc = -3;
   }
   else {
      DEBUG_YSTR   yLOG_snote   ("alpha (K-¯) tab");
      if (a_col <  40)  rc = -4;
      if (a_row < 499)  rc = -4;
   }
   if (rc < 0)  DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rc);
   else         DEBUG_YSTR   yLOG_sexit   (__FUNCTION__);
   return rc;
}



