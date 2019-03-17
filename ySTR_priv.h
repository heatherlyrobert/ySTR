/*===[[ HEADER GUARD ]]=======================================================*/
#ifndef YSTR_priv_hguard
#define YSTR_priv_hguard loaded



/*===[[ HEADER ]]=============================================================*/
/*345678901-12345678901-123456789-123456789-123456789-123456789-123456789-123456789-123456789-*/

#define     P_FOCUS     "PS (programming support)"
#define     P_NICHE     "st (string handling)"
#define     P_PURPOSE   "provide secure and useful string handling capabilities"

#define     P_NAMESAKE  "astrea-kori (star-maiden)"
#define     P_HERITAGE  "virgin goddess of justice, purity, and precision"
#define     P_IMAGERY   "elegant with shinning wings, angel light, and flamming torch"

#define     P_SYSTEM    "gnu/linux   (powerful, ubiquitous, technical, and hackable)"
#define     P_LANGUAGE  "ansi-c      (wicked, limitless, universal, and everlasting)"
#define     P_CODESIZE  "small       (appoximately 1,000 slocl)"

#define     P_AUTHOR    "heatherlyrobert"
#define     P_CREATED   "2013-09"
#define     P_DEPENDS   "none"

#define     P_VERMAJOR  "0.Xx pre-production"
#define     P_VERMINOR  "0.5x get gyges support cleaned up and integrated with gyges"
#define     P_VERNUM    "0.5g"
#define     P_VERTXT    "separated code and unit tests better for easier maintenance"



/*345678901-12345678901-123456789-123456789-123456789-123456789-123456789-123456789-123456789-*/
#define      _XOPEN_SOURCE
#include    <stdio.h>
#include    <stdlib.h>                  /* getenv()                            */
#include    <string.h>
#include    <math.h>  
#include    <time.h>         /* C_ANSI : time, strftime, localtime            */

#include    <yURG.h>                    /* heatherly program logger            */
#include    <yLOG.h>                    /* heatherly program logger            */
#include    "ySTR.h"



/* rapidly evolving version number to aid with visual change confirmation     */



#define     ySTR_ALL_HEADS   "hbsem"
#define     ySTR_ALL_TAILS   "tbsem"
#define     ySTR_ALL_INTER   "esm"


typedef     struct   tm           tTIME;


typedef struct cLOCAL tLOCAL;
struct cLOCAL {
   /*---(overall)-----------*/
   char        debug;
   int         logger;
   /*---(testing)-----------*/
   char        strtest     [100];
   int         argc;
   char       *argv        [20];
};
extern  tLOCAL mySTR;

#define     FONT_FULL      'f'       /* [a-z][0-9] */
#define     FONT_ALPHA     'a'       /* [a-z]      */
#define     FONT_NUMS      'n'       /* [0-9]      */
#define     FONT_BINARY    'b'       /* [0-1]      */
#define     TYPE_BINARY    "01 "
#define     TYPE_NUM       "0123456789"
#define     TYPE_ALPHA     "abcdefghijklmnopqrstuvwxyz "
#define     TYPE_ALNUM     "abcdefghijklmnopqrstuvwxyz 0123456789"
#define     TYPE_FULLER    "abcdefghijklmnopqrstuvwxyz 0123456789.,:-_'¶()"


extern char   unit_answer [LEN_RECD];


char        ySTR_testquiet     (void);
char        ySTR_testloud      (void);
char        ySTR_testend       (void);
char*       ySTR_unit          (char *a_question, int a_num);


char        ystr__gyges2tab         (char *a_src, char *a_pos, int *a_val, char *a_abs, char a_def);
char        ystr__gyges2col         (char *a_src, char *a_pos, int *a_val, char *a_abs);
char        ystr__gyges2row         (char *a_src, char *a_pos, int *a_val, char *a_abs);
char        ystr_gyges__check       (int a_tab, int a_col, int a_row, int a_abs);
char        ystr_gyges__legal       (int a_tab, int a_col, int a_row, char a_check);

char        ystr_gyges__unit_check  (int b, int x, int y, char z, char a_check);

char        ystr__getlang           (char *a_iso);

char        ystr_font__index        (char a_range, int a_letter);

#endif
