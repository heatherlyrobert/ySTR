/*===[[ START ]]==============================================================*/
#include    "ySTR.h"
#include    "ySTR_priv.h"

/*
 *  universal support for common validation of fields read
 *  from input sources, including yPARSE, which include
 *  standard error messages if yURG_msg and yURG_err are on.
 *
 */


char
ystr_audit_record       (int a_len, char a_recd [LEN_RECD])
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   int         l           =    0;
   /*---(header)-------------------------*/
   DEBUG_CONF  yLOG_senter  (__FUNCTION__);
   DEBUG_CONF  yLOG_sint    (a_len);
   /*---(check null)---------------------*/
   --rce;  if (a_recd == NULL) {
      yURG_err ('f', "strict tests > record is null");
      DEBUG_CONF  yLOG_snote   ("null/empty");
      DEBUG_CONF  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(check empty)--------------------*/
   --rce;  if (a_recd [0] == '\0') {
      yURG_err ('f', "strict tests > record is empty");
      DEBUG_CONF  yLOG_snote   ("null/empty");
      DEBUG_CONF  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(check length)-------------------*/
   l = strlen (a_recd);
   DEBUG_CONF  yLOG_sint    (l);
   yURG_msg ('-', "%då%sæ", l, a_recd);
   --rce;  if (l != a_len) {
      yURG_err ('f', "strict tests > record length is expected at %d characters, not %d", a_len, l);
      DEBUG_CONF  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_CONF  yLOG_sexit   (__FUNCTION__);
   return 1;
}

char
ystr_audit_column       (char n, char a_field [LEN_LABEL], int a_pos, char a_recd [LEN_RECD])
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        x_field     [LEN_LABEL] = "";
   char        x_ch        =  '-';
   /*---(header)-------------------------*/
   DEBUG_CONF  yLOG_senter  (__FUNCTION__);
   DEBUG_CONF  yLOG_sint    (n);
   /*---(check field)--------------------*/
   if      (a_field     == NULL)  strcpy   (x_field, "(null)");
   else if (a_field [0] == '\0')  strcpy   (x_field, "(empty)");
   else                           ystrlcpy (x_field, a_field, LEN_LABEL);
   DEBUG_CONF  yLOG_spoint  (x_field);
   /*---(check spacing)------------------*/
   DEBUG_CONF  yLOG_sint    (a_pos);
   x_ch = a_recd [a_pos];
   DEBUG_CONF  yLOG_schar   (x_ch);
   --rce;  if (x_ch != '§' && x_ch != '') {
      yURG_err ('f', "strict tests > (%d) field å%sæ start, delimiter not at %d", n, x_field, a_pos);
      DEBUG_CONF  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_CONF  yLOG_sexit   (__FUNCTION__);
   return 1;
}

char
ystr_audit_string       (char n, char a_field [LEN_LABEL], char *a_string, char *a_charset, int a_min, int a_max)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         l           =    0;
   char        x_update    [LEN_RECD]  = "";
   char        x_field     [LEN_LABEL] = "";
   /*---(header)-------------------------*/
   DEBUG_CONF  yLOG_senter  (__FUNCTION__);
   DEBUG_CONF  yLOG_sint    (n);
   /*---(check field)--------------------*/
   if      (a_field     == NULL)  strcpy   (x_field, "(null)");
   else if (a_field [0] == '\0')  strcpy   (x_field, "(empty)");
   else                           ystrlcpy (x_field, a_field, LEN_LABEL);
   DEBUG_CONF  yLOG_spoint  (x_field);
   /*---(check string)-------------------*/
   --rce;  if (a_string == NULL) {
      yURG_err ('f', "field tests > (%d) field å%sæ content is null", n, x_field);
      DEBUG_CONF  yLOG_snote   ("null/empty");
      DEBUG_CONF  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_string [0] == '\0') {
      yURG_err ('f', "field tests > (%d) field å%sæ content is empty", n, x_field);
      DEBUG_CONF  yLOG_snote   ("null/empty");
      DEBUG_CONF  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(check charset)------------------*/
   --rce;  if (a_charset == NULL) {
      yURG_err ('f', "field tests > (%d) field å%sæ charset is null", n, x_field);
      DEBUG_CONF  yLOG_snote   ("null/empty");
      DEBUG_CONF  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_charset [0] == '\0') {
      yURG_err ('f', "field tests > (%d) field å%sæ charset is empty", n, x_field);
      DEBUG_CONF  yLOG_snote   ("null/empty");
      DEBUG_CONF  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(check too short)----------------*/
   l = strlen (a_string);
   DEBUG_CONF  yLOG_sint    (l);
   DEBUG_CONF  yLOG_sint    (a_min);
   --rce;  if (l < a_min) {
      yURG_err ('f', "field tests > (%d) field å%sæ length is %då%sæ but must be >= %d", n, x_field, l, a_string, a_min);
      DEBUG_CONF  yLOG_snote   ("too short");
      DEBUG_CONF  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_CONF  yLOG_sint    (a_max);
   --rce;  if (l >= a_max) {
      yURG_err ('f', "field tests > (%d) field å%sæ length is %då%sæ but must be < %d", n, x_field, l, a_string, a_max);
      DEBUG_CONF  yLOG_snote   ("too long");
      DEBUG_CONF  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(check clean)--------------------*/
   ystrlcpy (x_update, a_string, a_max);
   rc = ystrlmark (x_update, a_charset, a_max);
   DEBUG_CONF  yLOG_sint    (rc);
   --rce;  if (rc != 0) {
      yURG_err ('f', "field tests > (%d) field å%sæ contains bad chars å%sæ marked as (°)", n, x_field, x_update);
      DEBUG_CONF  yLOG_snote   ("funky chars");
      DEBUG_CONF  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_CONF  yLOG_sexit   (__FUNCTION__);
   return 1;
}

char
ystr_audit_number       (char n, char a_field [LEN_LABEL], int a_value, int a_min, int a_max)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        x_field     [LEN_LABEL] = "";
   /*---(header)-------------------------*/
   DEBUG_CONF  yLOG_senter  (__FUNCTION__);
   DEBUG_CONF  yLOG_sint    (n);
   /*---(check field)--------------------*/
   if      (a_field     == NULL)  strcpy   (x_field, "(null)");
   else if (a_field [0] == '\0')  strcpy   (x_field, "(empty)");
   else                           ystrlcpy (x_field, a_field, LEN_LABEL);
   DEBUG_CONF  yLOG_spoint  (x_field);
   /*---(check range)--------------------*/
   --rce;  if (a_value < a_min) {
      yURG_err ('f', "field tests > (%d) field å%sæ value is (%d) but must be >= %d", n, x_field, a_value, a_min);
      DEBUG_CONF  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_value > a_max) {
      yURG_err ('f', "field tests > (%d) field å%sæ value is (%d) but must be <= %d", n, x_field, a_value, a_max);
      DEBUG_CONF  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_CONF  yLOG_sexit   (__FUNCTION__);
   return 1;
}

char
ystr_audit_char         (char n, char a_field [LEN_LABEL], char a_char, char *a_dataset)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        x_field     [LEN_LABEL] = "";
   char       *p           = NULL;
   /*---(header)-------------------------*/
   DEBUG_CONF  yLOG_senter  (__FUNCTION__);
   DEBUG_CONF  yLOG_sint    (n);
   /*---(check field)--------------------*/
   if      (a_field     == NULL)  strcpy   (x_field, "(null)");
   else if (a_field [0] == '\0')  strcpy   (x_field, "(empty)");
   else                           ystrlcpy (x_field, a_field, LEN_LABEL);
   DEBUG_CONF  yLOG_spoint  (x_field);
   /*---(check clean)--------------------*/
   --rce;  if (a_char  == 0) {
      yURG_err ('f', "field tests > (%d) field å%sæ is zero/null", n, x_field);
      DEBUG_CONF  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   p  = strchr (a_dataset, a_char);
   --rce;  if (p == NULL) {
      yURG_err ('f', "field tests > (%d) field å%sæ is (%c/%d) not in å%sæ", n, x_field, ychrvisible (a_char), a_char, a_dataset);
      DEBUG_CONF  yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_CONF  yLOG_sexit   (__FUNCTION__);
   return 1;
}


