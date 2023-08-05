/*===[[ HEADER GUARD ]]=======================================================*/
#ifndef YSTR_priv_hguard
#define YSTR_priv_hguard loaded



/*===[[ HEADER ]]=============================================================*/
/*345678901-12345678901-123456789-123456789-123456789-123456789-123456789-123456789-123456789-*/

#define     P_FOCUS     "PS (programming support)"
#define     P_NICHE     "st (string handling)"
#define     P_SUBJECT   "useful, safe string handling"
#define     P_PURPOSE   "provide secure and useful string handling capabilities"

#define     P_NAMESAKE  "astrea-kori (star-maiden)"
#define     P_HERITAGE  "virgin goddess of justice, purity, and precision"
#define     P_IMAGERY   "elegant with shinning wings, angel light, and flamming torch"
#define     P_REASON    "greek goddess of precision keeps my strings safe"

#define     P_ONELINE   P_NAMESAKE " " P_SUBJECT

#define     P_BASENAME  "libySTR.so"
#define     P_FULLPATH  "/usr/local/lib64/libySTR.so"
#define     P_SUFFIX    "n/a"
#define     P_CONTENT   "n/a"

#define     P_SYSTEM    "gnu/linux   (powerful, ubiquitous, technical, and hackable)"
#define     P_LANGUAGE  "ansi-c      (wicked, limitless, universal, and everlasting)"
#define     P_CODESIZE  "small       (appoximately 1,000 slocl)"

#define     P_AUTHOR    "heatherlyrobert"
#define     P_CREATED   "2013-09"
#define     P_DEPENDS   "yLOG,yURG"

#define     P_VERMAJOR  "1.--, production"
#define     P_VERMINOR  "1.1-, use everywhere and make improvements"
#define     P_VERNUM    "1.1n"
#define     P_VERTXT    "small updates including to ySTR_solo.h"

#define     P_PRIORITY  "direct, simple, brief, vigorous, and lucid (h.w. fowler)"
#define     P_PRINCIPAL "[grow a set] and build your wings on the way down (r. bradbury)"
#define     P_REMINDER  "there are many better options, but i *own* every byte of this one"



/*345678901-12345678901-123456789-123456789-123456789-123456789-123456789-123456789-123456789-*/
#define      _XOPEN_SOURCE
#include    <stdio.h>
#include    <stdlib.h>                  /* getenv()                            */
#include    <string.h>
#include    <unistd.h>
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
   char        strtest     [LEN_RECD];
   int         argc;
   char       *argv        [20];
};
extern  tLOCAL mySTR;

#define     FONT_FULL      'f'       /* [a-z][0-9] */
#define     FONT_ALPHA     'a'       /* [a-z]      */
#define     FONT_NUMS      'n'       /* [0-9]      */
#define     FONT_BINARY    'b'       /* [0-1]      */
#define     FONT_MAYANC    'm'       /* [0-1]      */


extern char   unit_answer [LEN_RECD];


char        ySTR_testquiet     (void);
char        ySTR_testloud      (void);
char        ySTR_testend       (void);
char*       ySTR_unit          (char *a_question, int a_num);

/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        ystr__prefix            (cchar *a_str, char *a_out);
char        ystr__suffix            (cchar *a_str, char *a_out);
char        strl__home              (char *a_home);
char        strl__name              (char *a_home, char *a_name);

char        ystr__gyges2tab         (char *a_src, char *a_pos, int *a_val, char *a_abs, char a_def);
char        ystr__gyges2col         (char *a_src, char *a_pos, int *a_val, char *a_abs);
char        ystr__gyges2row         (char *a_src, char *a_pos, int *a_val, char *a_abs);
char        ystr_gyges__check       (int a_tab, int a_col, int a_row, int a_abs);
char        ystr_gyges__legal       (int a_tab, int a_col, int a_row, char a_check);

char        ystr_gyges__unit_check  (int b, int x, int y, char z, char a_check);

char        ystr__getlang           (char *a_iso);

char        ystr_font__index        (char a_range, int a_letter);
char*       FONT__unit              (char *a_question, int a_num);

#endif
