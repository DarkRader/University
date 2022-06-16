#include <fstream>
#include "CFloat.h"
#include "CFloatBig.h"
#include "CInteger.h"
#include "CIntegerBig.h"
#include "CParsData.h"
#include "CShuntYardAlg.h"

//static void errEntr() {
//    CParsData x;
//
//    assert(!x.parsingDate("21512 + 2152m21"));
//    //Syntax error in numbers or variables!
//    assert(!x.parsingDate("2152 {214 + 21}"));
//    //Syntax error, try again!
//    assert(!x.parsingDate("21251.21525 + 2152"));
//    //Syntax error, try again!
//    assert(!x.parsingDate("21521,2512 / 2125 + 21"));
//    //You can't divide by decimal float!
//    assert(!x.parsingDate("212+ -2152 * 21"));
//    //Two characters follow each other, check the location of the brackets!
//    assert(!x.parsingDate("*215 + 21"));
//    //The operation cannot be at the beginning of the expression!
//    assert(!x.parsingDate("2151 + (22125 + 2125"));
//    //There is an opening bracket, but no closing one!
//    assert(!x.parsingDate("21521 + 215251 * 212)"));
//    //You can't write a closing bracket without an opening one!
//    assert(!x.parsingDate(" 219421 + 2151 = 2152"));
//    //The equal sign is in the wrong place!
//    assert(!x.parsingDate("212512 / 2212 / 0"));
//    //You can't divide by zero!
//    assert(x.parsingDate("A = 2125"));
//    //Variable is equal: 2125
//    assert(!x.parsingDate("212 + A + B"));
//    //A nonexistent variable is present in the expression!
//    assert(!x.parsingDate("212(215 + 212)"));
//    //You don't have a sign in front of the brackets, check it out!
//    assert(!x.parsingDate("21212 * (2125 - 212) 212"));
//    //You don't have a sign after the brackets, check it out!
//    assert(!x.parsingDate("wad = 215"));
//    //Syntax error in numbers or variables!
//}
//
//static void exprTest() {
//    CParsData x;
//    assert(x.parsingDate("2152151,2512521 + 215212,5125 * 21470 - 21521518"));
//    //4601243276.6262521
//    assert(x.parsingDate("2125125125 + 2124124,21521 * 1242 - 215251,515 + (64 / 2)"));
//    //4763072180.77582
//    assert(x.parsingDate("2142 / 2 + (- 2124 * 212 / 2 - 2124) -2141 + 214 / 2"));
//    //-228231
//    assert(x.parsingDate("20184 + 21421 - 214 + (-21512 * 1512) + (36 / 6)"));
//    //-32484747
//    assert(x.parsingDate("12412 * (212 + 212 / 2) + (2122 - 212) * 212"));
//    //"4351936"
//    assert(x.parsingDate("12412*(212+212/2)+(2122-212)*212"));
//    //"4351936"
//    assert(x.parsingDate("1 + 2*(3+4 / 2- (1+2)) * 2 + 1"));
//    //"10"
//    assert(x.parsingDate("(4*(2*(3+5))+7-(8+8)+1)/2"));
//    //"28"
//    assert(x.parsingDate("(3*0)+5*(6*3/3)"));
//    //"30"
//    assert(x.parsingDate("215,5212 + 4212,22 * 251,5 - (2125 - 2152,21) + 215,21"));
//    //"1059831.2712"
//    assert(x.parsingDate("(((2+3))) / 1 + 2 -3"));
//    //"4"
//    assert(x.parsingDate("(1+5*0-3-4+5/5)*0*3/1"));
//    //"0"
//    assert(x.parsingDate("(1+5*0-3-4+5/5) + 3 - 7 - (-7)"));
//    //"-2"
//    assert(x.parsingDate("7 + 8 - 9 * 3 + 4*(-5 + 3 - 12 / 4) * 7 + 8 * 0"));
//    //"-152"
//    assert(x.parsingDate("(25-4)/7+5*(12-3)"));
//    //"48"
//}
//
//static void testWorkVar() {
//    CParsData x;
//    assert(x.parsingDate("A = 215,5212 + 4212,22 * 251,5 - (2125 - 2152,21) + 215,21"));
//    //"1059831.2712"
//    assert(x.parsingDate("A + 214,512"));
//    //1060045,7832
//    assert(x.parsingDate("A = 2152"));
//    //Variable is equal: 2152
//    assert(x.parsingDate("B = 21212"));
//    //Variable is equal: 21212
//    assert(x.parsingDate("A + B + 212 * 2"));
//    //Result: 23788
//    assert(x.parsingDate("C = A + B + 212 * 2"));
//    //Variable is equal: 23788
//    assert(x.parsingDate("C + 12"));
//    //Result: 23800
//    assert(x.parsingDate("C + A + B * (21 - 21)"));
//    //Result: 25940
//}
//
//static void testBigNum() {
//    CParsData x;
//
//    assert(x.parsingDate("8946389845829385293853859 + 32936533235235235232535232"));
//    //41882923081064620526389091
//    assert(x.parsingDate("353453475347464586738467387464347563845738 + 28538467475645679845645986948576846584654654654"));
//    //28538820929121027310232725415964310932218500392
//    assert(x.parsingDate("778476796843052983530496458796854907896087905480974975498579048579548978540974597894059784095 + 3982759834694634636738467438763846943764843786739467834768347863784683"));
//    //778476796843052983530500441556689602530724643948413739345522813423335718008809366241923568778
//    assert(x.parsingDate("2581782675816726175261725861725617856217561257  - 2125167251725162571251521251521"));
//    //2581782675816724050094474136563046604696309736
//    assert(x.parsingDate("389285638265836825963852639325 - 215222845838435434584349732875823795329523592935"));
//    //-215222845838435434195064094609986969365670953610
//    assert(x.parsingDate("-2716572618726572167561785 + (-212957015829175071285102581052)"));
//    //-212959732401793797857270142837
//    assert(x.parsingDate("981785792478938572383756827358238957826378 + 2815821825772165872172561256461784891727817895821905291025890182598195281982591859218598219258190"));
//    //2815821825772165872172561256461784891727817895821905292007675975077133854366348686576837177084568
//    assert(x.parsingDate("-2192657192518276262176261625182 + 182651725861927587218572815215"));
//    //-2010005466656348674957688809967
//    assert(x.parsingDate("8379867834976894587845887904879508497894 + (-29108257917285017825910782592837572753238538258329738527385792)"));
//    //-29108257917285017825902402725002595858650692370424859018887898
//    assert(x.parsingDate("-2714721647261478261762476127461278 + 128751825781275812785718758217851792578190257128258175872598918"));
//    //128751825781275812785718758215137070930928778866495699745137640
//    assert(x.parsingDate("332895978239572835782758783258923 * 2192051792571751925701975291501925701205215"));
//    //729725225839982556609036744947505834699553898053016426767893834986502883445
//    assert(x.parsingDate("716247617246712647126746127647126471278 * 0"));
//    //0
//    assert(x.parsingDate("0 * 92195821958291859285918250981958210952152018219421"));
//    //0
//    assert(x.parsingDate("83173825873582783592 * (-2819285618596821965819281925816592629128521)"));
//    //-234490771129068194175914310588790041012898944777628076298027432
//    assert(x.parsingDate("-5197251925718752178521598 * (-51251251251952718572815278175827582)"));
//    //266365664264706875100846250546478455900290594980928911116036
//    assert(x.parsingDate("-13296205928105892189258198259128582901 * 10953820958302983592593235235"));
//    //-145644259161198695345941949384396270979592415715145496164491716735
//    assert(x.parsingDate("81962591562816251962851672582618521925 / 182795817825971258102517025790"));
//    //Result: 448383297 (rem. 88195887027607124560264292295)
//    assert(x.parsingDate("-2891685691265291856219421412414214214214 / (-2190727519257017520519275214214214124)"));
//    //Result: 1319 (rem. 2497404865665784658)
//    assert(x.parsingDate("2819682462189648291648261468219462198418902740174 / (-492184628196248948217804621421421)"));
//    //-5728912080255694 (rem. 425193974422912853325883493919000)
//    assert(x.parsingDate("-27815725487154281745271845725184218482 / 21752491745721547215487512842"));
//    //Result: -1278737434 (rem. 9124129980429498494563091054)
//    assert(x.parsingDate("98261829691825918259182752752969421846482194214 / 29107492179471024791270497120414421"));
//    //Result: 3375826027400 (rem. 25680804661156260137667560381058814)
//    assert(x.parsingDate("3375826027400 * 29107492179471024791270497120414421"));
//    //98261829691800237454521596492831754286101135400
//    assert(x.parsingDate("98261829691825918259182752752969421846482194214 - 98261829691800237454521596492831754286101135400"));
//    //25680804661156260137667560381058814
//    assert(x.parsingDate("0 / 8269184618946814482894124"));
//    //0
//    assert(!x.parsingDate("2901825615268206581252910752971925710 / 0"));
//    //warning! -- You can't divide by zero!
//    assert(x.parsingDate("62198478174987294178472874819724819748918,88214961924164729174267461724671247 + 29812789461264281984269462196428149,219642192486914286184296"));
//    //62198507987776755442754859089187016177068.10179181172856157792697061724671247
//    assert(x.parsingDate("-819682629164862174647162846128468912468912,940712084710274912749172471824 + (-72147251724587154725847157824,7241672451862546146254174)"));
//    //-819682629164934321898887433283194759626737.664879329896529527374589871824
//    assert(x.parsingDate("982168562981652918526185692816958126956928,52957180567182965162569186258162589 - 28169598169528651826591526819562295017295,950217957192075992501"));
//    //953998964812124266699594165997395831939632.57935384847975365912469186258162589
//    assert(x.parsingDate("271672628164274812456128545521874728,2891642861846281964821964 - 72198654276147627861489264819648268416824618469298641864928641986248,741285745217452785472185427571254821"));
//    //-72198654276147627861489264819647996744196454194486185736383120111520.452121459032824588989989027571254821
//    assert(x.parsingDate("-4092174029174247190472974129749210492142144421,2091479170924719042904721049414214421 + 29107491749274192749172491729407192479,1274891720497120479120794"));
//    //-4092174000066755441198781380576718762734951942.0816587450427598563783927049414214421
//    assert(x.parsingDate("2901479207149274192074917204971947029174092794172947921421,482167482071846128648216846218064 + (-82164862149621846912864821684612846281,49821684261846281648194221)"));
//    //2901479207149274191992752342822325182261227972488335075139.983950639453383312166274636218064
//    assert(x.parsingDate("21294861924148329173872189343242432,3902193729130217932143243 * 921740921740972194721042124,842174826184692184241"));
//    //19628345658311213649553862480933583169063407973628355741856300.9252837224322560047597540
//    assert(x.parsingDate("281946281948216948621894621894682,9420719407921704927194712094709412 * 29174971947294712904790127492179472194790127490127904712094729017490,924719274917942790172947912794721904"));
//    //8225774866483275190461451207002995234929535711586097830508468946217950884373400466807501979831602938.471986918391384806250626937919038007
//    assert(x.parsingDate("-291074972194729174927419072940,8472194871298748217847218468216498689421 * (-82164879628146826482168461284689216478921,7849219674621846281689426892164)"));
//    //23916140053146107148185778532350221343596969367743652861812655675949683.8099358432324390922995902880517975372867
//}

//function for history output
void greeting(void)
{
    std::cout << "Welcome to calculation with unlimited accuracy!" << std::endl;
    std::cout << std::endl;
    std::cout << "Rules for using the calculator: " << std::endl;
    std::cout << std::endl;
    std::cout << "You can use any of the following operators - '+', '-', '*', '/' and expressions inside brackets, that is, using - '(', ')'." << std::endl;
    std::cout << std::endl;
    std::cout << "You can also use variables and use the = sign to assign any expressions," << std::endl << "in the future you can use variables in your calculations, but for variables" << std::endl << "you can only use the letters 'A-Z' and 'a-z' the size of the letters plays a role," << std::endl << "you can also change values inside variables " << std::endl;
    std::cout << std::endl;
    std::cout << "Also pay attention to the use of a minus sign, you cannot write: '5 - -3'," << std::endl << "but you can write it using brackets: '5 - (-3)'" << std::endl;
    std::cout << std::endl;
    std::cout << "In the program, you cannot divide float decimal numbers," <<
    std::endl << "when using float decimal numbers, use a comma, for example '21525,2112'" << std::endl;
    std::cout << std::endl;
    std::cout << "The program has the ability to download and download the history of the calculator to download write 'download history' in small letters, without whitespaces, " << std::endl << "give a name to the file where you want to save the history." << std::endl;
    std::cout << std::endl;
    std::cout << "If you want to upload a story that you downloaded, write 'upload story' in small letters, without whitespaces,"  << std::endl << "write the name of the file where you downloaded it, in addition to the history of upload and variables that you assigned" << std::endl;
    std::cout << std::endl;
    std::cout << "To completit the program, write 'quit' in small letters" << std::endl;
    std::cout << std::endl;
}

//a function for transcoding the history from a standard file to a file that the user will create
void copyAnotherFile(const std::string & fileName)
{
    
    std::ofstream os;
    os.open(fileName);
    
    std::ifstream inFile("text.txt", std::ios::in);
    
    if(!inFile)
        return;
    
    std::string buffer;

    getline(inFile, buffer);
    while(!buffer.empty())
    {
        os << buffer << std::endl;
        buffer.clear();
        getline(inFile, buffer);
    }
    
    os.close();
}

//a function for displaying the history from the file that the user is trying to download
void uploadHistory(const std::string & fileName, CParsData & x)
{
    std::ifstream inFile(fileName, std::ios::in);
    
    if(!inFile) {
        std::cout << "There is no such file!" << std::endl;
        return;
    }
    
    std::string buffer;
    getline(inFile, buffer);
    while(!buffer.empty())
    {
        std::cout << buffer << std::endl;
        x.parsingDate(buffer);
        buffer.clear();
        getline(inFile, buffer);
    }
}

//a function that responds to a user's request to download or upload history
bool commandUser(std::string & commandUser, std::string & renamed, std::ofstream & os, CParsData & x)
{
    if(commandUser == "dowload history") {
        std::cout << "Write down what your file will be called" << std::endl;
        renamed = "Yes";
        return true;
    }
    
    if(renamed == "Yes") {
        os.close();
        commandUser += ".txt";
        copyAnotherFile(commandUser);
        os.open("text.txt");
        renamed = "No";
        return true;
    }
    
    if(commandUser == "upload history") {
        std::cout << "Enter the name of the file whose history you want to upload" << std::endl;
        renamed = "Ready";
        return true;
    }
    
    if(renamed == "Ready") {
        commandUser += ".txt";
        uploadHistory(commandUser, x);
        renamed = "No";
        return true;
    }
    
    return false;
}

int main() {
    
    //asserts for control program
//    errEntr();
//    exprTest();
//    testWorkVar
//    testBigNum();
    
    greeting();
    
    std::string operaceCal;
    CParsData x;
    std::ofstream os;
    os.open("text.txt");
    std::string renamed = "No";
    
    while(operaceCal != "quit") {
        std::getline(std::cin, operaceCal);
        
        if(std::cin.eof()) {
            break;
        }
        
        if(commandUser(operaceCal, renamed, os, x) == true)
            continue;
        
        if(x.parsingDate(operaceCal) == false)
            continue;

        if(operaceCal != "quit")
            os << operaceCal << std::endl;

    }
    
    os.close();

    
    return EXIT_SUCCESS;
}
