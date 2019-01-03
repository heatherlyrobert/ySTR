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
#define YSTR_VER_NUM   "0.5b"
#define YSTR_VER_TXT   "updated gyges functions to to bxyz format (vs old xyz). unit tests clean"


#define     LEN_HUGE        10000
#define     LEN_RECD         2000


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





char        ySTR_testquiet     (void);
char        ySTR_testloud      (void);
char        ySTR_testend       (void);
char*       ySTR_unit          (char *a_question, int a_num);


char        ystr__gyges2tab         (char *a_src, char *a_pos, int *a_val, char *a_abs, char a_def);
char        ystr__gyges2col         (char *a_src, char *a_pos, int *a_val, char *a_abs);
char        ystr__gyges2row         (char *a_src, char *a_pos, int *a_val, char *a_abs);
char        ystr_gyges__check       (int a_tab, int a_col, int a_row, int a_abs);
char        ystr_gyges__legal       (int a_tab, int a_col, int a_row, char a_check);

char        ystr_gyges__unit_check  (int a_tab, int a_col, int a_row, char a_check);


#endif
