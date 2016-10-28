#include<stdio.h>
#include<stdlib.h>
#include<math.h>

//For LPC
int FrameLength=256;
int polseHighPos=0;
#define pi 3.14159265358

double wwqing[]={0.000149421078453,
0.000597595007178,
0.001344253919647,
0.002388951549541,
0.003731063497474,
0.005369787604187,
0.007304144429987,
0.009532977840141,
0.012054955695883,
0.014868570650608,
0.017972141050792,
0.021363811941092,
0.025041556173017,
0.029003175616530,
0.033246302473833,
0.037768400694562,
0.042566767491544,
0.047638534956213,
0.052980671772711,
0.058589985029663,
0.064463122128522,
0.070596572787371,
0.076986671138963,
0.083629597921749,
0.090521382762593,
0.097657906549802,
0.105034903895052,
0.112647965682748,
0.120492541705279,
0.128563943382607,
0.136857346564560,
0.145367794414147,
0.154090200370186,
0.163019351187458,
0.172149910052584,
0.181476419773753,
0.190993306042403,
0.200694880764894,
0.210575345462196,
0.220628794735546,
0.230849219796014,
0.241230512055860,
0.251766466779543,
0.262450786792195,
0.273277086243339,
0.284238894423618,
0.295329659632231,
0.306542753092784,
0.317871472915207,
0.329309048101366,
0.340848642591985,
0.352483359352449,
0.364206244495054,
0.376010291435238,
0.387888445079305,
0.399833606041146,
0.411838634885427,
0.423896356394721,
0.435999563858022,
0.448141023378083,
0.460313478195001,
0.472509653023471,
0.484722258401111,
0.496943995045254,
0.509167558215622,
0.521385642080249,
0.533590944082063,
0.545776169303514,
0.557934034826625,
0.570057274085884,
0.582138641211355,
0.594170915359414,
0.606146905028547,
0.618059452357584,
0.629901437403849,
0.641665782398637,
0.653345455977481,
0.664933477382692,
0.676422920635650,
0.687806918676346,
0.699078667467724,
0.710231430062342,
0.721258540628942,
0.732153408436510,
0.742909521793458,
0.753520451939554,
0.763979856888295,
0.774281485217411,
0.784419179805244,
0.794386881510759,
0.804178632795004,
0.813788581281829,
0.823210983255770,
0.832440207094966,
0.841470736637101,
0.850297174476321,
0.858914245189185,
0.867316798487695,
0.875499812297549,
0.883458395759753,
0.891187792153812,
0.898683381740745,
0.905940684524234,
0.912955362928245,
0.919723224389528,
0.926240223863451,
0.932502466241655,
0.938506208680101,
0.944247862836110,
0.949723997013056,
0.954931338211443,
0.959866774085119,
0.964527354801480,
0.968910294804540,
0.973012974479810,
0.976832941720003,
0.980367913390621,
0.983615776694547,
0.986574590434830,
0.989242586174910,
0.991618169295584,
0.993699919948085,
0.995486593902703,
0.996977123292440,
0.998170617251262,
0.999066362446550,
0.999663823505453,
0.999962643334866,
0.999962643334866,
0.999663823505453,
0.999066362446550,
0.998170617251262,
0.996977123292440,
0.995486593902703,
0.993699919948085,
0.991618169295584,
0.989242586174910,
0.986574590434830,
0.983615776694547,
0.980367913390621,
0.976832941720003,
0.973012974479810,
0.968910294804540,
0.964527354801480,
0.959866774085119,
0.954931338211443,
0.949723997013056,
0.944247862836110,
0.938506208680101,
0.932502466241655,
0.926240223863451,
0.919723224389528,
0.912955362928245,
0.905940684524234,
0.898683381740745,
0.891187792153812,
0.883458395759753,
0.875499812297549,
0.867316798487695,
0.858914245189185,
0.850297174476321,
0.841470736637101,
0.832440207094966,
0.823210983255770,
0.813788581281829,
0.804178632795004,
0.794386881510759,
0.784419179805244,
0.774281485217411,
0.763979856888295,
0.753520451939554,
0.742909521793458,
0.732153408436510,
0.721258540628942,
0.710231430062342,
0.699078667467724,
0.687806918676346,
0.676422920635650,
0.664933477382692,
0.653345455977481,
0.641665782398637,
0.629901437403849,
0.618059452357584,
0.606146905028547,
0.594170915359414,
0.582138641211355,
0.570057274085884,
0.557934034826625,
0.545776169303514,
0.533590944082063,
0.521385642080249,
0.509167558215622,
0.496943995045254,
0.484722258401111,
0.472509653023471,
0.460313478195001,
0.448141023378083,
0.435999563858022,
0.423896356394721,
0.411838634885427,
0.399833606041146,
0.387888445079305,
0.376010291435238,
0.364206244495054,
0.352483359352449,
0.340848642591985,
0.329309048101366,
0.317871472915207,
0.306542753092784,
0.295329659632231,
0.284238894423618,
0.273277086243339,
0.262450786792195,
0.251766466779543,
0.241230512055860,
0.230849219796014,
0.220628794735546,
0.210575345462196,
0.200694880764894,
0.190993306042403,
0.181476419773753,
0.172149910052584,
0.163019351187458,
0.154090200370186,
0.145367794414147,
0.136857346564560,
0.128563943382607,
0.120492541705279,
0.112647965682748,
0.105034903895052,
0.097657906549802,
0.090521382762593,
0.083629597921749,
0.076986671138963,
0.070596572787371,
0.064463122128522,
0.058589985029663,
0.052980671772711,
0.047638534956213,
0.042566767491544,
0.037768400694562,
0.033246302473833,
0.029003175616530,
0.025041556173017,
0.021363811941092,
0.017972141050792,
0.014868570650608,
0.012054955695883,
0.009532977840141,
0.007304144429987,
0.005369787604187,
0.003731063497474,
0.002388951549541,
0.001344253919647,
0.000597595007178,
0.000149421078453
};

double wwzhuo[]={0.999990624300776 ,
0.999915620816661,
0.999765625099688,
0.999540659650681,
0.999240758216658,
0.998865965785767,
0.998416338580540,
0.997891944049454,
0.997292860856818,
0.996619178870972,
0.995870999150801,
0.995048433930583,
0.994151606603146,
0.993180651701361,
0.992135714877961,
0.991016952883689,
0.989824533543787,
0.988558635732820,
0.987219449347841,
0.985807175279907,
0.984322025383941,
0.982764222446955,
0.981134000154625,
0.979431603056242,
0.977657286528021,
0.975811316734796,
0.973893970590092,
0.971905535714585,
0.969846310392954,
0.967716603529140,
0.965516734600004,
0.963247033607401,
0.960907841028681,
0.958499507765610,
0.956022395091735,
0.953476874598185,
0.950863328137933,
0.948182147768510,
0.945433735693197,
0.942618504200689,
0.939736875603244,
0.936789282173339,
0.933776166078818,
0.930697979316568,
0.927555183644710,
0.924348250513336,
0.921077660993783,
0.917743905706468,
0.914347484747293,
0.910888907612623,
0.907368693122855,
0.903787369344596,
0.900145473511442,
0.896443551943389,
0.892682159964882,
0.888861861821507,
0.884983230595354,
0.881046848119043,
0.877053304888448,
0.873003199974115,
0.868897140931397,
0.864735743709310,
0.860519632558142,
0.856249439935804,
0.851925806412956,
0.847549380576916,
0.843120818934367,
0.838640785812871,
0.834109953261215,
0.829529000948600,
0.824898616062680,
0.820219493206476,
0.815492334294186,
0.810717848445882,
0.805896751881142,
0.801029767811607,
0.796117626332490,
0.791161064313061,
0.786160825286103,
0.781117659336377,
0.776032322988105,
0.770905579091479,
0.765738196708228,
0.760530950996253,
0.755284623093344,
0.750000000000000,
0.744677874461376,
0.739319044848358,
0.733924315037804,
0.728494494291952,
0.723030397137023,
0.717532843241037,
0.712002657290848,
0.706440668868442,
0.700847712326485,
0.695224626663162,
0.689572255396324,
0.683891446436947,
0.678183051961939,
0.672447928286307,
0.666686935734698,
0.660900938512343,
0.655090804575419,
0.649257405500847,
0.643401616355545,
0.637524315565161,
0.631626384782300,
0.625708708754267,
0.619772175190349,
0.613817674628647,
0.607846100302485,
0.601858348006422,
0.595855315961869,
0.589837904682349,
0.583807016838412,
0.577763557122221,
0.571708432111848,
0.565642550135269,
0.559566821134112,
0.553482156527154,
0.547389469073602,
0.541289672736166,
0.535183682543961,
0.529072414455238,
0.522956785219986,
0.516837712242408,
0.510716113443301,
0.504592907122363,
0.498469011820433,
0.492345346181704,
0.486222828815919,
0.480102378160568,
0.473984912343114,
0.467871349043265,
0.461762605355314,
0.455659597650564,
0.449563241439866,
0.443474451236280,
0.437394140417891,
0.431323221090796,
0.425262603952273,
0.419213198154173,
0.413175911166535,
0.407151648641459,
0.401141314277248,
0.395145809682845,
0.389166034242581,
0.383202884981261,
0.377257256429600,
0.371330040490037,
0.365422126302938,
0.359534400113215,
0.353667745137387,
0.347823041431082,
0.342001165757024,
0.336202991453508,
0.330429388303393,
0.324681222403623,
0.318959356035307,
0.313264647534366,
0.307597951162777,
0.301960116980422,
0.296351990717571,
0.290774413648019,
0.285228222462882,
0.279714249145083,
0.274233320844555,
0.268786259754152,
0.263373882986316,
0.257997002450501,
0.252656424731379,
0.247352950967845,
0.242087376732838,
0.236860491913996,
0.231673080595167,
0.226525920938787,
0.221419785069149,
0.216355438956579,
0.211333642302527,
0.206355148425611,
0.201420704148607,
0.196531049686422,
0.191686918535050,
0.186889037361547,
0.182138125895016,
0.177434896818647,
0.172780055662804,
0.168174300699189,
0.163618322836098,
0.159112805514772,
0.154658424606878,
0.150255848313121,
0.145905737063008,
0.141608743415774,
0.137365511962497,
0.133176679229399,
0.129042873582359,
0.124964715132660,
0.120942815643956,
0.116977778440511,
0.113070198316687,
0.109220661447723,
0.105429745301803,
0.101698018553428,
0.098026040998110,
0.094414363468399,
0.090863527751250,
0.087374066506753,
0.083946503188225,
0.080581351963689,
0.077279117638743,
0.074040295580836,
0.070865371644957,
0.067754822100749,
0.064709113561069,
0.061728702911988,
0.058814037244256,
0.055965553786231,
0.053183679838294,
0.050468832708746,
0.047821419651211,
0.045241837803543,
0.042730474128249,
0.040287705354446,
0.037913897921342,
0.035609407923270,
0.033374581056271,
0.031209752566235,
0.029115247198608,
0.027091379149683,
0.025138452019462,
0.023256758766118,
0.021446581662043,
0.019708192251508,
0.018041851309929,
0.016447808804745,
0.014926303857923,
0.013477564710088,
0.012101808686282,
0.010799242163365,
0.009570060539057,
0.008414448202622,
0.007332578507216,
0.006324613743875,
0.005390705117171,
0.004530992722534,
0.003745605525231,
0.003034661341025,
0.002398266818497,
0.001836517423049,
0.001349497422586,
0.000937279874872,
0.000599926616569,
0.000337488253968,
0.000150004155389,
0.000037502445281
};

double pulseZhuo_Low[]={
0.000011904584429,
-0.000015267777526,
-0.000098792432206,
0.000133013259936,
0.000205604208408,
-0.000429475264684,
-0.000191835517123,
0.000896682731069,
-0.000114236111758,
-0.001408876367312,
0.000847831801989,
0.001724108160359,
-0.002032728937581,
-0.001527860294653,
0.003521000997555,
0.000514400507177,
-0.004968299881311,
0.001509447180309,
0.005858650600647,
-0.004521314997144,
-0.005581339862873,
0.008206461331060,
0.003549215217439,
-0.011927505175088,
0.000664149279690,
0.014748785637041,
-0.007198294752812,
-0.015503814173227,
0.015821234259377,
0.012864839835709,
-0.025910161082980,
-0.005317785786039,
0.036508537177352,
-0.009216254406356,
-0.046454373071083,
0.035087009940024,
0.054558553503215,
-0.087929818327291,
-0.059800110124811,
0.312265725874276,
0.561312291352506,
0.311327077684938,
-0.059440600919955,
-0.087136091820049,
0.053900577208084,
0.034556466720780,
-0.045608025535390,
-0.009019353463637,
0.035611577985292,
-0.005169726379283,
-0.025101802731185,
0.012419063671681,
0.015216641257144,
-0.014854125658214,
-0.006869025870561,
0.014015065657269,
0.000628321890972,
-0.011231401848626,
0.003325511470467,
0.007648538028526,
-0.005172364028368,
-0.004164354943879,
0.005360235683999,
0.001371000726493,
-0.004476521126633,
0.000459370792007,
0.003113095395807,
-0.001335686407336,
-0.001754231285478,
0.001465763427088,
0.000708188617876,
-0.001152215014663,
-0.000091039028192,
0.000691735529213,
-0.000141866075208,
-0.000299901380037,
0.000132183096460,
0.000075083368801,
-0.000044018040606,
-0.000003822691911,
};

double pulseZhuo_High[]={
-0.606048583984375,
0.617156982421875,
-0.324218750000000,
0.060455322265625,
-0.173736572265625,
0.539031982421875,
-0.638916015625000,
0.160125732421875,
0.605194091796875,
-1.000000000000000,
0.779785156250000,
-0.111358642578125,
-0.409851074218750,
0.425781250000000,
-0.042449951171875,
-0.332122802734375,
0.372467041015625,
-0.117401123046875,
-0.090393066406250,
-0.017761230468750,
0.302886962890625,
-0.338592529296875,
-0.064239501953125,
0.534820556640625,
-0.506164550781250,
-0.080566406250000,
0.618530273437500,
-0.516845703125000,
-0.078216552734375,
0.465423583984375,
-0.278625488281250,
-0.073638916015625,
0.016113281250000,
0.360351562500000,
-0.409606933593750,
-0.123413085937500,
0.630371093750000,
-0.373352050781250,
-0.491546630859375,
0.997802734375000,
-0.536895751953125,
-0.366973876953125,
0.683166503906250,
-0.110870361328125,
-0.620330810546875,
0.687683105468750,
-0.107055664062500,
-0.444641113281250,
0.522979736328125,
-0.329772949218750,
0.263366699218750,
-0.367034912109375,
0.388671875000000,
-0.203399658203125,
-0.063537597656250,
0.283172607421875,
-0.447479248046875,
0.490234375000000,
-0.210540771484375,
-0.425476074218750,
0.999969482421875,
-0.989013671875000,
0.276977539062500,
0.529785156250000,
-0.731201171875000,
0.222808837890625,
0.464233398437500,
-0.759063720703125,
0.552734375000000,
-0.131134033203125,
-0.201354980468750,
0.326660156250000,
-0.268493652343750,
0.126800537109375,
-0.053863525390625,
0.142822265625000,
-0.277069091796875,
0.198059082031250,
0.181060791015625,
-0.598175048828125,
0.701599121093750,
-0.470062255859375,
0.244171142578125,
-0.303375244140625,
0.536590576171875,
-0.630676269531250,
0.499237060546875,
-0.363494873046875,
0.403076171875000,
-0.485656738281250,
0.344970703125000,
0.052886962890625,
-0.444580078125000,
0.557098388671875,
-0.365539550781250,
0.063934326171875,
0.115264892578125,
-0.025054931640625,
-0.321807861328125,
0.685394287109375,
-0.683654785156250,
0.132781982421875,
0.647430419921875,
-1.000000000000000,
0.599884033203125,
0.254211425781250,
-0.845062255859375,
0.787017822265625,
-0.303527832031250,
-0.150939941406250,
0.384155273437500,
-0.493469238281250,
0.550994873046875,
-0.481506347656250,
0.267974853515625,
-0.085052490234375,
0.099884033203125,
-0.229400634765625,
0.235382080078125,
-0.035797119140625,
-0.207061767578125,
0.316741943359375,
-0.283050537109375,
0.157745361328125,
0.085968017578125,
-0.443084716796875,
0.706604003906250,
-0.621917724609375,
0.257049560546875,
-0.031982421875000,
0.231933593750000,
-0.601684570312500,
0.624114990234375,
-0.184417724609375,
-0.258666992187500,
0.251281738281250,
0.091247558593750,
-0.285186767578125,
0.137603759765625,
0.060394287109375,
-0.038085937500000,
-0.023132324218750,
-0.226989746093750,
0.729309082031250,
-1.000000000000000,
0.762390136718750,
-0.251586914062500,
-0.095123291015625,
0.215393066406250,
-0.352081298828125,
0.529083251953125,
-0.414642333984375,
-0.166992187500000,
0.830657958984375,
-1.000000000000000,
0.620025634765625,
-0.206024169921875,
0.168304443359375,
-0.302673339843750,
0.154052734375000,
0.295135498046875,
-0.589050292968750,
0.439880371093750,
-0.110351562500000,
0.000122070312500,
-0.062408447265625,
-0.086151123046875,
0.522705078125000,
-0.795501708984375,
0.485778808593750,
0.206787109375000,
-0.670806884765625,
0.604797363281250,
-0.293609619140625,
0.134246826171875,
-0.132415771484375,
0.045471191406250,
0.134643554687500,
-0.128967285156250,
-0.167907714843750,
0.427001953125000,
-0.262054443359375,
-0.250305175781250,
0.634826660156250,
-0.588623046875000,
0.288177490234375,
-0.056976318359375,
-0.088012695312500,
0.365814208984375,
-0.783386230468750,
0.999969482421875,
-0.786956787109375,
0.334533691406250,
-0.110046386718750,
0.249938964843750,
-0.407562255859375,
0.231018066406250,
0.143737792968750,
-0.240325927734375,
-0.142425537109375,
0.631652832031250,
-0.693725585937500,
0.269744873046875,
0.135742187500000,
-0.028228759765625,
-0.505279541015625,
0.882293701171875,
-0.662750244140625,
0.019409179687500,
0.467193603515625,
-0.433227539062500,
0.077575683593750,
0.116912841796875,
0.075866699218750,
-0.439331054687500,
0.637023925781250,
-0.604888916015625,
0.548919677734375,
-0.614898681640625,
0.690216064453125,
-0.578796386718750,
0.283843994140625,
-0.016387939453125,
-0.059936523437500,
-0.004211425781250,
0.060760498046875,
-0.062164306640625,
0.066253662109375,
-0.091918945312500,
0.079650878906250,
-0.017883300781250,
0.012786865234375,
-0.160858154296875,
0.395294189453125,
-0.539550781250000,
0.500061035156250,
-0.324432373046875,
0.066406250000000,
0.292236328125000,
-0.702850341796875,
0.917388916015625,
-0.660003662109375,
-0.017608642578125,
0.660522460937500,
-0.807403564453125,
0.457733154296875,
-0.071990966796875,
0.095733642578125,
-0.528289794921875,
0.963684082031250,
-0.993041992187500,
0.548156738281250,
0.069000244140625,
-0.422271728515625,
0.265319824218750,
0.241119384765625,
-0.617584228515625,
0.490966796875000,
-0.011474609375000,
-0.238769531250000,
-0.123718261718750,
0.780334472656250,
-0.997406005859375,
0.468414306640625,
0.278991699218750,
-0.466125488281250,
-0.018707275390625,
0.485443115234375,
-0.274719238281250,
-0.450286865234375,
0.901306152343750,
-0.576293945312500,
-0.216278076171875,
0.762725830078125,
-0.692901611328125,
0.215240478515625,
0.254150390625000,
-0.482482910156250,
0.445343017578125,
-0.187316894531250,
-0.185821533203125,
0.463073730468750,
-0.461059570312500,
0.241455078125000,
-0.091613769531250,
0.225006103515625,
-0.550811767578125,
0.779785156250000,
-0.702423095703125,
0.320098876953125,
0.208374023437500,
-0.627685546875000,
0.646789550781250,
-0.151184082031250,
-0.540710449218750,
0.792724609375000,
-0.253692626953125,
-0.646453857421875,
0.999969482421875,
-0.429931640625000,
-0.543395996093750,
0.971893310546875,
-0.605804443359375,
0.118377685546875,
-0.226593017578125,
0.786193847656250,
-0.985382080078125,
0.375335693359375,
0.563507080078125,
-1.000000000000000,
0.747192382812500,
-0.359771728515625,
0.399139404296875,
-0.713134765625000,
0.696472167968750,
-0.123413085937500,
-0.500549316406250,
0.495574951171875,
0.203399658203125,
-0.941314697265625,
0.999969482421875,
-0.393920898437500,
-0.338226318359375,
0.573822021484375,
-0.275726318359375,
-0.080322265625000,
0.055908203125000,
0.301422119140625,
-0.544067382812500,
0.315185546875000,
0.268371582031250,
-0.709136962890625,
0.593750000000000,
0.012817382812500,
-0.598724365234375,
0.634918212890625,
-0.040130615234375,
-0.719146728515625,
0.999969482421875,
-0.616699218750000,
-0.054779052734375,
0.337280273437500,
-0.000793457031250,
-0.484161376953125,
0.454193115234375,
0.173004150390625,
-0.760559082031250,
0.680969238281250,
-0.082672119140625,
-0.260772705078125,
-0.112548828125000,
0.773437500000000,
-0.927276611328125,
0.403015136718750,
0.152832031250000,
-0.129211425781250,
-0.259124755859375,
0.278045654296875,
0.330444335937500,
-0.984649658203125,
0.999969482421875,
-0.529296875000000,
0.257781982421875,
-0.576141357421875,
0.999969482421875,
-0.888092041015625,
0.186431884765625,
0.385528564453125,
-0.273773193359375,
-0.301452636718750,
0.689025878906250,
-0.594940185546875,
0.316406250000000,
-0.236999511718750,
0.325225830078125,
-0.250518798828125,
-0.132080078125000,
0.583648681640625,
-0.761840820312500,
0.573211669921875,
-0.205230712890625,
-0.100219726562500,
0.232513427734375,
-0.225158691406250,
0.181610107421875,
-0.196258544921875,
0.283447265625000,
-0.350982666015625,
0.278198242187500,
-0.043121337890625,
-0.253662109375000,
0.503356933593750,
-0.677917480468750,
0.764038085937500,
-0.666748046875000,
0.293487548828125,
0.238464355468750,
-0.581939697265625,
0.463165283203125,
-0.004882812500000,
-0.343597412109375,
0.251251220703125,
0.152496337890625,
-0.425598144531250,
0.289428710937500,
0.083007812500000,
-0.263244628906250,
0.025482177734375,
0.408264160156250,
-0.581909179687500,
0.271118164062500,
0.262115478515625,
-0.512817382812500,
0.268585205078125,
0.126708984375000,
-0.130157470703125,
-0.354217529296875,
0.794128417968750,
-0.609893798828125,
-0.109741210937500,
0.650909423828125,
-0.501464843750000,
-0.027709960937500,
0.198913574218750,
0.199096679687500,
-0.561798095703125,
0.256561279296875,
0.509368896484375,
-0.888610839843750,
0.441894531250000,
0.306671142578125,
-0.523101806640625,
0.074676513671875,
0.392303466796875,
-0.347320556640625,
0.023071289062500,
0.005340576171875,
0.328247070312500,
-0.476196289062500,
0.035278320312500,
0.681121826171875,
-1.000000000000000,
0.739624023437500,
-0.247772216796875,
-0.053710937500000,
0.216583251953125,
-0.506317138671875,
0.858978271484375,
-0.861145019531250,
0.304168701171875,
0.450927734375000,
-0.815429687500000,
0.610076904296875,
-0.219543457031250,
0.111755371093750,
-0.324523925781250,
0.483489990234375,
-0.256347656250000,
-0.290039062500000,
0.755615234375000,
-0.766082763671875,
0.287139892578125,
0.336181640625000,
-0.639526367187500,
0.424346923828125,
0.047210693359375,
-0.278900146484375,
0.038177490234375,
0.375915527343750,
-0.429901123046875,
-0.059997558593750,
0.707489013671875,
-0.962890625000000,
0.680541992187500,
-0.200561523437500,
-0.093872070312500,
0.158020019531250,
-0.171417236328125,
0.179840087890625,
-0.038879394531250,
-0.273864746093750,
0.476623535156250,
-0.275878906250000,
-0.205474853515625,
0.467773437500000,
-0.181213378906250,
-0.406402587890625,
0.724945068359375,
-0.511871337890625,
0.057586669921875,
0.208343505859375,
-0.238189697265625,
0.335327148437500,
-0.653656005859375,
0.920989990234375,
-0.772064208984375,
0.255126953125000,
0.170166015625000,
-0.169769287109375,
-0.068817138671875,
0.089141845703125,
0.252197265625000,
-0.603820800781250,
0.549407958984375,
-0.097473144531250,
-0.355804443359375,
0.488128662109375,
-0.343353271484375,
0.157257080078125,
-0.036956787109375,
-0.079467773437500,
0.218688964843750,
-0.285705566406250,
0.217864990234375,
-0.109222412109375,
0.090087890625000,
-0.141967773437500,
0.141662597656250,
-0.076446533203125,
0.086090087890625,
-0.236267089843750,
0.357818603515625,
-0.235382080078125,
-0.078735351562500,
0.290161132812500,
-0.246734619140625,
0.167602539062500,
-0.356323242187500,
0.740814208984375,
-0.874847412109375,
0.463043212890625,
0.237701416015625,
-0.668792724609375,
0.580291748046875,
-0.253509521484375,
0.094909667968750,
-0.151763916015625,
0.149414062500000,
0.061096191406250,
-0.268524169921875,
0.176422119140625,
0.191680908203125,
-0.474060058593750,
0.346466064453125,
0.155426025390625,
-0.681610107421875,
0.861572265625000,
-0.549560546875000,
-0.103149414062500,
0.715332031250000,
-0.868713378906250,
0.398559570312500,
0.415374755859375,
-1.000000000000000,
0.994293212890625,
-0.480743408203125,
-0.087890625000000,
0.408203125000000,
-0.550628662109375,
0.713348388671875,
-0.865081787109375,
0.770355224609375,
-0.360351562500000,
-0.073425292968750,
0.169799804687500,
0.068267822265625,
-0.257263183593750,
0.078582763671875,
0.357055664062500,
-0.666229248046875,
0.648651123046875,
-0.461761474609375,
0.329833984375000,
-0.215881347656250,
-0.091369628906250,
0.602508544921875,
-0.995361328125000,
0.943847656250000,
-0.512542724609375,
0.111694335937500,
-0.053192138671875,
0.240692138671875,
-0.349273681640625,
0.240661621093750,
-0.101318359375000,
0.171539306640625,
-0.436981201171875,
0.652313232421875,
-0.623321533203125,
0.388793945312500,
-0.126586914062500,
-0.044311523437500,
0.135620117187500,
-0.218902587890625,
0.342071533203125,
-0.493286132812500,
0.587707519531250,
-0.501525878906250,
0.201293945312500,
0.130065917968750,
-0.183715820312500,
-0.154571533203125,
0.593902587890625,
-0.671051025390625,
0.255249023437500,
0.261077880859375,
-0.374633789062500,
0.044158935546875,
0.266113281250000,
-0.138641357421875,
-0.326812744140625,
0.692108154296875,
-0.741516113281250,
0.680572509765625,
-0.747711181640625,
0.817077636718750,
-0.572509765625000,
0.022460937500000,
0.383819580078125,
-0.267059326171875,
-0.175445556640625,
0.352264404296875,
0.027191162109375,
-0.585571289062500,
0.690856933593750,
-0.161071777343750,
-0.548187255859375,
0.838287353515625,
-0.542938232421875,
-0.010284423828125,
0.401947021484375,
-0.484375000000000,
0.392578125000000,
-0.329650878906250,
0.404510498046875,
-0.608276367187500,
0.844909667968750,
-0.966217041015625,
0.846618652343750,
-0.491058349609375,
0.076721191406250,
0.146942138671875,
-0.040069580078125,
-0.313293457031250,
0.658203125000000,
-0.752990722656250,
0.551513671875000,
-0.243286132812500,
0.109893798828125,
-0.297119140625000,
0.689117431640625,
-0.998931884765625,
0.999969482421875,
-0.728332519531250,
0.407409667968750,
-0.289581298828125,
0.417572021484375,
-0.577453613281250,
0.468688964843750,
0.010711669921875,
-0.601287841796875,
0.838104248046875,
-0.455078125000000,
-0.325927734375000,
0.948028564453125,
-1.000000000000000,
0.590179443359375,
-0.103729248046875,
-0.152160644531250,
0.191864013671875,
-0.150817871093750,
0.050140380859375,
0.141754150390625,
-0.305389404296875,
0.215576171875000,
0.160888671875000,
-0.550537109375000,
0.672271728515625,
-0.576507568359375,
0.541168212890625,
-0.651916503906250,
0.669677734375000,
-0.397247314453125,
0.016326904296875,
0.126556396484375,
-0.006072998046875,
-0.051055908203125,
-0.116912841796875,
0.193878173828125,
0.185516357421875,
-0.804626464843750,
0.978851318359375,
-0.399841308593750,
-0.380615234375000,
0.549377441406250,
-0.015686035156250,
-0.483734130859375,
0.305419921875000,
0.338470458984375,
-0.721832275390625,
0.532653808593750,
-0.159667968750000,
0.057434082031250,
-0.138580322265625,
-0.003326416015625,
0.444671630859375,
-0.794219970703125,
0.706695556640625,
-0.285797119140625,
-0.130767822265625,
0.390869140625000,
-0.534271240234375,
0.496673583984375,
-0.104125976562500,
-0.557373046875000,
0.998229980468750,
-0.778350830078125,
0.051757812500000,
0.532623291015625,
-0.512237548828125,
0.060241699218750,
0.294494628906250,
-0.261077880859375,
-0.012725830078125,
0.231170654296875,
-0.259460449218750,
0.137084960937500,
0.037567138671875,
-0.130889892578125,
-0.009399414062500,
0.409729003906250,
-0.851043701171875,
0.999969482421875,
-0.754272460937500,
0.226165771484375,
0.344268798828125,
-0.802215576171875,
0.999969482421875,
-0.772064208984375,
0.116577148437500,
0.565063476562500,
-0.748352050781250,
0.350067138671875,
0.134735107421875,
-0.222259521484375,
0.045471191406250,
-0.129791259765625,
0.590576171875000,
-0.868927001953125,
0.459106445312500,
0.319610595703125,
-0.616058349609375,
0.109161376953125,
0.557006835937500,
-0.578643798828125,
-0.005004882812500,
0.425170898437500,
-0.223785400390625,
-0.193084716796875,
0.191528320312500,
0.194305419921875,
-0.337890625000000,
-0.082214355468750,
0.619842529296875,
-0.635498046875000,
0.086029052734375,
0.505432128906250,
-0.753051757812500,
0.779815673828125,
-0.843536376953125,
0.875823974609375,
-0.616516113281250,
0.082580566406250,
0.364898681640625,
-0.465698242187500,
0.375213623046875,
-0.420135498046875,
0.661437988281250,
-0.854583740234375,
0.793975830078125,
-0.534637451171875,
0.248840332031250,
-0.009460449218750,
-0.196990966796875,
0.341552734375000,
-0.363586425781250,
0.274963378906250,
-0.133758544921875,
-0.082305908203125,
0.441345214843750,
-0.845275878906250,
0.985717773437500,
-0.655212402343750,
0.058074951171875,
0.344604492187500,
-0.330413818359375,
0.128723144531250,
-0.072387695312500,
0.165191650390625,
-0.152862548828125,
-0.031036376953125,
0.111267089843750,
0.139801025390625,
-0.510589599609375,
0.543975830078125,
-0.114807128906250,
-0.357391357421875,
0.361938476562500,
0.125061035156250,
-0.621551513671875,
0.666168212890625,
-0.264709472656250,
-0.184204101562500,
0.303222656250000,
-0.028198242187500,
-0.420715332031250,
0.747863769531250,
-0.772186279296875,
0.513641357421875,
-0.153289794921875,
-0.119842529296875,
0.262237548828125,
-0.375488281250000,
0.549377441406250,
-0.743255615234375,
0.851348876953125,
-0.846160888671875,
0.793579101562500,
-0.732604980468750,
0.616424560546875,
-0.405212402343750,
0.154296875000000,
0.053924560546875,
-0.228973388671875,
0.434356689453125,
-0.629943847656250,
0.657135009765625,
-0.449859619140625,
0.191802978515625,
-0.143981933593750,
0.306518554687500,
-0.359802246093750,
0.021697998046875,
0.580566406250000,
-0.983154296875000,
0.845733642578125,
-0.295654296875000,
-0.200683593750000,
0.273437500000000,
0.046752929687500,
-0.398895263671875,
0.421447753906250,
-0.053619384765625,
-0.417755126953125,
0.612335205078125,
-0.417419433593750,
0.115081787109375,
-0.095794677734375,
0.419006347656250,
-0.724243164062500,
0.644989013671875,
-0.254394531250000,
-0.024383544921875,
-0.039794921875000,
0.184844970703125,
-0.013275146484375,
-0.438842773437500,
0.688537597656250,
-0.409301757812500,
-0.116638183593750,
0.302307128906250,
0.048767089843750,
-0.527587890625000,
0.632934570312500,
-0.344360351562500,
0.065399169921875,
-0.087829589843750,
0.288513183593750,
-0.371307373046875,
0.245452880859375,
-0.057006835937500,
-0.053161621093750,
0.063598632812500,
0.035583496093750,
-0.287719726562500,
0.612060546875000,
-0.722259521484375,
0.379425048828125,
0.259246826171875,
-0.687866210937500,
0.544830322265625,
-0.005035400390625,
-0.412353515625000,
0.408752441406250,
-0.183502197265625,
0.123107910156250,
-0.311187744140625,
0.449005126953125,
-0.248962402343750,
-0.192321777343750,
0.475677490234375,
-0.328582763671875,
-0.098785400390625,
0.376007080078125,
-0.210815429687500,
-0.278198242187500,
0.685302734375000,
-0.694183349609375,
0.335357666015625,
0.103851318359375,
-0.384338378906250,
0.491699218750000,
-0.516540527343750,
0.437622070312500,
-0.123931884765625,
-0.423126220703125,
0.918762207031250,
-0.999145507812500,
0.599426269531250,
-0.056091308593750,
-0.224243164062500,
0.169311523437500,
-0.059814453125000,
0.163452148437500,
-0.434509277343750,
0.614685058593750,
-0.567138671875000,
0.420318603515625,
-0.381652832031250,
0.494140625000000,
-0.632080078125000,
0.691955566406250,
-0.703002929687500,
0.731414794921875,
-0.737976074218750,
0.594482421875000,
-0.242736816406250,
-0.199005126953125,
0.513732910156250,
-0.572296142578125,
0.449676513671875,
-0.362945556640625,
0.482299804687500,
-0.773010253906250,
0.999969482421875,
-0.953643798828125,
0.578033447265625,
-0.088684082031250,
-0.230743408203125,
0.228851318359375,
0.046722412109375,
-0.435699462890625,
0.766540527343750,
-0.885131835937500,
0.677612304687500,
-0.164794921875000,
-0.419311523437500,
0.730499267578125,
-0.589752197265625,
0.169372558593750,
0.144134521484375,
-0.115051269531250,
-0.117523193359375,
0.202880859375000,
0.032409667968750,
-0.378509521484375,
0.448181152343750,
-0.099884033203125,
-0.357879638671875,
0.424346923828125,
0.084350585937500,
-0.778564453125000,
0.999969482421875,
-0.502838134765625,
-0.300170898437500,
0.649047851562500,
-0.245208740234375,
-0.428344726562500,
0.630706787109375,
-0.199371337890625,
-0.262542724609375,
0.109588623046875,
0.535491943359375,
-0.873443603515625,
0.368255615234375,
0.569488525390625,
-1.000000000000000,
0.520416259765625,
0.311340332031250,
-0.647583007812500,
0.333648681640625,
0.005737304687500,
0.183502197265625,
-0.690246582031250,
0.844818115234375,
-0.389190673828125,
-0.207824707031250,
0.355712890625000,
-0.059722900390625,
-0.152770996093750,
-0.052947998046875,
0.412628173828125,
-0.457977294921875,
0.145294189453125,
0.111846923828125,
-0.005889892578125,
-0.285736083984375,
0.390502929687500,
-0.259185791015625,
0.182861328125000,
-0.303985595703125,
0.341125488281250,
0.031921386718750,
-0.636993408203125,
0.857849121093750,
-0.336700439453125,
-0.541503906250000,
0.999969482421875,
-0.729797363281250,
0.090881347656250,
0.297149658203125,
-0.264221191406250,
0.111816406250000,
-0.102294921875000
};


void copyData(double *a, double *b, int len){
    int i;
    for(i=0;i<len;i++){
        b[i]=a[i];
    }
}

double * enhance(double *x, double *y, int len){
    double *d;
    double alpha=0.3;
    d=(double *)malloc(sizeof(double)*(len-1));
    int j;
    for(j=0;j<len-1;j++){
        d[j]=0;
    }
    copyData(x,y,len);
    for(j=0;j<len-1;j++){
        d[j]=(x[j+1]-x[j])*alpha;
    }
    for(j=1;j<len-1;j++){
        y[j]=x[j-1]+d[j-1]+d[j-1]*d[j-1]/( d[j-1]*d[j-1]+d[j]*d[j] ) *( x[j+1]-x[j-1] -d[j]-d[j-1]) ;
    }
    free(d);
    return y;
}

double maxVal(double *y,int len){
    int i;
    double m=-1;
    for(i=0;i<len;i++){
        if(m<y[i]){
            m=y[i];
        }
        if(m<-y[i]){
            m=-y[i];
        }
    }
    return m;
}



void lsp2lpc (double *lsp, double *a, const int m)
{
   int i, k, mh1, mh2, flag_odd;
   double xx, xf, xff;
   static double *f = NULL, *p, *q, *a0, *a1, *a2, *b0, *b1, *b2;
   static int   size;

   flag_odd = 0;
   if (m%2==0)
      mh1 = mh2 = m / 2;
   else {
      mh1 = (m + 1) / 2;
      mh2 = (m - 1) / 2;
      flag_odd = 1;
   }

   if (f==NULL) {
      f = (double*)malloc( (5*m+6) *sizeof(double) );
      for(i=0;i<5*m+6;i++){
          f[i]=0.0f;
      }
      p  = f  + m;
      q  = p  + mh1;
      a0 = q  + mh2;
      a1 = a0 + (mh1+1);
      a2 = a1 + (mh1+1);
      b0 = a2 + (mh1+1);
      b1 = b0 + (mh2+1);
      b2 = b1 + (mh2+1);
      size = m;
   }
   if (m>size) {
      free(f);
      f = (double*)malloc( (5*m+6) *sizeof(double) );
      p  = f  + m;
      q  = p  + mh1;
      a0 = q  + mh2;
      a1 = a0 + (mh1+1);
      a2 = a1 + (mh1+1);
      b0 = a2 + (mh1+1);
      b1 = b0 + (mh2+1);
      b2 = b1 + (mh2+1);
      size = m;
   }
    for(i=0;i<m;i++){
        f[i]=lsp[i];
    }
   for (i=k=0; i<mh1; i++,k+=2)
      p[i] = -2.0 * cos( f[k]);
   for (i=k=0; i<mh2; i++,k+=2)
      q[i] = -2.0 * cos( f[k+1]);
   xx = 1.0;
   xf = xff = 0.0;
   for (k=0; k<=m; k++) {
      if (flag_odd) {
         a0[0] = xx;
         b0[0] = xx - xff;
         xff = xf;
         xf  = xx;
      }
      else {
         a0[0] = xx + xf;
         b0[0] = xx - xf;
         xf = xx;
      }

      for (i=0; i<mh1; i++) {
         a0[i+1] = a0[i] + p[i] * a1[i] + a2[i];
         a2[i] = a1[i];
         a1[i] = a0[i];
      }
      for (i=0; i<mh2; i++) {
         b0[i+1] = b0[i] + q[i] * b1[i] + b2[i];
         b2[i] = b1[i];
         b1[i] = b0[i];
      }

      if (k!=0)
         a[k-1] = -0.5 * (a0[mh1] + b0[mh2]);

      xx = 0.0;
   }
   for (i=m-1; i>=0; i--)
      a[i+1] = -a[i];
   a[0] = 1.0;
   return;
}

void LpcFilter(double *lpc, int order, double *buff,int qingzhuo){
    int i,j,k;
    for(i=0;i<FrameLength;i++){
        buff[i]=0;
        for(j=1;j<=order;j++){
            k=i-j;
            if(k>=0){
                buff[i]-=buff[k]*lpc[j];
            }
        }
        if(qingzhuo==0){
            //buff[i]+=(double)rand()/RAND_MAX-0.5;
            double temp_d = (double)rand()/RAND_MAX-0.5;
            buff[i] += temp_d;
            /*
            if(temp_d >= 0.5 || temp_d <= -0.5)
            {
                printf("%f ",temp_d);
            }
            */

        }
        else{
            if(i<80){
                buff[i]+= pulseZhuo_Low[i];
            }
            buff[i]+= pulseZhuo_High[polseHighPos]/8;
            polseHighPos++;
            if(polseHighPos==1024){
                polseHighPos=0;
            }
        }
    }
}

double filter(double *b,double *a,double *input,double *buff,int bOrder,int aOrder,int frameLen){
    int i,j,k;
    double m=0;
    for(i=0;i<frameLen;i++){
        buff[i]=0;
        for(j=0;j<=bOrder;j++){
            k=i-j;
            if(k>=0){
                buff[i]+=b[j]*input[i-j];
            }
        }

        for(j=1;j<=aOrder;j++){
            k=i-j;
            if(k>=0){
                buff[i]-=a[j]*buff[i-j];
            }
        }
        if(buff[i]>m){
            m=buff[i];
        }
        if(-buff[i]>m){
            m=-buff[i];
        }
    }
    return m;
}


double HighPassFilter(double *input,double *buff,int frameLen){
    double b[]={1,-5,10,-10,5,-1};
    double a[]={1.0,-4.872922289230946,9.499726110519886,-9.261332241695410,
                4.515182753749494,-0.880654245646732};
    return filter(b,a,input,buff,5,5,frameLen);
}

double * LPCSynth(double **lsp, double *lf0, int order, int frameNum,int *len){
    double *y,*buff,*pbuff,*hpbuff;
    int id=1;
    int iid,qz;
    double *plsp,*elsp,pgn,plf0,*lpc;
    double max,pmax;
    int i;
    int length=0.9*frameNum*80+FrameLength;



    *len = length;
    y=(double *) malloc(sizeof(double)*length );
    buff=(double *) malloc(sizeof(double)*FrameLength );
    hpbuff=(double *) malloc(sizeof(double)*FrameLength );
    elsp=(double *) malloc(sizeof(double)*order );




    for(i=0;i<length;i++){
        y[i]=0;
    }
    lpc=(double *)malloc(sizeof(double)*25);
    while(id<length-FrameLength){
        iid=(id*frameNum)/(length-FrameLength);

        if(iid>=frameNum){
            iid=frameNum-1;
        }
        plsp=lsp[iid];
        plf0=lf0[iid];
        pgn=exp(lsp[iid][0]);
        qz=(plf0==0);

        enhance(plsp+1,elsp,order);
        lsp2lpc (elsp, lpc, order);
        LpcFilter(lpc, order, buff,1-qz);
        pmax=HighPassFilter(buff,hpbuff,FrameLength);
        max=maxVal(buff,FrameLength);

        for(i=0;i<=FrameLength;i++){
            if(qz){
                y[id+i]+=hpbuff[i] *max/pmax  *wwqing[i]*(pgn);
            }
            else{
                y[id+i]+=hpbuff[i] *max/pmax   *wwzhuo[i]* sqrt(16000/exp(plf0))*(pgn);
            }
        }
        if(plf0!=0){
            id=id+16000/exp(plf0);
        }
        else{
            id=id+40;
        }
    }
    free(buff);
    free(hpbuff);
    free(elsp);

    max=maxVal(y,length-160-FrameLength);
    for(i=0;i<length;i++){
        y[i]=y[i]/max;
    }
    return y;
}