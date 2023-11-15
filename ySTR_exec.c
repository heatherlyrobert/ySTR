/*===[[ START ]]==============================================================*/
#include    "ySTR.h"
#include    "ySTR_priv.h"



/*====================------------------------------------====================*/
/*===----                           arguments                          ----===*/
/*====================------------------------------------====================*/
static void      o___ARGS____________________o (void) {;}

char         /*--> parse command line ----------------------------------------*/
ystrlparse               (char *a_src, char *a_disp, char *a_final, char a_maxc, int *a_cnt, char *a_ptr [], int a_maxl)
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
   ystrlcpy  (mySTR.strtest , "", LEN_RECD);
   if (a_disp != NULL)   ystrlcpy  (a_disp, "", a_maxl);
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
   ystrlcpy (a_final, a_src, a_maxl);
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
   if (a_disp != NULL)   ystrlcpy  (a_disp, a_final, a_maxl);
   ystrlcpy  (mySTR.strtest , a_final, LEN_RECD);
   ystrldchg (a_final, '¤', '\0', LEN_RECD);
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
ystrlfile                (char *a_option, char *a_holder, char *a_value, char *a_ext, int a_max)
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
   ystrlcpy (a_holder, "", a_max);
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
      if (strchr (YSTR_FILES, a_value [i]) != NULL)  continue;
      if (a_option != NULL)  yURG_err ('f', "%s <name>, name can not have a <%c> at character %d", a_option, a_value [i], i);
      DEBUG_YSTR  yLOG_char  ("bad char"  , a_value [i]);
      DEBUG_YSTR  yLOG_exitr (__FUNCTION__, rce);
      return rce;
   }
   /*---(check extension)----------------*/
   ystrlcpy (t, a_value, a_max);
   DEBUG_YSTR  yLOG_point   ("a_ext"     , a_ext);
   if (a_ext != NULL) {
      DEBUG_YSTR  yLOG_note    ("extention provided");
      e = strlen (a_ext);
      if (e > 0) {
         DEBUG_YSTR  yLOG_complex ("test"      , "%2d, %2d, %c", l, e, a_ext [0]);
         if (l > e + 1) {
            DEBUG_YSTR  yLOG_complex ("compare"   , "[%s] to [%s]", a_ext, t + l - e);
            if (strcmp (t + l - e, a_ext) != 0) {
               if (a_ext [0] != '.')  ystrlcat (t, ".", a_max);
               ystrlcat (t, a_ext, a_max);
               DEBUG_YSTR  yLOG_info    ("fixed"     , t);
            }
         }
      }
   }
   /*---(save back)----------------------*/
   DEBUG_YSTR  yLOG_point   ("a_holder"  , a_holder);
   ystrlcpy (a_holder, t, a_max);
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
ystrlhome                (char *a_home)
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
   ystrlcpy (a_home, ""    , LEN_HUND);
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
   ystrlcpy (a_home, x_home, LEN_HUND);
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
ystrlbase               (cchar a_name [LEN_PATH], char r_path [LEN_PATH], char r_base [LEN_HUND], char r_proj [LEN_LABEL], char *r_level)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_name      [LEN_PATH]  = "";
   char       *p           = NULL;
   char       *q           = NULL;
   int         x_len       =    0;
   int         l           =    0;
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_senter  (__FUNCTION__);
   /*---(default)------------------------*/
   if (r_path  != NULL)  strcpy (r_path, "");
   if (r_base  != NULL)  strcpy (r_base, "");
   if (r_proj  != NULL)  strcpy (r_proj, "");
   if (r_level != NULL)  *r_level = 0;
   /*---(defense)------------------------*/
   DEBUG_YSTR   yLOG_spoint  (a_name);
   --rce;  if (a_name == NULL) {
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   x_len = strlen (a_name);
   DEBUG_YSTR   yLOG_sint    (x_len);
   --rce;  if (x_len <= 0) {
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   ystrlcpy (x_name, a_name, LEN_PATH);
   if (x_len > 1 && x_name [x_len - 1] == '/')  x_name [--x_len] = '\0';
   DEBUG_YSTR   yLOG_snote   (x_name);
   /*---(calculate level)----------------*/
   c = ystrldcnt (x_name, '/', LEN_PATH);
   if (x_name [0] == '/' && c > 0)  --c;
   if (r_level != NULL)  *r_level = c;
   /*---(parse)--------------------------*/
   p = strrchr (x_name, '/');
   DEBUG_YSTR   yLOG_spoint  (p);
   if (p == NULL)  p = x_name;
   else            ++p;
   q = strrchr (p, '.');
   DEBUG_YSTR   yLOG_spoint  (q);
   if (q != NULL)  ++q;
   /*---(handle path)--------------------*/
   if (p != x_name) {
      l = p - x_name;
      if (r_path != NULL)  ystrlcpy (r_path, x_name, l + 1);
      rc += 1;
   }
   /*---(handle base)--------------------*/
   l = p - x_name;
   if (l < x_len) {
      if (r_base != NULL)  ystrlcpy (r_base, p, LEN_HUND);
      rc += 2;
   }
   /*---(handle proj)--------------------*/
   if (strncmp ("/home/system/", x_name, 13) == 0 && p == x_name + 13) {
      if (q == NULL)  l = LEN_LABEL;
      else            l = q - p;
      if (l > LEN_LABEL)  l = LEN_LABEL;
      DEBUG_YSTR   yLOG_sint    (l);
      if (r_proj != NULL)  ystrlcpy (r_proj, p, l);
   }
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_sexit   (__FUNCTION__);
   return rc;
}

char
ystrlproj                (char *a_home, char *a_name)
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
   ystrlcpy (a_name, ""    , LEN_LABEL);
   DEBUG_YSTR   yLOG_spoint  (a_home);
   --rce;  if (a_home == NULL) {
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   x_len = strlen (a_home);
   DEBUG_YSTR   yLOG_sint    (x_len);
   --rce;  if (x_len <= 0) {
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   ystrlcpy (x_home, a_home, LEN_HUND);
   DEBUG_YSTR   yLOG_snote   (x_home);
   /*---(get the name)-------------------*/
   p = strrchr (x_home, '/');
   DEBUG_YSTR   yLOG_spoint  (p);
   if (p == NULL)   p = x_home;
   else             ++p;
   q = strchr  (p, '.');
   DEBUG_YSTR   yLOG_spoint  (q);
   if (q == NULL)  x_len = LEN_LABEL;
   else            x_len = q - p + 1;
   if (x_len > LEN_LABEL)  x_len = LEN_LABEL;
   DEBUG_YSTR   yLOG_sint    (x_len);
   /*---(save back)----------------------*/
   ystrlcpy (a_name, p, x_len);
   DEBUG_YSTR   yLOG_snote   (a_name);
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
ystrlhere                 (char *a_home, char *a_name)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_home      [LEN_HUND]  = "";
   char        x_name      [LEN_LABEL] = "";
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_enter   (__FUNCTION__);
   /*---(defaults)-----------------------*/
   if (a_home != NULL)    ystrlcpy (a_home, "", LEN_HUND);
   if (a_name != NULL)    ystrlcpy (a_name, "", LEN_LABEL);
   /*---(get directory)------------------*/
   rc = ystrlhome (x_home);
   DEBUG_YSTR   yLOG_value   ("get_home"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(get name)-----------------------*/
   rc = ystrlproj (x_home, x_name);
   DEBUG_YSTR   yLOG_value   ("get_name"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save results)-------------------*/
   ystrlcpy (a_home, x_home, LEN_HUND);
   ystrlcpy (a_name, x_name, LEN_LABEL);
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        file reading                          ----===*/
/*====================------------------------------------====================*/
static void      o___FILE____________________o (void) {;}

char*
ystrlrecd                (cchar *a_name, int n, int *c, char *a_recd, int a_max)
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
   if (a_recd != NULL)  ystrlcpy (a_recd, mySTR.strtest, a_max);
   /*---(complete)-----------------------*/
   return mySTR.strtest;
}

char*
ystrlread                (cchar *a_name, int n, int *c)
{
   return ystrlrecd (a_name, n, c, mySTR.strtest, LEN_RECD);
}

char
ystrlexport              (int a_line, char *a_recd)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   FILE       *f           = NULL;
   char        rc          =    0;
   int         x_len       =    0;
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YSTR   yLOG_spoint  ( a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(open)---------------------------*/
   if (a_line == 0)  f = fopen (YSTR_CLIP, "wt");
   else              f = fopen (YSTR_CLIP, "at");
   DEBUG_YSTR   yLOG_spoint  (f);
   --rce;  if (f == NULL) {
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(write)--------------------------*/
   x_len = fprintf (f, "%s\n", a_recd);
   DEBUG_YSTR   yLOG_sint    (x_len);
   /*---(close)--------------------------*/
   rc    = fclose (f);
   DEBUG_YSTR   yLOG_sint    (rc);
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
ystrlimport              (int a_line, char *a_recd, int *a_len)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   FILE       *f           = NULL;
   char        x_recd      [LEN_RECD] = "";
   int         x_len       =    0;
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YSTR   yLOG_spoint  (a_recd);
   --rce;  if (a_recd == NULL) {
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(defaults)-----------------------*/
   if (a_len != NULL)  *a_len = 0;
   ystrlcpy (a_recd, "", LEN_RECD);
   /*---(open)---------------------------*/
   f = fopen (YSTR_CLIP, "rt");
   DEBUG_YSTR   yLOG_spoint  (f);
   --rce;  if (f == NULL) {
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(read)---------------------------*/
   --rce;  while (c <= a_line)  {
      fgets (x_recd, LEN_RECD, f);
      if (feof (f)) {
         DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      ++c;
   }
   DEBUG_YSTR   yLOG_sint    (c);
   /*---(close)--------------------------*/
   rc = fclose (f);
   DEBUG_YSTR   yLOG_sint    (rc);
   /*---(clean)--------------------------*/
   x_len = strlen (x_recd);
   if (x_len > 0) {
      DEBUG_YSTR   yLOG_sint    (x_len);
      DEBUG_YSTR   yLOG_schar   (ychrvisible (x_recd [x_len - 1]));
      if (x_recd [x_len - 1] == '\n')  x_recd [--x_len] = '\0';
      if (x_len > 0) {
         DEBUG_YSTR   yLOG_schar   (ychrvisible (x_recd [x_len - 1]));
         if (x_recd [x_len - 1] == '³' )  x_recd [--x_len] = '\0';
      }
   }
   /*---(copy)---------------------------*/
   ystrlcpy (a_recd, x_recd, LEN_RECD);
   if (a_len != NULL)  *a_len = x_len;
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      date handling                           ----===*/
/*====================------------------------------------====================*/
static void      o___DATES___________________o (void) {;}

char
ystrl_age                (long a_now, long a_epoch, char a_fmt, char r_age [LEN_SHORT])
{  /*---(notes)--------------------------*/
   /*
    *  age is almost always more important to me than date, and
    *  quicker for me to interpret.  it also only needs three chars.
    *  if i keep to one way of presenting, it is even easier, for me.
    *  build-once, use-often.
    *
    *  -  = normal lower case units (also 'n' type)
    *  u  = upper case for large units
    *  N  = fill spaces with '·'
    *  U  = both u and N options
    */
   /*---(locals)-------------------------*/
   char        rce         =  -10;
   long        x_age       =    0;
   char        x_unit      =  '-';
   /*---(default)------------------------*/
   if (r_age != NULL)  strcpy (r_age, "  ·");
   /*---(defense)------------------------*/
   --rce;  if (r_age == NULL)  return rce;
   /*---(weird epoch)--------------------*/
   --rce;  if (a_epoch <= 0) {
      strcpy (r_age, "#/n");  /* n = negative/zero */
      return rce;
   }
   /*---(time difference)----------------*/
   x_age = a_now - a_epoch;
   --rce;  if (x_age < 0) {
      strcpy (r_age, "#/f");  /* f = future epoch  */
      return rce;
   }
   /*---(figure age)---------------------*/
   x_unit = 's';
   if (x_age == 0) {
      strcpy (r_age, " <s");
      return 0;
   }
   --rce;  if (x_age >= 60) {
      x_age /= 60; x_unit = 'm';
      if (x_age >= 60) {
         x_age /= 60; x_unit = 'h';
         if (x_age >= 24) {
            x_age /= 24; x_unit = 'd';
            if (x_age >= 30) {                /* months avg 30 days, close ;) */
               x_age /= 30; x_unit = 'o';
               if (x_age >= 12) {
                  x_age /= 12; x_unit = 'y';
                  if (x_age >= 100) {
                     x_age /= 100; x_unit = 'c';
                     if (x_age >= 100) {
                        strcpy (r_age, "#/h");  /* huge date 100+ centuries */
                        return rce;
                     }
                  }
               }
            }
         }
      }
   }
   /*---(adjust for format)--------------*/
   if (a_fmt != 0 && strchr ("uU", a_fmt) != NULL) {
      switch (x_unit) {
      case 'o' :  x_unit = 'M';  break;
      case 'y' :  x_unit = 'Y';  break;
      case 'c' :  x_unit = 'C';  break;
      }
   }
   /*---(save-back)----------------------*/
   sprintf (r_age, "%2d%c", x_age, x_unit);
   /*---(check for fill)-----------------*/
   if (a_fmt != 0 && strchr ("NU", a_fmt) != NULL) {
      if (r_age [0] == ' ')  r_age [0] = '·';
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
ystrlage                 (long a_epoch, char a_fmt, char r_age [LEN_SHORT])
{
   return ystrl_age (time (NULL), a_epoch, a_fmt, r_age);
}

char
ystrlager                (long a_now, long a_epoch, char a_fmt, char r_age [LEN_SHORT])
{
   return ystrl_age (a_now, a_epoch, a_fmt, r_age);
}

char
ystr_size                (llong a_bytes, char a_base, char a_fmt, char a_size [LEN_SHORT])
{  /*---(notes)--------------------------*/
   /*
    *  scaled sizes are almost always more important to me than single unit.
    *  quicker for me to interpret.  it also only needs three chars.
    *  if i keep to one way of presenting, it is even easier, for me.
    *  build-once, use-often.
    *
    *  -  = normal lower case units (also 'n' type)
    *  u  = upper case for large units
    *  N  = fill spaces with '·'
    *  U  = both u and N options
    *  t  = shows less than 1,000 numbers (rather than <k)
    *  T  = t plus U and N
    *
    */
   /*---(locals)-------------------------*/
   char        rce         =  -10;
   llong       x_size      =    0;
   char        x_unit      =  '-';
   int         x_mult      = 1000;
   /*---(default)------------------------*/
   if (a_bytes != NULL)  strcpy (a_size, "   ·");
   /*---(defense)------------------------*/
   --rce;  if (a_size == NULL)  return rce;
   /*---(weird epoch)--------------------*/
   --rce;  if (a_bytes <  0) {
      strcpy (a_size, "#/ne");  /* n = negative/zero */
      return rce;
   }
   x_size  = a_bytes;
   /*---(check trival size)--------------*/
   if (a_base = 'b')  x_mult = 1024;
   x_unit  = '´';
   if (strchr ("tT", a_fmt) == NULL && x_size == 0) {
      strcpy (a_size, "  <´");
      return 0;
   }
   /*---(figure size)--------------------*/
   if (x_size >= x_mult) {
      x_size /= x_mult;
      x_unit  = 'k';
      if (x_size >= x_mult) {
         x_size /= x_mult;
         x_unit  = 'm';
         if (x_size >= x_mult) {
            x_size /= x_mult;
            x_unit  = 'g';
            if (x_size >= x_mult) {
               x_size /= x_mult;
               x_unit  = 't';
               if (x_size >= x_mult) {
                  strcpy (a_size, "#/hu");  /* 1,000+ exabytes */
                  return rce;
               }
            }
         }
      }
   }
   /*---(adjust for format)--------------*/
   if (a_fmt != 0 && strchr ("uUtT", a_fmt) != NULL) {
      switch (x_unit) {
      case 'm' :  x_unit = 'M';  break;
      case 'g' :  x_unit = 'G';  break;
      case 't' :  x_unit = 'T';  break;
      }
   }
   /*---(save-back)----------------------*/
   if (strchr ("tT", a_fmt) == NULL && x_unit == '´') {
      strcpy (a_size, "  <k");
   } else {
      sprintf (a_size, "%3d%c", x_size, x_unit);
   }
   /*---(check for fill)-----------------*/
   if (a_fmt != 0 && strchr ("NTU", a_fmt) != NULL) {
      if (a_size [0] == ' ')  a_size [0] = '·';
      if (a_size [1] == ' ')  a_size [1] = '·';
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
ystrlsize                (llong a_bytes, char a_fmt, char a_size [LEN_SHORT])
{
   return ystr_size (a_bytes, 'b', a_fmt, a_size);
}

char
ystrlcount               (llong a_value, char a_fmt, char a_count [LEN_SHORT])
{
   return ystr_size (a_value, '-', a_fmt, a_count);
}

/*> char                                                                              <* 
 *> ystrlsize                (llong a_bytes, char a_fmt, char a_size [LEN_SHORT])     <* 
 *> {  /+---(notes)--------------------------+/                                       <* 
 *>    /+                                                                             <* 
 *>     *  scaled sizes are almost always more important to me than single unit.      <* 
 *>     *  quicker for me to interpret.  it also only needs three chars.              <* 
 *>     *  if i keep to one way of presenting, it is even easier, for me.             <* 
 *>     *  build-once, use-often.                                                     <* 
 *>     *                                                                             <* 
 *>     *  -  = normal lower case units (also 'n' type)                               <* 
 *>     *  u  = upper case for large units                                            <* 
 *>     *  N  = fill spaces with '·'                                                  <* 
 *>     *  U  = both u and N options                                                  <* 
 *>     *  t  = shows less than 1,000 numbers (rather than <k)                        <* 
 *>     *  T  = t plus U and N                                                        <* 
 *>     *                                                                             <* 
 *>     +/                                                                            <* 
 *>    /+---(locals)-------------------------+/                                       <* 
 *>    char        rce         =  -10;                                                <* 
 *>    llong       x_size      =    0;                                                <* 
 *>    char        x_unit      =  '-';                                                <* 
 *>    /+---(default)------------------------+/                                       <* 
 *>    if (a_bytes != NULL)  strcpy (a_size, "   ·");                                 <* 
 *>    /+---(defense)------------------------+/                                       <* 
 *>    --rce;  if (a_size == NULL)  return rce;                                       <* 
 *>    /+---(weird epoch)--------------------+/                                       <* 
 *>    --rce;  if (a_bytes <  0) {                                                    <* 
 *>       strcpy (a_size, "#/ne");  /+ n = negative/zero +/                           <* 
 *>       return rce;                                                                 <* 
 *>    }                                                                              <* 
 *>    x_size  = a_bytes;                                                             <* 
 *>    /+---(check trival size)--------------+/                                       <* 
 *>    x_unit  = '´';                                                                 <* 
 *>    if (strchr ("tT", a_fmt) == NULL && x_size == 0) {                             <* 
 *>       strcpy (a_size, "  <´");                                                    <* 
 *>       return 0;                                                                   <* 
 *>    }                                                                              <* 
 *>    /+---(figure size)--------------------+/                                       <* 
 *>    if (x_size >= 1000) {                                                          <* 
 *>       x_size /= 1000;                                                             <* 
 *>       x_unit  = 'k';                                                              <* 
 *>       if (x_size >= 1000) {                                                       <* 
 *>          x_size /= 1000;                                                          <* 
 *>          x_unit  = 'm';                                                           <* 
 *>          if (x_size >= 1000) {                                                    <* 
 *>             x_size /= 1000;                                                       <* 
 *>             x_unit  = 'g';                                                        <* 
 *>             if (x_size >= 1000) {                                                 <* 
 *>                x_size /= 1000;                                                    <* 
 *>                x_unit  = 't';                                                     <* 
 *>                if (x_size >= 1000) {                                              <* 
 *>                   strcpy (a_size, "#/hu");  /+ 1,000+ exabytes +/                 <* 
 *>                   return rce;                                                     <* 
 *>                }                                                                  <* 
 *>             }                                                                     <* 
 *>          }                                                                        <* 
 *>       }                                                                           <* 
 *>    }                                                                              <* 
 *>    /+---(adjust for format)--------------+/                                       <* 
 *>    if (a_fmt != 0 && strchr ("uUtT", a_fmt) != NULL) {                            <* 
 *>       switch (x_unit) {                                                           <* 
 *>       case 'm' :  x_unit = 'M';  break;                                           <* 
 *>       case 'g' :  x_unit = 'G';  break;                                           <* 
 *>       case 't' :  x_unit = 'T';  break;                                           <* 
 *>       }                                                                           <* 
 *>    }                                                                              <* 
 *>    /+---(save-back)----------------------+/                                       <* 
 *>    if (strchr ("tT", a_fmt) == NULL && x_unit == '´') {                           <* 
 *>       strcpy (a_size, "  <k");                                                    <* 
 *>    } else {                                                                       <* 
 *>       sprintf (a_size, "%3d%c", x_size, x_unit);                                  <* 
 *>    }                                                                              <* 
 *>    /+---(check for fill)-----------------+/                                       <* 
 *>    if (a_fmt != 0 && strchr ("NTU", a_fmt) != NULL) {                             <* 
 *>       if (a_size [0] == ' ')  a_size [0] = '·';                                   <* 
 *>       if (a_size [1] == ' ')  a_size [1] = '·';                                   <* 
 *>    }                                                                              <* 
 *>    /+---(complete)-----------------------+/                                       <* 
 *>    return 0;                                                                      <* 
 *> }                                                                                 <*/

char
ystr2mongo               (long a_epoch, char *a_mongo)
{
   /*---(locals)-----------+-----+-----+-*/
   long        x_now       =    0;
   tTIME      *x_broke     = NULL;
   /*---(set time)-----------------------*/
   if (a_epoch > 0)  x_now  = a_epoch;
   else              x_now  = time (NULL);
   /*---(break it down)------------------*/
   x_broke   = localtime (&x_now);
   /*---(take the pieces)----------------*/
   a_mongo [0] = YSTR_MONGO [x_broke->tm_year - 100];
   a_mongo [1] = YSTR_MONGO [x_broke->tm_mon];
   a_mongo [2] = YSTR_MONGO [x_broke->tm_mday - 1];
   a_mongo [3] = YSTR_MONGO [x_broke->tm_hour];
   a_mongo [4] = YSTR_MONGO [x_broke->tm_min];
   a_mongo [5] = YSTR_MONGO [x_broke->tm_sec];
   a_mongo [6] = '\0';
   /*---(complete)-----------------------*/
   return 0;
}

char
ystr4mongo               (char *a_mongo, long *a_epoch)
{
   /*---(locals)-----------+-----+-----+-*/
   tTIME       x_broke;
   /*---(take the pieces)----------------*/
   x_broke.tm_year  = strchr (YSTR_MONGO, a_mongo [0]) - YSTR_MONGO + 100;
   x_broke.tm_mon   = strchr (YSTR_MONGO, a_mongo [1]) - YSTR_MONGO;
   x_broke.tm_mday  = strchr (YSTR_MONGO, a_mongo [2]) - YSTR_MONGO + 1;
   x_broke.tm_hour  = strchr (YSTR_MONGO, a_mongo [3]) - YSTR_MONGO;
   x_broke.tm_min   = strchr (YSTR_MONGO, a_mongo [4]) - YSTR_MONGO;
   x_broke.tm_sec   = strchr (YSTR_MONGO, a_mongo [5]) - YSTR_MONGO;
   x_broke.tm_isdst = -1;
   /*---(break it down)------------------*/
   *a_epoch   = mktime (&x_broke);
   /*---(complete)-----------------------*/
   return 0;
}


