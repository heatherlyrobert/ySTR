/*===[[ START ]]==============================================================*/
#include    "ySTR.h"
#include    "ySTR_priv.h"


/*
 *  this is a security head-fake, not a value added language library.  all
 *  translations are subject to great mistakes and typing issues.  the only
 *  purpose is to confuse hackers and crackers for a few precious seconds ;)
 *
 */
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
   char     passed      [LEN_HUND];         /* distrust left behind           */
   char     failed      [LEN_HUND];         /* abandon hope (enter tarpit)    */
   char     timeout     [LEN_HUND];         /* eat poop, dumb ass             */
   char     refresh     [LEN_HUND];         /* translation                    */
   char     cancel      [LEN_HUND];         /* translation                    */
   char     questions   [LEN_HUND];         /* translation                    */
   char     recover     [LEN_HUND];         /* translation                    */
   char     locked      [LEN_HUND];         /* translation                    */
   char     invalid     [LEN_HUND];         /* translation                    */
} const ystr_langs    [MAX_LANGS] = {
   /* 123   123456789012345        123456789012345    123456789012345    123456789012345    123456789012345    123456789012345    123456789012345    123456789012345    123456789012345    123456789012345    123456789012345    12345678901234567890    123456789012345678901234567890123456789012345678901234567890 */
   /* iso,  ---language---    gmt  ---cluster------   --number/seq----   ---date---------   ---host---------   ---user---------   ---token/num----   ---password-----   ---attempt------   ---denied-------   ---locked-------   ---time-remaining----   ---success----------------------------------------------    ---failed and enter a tarpit---------------------------------    ---eat shit dumb ass--------------------   ---once more into hole -----------------------   ---i came into total darkness---------------  ---security questions------   ---send one-time code-------   --locked (user)-  -invalid (user)---*/
   { "et" , "estonian"       ,  0, "kobar"          , "jada"           , "kuupaev"        , "vastuvotva"     , "kasutaja"       , "sumboolne"      , "parool"         , "katse"          , "eitada"         , "lukustatud"     , "aega jaanud"         , "siin peab koik usaldamatus jaama maha"                  , "loobu lootust koigile kes te siia sisnete"                    , "kurat sa aknakruvi"                      , "veel kord auk"                                , "tulin kokku tumedamaks"                     , "turvalisuse kusimused"    , "saatke uks ajakood"         , "lukus"         , "on kehtetu"      },
   { "nl" , "dutch"          ,  0, "bundel"         , "volgorde"       , "datum"          , "gastheer"       , "gebruiker"      , "teken"          , "wachtwoord"     , "poging"         , "ontkennen"      , "opgesloten"     , "overgebleven tijd"   , "hier moet alle wantrouwen achterblijven"                , "verlatt hoop allen die hier binnenkomen"                      , "eet kak, stomme reet"                    , "nog een keer in het gat"                      , "ik kwam in totale duisternis"               , "veiligheidsvragen"        , "stuur een tijdcode"         , "vergrendeld"   , "ongeldig"        },
   { "fi" , "finnish"        ,  0, "ryhma"          , "jarjestys"      , "paivays"        , "isanta"         , "kayttaja"       , "symbolinen"     , "salasana"       , "yritys"         , "kieltaa"        , "kiinni"         , "aikaa jaljella"      , "taalla kaikkien luottamus on jatettava jaljelle"        , "hylkaa toivoa kaikkia teita kotka tulette tanne"              , "syoda kakko, tyhma perse"                , "jalleen kerran reikaan"                       , "tulin tummiksi"                             , "turvallisuuskysymykset"   , "lehettaa yhden aikakoodin"  , "on lukittu"    , "on virheellinen" },
   { "gl" , "galacian"       ,  0, "auxiliares"     , "secuencia"      , "data"           , "anfitrion"      , "usuario"        , "simbolo"        , "contrasinal"    , "intento"        , "negar"          , "bloqueado"      , "tempo restante"      , "aqui debe desconfiar de todos os xeitos"                , "abandonar a esperanza a todos os que entre aqui"              , "come poop, burro mudo"                   , "unha vez mais no burato"                      , "entre e foscos totales"                     , "preguntas de seguridade"  , "envia un codigo de tempo"   , "bloqueado"     , "non e valido"    },
   { "de" , "german"         ,  0, "haufen"         , "sequenz"        , "datum"          , "gastgeber"      , "benutzer"       , "zeichen"        , "kennwort"       , "versuch"        , "verweigern"     , "eingesperrt"    , "verbleibende zeit"   , "hier mussen alle mibtrauen zuruckgelassen werden"       , "hoffen sie alle, die heir eintreten"                          , "essen kacke, dummer arsch"               , "noch einmal ins loch"                         , "ich bin total dunkel geworden"              , "sicherheitsfragen"        , "senden sie einen zeitcode"  , "gesperrt"      , "ungultig"        },
   { "is" , "icelandic"      ,  0, "pyrping"        , "roo"            , "dagsetning"     , "gestgjafi"      , "notandi"        , "skapi"          , "lykiloro"       , "tilraun"        , "neita"          , "laest"          , "timi eftir"          , "her verour allt vantraust ao vera eftir"                , "yfirgefio vona allir sem koma inn her"                        , "borda skop, heimsk rass"                 , "einu sinni i holu"                            , "eg komst i heildarmork"                     , "oryggisspurningar"        , "sendu einu sinni koda"      , "laest"         , "ogidur"          },
   { "pl" , "polish"         ,  0, "grupa"          , "sekwencja"      , "data"           , "gospodarz"      , "uzythownik"     , "zeton"          , "hasto"          , "proba"          , "zaprzeczac"     , "zablokowany"    , "pozostaly czas"      , "tataj wszyscy niechetnie zostaja zostawieni"            , "porzuccie nadzieji wszyscy ktorzy tu wejdacie"                , "jesc kupe, glupi tylek"                  , "jeszcze raz w dziure"                         , "doszedlem do totalnego zaciemnienia"        , "pytania bezpieczenstwa"   , "wyslij jeden kod czasowy"   , "zablokowany"   , "jest niewazny"   },
   { "sv" , "swedish"        ,  0, "kluster"        , "sekvens"        , "datum"          , "vard"           , "anvandaren"     , "byggnad"        , "losenord"       , "forsok"         , "forneka"        , "last"           , "aterstanende tid"    , "har maste all misstro vara kvar"                        , "forlat hoppas alla ni som kommer in har"                      , "at poppa, bum rampa"                     , "en gang till i halet"                         , "jag kom in i totalt morkretar"              , "sakerhetsfragor"          , "skicka en gangskod"         , "last"          , "ogitig"          },
   { "tr" , "turkish"        ,  0, "kume"           , "dizi"           , "tarih"          , "ev sahibi"      , "kullanici"      , "simgi"          , "sifre"          , "girisim"        , "reddetmek"      , "kilitli"        , "kalan sure"          , "burada tum guvensizlik geride kalmalidir"               , "buraya giren herkesin umudunu birak"                          , "kaka ye, aptal esek"                     , "delige bir kez daha"                          , "tamamen karanliklara girdim"                , "guvenlik sorulari"        , "bir zaman kodu gonder"      , "kilitli"       , "gecersiz"        },
   { "cy" , "welsh"          ,  0, "clwstwr"        , "dilyniant"      , "dyddiad"        , "llu"            , "defnyddiwr"     , "tocyn"          , "cyfrinair"      , "ymgais"         , "gwadu"          , "wedi'i gloi"    , "amser yn weddill"    , "rhaid i bawb ddiffyg ymddiriedaeth gael ei adae ar ol"  , "gwahardd gobeithio pawb yr ydych yn mynd yma"                 , "bwyta poop, ass fud"                     , "unwaith eto i mewn i dwll"                    , "daeth i mewn i dywyllwyr llawn"             , "cwestiynau diogelwch"     , "anfonwch un cod amser"      , "weldi'i goli"  , "allilys"         },
   { "ga" , "irish"          ,  0, "braisle"        , "seicheamh"      , "date"           , "ostach"         , "usaideoir"      , "chomhartha"     , "focal faire"    , "iarracht"       , "dhiultu"        , "faoi ghlas"     , "am ata fagtha"       , "ni mor gach mishuim a fhagail taobh thiar de seo"       , "deireadh dochais go heir sibh siud a theann isteach anseo"    , "buail ithe, asal balbh"                  , "uair amhain nios mo isteach sa poll"          , "thainig me i n-dorchadas iomlana"           , "ceisteanna slandala"      , "seol cod ama amhain"        , "faio ghlas"    , "neamhbhaili"     },
   { "gd" , "scottish"       ,  0, "leanmhainn"     , "cuideachd"      , "tide"           , "thrang"         , "cheachdaiche"   , "taiken"         , "tyrst"          , "pree"           , "dhiutl"         , "glaiste"        , "uine air fhagail"    , "an seo feumaidh an earbsa a bhith air fhagail air chul" , "leig as a dh'fhuireach a huile duine a thig asteach an seo"   , "ithe pog, asal balbh"                    , "aon uair eile a-steach gu toll"               , "thainig mi gu leir dorchadas"               , "ceistean tearainteachd"   , "cuir aon chod uine"         , "glaiste"       , "neo-dhligheach"  },
   { "la" , "latin"          ,  0, "botrus"         , "sequentia"      , "tempus"         , "militiae"       , "nomen"          , "indicium"       , "secretum"       , "conatus"        , "negare"         , "clausa"         , "temporis"            , "qui si convien lasciare ogne sospettoo"                 , "hic omnes qui ingrediuntur desperantibus"                     , "irrumabo vos fenestram lingent"          , "plus semel in foraminis"                      , "lo venne in loco d'ogne luce muto"          , "securitatem quaestiones"  , "codice nunc mitte"          , "clausa"        , "invalidum"       },
   { "mt" , "maltese"        ,  0, "cluster"        , "sekwenza"       , "hin"            , "ospitanti"      , "utent"          , "numru"          , "sigriet"        , "tentattiv"      , "tichad"         , "maqful"         , "hin li jifdal"       , "hawnhekk in-nuqqas ta fiducja kollha jithalla barra"    , "abandon tama lil dawk kollha li jidhlu hawn"                  , "jieklu hmieg, hmar mutu"                 , "ghal darb ohra go toqba"                      , "jien dahal f'post null minn bull dawl"      , "kwistjonijiet ta sigurta" , "ibghat kodici ta darba"     , "imsakkar"      , "invalidu"        },
   { "en" , "american"       ,  0, "cluster"        , "sequence"       , "date"           , "host"           , "user"           , "token"          , "password"       , "attempt"        , "denied"         , "locked"         , "time remaining"      , "here must all distrust be left behind"                  , "abandon hope all ye who enter here"                           , "fuck you, window licker"                 , "once more into the breech"                    , "i came into a place void of all light"      , "security questions"       , "send one-time code"         , "locked"        , "invalid"         },
   { "--" , "-------"        ,  0, ""               , ""               , ""               , ""        "      , ""               , ""               , ""               , ""        "      , ""               , ""               , ""                    , ""                                                       , ""                                                             , ""                                        , ""                                             , ""                                           , ""                         , ""                           },
};

#define     MAX_CLUSTER     200
#define     CNT_CLUSTER      64
static const char  ystr_clusters   [MAX_CLUSTER][LEN_LABEL] = {
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
static const char ystr_hosts [MAX_HOST][LEN_LABEL] = {
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

static char *s_dark = "\033[0;30m";
static char *s_ligh = "\033[1;30m";

static char *s_bloo = "\033[0;31m";
static char *s_redd = "\033[1;31m";

static char *s_fore = "\033[0;32m";
static char *s_lawn = "\033[1;32m";

static char *s_gold = "\033[0;33m";
static char *s_yell = "\033[1;33m";

static char *s_navy = "\033[0;34m";
static char *s_teal = "\033[1;34m";

static char *s_indi = "\033[0;35m";
static char *s_mage = "\033[1;35m";

static char *s_sadd = "\033[0;36m";
static char *s_salm = "\033[1;34m";

static char *s_mint = "\033[0;31m";
static char *s_pale = "\033[1;31m";

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
ySTR_language           (void)
{
   return rand () % (CNT_LANGS - 1);
}

char
ySTR_host               (char l, char n, char *a_title, char *a_content)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YSTR   yLOG_sint    (l);
   --rce;  if (l < 0 || l >= CNT_LANGS) {
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(cluster)------------------------*/
   DEBUG_YSTR   yLOG_value   ("n"         , n);
   if (n < 0)  n = rand () % CNT_HOST;
   n %= CNT_HOST;
   DEBUG_YSTR   yLOG_value   ("n"         , n);
   /*---(return)-------------------------*/
   if (a_title   != NULL)  strlcpy (a_title  , ystr_langs [l].host   , LEN_LABEL);
   if (a_content != NULL)  strlcpy (a_content, ystr_hosts [n]        , LEN_LABEL);
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
   return n;
}

char
ySTR_cluster            (char l, char n, char *a_title, char *a_content)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YSTR   yLOG_sint    (l);
   --rce;  if (l < 0 || l >= CNT_LANGS) {
      DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(cluster)------------------------*/
   DEBUG_YSTR   yLOG_value   ("n"         , n);
   if (n < 0)  n = rand () % CNT_CLUSTER;
   n %= CNT_CLUSTER;
   DEBUG_YSTR   yLOG_value   ("n"         , n);
   /*---(return)-------------------------*/
   if (a_title   != NULL)  strlcpy (a_title  , ystr_langs [l].cluster, LEN_LABEL);
   if (a_content != NULL)  strlcpy (a_content, ystr_clusters [n]     , LEN_LABEL);
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_sexitr  (__FUNCTION__, rce);
   return n;
}

char
ySTR_prompt             (char a_style, char *a_prefix, int a_lang, int a_cluster, int  a_host, char *a_prompt, char *a_key)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_num       [LEN_SHORT];
   int         i           =    0;
   char        x_rand      [LEN_LABEL];
   char        t           [LEN_LABEL] = "";
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
   if (a_key != NULL)   strcpy (a_key   , "");
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
   for (i = 0; i < 6; ++i)  x_rand [i] = (rand () % 10) + '0';
   x_rand [ 2] = '-';
   x_rand [ 6] = '\0';
   /*---(prompt)-------------------------*/
   --rce;  switch (a_style) {
   case YSTR_BREADCRUMB :
      sprintf (a_prompt, "%s #%02d.%s> %s #%02d.%s> [%s] %s :",
            ystr_langs [a_lang].cluster, a_cluster, ystr_clusters [a_cluster],
            ystr_langs [a_lang].host   , a_host   , ystr_hosts    [a_host]   ,
            x_rand, ystr_langs [a_lang].user);
      break;
   case YSTR_BREADCOLOR :
      if (strlen (a_prefix) > 0)  sprintf (t, "%s[%s] ", s_bloo, a_prefix);
      sprintf (a_prompt, "%s%s %s#%02d.%s%s> %s %s#%02d.%s%s> [%s/%s%s%s] %s :",
            s_bloo, ystr_langs [a_lang].cluster,
            s_gold, a_cluster, ystr_clusters [a_cluster],
            s_bloo, ystr_langs [a_lang].host   ,
            s_gold, a_host   , ystr_hosts    [a_host]   ,
            s_bloo, x_rand,
            s_gold, a_prefix,
            s_bloo, ystr_langs [a_lang].user);
      break;
   default :
      DEBUG_YSTR   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save key)-----------------------*/
   sprintf (x_num, "%02d", a_host);
   if (a_key != NULL)   sprintf (a_key, "#%c%c%c", ystr_hosts [a_host][1], x_num [1], ystr_langs [a_lang].cluster [1]);
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
   case YSTR_BREADCOLOR :
      sprintf (a_prompt, "%s%s (%s@%s %s, %s?%s %s) :",
            s_bloo, ystr_langs [a_lang].password,
            s_gold, s_bloo, ystr_langs [a_lang].recover,
            s_gold, s_bloo, ystr_langs [a_lang].questions);
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
   case YSTR_USERNAME  :
      sprintf (a_word, "%s"   , ystr_langs [a_lang].user);
      break;
   case YSTR_TOKEN     :
      sprintf (a_word, "%s"   , ystr_langs [a_lang].token);
      break;
   case YSTR_PASSWORD  :
      sprintf (a_word, "%s"   , ystr_langs [a_lang].password);
      break;
   case YSTR_PASSED    :
      sprintf (a_word, "%s"   , ystr_langs [a_lang].passed);
      break;
   case YSTR_FAILURE   :
      sprintf (a_word, "%s"   , ystr_langs [a_lang].failed);
      break;
   case YSTR_TIMEOUT   :
      sprintf (a_word, "%s"   , ystr_langs [a_lang].timeout);
      break;
   case YSTR_REFRESH   :
      sprintf (a_word, "%s"   , ystr_langs [a_lang].refresh);
      break;
   case YSTR_CANCEL    :
      sprintf (a_word, "%s"   , ystr_langs [a_lang].cancel);
      break;
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

char
ySTR_prompt_box         (int a_lang, int a_cluster, int a_host, char *a_date, int x, int y)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   char        t           [LEN_DESC];
   char        x_rand      [LEN_DESC];
   /*---(header)-------------------------*/
   DEBUG_YSTR   yLOG_enter   (__FUNCTION__);
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
   for (i = 0; i < 20; ++i)  x_rand [i] = (rand () % 10) + '0';
   x_rand [20] = '\0';
   x_rand [ 3] = '-';
   x_rand [ 8] = '/';
   x_rand [14] = '-';
   /*---(build box)----------------------*/
   sprintf (t, "%-12.12s [%-20.20s]"         , ystr_langs [a_lang].cluster , ystr_clusters [a_cluster]);
   ystr_oneline (t, x, y++, YSTR_CLEAR);
   sprintf (t, "%-12.12s [%02d/%02d%-15.15s]", ystr_langs [a_lang].seq     , a_cluster, a_host, "");
   ystr_oneline (t, x, y++, YSTR_CLEAR);
   sprintf (t, "%-12.12s [%-20.20s]"         , ystr_langs [a_lang].host    , ystr_hosts [a_host]);
   ystr_oneline (t, x, y++, YSTR_CLEAR);
   sprintf (t, "%-12.12s [%-20.20s]"         , ystr_langs [a_lang].date    , a_date);
   ystr_oneline (t, x, y++, YSTR_CLEAR);
   sprintf (t, "%-12.12s [%-20.20s]"         , ystr_langs [a_lang].user    , " ");
   ystr_oneline (t, x, y++, YSTR_CLEAR);
   sprintf (t, "%-12.12s [%-20.20s]"         , ystr_langs [a_lang].token   , " ");
   ystr_oneline (t, x, y++, YSTR_CLEAR);
   sprintf (t, "%-12.12s [%-20.20s]"         , ystr_langs [a_lang].password, " ");
   ystr_oneline (t, x, y++, YSTR_CLEAR);
   sprintf (t, "%-12.12s [%-20.20s]"         , ystr_langs [a_lang].attempt , x_rand);
   ystr_oneline (t, x, y++, YSTR_CLEAR);
   /*---(complete)-----------------------*/
   DEBUG_YSTR   yLOG_exit    (__FUNCTION__);
   return 0;
}



