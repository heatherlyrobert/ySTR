/*===[[ HEADER GUARD ]]=======================================================*/
/*········´ ´···············guard·´ ´·········································*/
#ifndef    YSTR_uver_guard
#define    YSTR_uver_guard   loaded
/*········´ ´·····················´ ´·········································*/



/*===[[ BEG GNU GENERAL PUBLIC LICENSE (GPL) WARNING ]]=======================*/
/*´´·········1·········2·········3·········4·········5·········6·········7·········8  */

#define  P_COPYRIGHT   \
   "copyright (c) 2013 robert.s.heatherly at balsashrike at gmail dot com"

#define  P_LICENSE     \
   "the only place you could have gotten this code is my github, my website,¦"   \
   "or illegal sharing. given that, you should be aware that this is GPL licensed."

#define  P_COPYLEFT    \
   "the GPL COPYLEFT REQUIREMENT means any modifications or derivative works¦"   \
   "must be released under the same GPL license, i.e, must be free and open."

#define  P_INCLUDE     \
   "the GPL DOCUMENTATION REQUIREMENT means that you must include the original¦" \
   "copyright notice and the full licence text with any resulting anything."

#define  P_AS_IS       \
   "the GPL NO WARRANTY CLAUSE means the software is provided without any¦"      \
   "warranty and the author cannot be held liable for damages."

#define  P_THEFT    \
   "if you knowingly violate the spirit of these ideas, i suspect you might¦"    \
   "find any number of freedom-minded hackers may take it quite personally ;)"

/*´´·········1·········2·········3·········4·········5·········6·········7·········8  */
/*===[[ END GNU GENERAL PUBLIC LICENSE (GPL) WARNING ]]=======================*/



#include    "ySTR_solo.h"

/*
 * ystrlcpy
 * ystrlcat
 * ystrltrim
 * ystrlencode
 * ystrldecode
 * ystrlundelay
 */


char
ystrutrim               (uchar *b_src, int a_max)
{
   /*---(locals)-----------+-----+-----+-*/
   char           rce      =  -10;
   register char *s        = NULL;
   register char *e        = NULL;
   register int   n        = a_max;
   register int   c        =    0;
   register char  l        =  '-';
   char           m        =   26;          /* this is the marker char        */
   int            x_len    =    0;
   int            x_lim    =    0;
   char           x_str    =  '-';
   char          *x_work   = NULL;
   /*---(defense)------------------------*/
   --rce;  if (b_src == NULL)  return rce;
   if (a_max <= 0) {
      b_src [0] = '\0';
      return 1;
   }
   /*---(get the length)-----------------*/
   x_work = strdup (b_src);
   x_len = strlen (x_work);
   if (x_len < 0)  {
      x_work [a_max] = '\0';
      x_len         = a_max;
   }
   /*---(mark leading)-------------------*/
   s    = x_work;
   n    = a_max;
   while (*s != '\0') {
      if (n < 1)                                  break;
      if (*s != ' ' && *s != '\t' && *s != '\v')  break;
      *s = m;
      n--;
      s++;
   }
   /*---(wack trailing)------------------*/
   e    = x_work + x_len - 1;
   n    = a_max;
   while (e >= x_work) {
      if (n < 1)                                  break;
      if (*e != ' ' && *e != '\t' && *e != '\v')  break;
      *e = '\0';
      --x_len;
      e--;
      n--;
   }
   /*---(save-back)----------------------*/
   strcpy (b_src, s);
   free (x_work);
   /*---(complete)-----------------------*/
   return 0;
}

char
ystruencode             (uchar *b_src)
{
   register uchar *s        = b_src;
   while (*s != '\0') {
      switch (*s) {
      case G_KEY_SPACE  : s [0] = G_CHAR_SPACE ; break;
      case G_KEY_RETURN : s [0] = G_CHAR_RETURN; break;
      case G_KEY_ESCAPE : s [0] = G_CHAR_ESCAPE; break;
      case G_KEY_BS     : s [0] = G_CHAR_BS    ; break;
      case G_KEY_DEL    : s [0] = G_CHAR_DEL   ; break;
      case G_KEY_GROUP  : s [0] = G_CHAR_GROUP ; break;
      case G_KEY_FIELD  : s [0] = G_CHAR_FIELD ; break;
      }
      ++s;
   }
   return 0;
}

char
ystrudecode             (uchar *b_src)
{
   register uchar *s        = b_src;
   while (*s != '\0') {
      switch (*s) {
      case G_CHAR_SPACE  : s [0] = G_KEY_SPACE ; break;
      case G_CHAR_RETURN : s [0] = G_KEY_RETURN; break;
      case G_CHAR_ESCAPE : s [0] = G_KEY_ESCAPE; break;
      case G_CHAR_BS     : s [0] = G_KEY_BS    ; break;
      case G_CHAR_DEL    : s [0] = G_KEY_DEL   ; break;
      case G_CHAR_GROUP  : s [0] = G_KEY_GROUP ; break;
      case G_CHAR_FIELD  : s [0] = G_KEY_FIELD ; break;
      case G_CHAR_NULL   : s [0] = G_KEY_NULL  ; break;
      }
      ++s;
   }
   return 0;
}

char
ystrureplace            (uchar *a_src, uchar *a_old, uchar *a_new, int a_max)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;
   register uchar  *s           = a_src;         /* source pointer                 */
   register uchar  *t           = a_src;         /* source pointer                 */
   register uchar  *o           = a_old;         /* search pointer                 */
   int         n           = 0;
   int         lenf        = strlen (a_src);
   int         leno        = strlen (a_old);
   int         lenn        = strlen (a_new);
   int         lend        = lenn - leno;
   char        x_final     [LEN_HUGE] = "";
   /*---(defenses)-----------------------*/
   --rce;  if (a_src == NULL)           return  rce;
   --rce;  if (a_old == NULL)           return  rce;
   --rce;  if (a_new == NULL)           return  rce;
   --rce;  if (a_max >= LEN_HUGE)       return  rce;
   /*---(cycle)--------------------------*/
   --rce;
   while (1) {
      t = strstr (s, o);
      if (t == NULL)                    break;
      if (lenf + lend >= LEN_HUGE)      break;
      if (t - a_src + lenn >= a_max)    break;
      n = t - s;
      strncat  (x_final, s, n);
      strcat   (x_final, a_new);
      s = t + leno;
   }
   strcat   (x_final, s);
   strlcpy  (a_src, x_final, a_max);
   /*---(complete)-----------------------*/
   return 0;
}

char
ystruundelay            (uchar *a_src, int a_max)
{
   /*---(locals)-----------+-----+-----+-*/
   char        t           [5] = "";
   char        dslash      [5] = "\\\\";
   char        dquote      [5] = "\\\"";
   /*---(normal)-------------------------*/
   sprintf (t, "%c", G_CHAR_DBSLASH);
   ystrureplace (a_src, t, dslash, a_max);
   sprintf (t, "%c", G_CHAR_DDQUOTE);
   ystrureplace (a_src, t, dquote, a_max);
   /*---(complete)-----------------------*/
   return 0;
}
