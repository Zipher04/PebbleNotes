<map version="1.0.1">
<!-- To view this file, download free mind mapping software FreeMind from http://freemind.sourceforge.net -->
<node CREATED="1504185860552" ID="ID_1519829230" MODIFIED="1504423952377" TEXT="gTask">
<node CREATED="1504185860552" ID="ID_1996994427" MODIFIED="1504426853635" POSITION="right" TEXT="old">
<node CREATED="1504186054414" FOLDED="true" ID="ID_534756381" MODIFIED="1504447114230" TEXT="ready">
<node CREATED="1504186169191" ID="ID_77234074" MODIFIED="1504188413697" TEXT="have token">
<node CREATED="1504185951752" ID="ID_16451250" MODIFIED="1504701299623" TEXT="phone send ready=0">
<arrowlink DESTINATION="ID_883693535" ENDARROW="Default" ENDINCLINATION="341;0;" ID="Arrow_ID_1222782293" STARTARROW="None" STARTINCLINATION="341;0;"/>
</node>
<node CREATED="1504186071547" ID="ID_487711553" MODIFIED="1504274145953" TEXT="phone send option=45">
<arrowlink DESTINATION="ID_1778433768" ENDARROW="Default" ENDINCLINATION="184;0;" ID="Arrow_ID_959854216" STARTARROW="None" STARTINCLINATION="184;0;"/>
</node>
</node>
<node CREATED="1504186179794" ID="ID_383576620" MODIFIED="1504188386014" TEXT="else">
<node CREATED="1504186186560" ID="ID_100052578" MODIFIED="1504274478648" TEXT="phone send get token=41">
<arrowlink DESTINATION="ID_1826574279" ENDARROW="Default" ENDINCLINATION="141;0;" ID="Arrow_ID_1175158633" STARTARROW="None" STARTINCLINATION="141;0;"/>
</node>
</node>
</node>
<node CREATED="1504186234420" ID="ID_645841541" MODIFIED="1504446540146" TEXT="watch send">
<node CREATED="1504188503857" ID="ID_1648694515" MODIFIED="1504188554604" TEXT="10 get">
<node CREATED="1504188506979" ID="ID_719466423" MODIFIED="1504188676536" TEXT="scope=0 get lists"/>
<node CREATED="1504188511414" ID="ID_1482906678" MODIFIED="1504188679084" TEXT="scope=1 get tasks"/>
<node CREATED="1504188512354" ID="ID_1813486934" MODIFIED="1504188681296" TEXT="scope=2 get task"/>
</node>
<node CREATED="1504188555165" ID="ID_19326348" MODIFIED="1504188772160" TEXT="11 update task status">
<icon BUILTIN="yes"/>
<node CREATED="1504188592796" ID="ID_599448181" MODIFIED="1504188684148" TEXT="scope=2 update task"/>
</node>
<node CREATED="1504188617573" ID="ID_392917780" MODIFIED="1505399424673" TEXT="12 create task">
<arrowlink DESTINATION="ID_256972472" ENDARROW="Default" ENDINCLINATION="297;0;" ID="Arrow_ID_968756280" STARTARROW="None" STARTINCLINATION="297;0;"/>
<icon BUILTIN="yes"/>
<node CREATED="1504188646524" ID="ID_1428501380" MODIFIED="1504188713233" TEXT="scope=2 create task"/>
</node>
<node CREATED="1504188738815" ID="ID_1927455249" MODIFIED="1504274637763" TEXT="41 retrieve token reply">
<linktarget COLOR="#b0b0b0" DESTINATION="ID_1927455249" ENDARROW="Default" ENDINCLINATION="103;-3;" ID="Arrow_ID_1430280907" SOURCE="ID_1826574279" STARTARROW="None" STARTINCLINATION="94;0;"/>
</node>
</node>
<node CREATED="1504271189482" ID="ID_1198128661" MODIFIED="1504530362979" TEXT="watch get">
<node CREATED="1504271196464" FOLDED="true" ID="ID_608604032" MODIFIED="1504358214736" TEXT="50 error">
<node CREATED="1504272093393" ID="ID_1553223837" MODIFIED="1504272104219" TEXT="show message"/>
<node CREATED="1504275116347" ID="ID_757274245" MODIFIED="1504275141260" TEXT="sender">
<node CREATED="1504275142921" ID="ID_888956593" MODIFIED="1504276005473" TEXT=" displayError()"/>
</node>
</node>
<node CREATED="1504272105892" FOLDED="true" ID="ID_1168710248" MODIFIED="1504701764919" TEXT="40 save/delete token">
<node CREATED="1504272524663" ID="ID_301353149" MODIFIED="1504272541673" TEXT="for access/refresh token"/>
<node CREATED="1504275116347" ID="ID_131957334" MODIFIED="1504275141260" TEXT="sender">
<node CREATED="1504275142921" ID="ID_121837750" MODIFIED="1504364946993" TEXT="Pebble.addEventListener(&quot;webviewclosed&quot;"/>
</node>
</node>
<node CREATED="1504272697417" FOLDED="true" ID="ID_1826574279" MODIFIED="1504364926289" TEXT="41 get token">
<arrowlink DESTINATION="ID_1927455249" ENDARROW="Default" ENDINCLINATION="103;-3;" ID="Arrow_ID_1430280907" STARTARROW="None" STARTINCLINATION="94;0;"/>
<linktarget COLOR="#b0b0b0" DESTINATION="ID_1826574279" ENDARROW="Default" ENDINCLINATION="141;0;" ID="Arrow_ID_1175158633" SOURCE="ID_100052578" STARTARROW="None" STARTINCLINATION="141;0;"/>
<node CREATED="1504274554498" ID="ID_1550861024" MODIFIED="1504274562161" TEXT="read token and send 41"/>
</node>
<node CREATED="1504273542718" FOLDED="true" ID="ID_1778433768" MODIFIED="1504701774861" TEXT="45 set option">
<linktarget COLOR="#b0b0b0" DESTINATION="ID_1778433768" ENDARROW="Default" ENDINCLINATION="184;0;" ID="Arrow_ID_959854216" SOURCE="ID_487711553" STARTARROW="None" STARTINCLINATION="184;0;"/>
<node CREATED="1504275116347" ID="ID_483742945" MODIFIED="1504275141260" TEXT="sender">
<node CREATED="1504275142921" ID="ID_1197644917" MODIFIED="1504364946993" TEXT="Pebble.addEventListener(&quot;webviewclosed&quot;"/>
</node>
</node>
<node CREATED="1504273560591" ID="ID_883693535" MODIFIED="1504701273095" TEXT="0 ready">
<linktarget COLOR="#b0b0b0" DESTINATION="ID_883693535" ENDARROW="Default" ENDINCLINATION="341;0;" ID="Arrow_ID_1222782293" SOURCE="ID_16451250" STARTARROW="None" STARTINCLINATION="341;0;"/>
<node CREATED="1504273568939" ID="ID_1401283285" MODIFIED="1504273580534" TEXT="com_js_ready = ture"/>
<node CREATED="1504273590059" ID="ID_1104207450" MODIFIED="1504273595927" TEXT="call the callback"/>
<node CREATED="1504275116347" ID="ID_1658449265" MODIFIED="1504275141260" TEXT="sender">
<node CREATED="1504275142921" ID="ID_315541486" MODIFIED="1504275263675" TEXT="ready()"/>
</node>
</node>
<node CREATED="1504273852877" FOLDED="true" ID="ID_1713881468" MODIFIED="1504530369504" TEXT="20 array start">
<node CREATED="1504273860031" ID="ID_510424784" MODIFIED="1504273884743" TEXT="get count for lists or tasks"/>
<node CREATED="1504275116347" ID="ID_94746252" MODIFIED="1504275141260" TEXT="sender">
<node CREATED="1504275142921" ID="ID_942052660" MODIFIED="1504275145876" TEXT=" doGetAllLists()"/>
</node>
</node>
<node CREATED="1504273908983" FOLDED="true" ID="ID_877860807" MODIFIED="1504363518257" TEXT="21 array item">
<node CREATED="1504273920591" ID="ID_1783645693" MODIFIED="1504273947241" TEXT="set list or task item"/>
<node CREATED="1504275116347" ID="ID_247768084" MODIFIED="1504275141260" TEXT="sender">
<node CREATED="1504275142921" ID="ID_736896076" MODIFIED="1504275145876" TEXT=" doGetAllLists()"/>
</node>
</node>
<node CREATED="1504274102649" FOLDED="true" ID="ID_94521923" MODIFIED="1504363518942" TEXT="22 array end">
<node CREATED="1504274108950" ID="ID_1047317882" MODIFIED="1504274119619" TEXT="end list or task"/>
<node CREATED="1504275116347" ID="ID_1318534653" MODIFIED="1504275141260" TEXT="sender">
<node CREATED="1504275142921" ID="ID_573846600" MODIFIED="1504275145876" TEXT=" doGetAllLists()"/>
</node>
</node>
<node CREATED="1504273949437" FOLDED="true" ID="ID_1717723608" MODIFIED="1504363519622" TEXT="23 update item">
<node CREATED="1504275116347" ID="ID_725297519" MODIFIED="1504275141260" TEXT="sender">
<node CREATED="1504275142921" ID="ID_72172670" MODIFIED="1504363279135" TEXT="doUpdateTaskStatus()"/>
</node>
</node>
<node CREATED="1504273991931" FOLDED="true" ID="ID_256972472" MODIFIED="1505399424673" TEXT="24 add item">
<linktarget COLOR="#b0b0b0" DESTINATION="ID_256972472" ENDARROW="Default" ENDINCLINATION="297;0;" ID="Arrow_ID_968756280" SOURCE="ID_392917780" STARTARROW="None" STARTINCLINATION="297;0;"/>
<node CREATED="1504275116347" ID="ID_1287822184" MODIFIED="1504275141260" TEXT="sender">
<node CREATED="1504275142921" ID="ID_900284774" MODIFIED="1504363506350" TEXT="doCreateTask()"/>
</node>
</node>
</node>
<node CREATED="1504186337106" FOLDED="true" ID="ID_861117278" MODIFIED="1504426858266" TEXT="codes">
<node CREATED="1504185980894" FOLDED="true" ID="ID_1337160866" MODIFIED="1504186630970">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      CODE_READY = 0,
    </p>
  </body>
</html></richcontent>
<icon BUILTIN="button_ok"/>
<node CREATED="1504186504275" MODIFIED="1504186504306" TEXT="// JS side is ready (and have access token)"/>
</node>
<node CREATED="1504186371609" FOLDED="true" ID="ID_152833662" MODIFIED="1504188545745">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      CODE_GET = 10,
    </p>
  </body>
</html></richcontent>
<icon BUILTIN="button_ok"/>
<node CREATED="1504186518190" MODIFIED="1504186518221" TEXT="// get some info"/>
</node>
<node CREATED="1504186391597" FOLDED="true" ID="ID_1032379530" MODIFIED="1504188628430">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      CODE_UPDATE = 11,
    </p>
  </body>
</html></richcontent>
<icon BUILTIN="button_ok"/>
<node CREATED="1504186539673" MODIFIED="1504186539689" TEXT="// change some info (e.g. mark task as done/undone)"/>
</node>
<node CREATED="1504186384941" FOLDED="true" ID="ID_394162961" MODIFIED="1504188779292">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      CODE_POST = 12,
    </p>
  </body>
</html></richcontent>
<icon BUILTIN="button_ok"/>
<node CREATED="1504186545961" MODIFIED="1504186545977" TEXT="// insert new info (e.g. add new task)"/>
</node>
<node CREATED="1504186403886" FOLDED="true" ID="ID_903297198" MODIFIED="1504273917498">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      CODE_ARRAY_START = 20,
    </p>
  </body>
</html></richcontent>
<icon BUILTIN="button_ok"/>
<node CREATED="1504186554364" MODIFIED="1504186554384" TEXT="// start array transfer; app must allocate memory (includes count)"/>
</node>
<node CREATED="1504186416943" FOLDED="true" ID="ID_1246557681" MODIFIED="1504273917514">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      CODE_ARRAY_ITEM = 21,
    </p>
  </body>
</html></richcontent>
<icon BUILTIN="button_ok"/>
<node CREATED="1504186559426" MODIFIED="1504186559457" TEXT="// array item"/>
</node>
<node CREATED="1504186423498" ID="ID_835567993" MODIFIED="1504424578643">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      CODE_ARRAY_END = 22,
    </p>
  </body>
</html></richcontent>
<icon BUILTIN="button_ok"/>
<node CREATED="1504186564054" ID="ID_603846292" MODIFIED="1504186564085" TEXT="// end array transfer; transaction is finished"/>
</node>
<node CREATED="1504186428150" FOLDED="true" ID="ID_1884276769" MODIFIED="1504274615571">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      CODE_ITEM_UPDATED = 23,
    </p>
  </body>
</html></richcontent>
<icon BUILTIN="button_ok"/>
<node CREATED="1504186572788" MODIFIED="1504186572816" TEXT="// very similar to ARRAY_ITEM, but contains only changed fields"/>
</node>
<node CREATED="1504186434568" ID="ID_622089195" MODIFIED="1504274615555">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      CODE_ITEM_ADDED = 24,
    </p>
  </body>
</html></richcontent>
<icon BUILTIN="button_ok"/>
</node>
<node CREATED="1504186439609" FOLDED="true" ID="ID_1161715915" MODIFIED="1504272126171">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      CODE_SAVE_TOKEN = 40,
    </p>
  </body>
</html></richcontent>
<icon BUILTIN="button_ok"/>
<node CREATED="1504186478518" MODIFIED="1504186478518" TEXT="// save (new) access token to watchapp as a backup; no need to reply. args: key_*_token or none to delete"/>
</node>
<node CREATED="1504186445628" FOLDED="true" ID="ID_1055431783" MODIFIED="1504186650937">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      CODE_RETRIEVE_TOKEN = 41,
    </p>
  </body>
</html></richcontent>
<icon BUILTIN="button_ok"/>
<node CREATED="1504186495085" MODIFIED="1504186495118" TEXT="// token lost, try to retrieve; query - no args, answer - args: key_*_token or none"/>
</node>
<node CREATED="1504186454700" ID="ID_980344424" MODIFIED="1504188429095">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      CODE_SET_OPTION = 45,
    </p>
  </body>
</html></richcontent>
<icon BUILTIN="button_ok"/>
</node>
<node CREATED="1504186458489" FOLDED="true" ID="ID_330615145" MODIFIED="1504272126144">
<richcontent TYPE="NODE"><html>
  <head>
    
  </head>
  <body>
    <p>
      CODE_ERROR = 50,
    </p>
  </body>
</html></richcontent>
<icon BUILTIN="button_ok"/>
<node CREATED="1504186610271" MODIFIED="1504186610310" TEXT="// some error occured; description may be included"/>
</node>
</node>
<node COLOR="#996600" CREATED="1504323620306" ID="ID_1652131130" MODIFIED="1504794870184" TEXT="ask(o)">
<node CREATED="1504324538691" ID="ID_1845157650" MODIFIED="1504361297929" TEXT="getJson()">
<node CREATED="1504324577883" ID="ID_1297741890" MODIFIED="1504361293803" TEXT="queryTasks()">
<node CREATED="1504328123101" ID="ID_647436042" MODIFIED="1504361279672" TEXT="doGetAllLists()"/>
<node CREATED="1504361279894" ID="ID_259732655" MODIFIED="1504361287444" TEXT="doGetOneList()"/>
<node CREATED="1504361437293" ID="ID_626740790" MODIFIED="1504361441313" TEXT="doUpdateTaskStatus()"/>
</node>
<node CREATED="1504326887787" ID="ID_972743369" MODIFIED="1504326887787" TEXT="(endpoint, params, success, method, send_data)"/>
<node CREATED="1504335198175" ID="ID_1695147122" MODIFIED="1504335201014" TEXT="success(data, event, xhr)"/>
<node CREATED="1504327415118" ID="ID_1524718956" MODIFIED="1504327418861" TEXT="g_access_token is used"/>
</node>
<node CREATED="1504326881729" ID="ID_1619024070" MODIFIED="1504326881729" TEXT="(url, success, failure, headers, method, data)"/>
</node>
</node>
<node CREATED="1504423933564" FOLDED="true" ID="ID_931319196" MODIFIED="1505556845388" POSITION="left" TEXT="read only list named pebble">
<node CREATED="1504423969263" ID="ID_929607298" MODIFIED="1504530678043" TEXT="persist store">
<node CREATED="1504426753175" ID="ID_970536324" MODIFIED="1504426758285" TEXT="tokens"/>
<node CREATED="1504424240860" ID="ID_396693631" MODIFIED="1504424252024" TEXT="list">
<node CREATED="1504424270323" ID="ID_1128633065" MODIFIED="1505047430867" TEXT="id=45"/>
<node CREATED="1504433452697" ID="ID_716366038" MODIFIED="1504433457519" TEXT="length"/>
<node CREATED="1504441208099" ID="ID_1822430290" MODIFIED="1504944944333" TEXT="Updated=25">
<node CREATED="1504944945442" ID="ID_868860866" MODIFIED="1504944949933" TEXT="last sync time"/>
</node>
</node>
<node CREATED="1504424358949" ID="ID_1439131455" MODIFIED="1504424360914" TEXT="task">
<node CREATED="1504424365297" ID="ID_774786915" MODIFIED="1504969341707" TEXT="id=45"/>
<node CREATED="1504424383031" ID="ID_1431124343" MODIFIED="1504426902482" TEXT="title=50"/>
<node CREATED="1504424682511" ID="ID_371429475" MODIFIED="1504426905399" TEXT="note=50"/>
<node CREATED="1504424684977" ID="ID_819690010" MODIFIED="1504426895503" TEXT="done=1">
<node CREATED="1504969395752" ID="ID_1700616158" MODIFIED="1504969412194" TEXT="change to &apos;status&apos; in js"/>
<node CREATED="1504970513202" ID="ID_1191297204" MODIFIED="1504970523991" TEXT="0=&quot;needsAction&quot;"/>
<node CREATED="1504970490168" ID="ID_1439291091" MODIFIED="1504970512548" TEXT="1=&quot;completed&quot;"/>
<node CREATED="1504970525082" ID="ID_837263145" MODIFIED="1504970537270" TEXT="-1=&quot;deleted&quot;"/>
</node>
<node CREATED="1504424389568" ID="ID_1271853890" MODIFIED="1504969390469" TEXT="updated=25"/>
</node>
</node>
<node CREATED="1504424043458" FOLDED="true" ID="ID_1121933629" MODIFIED="1504424946941" TEXT="UI">
<node CREATED="1504424472841" ID="ID_138569916" MODIFIED="1504424474650" TEXT="main">
<node CREATED="1504424444302" ID="ID_1551697469" MODIFIED="1504424451276" TEXT="hold mid">
<node CREATED="1504424052379" ID="ID_1484693087" MODIFIED="1504424053840" TEXT="task">
<node CREATED="1504424491832" ID="ID_32854055" MODIFIED="1504424521274" TEXT="hold mid">
<node CREATED="1504424140809" ID="ID_142533479" MODIFIED="1504424144366" TEXT="edit task"/>
</node>
<node CREATED="1504424498231" ID="ID_335801290" MODIFIED="1504424507421" TEXT="hold down">
<node CREATED="1504424158239" ID="ID_782967365" MODIFIED="1504424164359" TEXT="edit note"/>
</node>
<node CREATED="1504424588176" ID="ID_1485861426" MODIFIED="1504424592508" TEXT="up">
<node CREATED="1504424594213" ID="ID_1015343314" MODIFIED="1504424600460" TEXT="previous"/>
</node>
<node CREATED="1504424601547" ID="ID_1148735391" MODIFIED="1504424602674" TEXT="down">
<node CREATED="1504424612313" ID="ID_130380457" MODIFIED="1504424614161" TEXT="next"/>
</node>
<node CREATED="1504424532040" ID="ID_1046735533" MODIFIED="1504424608052" TEXT="mid">
<node CREATED="1504424544367" ID="ID_1891580703" MODIFIED="1504424550196" TEXT="done"/>
<node CREATED="1504424550505" ID="ID_84650807" MODIFIED="1504424553288" TEXT="undone"/>
</node>
</node>
<node CREATED="1504424079760" ID="ID_338356558" MODIFIED="1504424083037" TEXT="note"/>
</node>
<node CREATED="1504424532040" ID="ID_1112690083" MODIFIED="1504424608052" TEXT="mid">
<node CREATED="1504424544367" ID="ID_1598159688" MODIFIED="1504424550196" TEXT="done"/>
<node CREATED="1504424550505" ID="ID_1728403227" MODIFIED="1504424553288" TEXT="undone"/>
</node>
<node CREATED="1504424588176" ID="ID_1242574147" MODIFIED="1504424592508" TEXT="up">
<node CREATED="1504424594213" ID="ID_1502023261" MODIFIED="1504424600460" TEXT="previous"/>
</node>
<node CREATED="1504424601547" ID="ID_651559777" MODIFIED="1504424602674" TEXT="down">
<node CREATED="1504424612313" ID="ID_1999460061" MODIFIED="1504424614161" TEXT="next"/>
</node>
</node>
<node CREATED="1504424046632" ID="ID_826903403" MODIFIED="1504424049058" TEXT="tasks"/>
<node CREATED="1504424075611" ID="ID_1003754237" MODIFIED="1504424077540" TEXT="status"/>
<node CREATED="1504424087400" ID="ID_246331821" MODIFIED="1504424187763" TEXT="create task">
<node CREATED="1504424191147" ID="ID_849658343" MODIFIED="1504424196439" TEXT="voice"/>
<node CREATED="1504424196968" ID="ID_1994251724" MODIFIED="1504424208285" TEXT="trinity input"/>
</node>
</node>
<node CREATED="1504423938225" FOLDED="true" ID="ID_1576755239" MODIFIED="1504426810046" TEXT="process">
<node CREATED="1504424799663" ID="ID_1595893910" MODIFIED="1504424817918" TEXT="if phone and internet connected">
<node CREATED="1504424950911" ID="ID_1818397075" MODIFIED="1504424958144" TEXT="get token from pebble"/>
<node CREATED="1504424858258" ID="ID_509907107" MODIFIED="1504424867291" TEXT="update data from google"/>
<node CREATED="1504424963654" ID="ID_866642573" MODIFIED="1504424964781" TEXT="update data from pebble "/>
<node CREATED="1504425036247" ID="ID_640756383" MODIFIED="1504425042374" TEXT="update pebble data">
<node CREATED="1504425059558" ID="ID_1278354600" MODIFIED="1504425119607" TEXT="if watch data not modified">
<node CREATED="1504425072181" ID="ID_1863893454" MODIFIED="1504425084896" TEXT="read data from google"/>
<node CREATED="1504426635475" ID="ID_1238093686" MODIFIED="1504426646966" TEXT="update watch"/>
</node>
<node CREATED="1504425086302" ID="ID_1711986791" MODIFIED="1504425111668" TEXT="if watch data modified">
<node CREATED="1504425072181" ID="ID_860563662" MODIFIED="1504426676248" TEXT="read data from watch"/>
<node CREATED="1504426635475" ID="ID_807207045" MODIFIED="1504426686177" TEXT="update google"/>
</node>
<node CREATED="1504426687439" ID="ID_1318176552" MODIFIED="1504426693871" TEXT="if both modified">
<node CREATED="1504425072181" ID="ID_259377718" MODIFIED="1504425084896" TEXT="read data from google"/>
<node CREATED="1504425072181" ID="ID_207379699" MODIFIED="1504426676248" TEXT="read data from watch"/>
<node CREATED="1504426635475" ID="ID_191666897" MODIFIED="1504426646966" TEXT="update watch"/>
<node CREATED="1504426635475" ID="ID_567145976" MODIFIED="1504426686177" TEXT="update google"/>
</node>
</node>
</node>
</node>
<node CREATED="1504446650853" ID="ID_919731676" MODIFIED="1504446652240" TEXT="js">
<node CREATED="1504446662035" ID="ID_1145497580" MODIFIED="1504446676089" TEXT="ready">
<node CREATED="1504701245762" ID="ID_1818589876" MODIFIED="1505015917386" TEXT="send 41 get token">
<node CREATED="1505031652982" ID="ID_1807999357" MODIFIED="1505031656109" TEXT="get 41"/>
</node>
<node CREATED="1504703938213" ID="ID_1181203489" MODIFIED="1505015928757" TEXT="send 0">
<node CREATED="1504968012918" ID="ID_1455640518" MODIFIED="1505016745120" TEXT="SendListToPhone()">
<node CREATED="1504970952385" ID="ID_1401012282" MODIFIED="1505043361789" TEXT="get 52 sned list">
<node CREATED="1505043336817" ID="ID_1070781965" MODIFIED="1505043415380" TEXT="send 56 list ack"/>
</node>
</node>
</node>
<node CREATED="1504701350066" ID="ID_362865470" MODIFIED="1504701368136" TEXT="45 update option"/>
</node>
<node CREATED="1504446653993" ID="ID_1903900176" MODIFIED="1504446658202" TEXT="send"/>
<node CREATED="1504447330140" ID="ID_11127287" MODIFIED="1504970998811" TEXT="get">
<node CREATED="1504969956201" ID="ID_59768243" MODIFIED="1505015940025" TEXT="SendTasksToPhone()">
<node CREATED="1505043492228" ID="ID_318497487" MODIFIED="1505043577327" TEXT="get 54 task">
<node CREATED="1505043578269" ID="ID_469550717" MODIFIED="1505043584888" TEXT="send 58 task ack"/>
</node>
<node CREATED="1505043585283" ID="ID_247720568" MODIFIED="1505043591359" TEXT="get 55 task end">
<node CREATED="1505043591729" ID="ID_1877662604" MODIFIED="1505043600581" TEXT="send 55 task end ack"/>
</node>
</node>
<node CREATED="1504971017062" ID="ID_1024012547" MODIFIED="1505015990624" TEXT="get 51, sync google">
<node CREATED="1504701389982" ID="ID_831925842" MODIFIED="1504968055614" TEXT="GetListFromGoogle()"/>
<node CREATED="1504944573636" ID="ID_1436539454" MODIFIED="1504968069151" TEXT="SyncWatchAndGoogle()"/>
<node CREATED="1504944586970" ID="ID_23268660" MODIFIED="1504968083160" TEXT="SendListToWatch()">
<node CREATED="1504971093777" ID="ID_929613608" MODIFIED="1505016025505" TEXT="send 52, 53, 54, 55">
<node CREATED="1505032728554" ID="ID_264070814" MODIFIED="1505032731127" TEXT="ts_show_pebble();"/>
</node>
</node>
</node>
</node>
<node CREATED="1504792354786" ID="ID_463694096" MODIFIED="1504792468663" TEXT="send list payload">
<node CREATED="1504424270323" ID="ID_944476582" MODIFIED="1504426870014" TEXT="id=33"/>
<node CREATED="1504433452697" ID="ID_664613810" MODIFIED="1504433457519" TEXT="length"/>
<node CREATED="1504441208099" ID="ID_21818342" MODIFIED="1504441211540" TEXT="modified"/>
<node CREATED="1504424253269" ID="ID_1418016958" MODIFIED="1504441203603" TEXT="sync time=25"/>
</node>
<node CREATED="1504792409302" ID="ID_191862871" MODIFIED="1504792462873" TEXT="send task payload">
<node CREATED="1504424365297" ID="ID_415354767" MODIFIED="1504426884399" TEXT="id=33"/>
<node CREATED="1504424684977" ID="ID_1042034194" MODIFIED="1504931173465" TEXT="status=1"/>
<node CREATED="1504424383031" ID="ID_1060895740" MODIFIED="1504426902482" TEXT="title=50"/>
<node CREATED="1504424682511" ID="ID_321723283" MODIFIED="1504426905399" TEXT="note=50"/>
<node CREATED="1504424389568" ID="ID_1021276795" MODIFIED="1504793781763" TEXT="updated=25"/>
</node>
</node>
</node>
<node CREATED="1504340792372" FOLDED="true" ID="ID_142059916" MODIFIED="1504969347822" POSITION="right" TEXT="g_tasklists">
<node CREATED="1504340798652" ID="ID_1938517210" MODIFIED="1504340802762" TEXT="titles"/>
<node CREATED="1504340803023" ID="ID_830684041" MODIFIED="1504363018824" TEXT="ids=33">
<node CREATED="1504363006485" ID="ID_1885032787" MODIFIED="1504363008517" TEXT="MTcyNTAzMDk3ODEzNjE2Nzg2MTM6MDow"/>
</node>
<node CREATED="1504363050666" FOLDED="true" ID="ID_335803586" MODIFIED="1504363061801" TEXT="updated">
<node CREATED="1504360192069" ID="ID_1361127096" MODIFIED="1504360192069" TEXT="RFC 3339 timestamp"/>
<node CREATED="1504362894024" ID="ID_1508991072" MODIFIED="1504362895664" TEXT="2017-09-02T14:08:02.000Z"/>
</node>
<node CREATED="1504359365076" ID="ID_801445801" MODIFIED="1504359366674" TEXT="task">
<node CREATED="1504359367803" ID="ID_718840811" MODIFIED="1504362738851" TEXT="id=45">
<node CREATED="1504362712662" ID="ID_1759449727" MODIFIED="1504362714417" TEXT="MTcyNTAzMDk3ODEzNjE2Nzg2MTM6MDoxNTUzNzUwODM2"/>
</node>
<node CREATED="1504359371830" ID="ID_1521141709" MODIFIED="1504359374139" TEXT="position"/>
<node CREATED="1504359375896" FOLDED="true" ID="ID_1174690831" MODIFIED="1504360270147" TEXT="status">
<node CREATED="1504360170114" MODIFIED="1504360170114" TEXT="&quot;needsAction&quot;"/>
<node CREATED="1504360176681" MODIFIED="1504360176681" TEXT="&quot;completed&quot;"/>
</node>
<node CREATED="1504359379164" ID="ID_813521758" MODIFIED="1504363222241" TEXT="title=?"/>
<node CREATED="1504359397686" ID="ID_1354528997" MODIFIED="1504363218381" TEXT="notes=?"/>
<node CREATED="1504359401412" ID="ID_424136946" MODIFIED="1504705531673" TEXT="updated=25">
<node CREATED="1504360192069" ID="ID_1263793899" MODIFIED="1504360192069" TEXT="RFC 3339 timestamp"/>
<node CREATED="1504362894024" ID="ID_810449916" MODIFIED="1504362895664" TEXT="2017-09-02T14:08:02.000Z"/>
</node>
<node CREATED="1504359406656" ID="ID_757867957" MODIFIED="1504359407805" TEXT="due"/>
</node>
</node>
<node CREATED="1505556847793" ID="ID_660199625" MODIFIED="1505556853118" POSITION="left" TEXT="Create tast">
<node CREATED="1505556855234" ID="ID_265959558" MODIFIED="1505556872743" TEXT="ts_select_click_cb()"/>
<node CREATED="1505556873153" ID="ID_905678435" MODIFIED="1505556885746" TEXT="ts_create_task()">
<node CREATED="1505556940895" ID="ID_1747138969" MODIFIED="1505556944584" TEXT="dictation"/>
</node>
<node CREATED="1505556886344" ID="ID_1264760129" MODIFIED="1505557247843" TEXT="ts_create_task_cb"/>
<node CREATED="1505557265695" ID="ID_625806657" MODIFIED="1505558098963" TEXT="comm_create_task()">
<node CREATED="1505557295744" ID="ID_1395010243" MODIFIED="1505557363166" TEXT="send CODE_POST=12"/>
</node>
<node CREATED="1505557352301" ID="ID_1556550038" MODIFIED="1505558070082" TEXT="doCreateTask()">
<node CREATED="1505557582354" ID="ID_1266957979" MODIFIED="1505557723280" TEXT="get CODE_ITEM_ADDED=24"/>
</node>
<node CREATED="1505557752908" ID="ID_288838468" MODIFIED="1505557755222" TEXT="ts_append_item()"/>
<node CREATED="1505559323158" ID="ID_901609197" MODIFIED="1505559324712" TEXT="tertiary_text_prompt"/>
</node>
<node CREATED="1505559328590" ID="ID_69629587" MODIFIED="1505559333749" POSITION="left" TEXT="tertiary">
<node CREATED="1505559446359" ID="ID_1849629866" MODIFIED="1505559451341" TEXT="tertiary_text_prompt()">
<node CREATED="1505559479276" ID="ID_900551870" MODIFIED="1505559511914" TEXT="const char* title"/>
<node CREATED="1505559493333" ID="ID_1632492362" MODIFIED="1505559494468" TEXT="TertiaryTextCallback callback">
<node CREATED="1505559541044" ID="ID_1169350728" MODIFIED="1505559542104" TEXT="const char* result"/>
<node CREATED="1505559542550" ID="ID_1478571747" MODIFIED="1505559550289" TEXT="size_t result_length"/>
<node CREATED="1505559568132" ID="ID_1082023717" MODIFIED="1505559569115" TEXT="void* extra"/>
</node>
<node CREATED="1505559498936" ID="ID_1315363005" MODIFIED="1505559502350" TEXT="void* extra"/>
</node>
</node>
</node>
</map>
