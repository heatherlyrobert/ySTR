/*===[[ HEADER GUARD ]]=======================================================*/
#ifndef YSTR_priv_hguard
#define YSTR_priv_hguard loaded



#define      _XOPEN_SOURCE
#include    <stdio.h>
#include    <stdlib.h>                  /* getenv()                            */
#include    <string.h>

#include    <yLOG.h>                    /* heatherly program logger            */
#include    "ySTR.h"




/* rapidly evolving version number to aid with visual change confirmation     */
#define YSTR_VER_NUM   "0.2f"
#define YSTR_VER_TXT   "moved to make_program makefile enhancement"




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
char*       ySTR_unit          (char *a_question, int a_num);



#endif
