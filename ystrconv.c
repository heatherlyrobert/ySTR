#include    "ystrconv.h"



/*====================------------------------------------====================*/
/*===----                        debugging setup                       ----===*/
/*====================------------------------------------====================*/
static void      o___DEBUGGING__________o (void) {;}

char
PROG_debugging          (int a_argc, char *a_argv[])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG  yLOG_enter   (__FUNCTION__);
   /*---(initialize)---------------------*/
   rc = yURG_logger  (a_argc, a_argv);
   DEBUG_PROG  yLOG_value   ("logger"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }

   rc = yURG_urgs    (a_argc, a_argv);
   DEBUG_PROG  yLOG_value   ("urgs"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG    yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG  yLOG_exit  (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        program startup                       ----===*/
/*====================------------------------------------====================*/
static void      o___STARTUP____________o (void) {;}

char
PROG__init              (int a_argc, char *a_argv[])
{
   /*---(locals)-----------+-----+-----+-*/
   /*---(header)-------------------------*/
   DEBUG_PROG  yLOG_enter   (__FUNCTION__);
   /*---(complete)-----------------------*/
   DEBUG_PROG  yLOG_exit  (__FUNCTION__);
   return 0;
}

char
PROG__args              (int a_argc, char *a_argv[])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           = 0;
   char       *a           = NULL;
   char       *b           = NULL;          /* next argument                  */
   /*---(header)-------------------------*/
   DEBUG_PROG  yLOG_enter   (__FUNCTION__);
   /*---(process)------------------------*/
   DEBUG_PROG  yLOG_value   ("a_argc"    , a_argc);
   for (i = 1; i < a_argc; ++i) {
      /*---(prepare)---------------------*/
      a = a_argv [i];
      DEBUG_ARGS  yLOG_complex ("arg"    , "%d %-20.20s", i, a);
      /*---(filter urgents)--------------*/
      if (a [0] == '@') {
         DEBUG_PROG   yLOG_note    ("filtering urgent out");
         continue;
      }
      /*---(simple)----------------------*/
      /*> if      (strcmp  (a, "--version"      ) == 0)  PROG_vershow ();             <* 
       *> else if (strcmp  (a, "--quick"        ) == 0)  PROG_usage   ();             <* 
       *> else if (strcmp  (a, "--help"         ) == 0)  PROG_usage   ();             <* 
       *> else if (strcmp  (a, "--loud"         ) == 0)  yURG_all_tmplive ();         <* 
       *> /+---(trouble)---------------------+/                                       <* 
       *> else {                                                                      <* 
       *>    DEBUG_PROG  yLOG_note  ("argument not understood");                      <* 
       *>    DEBUG_PROG  yLOG_exitr (__FUNCTION__, -3);                               <* 
       *>    return -3;                                                               <* 
       *> }                                                                           <*/
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG  yLOG_exit  (__FUNCTION__);
   return 0;
}

char
PROG__begin             (void)
{
   /*---(locals)-----------+-----+-----+-*/
   /*---(header)-------------------------*/
   DEBUG_PROG  yLOG_enter   (__FUNCTION__);
   /*---(complete)-----------------------*/
   DEBUG_PROG  yLOG_exit  (__FUNCTION__);
   return 0;
}

char
PROG_startup            (int a_argc, char *a_argv[])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   yURG_stage_check (YURG_BEG);
   DEBUG_PROG  yLOG_enter   (__FUNCTION__);
   /*---(initialize)---------------------*/
   if (rc >= 0) {
      rc = PROG__init    (a_argc, a_argv);
      DEBUG_PROG  yLOG_value   ("init"      , rc);
   }
   /*---(arguments)----------------------*/
   if (rc >= 0) {
      rc = PROG__args    (a_argc, a_argv);
      DEBUG_PROG  yLOG_value   ("args"      , rc);
   }
   /*---(begin)--------------------------*/
   if (rc >= 0) {
      rc = PROG__begin   ();
      DEBUG_PROG  yLOG_value   ("args"      , rc);
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG  yLOG_exit  (__FUNCTION__);
   yURG_stage_check (YURG_MID);
   return rc;
}



/*====================------------------------------------====================*/
/*===----                        program shutdown                      ----===*/
/*====================------------------------------------====================*/
static void      o___SHUTDOWN___________o (void) {;}

char
PROG__end               (void)
{
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(wrap-up)------------------------*/
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   DEBUG_PROG   yLOGS_end    ();
   return 0;
}

char         /*-> shutdown program and free memory ---[ ------ [gz.422.001.03]*/ /*-[00.0000.111.!]-*/ /*-[--.---.---.--]-*/
PROG_shutdown          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   yURG_stage_check (YURG_END);
   /*---(complete)-----------------------*/
   return PROG__end ();
}



/*====================------------------------------------====================*/
/*===----                          main driver                         ----===*/
/*====================------------------------------------====================*/
static void      o___MAIN_______________o (void) {;}

char
main                    (int a_argc, char *a_argv[])
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =   -1;
   char        x_input     [LEN_HUND]  = "";
   ullong      x_ullong    =    0;
   char        x_sbin      [LEN_HUND]  = "";
   char        x_soct      [LEN_HUND]  = "";
   char        x_shex      [LEN_HUND]  = "";
   char        x_smgo      [LEN_HUND]  = "";
   ullong      x_vbin, x_voct, x_vhex, x_vmgo;
   char        x_good      =  '°';
   char       *p           = NULL;
   /*---(initialize)---------------------*/
   rc = PROG_debugging (a_argc, a_argv);
   DEBUG_PROG    yLOG_value   ("urgents"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = PROG_startup   (a_argc, a_argv);
   DEBUG_PROG    yLOG_value   ("startup"   , rc);
   --rce;  if (rc < 0) {
      rc = PROG_shutdown ();
      DEBUG_PROG    yLOG_value   ("shutdown"  , rc);
      DEBUG_PROG  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(dispatch)-----------------------*/
   DEBUG_PROG   yLOG_value   ("a_argc"    , a_argc);
   --rce;  if (a_argc  < 2) {
      printf ("requires argument\n");
      DEBUG_PROG  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(process input)------------------*/
   strlcpy (x_input, a_argv [1], LEN_HUND);
   DEBUG_PROG    yLOG_info    ("x_input"   , x_input);
   printf ("x_input  %s\n", x_input);
   switch (x_input [0]) {
   case 'b' :  case 'é' :  rc = ystr2bin   (x_input, &x_ullong, NULL);  break;
   case 'o' :  case 'ö' :  rc = ystr2oct   (x_input, &x_ullong, NULL);  break;
   case 'x' :  case 'õ' :  rc = ystr2hex   (x_input, &x_ullong, NULL);  break;
   case 'z' :  case 'ÿ' :  rc = ystr2mongo (x_input, &x_ullong, NULL);  break;
   default  :  x_ullong = (ullong) strtoull (x_input, &p, 10);  break;
   }
   DEBUG_PROG    yLOG_value   ("convert"   , rc);
   printf ("x_ullong %llu\n", x_ullong);
   --rce;  if (rc < 0) {
      DEBUG_PROG  yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = ystrl4bin   (x_ullong, 0.0, 0, 'g', LEN_HUND , x_sbin);
   rc = ystr2bin    (x_sbin  , &x_vbin, NULL);
   if (x_vbin == x_ullong)  x_good = 'y'; else x_good = '°';
   printf ("%-100.100s  %c  %llu\n", x_sbin, x_good, x_vbin);
   rc = ystrl4oct   (x_ullong, 0.0, 0, 'g', LEN_DESC , x_soct);
   rc = ystr2oct    (x_soct  , &x_voct, NULL);
   if (x_voct == x_ullong)  x_good = 'y'; else x_good = '°';
   printf ("%-100.100s  %c  %llu\n", x_soct, x_good, x_voct);
   rc = ystrl4hex   (x_ullong, 0.0, 0, 'g', LEN_TITLE, x_shex);
   rc = ystr2hex    (x_shex  , &x_vhex, NULL);
   if (x_vhex == x_ullong)  x_good = 'y'; else x_good = '°';
   printf ("%-100.100s  %c  %llu\n", x_shex, x_good, x_vhex);
   rc = ystrl4mongo (x_ullong, 0.0, 0, 'g', LEN_TITLE, x_smgo);
   rc = ystr2mongo  (x_smgo  , &x_vmgo, NULL);
   if (x_vmgo == x_ullong)  x_good = 'y'; else x_good = '°';
   printf ("%-100.100s  %c  %llu\n", x_smgo, x_good, x_vmgo);
   /*---(wrap-up)------------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   rc = PROG_shutdown ();
   DEBUG_PROG    yLOG_value   ("shutdown"  , rc);
   /*---(complete)-----------------------*/
   return 0;
}

