/*===[[ START ]]==============================================================*/
#include    "ySTR.h"
#include    "ySTR_priv.h"



tLOCAL    mySTR;





/*====================------------------------------------====================*/
/*===----                           utility                            ----===*/
/*====================------------------------------------====================*/
static void      o___UTILITY_________________o (void) {;}

char        ySTR_ver     [500];

char*      /* ---- : return library versioning information -------------------*/
ySTR_version       (void)
{
   char    t [20] = "";
#if    __TINYC__ > 0
   strlcpy (t, "[tcc built  ]", 15);
#elif  __GNUC__  > 0
   strlcpy (t, "[gnu gcc    ]", 15);
#elif  __HEPH__  > 0
   strncpy (t, "[hephaestus ]", 15);
#else
   strlcpy (t, "[unknown    ]", 15);
#endif
   snprintf (ySTR_ver, 100, "%s   %s : %s", t, P_VERNUM, P_VERTXT);
   return ySTR_ver;
}

char         /*--> set debugging mode --------------------[ ------ [ ------ ]-*/
ySTR_debug         (char a_flag)
{
   /*---(set debug flag)-----------------*/
   if   (a_flag == 'y')  mySTR.debug   = 'y';
   else                  mySTR.debug   = '-';
   /*---(complete)-----------------------*/
   return 0;
}

char
str9align            (char a_align)
{
   if (a_align  == ' ')                                               return -1;
   if (a_align  ==  0 )                                               return -2;
   if (strchr ("? <|> [^] {} :'", a_align) == NULL)                   return -3;
   return 0;
}

char
str9filler           (char a_filler)
{
   if (a_filler == ' ')                                               return -1;
   if (a_filler ==  0 )                                               return -2;
   if (strchr ("? !-=_ +.@~"    , a_filler) == 0)                     return -3;
   return 0;
}

char
str9format           (char a_format)
{
   if (a_format == ' ')                                                return -1;
   if (a_format ==  0 )                                                return -2;
   if (strchr ("? iIfF ,cCaAsS$#pP eE rR bBoOxXzZ tTdD", a_format) == 0) return -3;
   return 0;
}

char
str9decs             (int a_decs)
{
   if (a_decs < 0)  return -1;
   if (a_decs > 9)  return -2;
   return 0;
}



/*====================------------------------------------====================*/
/*===----                    unit testing accessor                     ----===*/
/*====================------------------------------------====================*/
static void      o___UNITTEST________________o (void) {;}

char          unit_answer [LEN_RECD];

char*            /* [------] unit test accessor ------------------------------*/
ySTR_unit          (char *a_question, int a_num)
{
   /*---(locals)-----------+-----+-----+-*/
   char        s           [LEN_LABEL];
   uchar       t           [LEN_RECD ];
   int         i           =    0;
   /*---(initialize)---------------------*/
   strlcpy (unit_answer, "ySTR_unit, unknown request", 100);
   /*---(string testing)-----------------*/
   if      (strncmp(a_question, "string"    , 20)  == 0) {
      snprintf (unit_answer, LEN_RECD, "ySTR string      : [%s]", mySTR.strtest);
   }
   else if (strncmp(a_question, "values"    , 20)  == 0) {
      strlcpy (t, "", LEN_RECD);
      for (i = 0; i < 10; ++i) {
         if (mySTR.strtest [i] == 0)  break;
         sprintf (s, "%03d", (uchar) mySTR.strtest [i]);
         if (i > 0)  strlcat (t, " ", LEN_RECD);
         strlcat (t, s  , LEN_RECD);
      }
      snprintf (unit_answer, LEN_RECD, "ySTR values      : %s", t);
   }
   else if (strncmp(a_question, "work"      , 20)  == 0) {
      snprintf (unit_answer, LEN_RECD, "ySTR work        : %2d[%s]", strlen (mySTR.strtest), mySTR.strtest);
   }
   /*---(argument testing)---------------*/
   else if (strncmp(a_question, "argc"      , 20)  == 0) {
      snprintf (unit_answer, LEN_RECD, "ySTR argc        : %d", mySTR.argc);
   }
   else if (strncmp(a_question, "argv"      , 20)  == 0) {
      if (a_num < 20 && a_num < mySTR.argc)  {
         snprintf (unit_answer, LEN_RECD, "ySTR argv (%2d)   : %3d [%-.40s]", a_num, strllen (mySTR.argv[a_num], 2000), mySTR.argv[a_num]);
      } else {
         snprintf (unit_answer, LEN_RECD, "ySTR argv (%2d)   : index out of range", a_num);
      }
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}

char       /*----: set up program urgents/debugging --------------------------*/
ySTR_testquiet     (void)
{
   ySTR_debug ('-');
   return 0;
}

char       /*----: set up program urgents/debugging --------------------------*/
ySTR_testloud      (void)
{
   ySTR_debug ('y');
   mySTR.logger = yLOGS_begin ("ySTR" , YLOG_SYS, YLOG_NOISE);
   yURG_by_name  ("kitchen"      , YURG_ON);
   yURG_by_name  ("ystr"         , YURG_ON);
   DEBUG_YSTR   yLOG_info     ("ySTR"    , ySTR_version   ());
   return 0;
}

char       /*----: stop logging ----------------------------------------------*/
ySTR_testend       (void)
{
   DEBUG_YSTR  yLOGS_end     ();
   return 0;
}



/*===[[ END ]]================================================================*/
