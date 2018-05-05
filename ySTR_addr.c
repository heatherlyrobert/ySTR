/*===[[ START ]]==============================================================*/
#include    "ySTR.h"
#include    "ySTR_priv.h"



static int ySTR_amx  =     0;
static int ySTR_amy  =     0;
static int ySTR_amz  =     0;

static int ySTR_lmx  =     0;
static int ySTR_lmy  =     0;
static int ySTR_lmz  =     0;

static int ySTR_axx  =   702;
static int ySTR_axy  = 99998;
static int ySTR_axz  =    35;

static int ySTR_lxx  =   702;
static int ySTR_lxy  = 99998;
static int ySTR_lxz  =    35;



char
str0gyges         (int x_min, int x_max, int y_min, int y_max, int z_min, int z_max)
{
   ySTR_lmx = x_min;
   ySTR_lmy = y_min;
   ySTR_lmz = z_min;
   ySTR_lxx = x_max;
   ySTR_lxy = y_max;
   ySTR_lxz = z_max;
   return 0;
}

char         /*-> convert label into tab, col, row ---[ leaf   [ge.#HB.1B#.Z0]*/ /*-[01.0000.K44.W]-*/ /*-[--.---.---.--]-*/
str2gyges         (char *a_src, int *x, int *y, int *z, char *a_abs, int a_def)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;           /* return code for errors         */
   int         x_len       =   0;           /* length of label                */
   int         i           =   0;           /* iterator -- character position */
   int         s_tab       =   0;           /* starting position of tab chars */
   int         x_tab       =   0;           /* working tab value              */
   int         s_col       =   0;           /* starting position of col chars */
   int         x_col       =   0;           /* working col value              */
   int         s_row       =   0;           /* starting position of row chars */
   int         x_row       =   0;           /* working row value              */
   int         e_row       =   0;           /* ending position of row chars   */
   int         x_abs       =   0;           /* working value for absolutes    */
   static char x_lsave     [LEN_LABEL] = "-----";
   static int  x_tsave, x_csave, x_rsave, x_asave, x_dsave;
   /*---(header)-------------------------*/
   DEBUG_STRG   yLOG_enter   (__FUNCTION__);
   /*---(prepare values)-----------------*/
   if (x     != NULL)  *x     = -1;
   if (y     != NULL)  *y     = -1;
   if (z     != NULL)  *z     = -1;
   if (a_abs != NULL)  *a_abs =  0;
   /*---(defense: empty label)-----------*/
   DEBUG_STRG   yLOG_point   ("a_src"     , a_src);
   --rce;  if (a_src == NULL) {
      DEBUG_STRG   yLOG_note    ("aborting, no a_src means no point");
      DEBUG_STRG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_STRG   yLOG_info    ("a_src"     , a_src);
   /*---(shortcut)-----------------------*/
   if (strcmp (a_src, x_lsave) == 0 && a_def == x_dsave) {
      DEBUG_STRG   yLOG_note    ("shortcut, same as last request");
      /*---(return values)------------------*/
      if (z     != NULL)  *z     = x_tsave;
      if (x     != NULL)  *x     = x_csave;
      if (y     != NULL)  *y     = x_rsave;
      if (a_abs != NULL)  *a_abs = x_asave;
      /*---(complete)-----------------------*/
      DEBUG_STRG   yLOG_exit    (__FUNCTION__);
      return  0;
   }
   /*---(display)------------------------*/
   DEBUG_STRG   yLOG_point   ("*z"        , z);
   DEBUG_STRG   yLOG_point   ("*x"        , x);
   DEBUG_STRG   yLOG_point   ("*y"        , y);
   DEBUG_STRG   yLOG_point   ("*a_abs"    , a_abs);
   DEBUG_STRG   yLOG_value   ("a_def"     , a_def);
   /*---(check sizes)--------------------*/
   x_len = strllen (a_src, LEN_LABEL);
   DEBUG_STRG   yLOG_value   ("x_len"       , x_len);
   --rce;  if (x_len <=  0) {
      DEBUG_STRG   yLOG_note    ("aborting, a_src contains nothing, no point");
      DEBUG_STRG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (x_len >  12) {  /* a1 to $Z$ab$12345 */
      DEBUG_STRG   yLOG_note    ("aborting, a_src too long for legal address");
      DEBUG_STRG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(defense: check special)---------*/
   --rce;  if (strcmp (a_src, "ROOT") == 0) {
      DEBUG_STRG   yLOG_note    ("aborting, no need to parse root");
      DEBUG_STRG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (x_len == 1 && strchr (",.-", a_src [0]) != NULL) {
      DEBUG_STRG   yLOG_note    ("aborting, no need to parse special char (,.-)");
      DEBUG_STRG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(look for absolute tab)----------*/
   DEBUG_STRG   yLOG_char    ("CH"        , a_src [s_tab]);
   if (a_src [s_tab] == '@') {
      x_abs  = 7;
      ++s_tab;
      DEBUG_STRG   yLOG_char    ("CH"        , a_src [s_tab]);
   }
   else if (a_src[s_tab] == '$') {
      x_abs  = 4;
      ++s_tab;
   }
   DEBUG_STRG   yLOG_value   ("x_abs"     , x_abs);
   DEBUG_STRG   yLOG_value   ("s_tab"     , s_tab);
   /*---(parse tab characters)-----------*/
   s_col = s_tab;
   DEBUG_STRG   yLOG_char    ("CH"        , a_src [s_tab]);
   if (strchr ("0123456789", a_src [s_tab]) != NULL) {
      x_tab = a_src[s_tab] - '0';
      ++s_col;
   } else if (strchr ("ABCDEFGHIJKLMNOPQRSTUVWXYZ", a_src [s_tab]) != NULL) {
      x_tab = a_src[s_tab] - 'A' + 10;
      ++s_col;
   } else {
      x_tab = a_def;
   }
   DEBUG_STRG   yLOG_complex ("tab"       , "z = %d,  abs range %d to %d,  loc range %d to %d", x_tab, ySTR_amz, ySTR_axz, ySTR_lmz, ySTR_lxz);
   --rce;  if (x_tab  < ySTR_amz || x_tab  < ySTR_lmz) {
      DEBUG_STRG   yLOG_note    ("z-pos too low (absolute or local)");
      DEBUG_STRG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (x_tab  > ySTR_axz || x_tab  > ySTR_lxz) {
      DEBUG_STRG   yLOG_note    ("z-pos too high (absolute or local)");
      DEBUG_STRG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if (s_col == s_tab && x_abs == 4)  x_abs = 1;
   /*---(look for absolute col)----------*/
   DEBUG_STRG   yLOG_value   ("s_col"     , s_col);
   DEBUG_STRG   yLOG_char    ("CH"        , a_src [s_col]);
   if (a_src [s_col] == '$') {
      x_abs += 1;
      ++s_col;
   }
   DEBUG_STRG   yLOG_value   ("x_abs"     , x_abs);
   DEBUG_STRG   yLOG_value   ("s_col"     , s_col);
   /*---(parse col characters)-----------*/
   s_row = s_col;
   for (i = s_col; i < s_col + 2; ++i) {
      DEBUG_STRG   yLOG_char    ("CH"        , a_src [i]);
      if (strchr ("abcdefghijklmnopqrstuvwxyz", a_src [i]) == 0)   break;
      if (i >  s_col)  x_col *= 26;
      x_col += a_src [i] - 'a' + 1;
      ++s_row;
   }
   DEBUG_STRG   yLOG_value   ("x_col"     , x_col);
   DEBUG_STRG   yLOG_value   ("s_row"     , s_row);
   --rce;  if (s_row == s_col) {
      DEBUG_STRG   yLOG_note    ("aborting, no column found");
      DEBUG_STRG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --x_col;
   DEBUG_STRG   yLOG_complex ("col"       , "x = %d,  abs range %d to %d,  loc range %d to %d", x_col, ySTR_amx, ySTR_axx, ySTR_lmx, ySTR_lxx);
   --rce;  if (x_col  < ySTR_amx || x_col  < ySTR_lmx) {
      DEBUG_STRG   yLOG_note    ("x-pos too low (absolute or local)");
      DEBUG_STRG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (x_col  > ySTR_axx || x_col  > ySTR_lxx) {
      DEBUG_STRG   yLOG_note    ("x-pos too high (absolute or local)");
      DEBUG_STRG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(look for absolute row)----------*/
   DEBUG_STRG   yLOG_value   ("s_row"     , s_row);
   DEBUG_STRG   yLOG_char    ("CH"        , a_src [s_row]);
   if (a_src [s_row] == '$') {
      x_abs += 2;
      ++s_row;
   }
   DEBUG_STRG   yLOG_value   ("x_abs"     , x_abs);
   DEBUG_STRG   yLOG_value   ("s_row"     , s_row);
   if (x_abs > 7)  x_abs = 7;
   /*---(parse row characters)-----------*/
   e_row = s_row;
   for (i = s_row; i < x_len; ++i) {
      DEBUG_STRG   yLOG_char    ("CH"        , a_src[i]);
      if (strchr ("0123456789", a_src[i]) == 0)   break;
      if (i >  s_row)  x_row *= 10;
      x_row += a_src[i] - '0';
      ++e_row;
   }
   DEBUG_STRG   yLOG_value   ("x_row"     , x_row);
   DEBUG_STRG   yLOG_value   ("e_row"     , e_row);
   --rce;  if (e_row != x_len  ) {
      DEBUG_STRG   yLOG_note    ("aborting, no row found");
      DEBUG_STRG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --x_row;
   DEBUG_STRG   yLOG_complex ("row"       , "y = %d,  abs range %d to %d,  loc range %d to %d", x_row, ySTR_amy, ySTR_axy, ySTR_lmy, ySTR_lxy);
   --rce;  if (x_row  < ySTR_amy || x_row  < ySTR_lmy) {
      DEBUG_STRG   yLOG_note    ("y-pos too low (absolute or local)");
      DEBUG_STRG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (x_row  > ySTR_axy || x_row  > ySTR_lxy) {
      DEBUG_STRG   yLOG_note    ("y-pos too high (absolute or local)");
      DEBUG_STRG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save for shortcut)--------------*/
   strlcpy (x_lsave, a_src, LEN_LABEL);
   x_tsave = x_tab;
   x_csave = x_col;
   x_rsave = x_row;
   x_asave = x_abs;
   x_dsave = a_def;
   /*---(return values)------------------*/
   if (z     != NULL)  *z     = x_tab;
   if (x     != NULL)  *x     = x_col;
   if (y     != NULL)  *y     = x_row;
   if (a_abs != NULL)  *a_abs = x_abs;
   /*---(complete)-----------------------*/
   DEBUG_STRG   yLOG_exit    (__FUNCTION__);
   return  0;
}

char         /*-> convert position into label --------[ ------ [ge.C90.177.91]*/ /*-[01.0000.C33.U]-*/ /*-[--.---.---.--]-*/
str4gyges         (int x, int y, int z, char a_abs, char *a_out)
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
   DEBUG_STRG   yLOG_enter   (__FUNCTION__);
   /*---(defense: valid output)----------*/
   --rce;  if (a_out == NULL) {
      DEBUG_STRG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   strlcpy (a_out  , "n/a", LEN_LABEL);
   strlcpy (x_label, "n/a", LEN_LABEL);
   /*---(defense: legal reference)-------*/
   --rce;  if (a_abs < 0 || a_abs > 7) {
      DEBUG_STRG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_STRG   yLOG_complex ("x"         , "x = %d,  abs range %d to %d,  loc range %d to %d", x, ySTR_amx, ySTR_axx, ySTR_lmx, ySTR_lxx);
   --rce;  if (x  < ySTR_amx || x  < ySTR_lmx || x  > ySTR_axx || x  > ySTR_lxx) {
      DEBUG_STRG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_STRG   yLOG_complex ("y"         , "y = %d,  abs range %d to %d,  loc range %d to %d", y, ySTR_amy, ySTR_axy, ySTR_lmy, ySTR_lxy);
   --rce;  if (y  < ySTR_amy || y  < ySTR_lmy || y  > ySTR_axy || y  > ySTR_lxy) {
      DEBUG_STRG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_STRG   yLOG_complex ("z"         , "z = %d,  abs range %d to %d,  loc range %d to %d", z, ySTR_amz, ySTR_axz, ySTR_lmz, ySTR_lxz);
   --rce;  if (z  < ySTR_amz || z  < ySTR_lmz || z  > ySTR_axz || z  > ySTR_lxz) {
      DEBUG_STRG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(figure out tab name)------------*/
   if (z <= 9)     x_tab = z + '0';
   else            x_tab = z - 10 + 'A';
   /*---(figure out column name)---------*/
   if   (x < 26)  {
      x_cname[0] = x + 'a';
   } else  {
      x_cname[0] = (x / 26) - 1 + 'a';
      x_cname[1] = (x % 26) + 'a';
   }
   x_cname[2] = '\0';
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
   sprintf (x_label, "%s%c%s%s%s%d", x_tref, x_tab, x_cref, x_cname, x_rref, y + 1);
   strcpy  (a_out, x_label);
   /*---(complete)-----------------------*/
   DEBUG_STRG   yLOG_exit    (__FUNCTION__);
   return  0;
}

char         /*-> convert position into label --------[ ------ [ge.C90.177.91]*/ /*-[01.0000.C33.U]-*/ /*-[--.---.---.--]-*/
str6gyges         (char *a_src, int a_def, char *a_out)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   int         x, y, z;
   int         x_abs       =    0;
   /*---(default)------------------------*/
   if (a_out != NULL)    strlcpy (a_out  , "n/a", LEN_LABEL);
   /*---(get coordinates)----------------*/
   rc = str2gyges (a_src, &x, &y, &z, &x_abs, a_def);
   if (rc < 0)   return rc;
   /*---(make new label)-----------------*/
   rc = str4gyges (x, y, z, x_abs, a_out);
   if (rc < 0)   return rc;
   /*---(complete)-----------------------*/
   return 0;
}

char         /*-> convert position into label --------[ ------ [ge.C90.177.91]*/ /*-[01.0000.C33.U]-*/ /*-[--.---.---.--]-*/
str8gyges         (char *a_src, int xo, int yo, int zo, char *a_out)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   int         x, y, z;
   int         x_abs       =    0;
   /*---(default)------------------------*/
   if (a_out != NULL)    strlcpy (a_out  , "n/a", LEN_LABEL);
   /*---(get coordinates)----------------*/
   rc = str2gyges (a_src, &x, &y, &z, &x_abs, 0);
   if (rc < 0)   return rc;
   /*---(update coordinates)-------------*/
   switch (x_abs) {
   case 0 :  x += xo; y += yo; z += zo;  break;
   case 1 :           y += yo; z += zo;  break;
   case 2 :  x += xo;          z += zo;  break;
   case 3 :                    z += zo;  break;
   case 4 :  x += xo; y += yo;           break;
   case 5 :  x += xo;                    break;
   case 6 :           y += yo;           break;
   case 7 :                              break;
   }
   /*---(make new label)-----------------*/
   rc = str4gyges (x, y, z, x_abs, a_out);
   if (rc < 0)   return rc;
   /*---(complete)-----------------------*/
   return 0;
}


