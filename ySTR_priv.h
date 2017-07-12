/*===[[ HEADER GUARD ]]=======================================================*/
#ifndef YSTR_priv_hguard
#define YSTR_priv_hguard loaded



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
#define YSTR_VER_NUM   "0.2n"
#define YSTR_VER_TXT   "updated, cleaned, enhanced, and tested strl4bin"



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
extern  tLOCAL its;
#define     DEBUG_STRG     if (its.debug == 'y')


char        ySTR_testquiet     (void);
char        ySTR_testloud      (void);
char        ySTR_testend       (void);
char*       ySTR_unit          (char *a_question, int a_num);



#endif
