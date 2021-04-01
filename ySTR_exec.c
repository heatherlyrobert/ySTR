/*===[[ START ]]==============================================================*/
#include    "ySTR.h"
#include    "ySTR_priv.h"



/*====================------------------------------------====================*/
/*===----                           arguments                          ----===*/
/*====================------------------------------------====================*/
static void      o___ARGS____________________o (void) {;}

char         /*--> parse command line ----------------------------------------*/
strlparse               (char *a_src, char *a_disp, char *a_final, char a_maxc, int *a_cnt, char *a_ptr [], int a_maxl)
{
   /*---(locals)-------------------------*/
   char        rce         =  -10;
   int         l           =    0;          /* source length                  */
   int         n           =    0;          /* maximum source length          */
   int         c           =    0;          /* argument count                 */
   int         i           =    0;          /* position count                 */
   char        x_double    =  '-';
   char       *x_dir       = NULL;
   /*---(header)-------------------------*/
   DEBUG_YSTR  yLOG_enter   (__FUNCTION__);
   /*---(defaults)-----------------------*/
   strlcpy  (mySTR.strtest , "", LEN_RECD);
   if (a_disp != NULL)   strlcpy  (a_disp, "", a_maxl);
   /*---(defense)------------------------*/
   DEBUG_YSTR  yLOG_point   ("a_src"     , a_src);
   --rce;  if (a_src == NULL) {
      DEBUG_YSTR  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR  yLOG_info    ("a_src"     , a_src);
   DEBUG_YSTR  yLOG_point   ("a_final"   , a_final);
   --rce;  if (a_final == NULL) {
      DEBUG_YSTR  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR  yLOG_value   ("a_maxc"    , a_maxc);
   --rce;  if (a_maxc <= 0) {
      DEBUG_YSTR  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR  yLOG_point   ("a_ptr"     , a_ptr);
   --rce;  if (a_ptr == NULL) {
      DEBUG_YSTR  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR  yLOG_value   ("a_maxl"    , a_maxl);
   --rce;  if (a_maxl <= 0) {
      DEBUG_YSTR  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   l = strlen (a_src);
   if (l > a_maxl)  l = a_maxl;
   DEBUG_YSTR  yLOG_value   ("l"         , l);
   for (i = 0; i < a_maxc; ++i)  a_ptr [i] = NULL;
   if (a_maxc <= 1)  {
      if (a_cnt != NULL)  *a_cnt = c + 1;
      DEBUG_YSTR  yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(copy source)--------------------*/
   strlcpy (a_final, a_src, a_maxl);
   a_ptr [c] = a_final;
   /*---(process string)-----------------*/
   for (i = 0; i < l; ++i) {
      /*---(header)----------------------*/
      DEBUG_YSTR  yLOG_complex ("position"  , "a_final [%3d]=%c/%03d, c=%3d", i, a_final [i], a_final [i], c);
      /*---(escaped quotes)--------------*/
      if (a_final [i] == '\\') {
         DEBUG_YSTR  yLOG_note    ("escaped character");
         if (a_final [i + 1] == '\'')  { ++i; continue; }
         if (a_final [i + 1] == '"')   { ++i; continue; }
      }
      /*---(char literals)---------------*/
      if (a_final [i] == '\'') {
         DEBUG_YSTR  yLOG_note    ("character literal");
         if (a_final [i + 1] == '\\' && a_final [i + 3] == '\'') { i += 3;  continue; }
         else if (a_final [i + 2] == '\'')                      { i += 2;  continue; }
      }
      /*---(double quotes)---------------*/
      if (a_final [i] == '"') {
         if (x_double == '-')  {
            DEBUG_YSTR  yLOG_note    ("openning double quote");
            x_double = 'y'; 
            continue;
         } else {
            DEBUG_YSTR  yLOG_note    ("closing double quote");
            x_double = '-';
            continue;
         }
      }
      if (x_double == 'y') {
         DEBUG_YSTR  yLOG_note    ("double quoted (protected)");
         continue;
      }
      /*---(find gaps)-------------------*/
      if (a_final [i] == ' ' || a_final [i] == '\t')  {
         DEBUG_YSTR  yLOG_note    ("unquoted gap marker (nulling)");
         if (c >= a_maxc - 2)  break;
         a_final [i] = '¤';
         while (a_final [i + 1] == ' ' || a_final [i] == '\t') {
            a_final [++i] = '¤';
         }
         if (a_final [i + 1] != '\0')  a_ptr [++c] = a_final + i + 1;
         continue;
      }
      /*---(done)------------------------*/
   }
   /*---(update)-------------------------*/
   if (a_disp != NULL)   strlcpy  (a_disp, a_final, a_maxl);
   strlcpy  (mySTR.strtest , a_final, LEN_RECD);
   strldchg (a_final, '¤', '\0', LEN_RECD);
   DEBUG_YSTR  yLOG_value   ("c"         , c);
   if (a_cnt != NULL)  *a_cnt = c + 1;
   /*---(complete)-----------------------*/
   DEBUG_YSTR  yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                    configuration support                     ----===*/
/*====================------------------------------------====================*/
static void      o___CONFIG__________________o (void) {;}

char
strlfile                (char *a_option, char *a_holder, char *a_value, char *a_ext, int a_max)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         l           =    0;
   int         e           =    0;
   int         i           =    0;
   char        t           [LEN_RECD]  = "";
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YSTR  yLOG_point   ("a_holder"  , a_holder);
   --rce;  if (a_holder == NULL) {
      DEBUG_YSTR  yLOG_exitr (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR  yLOG_info    ("a_holder"  , a_holder);
   strlcpy (a_holder, "", a_max);
   /*---(defense)------------------------*/
   DEBUG_YSTR  yLOG_point   ("a_value"   , a_value);
   --rce;  if (a_value == NULL) {
      if (a_option != NULL)  yURG_err ('f', "%s <name>, name can not be null", a_option);
      DEBUG_YSTR  yLOG_exitr (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR  yLOG_info    ("a_value"   , a_value);
   /*---(check length)-------------------*/
   l = strlen (a_value);
   DEBUG_YSTR  yLOG_value   ("l"         , l);
   --rce;  if (l <= 0) {
      if (a_option != NULL)  yURG_err ('f', "%s <name>, name can not be blank/empty", a_option);
      DEBUG_YSTR  yLOG_exitr (__FUNCTION__, rce);
      return rce;
   }
   /*---(check characters)---------------*/
   --rce;  for (i = 0; i < l; ++i) {
      if (strchr (LTRS_FILES, a_value [i]) != NULL)  continue;
      if (a_option != NULL)  yURG_err ('f', "%s <name>, name can not have a <%c> at character %d", a_option, a_value [i], i);
      DEBUG_YSTR  yLOG_char  ("bad char"  , a_value [i]);
      DEBUG_YSTR  yLOG_exitr (__FUNCTION__, rce);
      return rce;
   }
   /*---(check extension)----------------*/
   strlcpy (t, a_value, a_max);
   DEBUG_YSTR  yLOG_point   ("a_ext"     , a_ext);
   if (a_ext != NULL) {
      DEBUG_YSTR  yLOG_note    ("extention provided");
      e = strlen (a_ext);
      if (e > 0) {
         DEBUG_YSTR  yLOG_complex ("test"      , "%2d, %2d, %c", l, e, a_ext [0]);
         if (l > e + 1) {
            DEBUG_YSTR  yLOG_complex ("compare"   , "[%s] to [%s]", a_ext, t + l - e);
            if (strcmp (t + l - e, a_ext) != 0) {
               if (a_ext [0] != '.')  strlcat (t, ".", a_max);
               strlcat (t, a_ext, a_max);
               DEBUG_YSTR  yLOG_info    ("fixed"     , t);
            }
         }
      }
   }
   /*---(save back)----------------------*/
   DEBUG_YSTR  yLOG_point   ("a_holder"  , a_holder);
   strlcpy (a_holder, t, a_max);
   DEBUG_YSTR  yLOG_info    ("a_holder"  , a_holder);
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      location support                        ----===*/
/*====================------------------------------------====================*/
static void      o___LOCATION________________o (void) {;}

char
strlhome                (char *a_home)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_home      [LEN_HUND]  = "";
   char       *p           = NULL;
   int         x_len       =    0;
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_senter  (__FUNCTION__);
   /*---(check return)-------------------*/
   DEBUG_YSTR   yLOG_spoint  (a_home);
   --rce;  if (a_home == NULL) {
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(default)------------------------*/
   strlcpy (a_home, ""    , LEN_HUND);
   /*---(get the home)-------------------*/
   p = getcwd (x_home, LEN_HUND);
   DEBUG_YSTR   yLOG_spoint  (p);
   --rce;  if (p == NULL) {
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR   yLOG_snote   (x_home);
   x_len = strlen (x_home);
   DEBUG_YSTR   yLOG_sint    (x_len);
   /*---(check valid areas)--------------*/
   --rce; if (x_len > 16 && strncmp ("/home/system/"         , x_home, 13) == 0) {
      DEBUG_YSTR   yLOG_snote   ("system");
      ;;
   } else if (x_len > 16 && strncmp ("/home/monkey/"         , x_home, 13) == 0) {
      DEBUG_YSTR   yLOG_snote   ("monkey");
      ;;
   } else if (x_len > 25 && strncmp ("/home/member/p_gvskav/", x_home, 22) == 0) {
      DEBUG_YSTR   yLOG_snote   ("member");
      ;;
   } else if (x_len >  8 && strncmp ("/tmp/"                 , x_home,  5) == 0) {
      DEBUG_YSTR   yLOG_snote   ("unittest");
      ;;
   } else {
      DEBUG_YSTR   yLOG_snote   ("not allowed");
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(save back)----------------------*/
   strlcpy (a_home, x_home, LEN_HUND);
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
strlproj                (char *a_home, char *a_name)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_home      [LEN_HUND]  = "";
   char       *p           = NULL;
   char       *q           = NULL;
   int         x_len       =    0;
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_senter  (__FUNCTION__);
   /*---(check return)-------------------*/
   DEBUG_YSTR   yLOG_spoint  (a_name);
   --rce;  if (a_name == NULL) {
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   strlcpy (a_name, ""    , LEN_TITLE);
   DEBUG_YSTR   yLOG_spoint  (a_home);
   --rce;  if (a_home == NULL) {
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   x_len = strlen (a_home);
   DEBUG_YSTR   yLOG_sint    (x_home);
   --rce;  if (x_len <= 0) {
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   strlcpy (x_home, a_home, LEN_HUND);
   DEBUG_YSTR   yLOG_snote   (x_home);
   /*---(get the name)-------------------*/
   p = strrchr (x_home, '/');
   DEBUG_YSTR   yLOG_spoint  (p);
   if (p == NULL)   p = x_home;
   else             ++p;
   q = strchr  (p, '.');
   DEBUG_YSTR   yLOG_spoint  (q);
   if (q == NULL)  x_len = LEN_TITLE;
   else            x_len = q - p + 1;
   if (x_len > LEN_TITLE)  x_len = LEN_TITLE;
   DEBUG_YSTR   yLOG_sint    (x_len);
   /*---(save back)----------------------*/
   strlcpy (a_name, p, x_len);
   DEBUG_YSTR   yLOG_snote   (a_name);
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
strlhere                 (char *a_home, char *a_name)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_home      [LEN_HUND]  = "";
   char        x_name      [LEN_TITLE] = "";
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_enter   (__FUNCTION__);
   /*---(defaults)-----------------------*/
   if (a_name != NULL)    strlcpy (a_name, "", LEN_TITLE);
   if (a_home != NULL)    strlcpy (a_home, "", LEN_TITLE);
   /*---(get directory)------------------*/
   rc = strlhome (x_home);
   DEBUG_YSTR   yLOG_value   ("get_home"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(get name)-----------------------*/
   rc = strlproj (x_home, x_name);
   DEBUG_YSTR   yLOG_value   ("get_name"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save results)-------------------*/
   strlcpy (a_name, x_name, LEN_TITLE);
   strlcpy (a_home, x_home, LEN_HUND);
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        file reading                          ----===*/
/*====================------------------------------------====================*/
static void      o___FILE____________________o (void) {;}

char*
strlrecd                (cchar *a_name, int n, int *c, char *a_recd, int a_max)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   FILE       *f           = NULL;
   char        t           [LEN_RECD]  = "";
   int         i           =    0;
   int         x_len       =    0;
   /*---(defense)------------------------*/
   --rce;  if (a_name == NULL)         return "err  : name is null";
   --rce;  if (strlen (a_name) <= 0)   return "err  : name is empty";
   if (c != NULL)  *c = 0;
   strncpy (mySTR.strtest, "", a_max);
   /*---(open file)----------------------*/
   f = fopen (a_name                 , "rt");
   --rce;  if (f == NULL)              return "err  : file can not open";
   /*---(read records)-------------------*/
   while (1) {
      fgets (t, LEN_RECD, f);
      if (i != 0 && feof (f))  break;
      if (n <  0)  strncpy (mySTR.strtest, t, a_max);
      if (i == n)  strncpy (mySTR.strtest, t, a_max);
      if (feof (f))            break;
      ++i;
   }
   if (i > 999)  i = 999;
   /*---(clean record)-------------------*/
   x_len = strlen (mySTR.strtest);
   if (x_len > 0 && mySTR.strtest [x_len - 1] == '\n')  mySTR.strtest [--x_len] = '\0';
   /*---(close file)---------------------*/
   fclose (f);
   /*---(save back)----------------------*/
   if (c      != NULL)  *c = i;
   if (a_recd != NULL)  strlcpy (a_recd, mySTR.strtest, a_max);
   /*---(complete)-----------------------*/
   return mySTR.strtest;
}

char*
strlread                (cchar *a_name, int n, int *c)
{
   return strlrecd (a_name, n, c, mySTR.strtest, LEN_RECD);
}

