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
#define YSTR_VER_NUM   "0.2w"
#define YSTR_VER_TXT   "added a few more character constants"



/*---(character constants)------------*/
#define   G_CHAR_PLACE      164   /* ¤  placeholder      (  -)   */
#define   G_CHAR_GROUP      166   /* ¦  group separator  ( 29)   */
#define   G_CHAR_FIELD      167   /* §  field separator  ( 31)   */
#define   G_CHAR_BS         171   /* «  backspace        (127)   */
#define   G_CHAR_ENTER      182   /* ¶  return/newline   ( 10)   */
#define   G_CHAR_TAB        187   /* »  tab              (  9)   */
#define   G_CHAR_MARK       215   /* ×  mark             (  -)   */
#define   G_CHAR_NULL       216   /* Ø  null             (  0)   */
#define   G_CHAR_ESC        234   /* ê  escape           ( 27)   */
#define   G_CHAR_SPACE      223   /* ß  space            ( 32)   */
#define   G_CHAR_LQUEST     191   /* ¿  lead question    (  -)   */
#define   G_CHAR_DEGREE     176   /* °  degree mark      (  -)   */
#define   G_CHAR_FUNKY      186   /* º  funky mark       (  -)   */
#define   G_CHAR_STAFF      165   /* ¥  staff            (  -)   */


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
