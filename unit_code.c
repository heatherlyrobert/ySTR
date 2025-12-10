/*===[[ START ]]==============================================================*/
#include    "ySTR.h"
#include    "ySTR_priv.h"



char       /*----: set up program urgents/debugging --------------------------*/
ySTR_unit_quiet         (void)
{
   ySTR_debug ('-');
   return 0;
}

char       /*----: set up program urgents/debugging --------------------------*/
ySTR_unit_loud          (void)
{
   ySTR_debug ('y');
   mySTR.logger = yLOGS_begin ("ySTR" , YLOG_SYS, YLOG_NOISE);
   yURG_by_name  ("kitchen"      , YURG_ON);
   yURG_by_name  ("ystr"         , YURG_ON);
   DEBUG_YSTR   yLOG_info     ("ySTR"    , ySTR_version   ());
   return 0;
}

char       /*----: stop logging ----------------------------------------------*/
ySTR_unit_end           (void)
{
   DEBUG_YSTR  yLOGS_end     ();
   return 0;
}

