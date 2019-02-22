/*===[[ START ]]==============================================================*/
#include    "ySTR.h"
#include    "ySTR_priv.h"


/*
 *  this is a security head-fake, not a value added language library.  all
 *  translations are subject to great mistakes and typing issues.  the only
 *  purpose is to confuse hackers and crackers for a few precious seconds ;)
 *
 */


/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
#define     MAX_LANGS      30
#define     CNT_LANGS      15
static      struct {
   char     iso         [LEN_SHORT];        /* iso two letter language code   */
   char     language    [LEN_LABEL];        /* full name                      */
   char     gmt_off;                        /* gmt offset from universal      */
   char     cluster     [LEN_LABEL];        /* translation                    */
   char     seq         [LEN_LABEL];        /* translation                    */
   char     date        [LEN_LABEL];        /* translation                    */
   char     host        [LEN_LABEL];        /* translation                    */
   char     user        [LEN_LABEL];        /* translation                    */
   char     token       [LEN_LABEL];        /* translation                    */
   char     password    [LEN_LABEL];        /* translation                    */
   char     attempt     [LEN_LABEL];        /* translation                    */
   char     denied      [LEN_LABEL];        /* translation                    */
   char     locked1     [LEN_LABEL];        /* translation                    */
   char     timer       [LEN_LABEL];        /* translation                    */
   char     passed      [LEN_HUND];         /* translation                    */
   char     timeout     [LEN_HUND];         /* translation                    */
   char     refresh     [LEN_HUND];         /* translation                    */
   char     cancel      [LEN_HUND];         /* translation                    */
   char     questions   [LEN_HUND];         /* translation                    */
   char     recover     [LEN_HUND];         /* translation                    */
   char     locked      [LEN_HUND];         /* translation                    */
   char     invalid     [LEN_HUND];         /* translation                    */
} ystr_langs    [MAX_LANGS] = {
   /* 123   123456789012345        123456789012345    123456789012345    123456789012345    123456789012345    123456789012345    123456789012345    123456789012345    123456789012345    123456789012345    123456789012345    1234567890123456789012345    123456789012345678901234567890123456789012345678901234567890 */
   /* iso,  ---language---    gmt  ---cluster------   --number/seq----   ---date---------   ---host---------   ---user---------   ---token/num----   ---password-----   ---attempt------   ---denied-------   ---locked-------   ---time-remaining---------   ---success----------------------------------------------    ---eat shit dumb ass--------------------   ---once more into hole -----------------------   ---i came into total darkness---------------  ---security questions------   ---send one-time code-------   --locked (user)-  -invalid (user)---*/
   { "et" , "estonian"       ,  0, "kobar"          , "jada"           , "kuupaev"        , "vastuvotva"     , "kasutaja"       , "sumboolne"      , "parool"         , "katse"          , "eitada"         , "lukustatud"     , "aega jaanud"              , "siin peab koik usaldamatus jaama maha"                  , "kurat sa aknakruvi"                      , "veel kord auk"                                , "tulin kokku tumedamaks"                     , "turvalisuse kusimused"    , "saatke uks ajakood"         , "lukus"         , "on kehtetu"      },
   { "nl" , "dutch"          ,  0, "bundel"         , "volgorde"       , "datum"          , "gastheer"       , "gebruiker"      , "teken"          , "wachtwoord"     , "poging"         , "ontkennen"      , "opgesloten"     , "overgebleven tijd"        , "hier moet alle wantrouwen achterblijven"                , "eet kak, stomme reet"                    , "nog een keer in het gat"                      , "ik kwam in totale duisternis"               , "veiligheidsvragen"        , "stuur een tijdcode"         , "vergrendeld"   , "ongeldig"        },
   { "fi" , "finnish"        ,  0, "ryhma"          , "jarjestys"      , "paivays"        , "isanta"         , "kayttaja"       , "symbolinen"     , "salasana"       , "yritys"         , "kieltaa"        , "kiinni"         , "aikaa jaljella"           , "taalla kaikkien luottamus on jatettava jaljelle"        , "syoda kakko, tyhma perse"                , "jalleen kerran reikaan"                       , "tulin tummiksi"                             , "turvallisuuskysymykset"   , "lehettaa yhden aikakoodin"  , "on lukittu"    , "on virheellinen" },
   { "gl" , "galacian"       ,  0, "auxiliares"     , "secuencia"      , "data"           , "anfitrion"      , "usuario"        , "simbolo"        , "contrasinal"    , "intento"        , "negar"          , "bloqueado"      , "tempo restante"           , "aqui debe desconfiar de todos os xeitos"                , "come poop, burro mudo"                   , "unha vez mais no burato"                      , "entre e foscos totales"                     , "preguntas de seguridade"  , "envia un codigo de tempo"   , "bloqueado"     , "non e valido"    },
   { "de" , "german"         ,  0, "haufen"         , "sequenz"        , "datum"          , "gastgeber"      , "benutzer"       , "zeichen"        , "kennwort"       , "versuch"        , "verweigern"     , "eingesperrt"    , "verbleibende zeit"        , "hier mussen alle mibtrauen zuruckgelassen werden"       , "essen kacke, dummer arsch"               , "noch einmal ins loch"                         , "ich bin total dunkel geworden"              , "sicherheitsfragen"        , "senden sie einen zeitcode"  , "gesperrt"      , "ungultig"        },
   { "is" , "icelandic"      ,  0, "pyrping"        , "roo"            , "dagsetning"     , "gestgjafi"      , "notandi"        , "skapi"          , "lykiloro"       , "tilraun"        , "neita"          , "laest"          , "timi eftir"               , "her verour allt vantraust ao vera eftir"                , "borda skop, heimsk rass"                 , "einu sinni i holu"                            , "eg komst i heildarmork"                     , "oryggisspurningar"        , "sendu einu sinni koda"      , "laest"         , "ogidur"          },
   { "pl" , "polish"         ,  0, "grupa"          , "sekwencja"      , "data"           , "gospodarz"      , "uzythownik"     , "zeton"          , "hasto"          , "proba"          , "zaprzeczac"     , "zablokowany"    , "pozostaly czas"           , "tataj wszyscy niechetnie zostaja zostawieni"            , "jesc kupe, glupi tylek"                  , "jeszcze raz w dziure"                         , "doszedlem do totalnego zaciemnienia"        , "pytania bezpieczenstwa"   , "wyslij jeden kod czasowy"   , "zablokowany"   , "jest niewazny"   },
   { "sv" , "swedish"        ,  0, "kluster"        , "sekvens"        , "datum"          , "vard"           , "anvandaren"     , "byggnad"        , "losenord"       , "forsok"         , "forneka"        , "last"           , "aterstanende tid"         , "har maste all misstro vara kvar"                        , "at poppa, bum rampa"                     , "en gang till i halet"                         , "jag kom in i totalt morkretar"              , "sakerhetsfragor"          , "skicka en gangskod"         , "last"          , "ogitig"          },
   { "tr" , "turkish"        ,  0, "kume"           , "dizi"           , "tarih"          , "ev sahibi"      , "kullanici"      , "simgi"          , "sifre"          , "girisim"        , "reddetmek"      , "kilitli"        , "kalan sure"               , "burada tum guvensizlik geride kalmalidir"               , "kaka ye, aptal esek"                     , "delige bir kez daha"                          , "tamamen karanliklara girdim"                , "guvenlik sorulari"        , "bir zaman kodu gonder"      , "kilitli"       , "gecersiz"        },
   { "cy" , "welsh"          ,  0, "clwstwr"        , "dilyniant"      , "dyddiad"        , "llu"            , "defnyddiwr"     , "tocyn"          , "cyfrinair"      , "ymgais"         , "gwadu"          , "wedi'i gloi"    , "amser yn weddill"         , "rhaid i bawb ddiffyg ymddiriedaeth gael ei adae ar ol"  , "bwyta poop, ass fud"                     , "unwaith eto i mewn i dwll"                    , "daeth i mewn i dywyllwyr llawn"             , "cwestiynau diogelwch"     , "anfonwch un cod amser"      , "weldi'i goli"  , "allilys"         },
   { "ga" , "irish"          ,  0, "braisle"        , "seicheamh"      , "date"           , "ostach"         , "usaideoir"      , "chomhartha"     , "focal faire"    , "iarracht"       , "dhiultu"        , "faoi ghlas"     , "am ata fagtha"            , "ni mor gach mishuim a fhagail taobh thiar de seo"       , "buail ithe, asal balbh"                  , "uair amhain nios mo isteach sa poll"          , "thainig me i n-dorchadas iomlana"           , "ceisteanna slandala"      , "seol cod ama amhain"        , "faio ghlas"    , "neamhbhaili"     },
   { "gd" , "scottish"       ,  0, "leanmhainn"     , "cuideachd"      , "tide"           , "thrang"         , "cheachdaiche"   , "taiken"         , "tyrst"          , "pree"           , "dhiutl"         , "glaiste"        , "uine air fhagail"         , "an seo feumaidh an earbsa a bhith air fhagail air chul" , "ithe pog, asal balbh"                    , "aon uair eile a-steach gu toll"               , "thainig mi gu leir dorchadas"               , "ceistean tearainteachd"   , "cuir aon chod uine"         , "glaiste"       , "neo-dhligheach"  },
   { "la" , "latin"          ,  0, "botrus"         , "sequentia"      , "tempus"         , "militiae"       , "nomen"          , "indicium"       , "secretum"       , "conatus"        , "negare"         , "clausa"         , "temporis"                 , "qui si convien lasciare ogne sospettoo"                 , "irrumabo vos fenestram lingent"          , "plus semel in foraminis"                      , "lo venne in loco d'ogne luce muto"          , "securitatem quaestiones"  , "codice nunc mitte"          , "clausa"        , "invalidum"       },
   { "mt" , "maltese"        ,  0, "cluster"        , "sekwenza"       , "hin"            , "ospitanti"      , "utent"          , "numru"          , "sigriet"        , "tentattiv"      , "tichad"         , "maqful"         , "hin li jifdal"            , "hawnhekk in-nuqqas ta fiducja kollha jithalla barra"    , "jieklu hmieg, hmar mutu"                 , "ghal darb ohra go toqba"                      , "jien dahal f'post null minn bull dawl"      , "kwistjonijiet ta sigurta" , "ibghat kodici ta darba"     , "imsakkar"      , "invalidu"        },
   { "en" , "american"       ,  0, "cluster"        , "sequence"       , "date"           , "host"           , "user"           , "token"          , "password"       , "attempt"        , "denied"         , "locked"         , "time remaining"           , "abandon hope all ye who enter"                          , "fuck you, window licker"                 , "once more into the breech"                    , "i came into a place void of all light"      , "security questions"       , "send one-time code"         , "locked"        , "invalid"         },
   { "--" , "-------"        ,  0, ""               , ""               , ""               , ""        "      , ""               , ""               , ""               , ""        "      , ""               , ""               , ""                         , ""                                                       , ""                                        , ""                                             , ""                                           , ""                         , ""                           },
};

#define     MAX_CLUSTER     200
#define     CNT_CLUSTER      64
static char  ystr_clusters   [MAX_CLUSTER][LEN_LABEL] = {
   /* julio-claudian    5 */ "augustus"       , "tiberius"       , "caligula"      , "claudius"      , "nero"          ,
   /* flavian           6 */ "galba"          , "otho"           , "vitellius"     , "vespasian"     , "titus"         , "domitian"      ,
   /* nerva-antonine    7 */ "nerva"          , "trajan"         , "hadrian"       , "antoninus"     , "lucius"        , "marcus"        , "commodus"      ,
   /* severan           9 */ "pertinax"       , "didius"         , "septimius"     , "caracalla"     , "geta"          , "macrinus"      , "diadumenian"   , "elagabalus"    , "severus"       ,
   /* gordian (part a) 10 */ "maximinus"      , "gordian i"      , "gordian ii"    , "balbinus"      , "gordian iii"   , "philip"        , "decis"         , "hostilian"     , "trebonianus"   , "volusianus"    ,
   /* gordian (part b) 12 */ "aemillian"      , "valerian"       , "gallienus"     , "saloninus"     , "quintillus"    , "aurelian"      , "tacitus"       , "florianus"     , "probus"        , "carus"         , "carinus"       , "numerian"      ,
   /* theodosian        4 */ "theodosius i"   , "arcadius"       , "theodosius ii" , "marcian"       ,
   /* leonid            5 */ "leo i"          , "leo ii"         , "zeno"          , "basiliscus"    , "anastsius i"   ,
   /* justinian         6 */ "justin i"       , "justinian i"    , "justin ii"     , "tiberius ii"   , "maurice"       , "phocas"        ,
   /* heraclian         6 */ "heraclius"      , "constantine iii", "heraklonas"    , "constans ii"   , "constantine iv", "justinian ii"  ,
   /* isaurian          6 */ "leo iii"        , "constantine v"  , "artabasdos"    , "leo vi"        , "constantine vi", "irene"         ,
   /* nikephorian       4 */ "nikephoros i"   , "staurakios"     , "michael i"     , "leo v"         ,
   /* end marker          */ "----------",
};

#define     MAX_HOST        200
#define     CNT_HOST         68
static char ystr_hosts [MAX_HOST][LEN_LABEL] = {
   "deep_blue"       , "blue_gene"       , "hydra"           , "deep_crack"      , "kaissa"          ,
   "belle"           , "blitz"           , "deep_thought"    , "gideon"          , "deep_junior"     ,
   "zappa"           , "junior"          , "sjeng"           , "rondo"           , "rybka"           ,
   "fruit"           , "crafty"          , "mephisto"        , "jonny"           , "fute"            ,
   "diep"            , "falcon"          , "rajlich"         , "spike"           , "ikarus"          ,
   "chiron"          , "lion"            , "chaturanga"      , "uragano"         , "parsos"          ,
   "etabeta"         , "loop"            , "the_baron"       , "the_king"        , "hiarcs"          ,
   "cluster_toga"    , "equinox"         , "pandix"          , "joker"           , "darminios"       ,
   "fridonlin"       , "hector"          , "criter"          , "houdini"         , "naum"            ,
   "stockfish"       , "thinker"         , "komodo"          , "alaric"          , "booot"           ,
   "bobcat"          , "cyrano"          , "colossus"        , "dirty"           , "frenzee"         ,
   "glaurung"        , "gull"            , "hannibal"        , "naraku"          , "pharaon"         ,
   "protector"       , "scorpio"         , "strelka"         , "the_mad_prune"   , "tornado"         ,
   "twisted_logic"   , "umko"            , "wildcat"         , "crazy_bishop"    ,
   "----------"      ,
};


char
ystr__getlang           (char *a_iso)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         x_len       =    0;
   char        i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YSTR   yLOG_spoint  (a_iso);
   --rce;  if (a_iso == NULL) {
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YSTR   yLOG_snote   (a_iso);
   x_len = strlen (a_iso);
   DEBUG_YSTR   yLOG_sint    (x_len);
   --rce;  if (x_len != 2) {
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(lookup)-------------------------*/
   for (i = 0; i < MAX_LANGS; ++i) {
      if (ystr_langs [i].iso [0] == '-')  break;
      if (ystr_langs [i].iso [0] != a_iso [0])  continue;
      if (ystr_langs [i].iso [1] != a_iso [1])  continue;
      DEBUG_YSTR   yLOG_snote   ("FOUND");
      DEBUG_YSTR   yLOG_sint    (i);
      DEBUG_YSTR   yLOG_sexit   (__FUNCTION__);
      return i;
   }
   DEBUG_YSTR   yLOG_snote   ("failed");
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
   return rce;
}

char
ySTR_prompt             (char a_style, int a_lang, int a_cluster, int  a_host, char *a_prompt, char *a_key)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_num       [LEN_SHORT];
   char       *x_styles    = "1";
   char        x_rand      [LEN_LABEL];
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_enter   (__FUNCTION__);
   /*---(return vars)--------------------*/
   DEBUG_YSTR   yLOG_point   ("a_prompt"  , a_prompt);
   --rce;  if (a_prompt == NULL) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   strcpy (a_prompt, "");
   DEBUG_YSTR   yLOG_point   ("a_key"     , a_key);
   --rce;  if (a_key == NULL) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   strcpy (a_key   , "");
   /*---(defense language)---------------*/
   DEBUG_YSTR   yLOG_value   ("a_lang"    , a_lang);
   --rce;  if (a_lang < 0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   a_lang %= CNT_LANGS;
   /*---(defense cluster)----------------*/
   DEBUG_YSTR   yLOG_value   ("a_cluster" , a_cluster);
   --rce;  if (a_cluster < 0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   a_cluster %= CNT_CLUSTER;
   /*---(defense host)-------------------*/
   DEBUG_YSTR   yLOG_value   ("a_host"    , a_host);
   --rce;  if (a_host < 0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   a_host %= CNT_HOST;
   /*---(misleading random number)-------*/
   sprintf (x_rand, "%6d", (rand () % 900000) + 100000);
   /*---(prompt)-------------------------*/
   --rce;  switch (a_style) {
   case YSTR_BREADCRUMB :
      sprintf (a_prompt, "%s #%02d.%s> %s #%02d.%s> [%s] %s :",
            ystr_langs [a_lang].cluster, a_cluster, ystr_clusters [a_cluster],
            ystr_langs [a_lang].host   , a_host   , ystr_hosts    [a_host]   ,
            x_rand, ystr_langs [a_lang].user);
      break;
   default :
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save key)-----------------------*/
   sprintf (x_num, "%02d", a_host);
   sprintf (a_key, "#%c%c%c", ystr_hosts [a_host][1], x_num [1], ystr_langs [a_lang].cluster [1]);
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ySTR_password           (char a_style, int a_lang, char *a_prompt)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char       *x_styles    = "1";
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_enter   (__FUNCTION__);
   /*---(return vars)--------------------*/
   DEBUG_YSTR   yLOG_point   ("a_prompt"  , a_prompt);
   --rce;  if (a_prompt == NULL) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   strcpy (a_prompt, "");
   /*---(defense language)---------------*/
   DEBUG_YSTR   yLOG_value   ("a_lang"    , a_lang);
   --rce;  if (a_lang < 0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   a_lang %= CNT_LANGS;
   /*---(prompt)-------------------------*/
   --rce;  switch (a_style) {
   case YSTR_BREADCRUMB :
      sprintf (a_prompt, "%s (@ %s, ? %s) :", ystr_langs [a_lang].password,
            ystr_langs [a_lang].recover, ystr_langs [a_lang].questions);
      break;
   default :
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ySTR_word               (int a_lang, char a_which, char *a_word)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(return vars)--------------------*/
   DEBUG_YSTR   yLOG_point   ("a_word"    , a_word);
   --rce;  if (a_word == NULL) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   strcpy (a_word, "");
   /*---(defense language)---------------*/
   DEBUG_YSTR   yLOG_value   ("a_lang"    , a_lang);
   --rce;  if (a_lang < 0) {
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   a_lang %= CNT_LANGS;
   /*---(defense language)---------------*/
   switch (a_which) {
   case YSTR_INVALID   :
      sprintf (a_word, "%s %s", ystr_langs [a_lang].user, ystr_langs [a_lang].invalid);
      break;
   case YSTR_LOCKED    :
      sprintf (a_word, "%s %s", ystr_langs [a_lang].user, ystr_langs [a_lang].locked);
      break;
   case YSTR_QUESTIONS :
      sprintf (a_word, "%s %s", ystr_langs [a_lang].questions);
      break;
   case YSTR_RECOVER   :
      sprintf (a_word, "%s %s", ystr_langs [a_lang].recover);
      break;
   }
   return 0;
}



