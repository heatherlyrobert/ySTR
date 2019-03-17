/*===[[ START ]]==============================================================*/
#include    "ySTR.h"
#include    "ySTR_priv.h"



/*====================------------------------------------====================*/
/*===----                           delimeter                          ----===*/
/*====================------------------------------------====================*/
static void      o___DELIMITER_______________o (void) {;}

int          /*-> tbd --------------------------------[ leaf   [gn.530.341.50]*/ /*-[02.0000.000.!]-*/ /*-[--.---.---.--]-*/
strldcnt           (char *a_src, char  a_del, int a_max)
{  /*---(locals)-----------+-----------+-*/
   register char *s        = a_src;         /* source pointer                 */
   register int   n        = a_max;
   register int   c        = 0;
   register char  l        = '\0';          /* duplicate space skipper        */
   /*---(search)-------------------------*/
   while (*s != '\0') {
      if (n < 1)  break;
      if (*s == a_del) {
         if      (a_del != ' ')  ++c;
         else if (l     != ' ')  ++c;
      }
      l = *s;
      n--;
      s++;
   }
   /*---(complete)-----------------------*/
   return c;
}

int          /*--> find next delimiter in string ---------[ ------ [ ------ ]-*/
strldpos           (char *a_src, char  a_del, int a_cnt, int a_max)
{  /*---(locals)-----------+-----------+-*/
   register char *s        = a_src;         /* source pointer                 */
   register int   n        = a_max;
   register int   c        = 0;
   register char  l        = '\0';          /* duplicate space skipper        */
   /*---(search)-------------------------*/
   while (*s != '\0') {
      if (n < 1)  break;
      if (*s == a_del && l != ' ') {
         ++c;
         if (c >= a_cnt)  return a_max - n;
      }
      l = *s;
      n--;
      s++;
   }
   /*---(complete)-----------------------*/
   return -1;
}

int          /*--> find next delimiter in string ---------[ ------ [ ------ ]-*/
strlchr            (char *a_src, char  a_chr, int a_max)
{
   return strldpos (a_src, a_chr, 1, a_max);
}

int          /*--> change all delimeter in string --------[ ------ [ ------ ]-*/
strldchg           (char *a_src, char  a_del, char  a_new, int a_max)
{
   /*---(locals)-----------+-----------+-*/
   register char *s        = a_src;
   register int   n        = a_max;
   register int   c        = 0;
   /*---(compress)-----------------------*/
   while (*s != '\0') {
      if (n  <  1)  break;
      if (*s == a_del) {
         ++c;
         *s = a_new;
      }
      n--;
      s++;
   }
   /*---(complete)-----------------------*/
   return c;
}

int          /*--> remove all delimeter in string --------[ ------ [ ------ ]-*/
strlddel           (char *a_src, char  a_del, int a_max)
{
   /*---(locals)-----------+-----------+-*/
   register char *s        = a_src;
   register char  m        = a_del;
   register int   n        = a_max;
   register int   c        = 0;
   /*---(compress)-----------------------*/
   while (*(s + c) != '\0') {
      if (n  <  1)  break;
      n--;
      if (*(s + c) == m) {
         c++;
         continue;
      }
      *s = *(s + c);
      s++;
   }
   *s = '\0';
   /*---(complete)-----------------------*/
   return c;
}



/*====================------------------------------------====================*/
/*===----                           arguments                          ----===*/
/*====================------------------------------------====================*/
static void      o___ARGS____________________o (void) {;}

char       /*>---: PURPOSE : break string into an argv[] structure -----------*/
strlargs           (char *a_src, int a_max, int a_cnt, int *a_argc, char *a_argv[])
{
   /*---(defenses)-----------------------*/
   if (a_src == NULL) return -1;
   /*---(locals)-------------------------*/
   register char *s        = a_src;         /* source pointer                 */
   register int   n        = a_max;         /* maximum source length          */
   register int   c        = 0;             /* argument count                 */
   char           x_str    = '-';
   char           x_stop   = '-';
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_enter   (__FUNCTION__);
   DEBUG_YSTR   yLOG_point   ("a_src"     , a_src);
   DEBUG_YSTR   yLOG_value   ("a_max"     , a_max);
   DEBUG_YSTR   yLOG_value   ("a_cnt"     , a_cnt);
   DEBUG_YSTR   yLOG_point   ("a_argc"    , a_argc);
   DEBUG_YSTR   yLOG_point   ("a_argv"    , a_argv);
   /*---(trucate to protect)-------------*/
   /*> strltrunc (a_src, a_max);                                                      <*/
   /*---(process string)-----------------*/
   while (*s != '\0') {
      DEBUG_YSTR   yLOG_complex ("registers" , "*s=%c/%03d, n=%3d, c=%3d", *s, *s, n, c);
      /*---(end conditions)--------------*/
      if (n <= 1     )  break;
      if (c >  a_cnt )  break;
      /*---(handle character)------------*/
      if (*s != ' ' && *s != '\t' && *s != '\v') {
         DEBUG_YSTR   yLOG_note    ("handle as character");
         if (x_str == '-') {
            x_str = 'y';
            if (x_stop == 'y') {
               s++;
               break;
            }
            if (c <  a_cnt) {
               a_argv [c] = s;
               c++;
            }
            if (c >= a_cnt)  x_stop = 'y';
         }
      }
      /*---(handle whitespace)-----------*/
      else {
         DEBUG_YSTR   yLOG_note    ("handle as whitespace");
         x_str = '-';
         *s = '\0';
      }
      /*---(next character)--------------*/
      n--;
      s++;
   }
   /*---(update)-------------------------*/
   *a_argc = c;
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
   if (*s != '\0') {
      *s = '\0';
      if (c     >= a_cnt)  return -2;
      if (n     >= 0    )  return -3;
      if (a_max <= 0    )  return -4;
      if (a_cnt <= 0    )  return -5;
      return  -6;
   }
   if (n  <=  0  )  return -1;
   return 0;
}
