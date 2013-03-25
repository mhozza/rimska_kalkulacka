#include <iostream>
#include <cstring>
#include <string>

using namespace std;

#include "riesenie.h"
#include "tester.h"

void testyRimskaKalkulacka() {

  nastavSledovanieSkupiny("Testy rimskej kalkulacky");

  RIMSKA_KALKULACKA kalkulacka;  
  testEqual("II", kalkulacka.kalkulackaRimska("I + I"),"vypocet"); 
  testEqual("XX", kalkulacka.kalkulackaRimska("V * IV"),"vypocet"); 
  testEqual("XXXVIII", kalkulacka.kalkulackaRimska("D / XIII"),"vypocet"); 
  testEqual("MCCCXXIX", kalkulacka.kalkulackaRimska("MDCCXVI - CCCLXXXVII"),"vypocet"); 
  testEqual("MMMCMXCIX", kalkulacka.kalkulackaRimska("MMMCMXC + IX"),"vypocet"); 
  testEqual("I", kalkulacka.kalkulackaRimska("II - I"),"vypocet");


  testEqual("XX", kalkulacka.kalkulackaRimska(" XI + I X "),"vypocet"); 
  testEqual("V", kalkulacka.kalkulackaRimska("XXV/V"),"vypocet"); 
  testEqual("MCCXXII", kalkulacka.kalkulackaRimska(" MMCDXLIV - MCCXXII "),"vypocet"); 
  testEqual("XX", kalkulacka.kalkulackaRimska(" XI + I X "),"vypocet"); 
  testEqual("XX", kalkulacka.kalkulackaRimska(" XI + I X "),"vypocet"); 

  testEqual("PX", kalkulacka.kalkulackaRimska("MMM + MMX"),"");  
  testEqual("-CMXC", kalkulacka.kalkulackaRimska("MMX - MMM"),"");  
  testEqual("PM", kalkulacka.kalkulackaRimska("MMM * II"),"");  
  testEqual("O", kalkulacka.kalkulackaRimska("XXX / D"),"");  
  testEqual("O", kalkulacka.kalkulackaRimska("  MCDXLIV / MCDXLV"),"");  

  testEqual("I", kalkulacka.kalkulackaRimska("  -O = O"),"");  


  testEqual(CISLO_MIMO, kalkulacka.kalkulackaRimska("X / O"),"");    
 
  testEqual(ZLY_VYRAZ, kalkulacka.kalkulackaRimska("234567890"),"");    
  testEqual(ZLY_VYRAZ, kalkulacka.kalkulackaRimska(" MD "),"");    
  testEqual(ZLY_VYRAZ, kalkulacka.kalkulackaRimska(" MMMM + I "),"");    


  zhodnotenieVysledkov();
}


void testyParsovania()
{
  nastavSledovanieSkupiny("Testy parsovania");

  RIMSKA_KALKULACKA kalkulacka;
  testEqual(TVyraz(1,1,'+'), kalkulacka.parsuj("I + I"),"");
  testEqual(TVyraz(1505,516,'+'), kalkulacka.parsuj("   M DV+D  XVI "),"");
  testEqual(TVyraz(1554,131,'-'), kalkulacka.parsuj("  MD LI V - CX   XXI"),"");
  testEqual(TVyraz(1463,545,'-'), kalkulacka.parsuj(" MCD  L XIII-DXLV"),"");
  testEqual(TVyraz(356,904,'*'), kalkulacka.parsuj("CCC LVI* C  MIV"),"");
  testEqual(TVyraz(508,52,'*'), kalkulacka.parsuj("DVI I  I* LII"),"");
  testEqual(TVyraz(1,1580,'/'), kalkulacka.parsuj("I/MD LX   XX"),"");
  testEqual(TVyraz(1006,524,'/'), kalkulacka.parsuj("MV I/D XX IV"),"");
  testEqual(TVyraz(80,1506,'-'), kalkulacka.parsuj("LXX X-M  DVI"),"");
  testEqual(TVyraz(47,42,'*'), kalkulacka.parsuj("XLV II*  XLI I"),"");

  testEqual(TVyraz(1002,-60,'+'), kalkulacka.parsuj("MII + - LX"),"");  
  testEqual(TVyraz(-1002,-60,'+'), kalkulacka.parsuj("-MII + - LX"),"");  
  testEqual(TVyraz(-1002,60,'+'), kalkulacka.parsuj(" - MII + LX"),"");  
  testEqual(TVyraz(-1002,-60,'-'), kalkulacka.parsuj(" - MII -- LX"),"");  

  testEqual(TVyraz(-1002,0,'-'), kalkulacka.parsuj(" - MII -- O"),"");  
  testEqual(TVyraz(-1002,0,'-'), kalkulacka.parsuj(" - MII -- O"),"");

  try
  {
    testEqual(TVyraz(0,0,'~'), kalkulacka.parsuj("EEG"),"");  
  }
  catch (ZlyFormatException *e)
  {
    testTrue(1,"");
  }
  try
  {
    testEqual(TVyraz(0,0,'~'), kalkulacka.parsuj("GGGG"),"");  
  }
  catch (ZlyFormatException *e)
  {
    testTrue(1,"");
  }
  try
  {
  	testEqual(TVyraz(0,0,'~'), kalkulacka.parsuj("MUUU"),"");  
  }
  catch (ZlyFormatException *e)
  {
  	testTrue(1,"");
  }
  try
  {
  	testEqual(TVyraz(0,0,'~'), kalkulacka.parsuj("VII"),"");  
  }
  catch (ZlyFormatException *e)
  {
  	testTrue(1,"");
  }
  try
  {
    testEqual(TVyraz(0,0,'~'), kalkulacka.parsuj("V # V"),"");  
  }
  catch (ZlyFormatException *e)
  {
    testTrue(1,"");
  }  
  try
  {
  	testEqual(TVyraz(0,0,'~'), kalkulacka.parsuj("EZSDXFG"),"");  
  }
  catch (ZlyFormatException *e)
  {
  	testTrue(1,"");
  }
  try
  {
  	testEqual(TVyraz(0,0,'~'), kalkulacka.parsuj(" M-II + LX"),"");  
  }
  catch (ZlyFormatException *e)
  {
  	testTrue(1,"");
  }
  try
  {
    testEqual(TVyraz(0,0,'~'), kalkulacka.parsuj(" --MII + LX"),"");  
  }
  catch (ZlyFormatException *e)
  {
    testTrue(1,"");
  }

  try
  {
    testEqual(TVyraz(0,0,'~'), kalkulacka.parsuj(" MII --- LX"),"");  
  }
  catch (ZlyFormatException *e)
  {
    testTrue(1,"");
  }

  try
  {
  	testEqual(TVyraz(0,0,'~'), kalkulacka.parsuj("V+"),"");  
  }
  catch (ZlyFormatException *e)
  {
  	testTrue(1,"");
  }
  try
  {
  	testEqual(TVyraz(0,0,'~'), kalkulacka.parsuj("D - V*"),"");  
  }
  catch (ZlyFormatException *e)
  {
  	testTrue(1,"");
  }
  try
  {
  	testEqual(TVyraz(0,0,'~'), kalkulacka.parsuj("I ++ V"),"");  
  }
  catch (ZlyFormatException *e)
  {
  	testTrue(1,"");
  }
  try
  {
  	testEqual(TVyraz(0,0,'~'), kalkulacka.parsuj("-I V"),"");  
  }
  catch (ZlyFormatException *e)
  {
  	testTrue(1,"");
  }

  try
  {
  	testEqual(TVyraz(0,0,'~'), kalkulacka.parsuj("/MI - X"),"");  
  }
  catch (ZlyFormatException *e)
  {
  	testTrue(1,"");
  }

  try
  {
  	testEqual(TVyraz(0,0,'~'), kalkulacka.parsuj("M-DVII+XX"),"");  
  }
  catch (ZlyFormatException *e)
  {
  	testTrue(1,"");
  }

  try
  {
  	testEqual(TVyraz(0,0,'~'), kalkulacka.parsuj("LVII"),"");  
  }
  catch (ZlyFormatException *e)
  {
  	testTrue(1,"");
  }

  try
  {
  	testEqual(TVyraz(0,0,'~'), kalkulacka.parsuj("LVII"),"");  
  }
  catch (ZlyFormatException *e)
  {
  	testTrue(1,"");
  }

  try
  {
  	testEqual(TVyraz(0,0,'~'), kalkulacka.parsuj("MMIIV + D"),"");  
  }
  catch (ZlyFormatException *e)
  {
  	testTrue(1,"");
  }

  zhodnotenieVysledkov();
}

void testyPart2dec()
{
  nastavSledovanieSkupiny("Testy part2dec");

  RIMSKA_KALKULACKA kalkulacka;
  testEqual(0, kalkulacka.part2dec("","IVX"),"");
  testEqual(1, kalkulacka.part2dec("I","IVX"),"");
  testEqual(2, kalkulacka.part2dec("II","IVX"),"");
  testEqual(3, kalkulacka.part2dec("III","IVX"),"");
  testEqual(4, kalkulacka.part2dec("IV","IVX"),"");
  testEqual(5, kalkulacka.part2dec("V","IVX"),"");
  testEqual(6, kalkulacka.part2dec("VI","IVX"),"");
  testEqual(7, kalkulacka.part2dec("VII","IVX"),"");
  testEqual(8, kalkulacka.part2dec("VIII","IVX"),"");
  testEqual(9, kalkulacka.part2dec("IX","IVX"),"");

  try
  {
  	testEqual(-1, kalkulacka.part2dec("IXI","IVX"),"");  
  }
  catch (ZlyFormatException *e)
  {
  	testTrue(1,"");
  }
  try
  {
  	testEqual(-1, kalkulacka.part2dec("VX","IVX"),"");  
  }
  catch (ZlyFormatException *e)
  {
  	testTrue(1,"");
  }
  try
  {
  	testEqual(-1, kalkulacka.part2dec("IIII","IVX"),"");  
  }
  catch (ZlyFormatException *e)
  {
  	testTrue(1,"");
  }
  try
  {
  	testEqual(-1, kalkulacka.part2dec("IIV","IVX"),"");  
  }
  catch (ZlyFormatException *e)
  {
  	testTrue(1,"");
  }
  try
  {
  	testEqual(-1, kalkulacka.part2dec("VV","IVX"),"");  
  }
  catch (ZlyFormatException *e)
  {
  	testTrue(1,"");
  }
  try
  {
  	testEqual(-1, kalkulacka.part2dec("IVII","IVX"),"");  
  }
  catch (ZlyFormatException *e)
  {
  	testTrue(1,"");
  }
  try
  {
  	testEqual(-1, kalkulacka.part2dec("VIIII","IVX"),"");  
  }
  catch (ZlyFormatException *e)
  {
  	testTrue(1,"");
  }

  zhodnotenieVysledkov();
}


void testyPart2roman()
{
  nastavSledovanieSkupiny("Testy part2roman");

  RIMSKA_KALKULACKA kalkulacka;
  testEqual(""    , kalkulacka.part2roman(0,"IVX"),"");  
  testEqual("I"   , kalkulacka.part2roman(1,"IVX"),"");  
  testEqual("II"  , kalkulacka.part2roman(2,"IVX"),"");  
  testEqual("III" , kalkulacka.part2roman(3,"IVX"),"");  
  testEqual("IV"  , kalkulacka.part2roman(4,"IVX"),"");  
  testEqual("V"   , kalkulacka.part2roman(5,"IVX"),"");  
  testEqual("VI"  , kalkulacka.part2roman(6,"IVX"),"");  
  testEqual("VII" , kalkulacka.part2roman(7,"IVX"),"");  
  testEqual("VIII", kalkulacka.part2roman(8,"IVX"),"");  
  testEqual("IX"  , kalkulacka.part2roman(9,"IVX"),"");  

  /*
  try
  {
  	testEqual("---", kalkulacka.part2roman(10,"IVX"),"");  
  }
  catch (ZlyFormatException *e)
  {
  	testTrue(1,"");
  }

  try
  {
  	testEqual("---", kalkulacka.part2roman(-1,"IVX"),"");  
  }
  catch (ZlyFormatException *e)
  {
  	testTrue(1,"");
  }

  try
  {
  	testEqual("---", kalkulacka.part2roman(47,"IVX"),"");  
  }
  catch (ZlyFormatException *e)
  {
  	testTrue(1,"");
  }
  */


  zhodnotenieVysledkov();
}


void testyDecimal2roman()
{
  nastavSledovanieSkupiny("Testy Decimal2roman");

  RIMSKA_KALKULACKA kalkulacka;
  testEqual("XLVII", kalkulacka.decimal2roman(47),"");
  testEqual("XLIV", kalkulacka.decimal2roman(44),"");
  testEqual("M", kalkulacka.decimal2roman(1000),"");
  testEqual("MDCCLVIII", kalkulacka.decimal2roman(1758),"");
  testEqual("MMMCMXCIX", kalkulacka.decimal2roman(3999),"");
  testEqual("I", kalkulacka.decimal2roman(1),"");
  testEqual("CDXLIV", kalkulacka.decimal2roman(444),"");
  testEqual("MMDXXIII", kalkulacka.decimal2roman(2523),"");
  testEqual("DLV", kalkulacka.decimal2roman(555),"");
  testEqual("MMMDCCCLXXXVIII", kalkulacka.decimal2roman(3888),"");
  testEqual("MMMCXLII", kalkulacka.decimal2roman(3142),"");
  testEqual("MMMV", kalkulacka.decimal2roman(3005),"");
  testEqual("C", kalkulacka.decimal2roman(100),"");
  testEqual("M", kalkulacka.decimal2roman(1000),"");
  testEqual("MX", kalkulacka.decimal2roman(1010),"");
  testEqual("CCVIII", kalkulacka.decimal2roman(208),"");

  try
  {
  	testEqual("---", kalkulacka.decimal2roman(0),"");  
  }
  catch (CisloMimoException *e)
  {
  	testTrue(1,"");
  }
  try
  {
  	testEqual("---", kalkulacka.decimal2roman(4000),"");  
  }
  catch (CisloMimoException *e)
  {
  	testTrue(1,"");
  }
  try
  {
  	testEqual("---", kalkulacka.decimal2roman(-20),"");  
  }
  catch (CisloMimoException *e)
  {
  	testTrue(1,"");
  }


  zhodnotenieVysledkov();
}

void testyroman2dec()
{
  nastavSledovanieSkupiny("Testy roman2decimal");

  RIMSKA_KALKULACKA kalkulacka;
  testEqual(1324, kalkulacka.roman2decimal("MCCCXXIV"),"");
  testEqual(1004, kalkulacka.roman2decimal("MIV"),"");
  testEqual(37, kalkulacka.roman2decimal("XXXVII"),"");
  testEqual(666, kalkulacka.roman2decimal("DCLXVI"),"");
  testEqual(1900, kalkulacka.roman2decimal("MCM"),"");
  testEqual(1090, kalkulacka.roman2decimal("MXC"),"");
  testEqual(1, kalkulacka.roman2decimal("I"),"");
  testEqual(3999, kalkulacka.roman2decimal("MMMCMXCIX"),"");
  testEqual(3888, kalkulacka.roman2decimal("MMMDCCCLXXXVIII"),"");
  testEqual(200, kalkulacka.roman2decimal("CC"),"");
  testEqual(707, kalkulacka.roman2decimal("DCCVII"),"");
  testEqual(90, kalkulacka.roman2decimal("XC"),"");
  testEqual(1000, kalkulacka.roman2decimal("M"),"");
  testEqual(21, kalkulacka.roman2decimal("XXI"),"");
  testEqual(1539, kalkulacka.roman2decimal("MDXXXIX"),"");
  testEqual(555, kalkulacka.roman2decimal("DLV"),"");
  testEqual(444, kalkulacka.roman2decimal("CDXLIV"),"");
  testEqual(1020, kalkulacka.roman2decimal("MXX"),"");

  try
  {
  	testEqual(-1, kalkulacka.roman2decimal("MID"),"");  
  }
  catch (ZlyFormatException *e)
  {
  	testTrue(1,"");
  }
  try
  {
  	testEqual(-1, kalkulacka.roman2decimal("VIM"),"");  
  }
  catch (ZlyFormatException *e)
  {
  	testTrue(1,"");
  }
  try
  {
  	testEqual(-1, kalkulacka.roman2decimal("MMIIII"),"");  
  }
  catch (ZlyFormatException *e)
  {
  	testTrue(1,"");
  }
  try
  {
  	testEqual(-1, kalkulacka.roman2decimal("MMDMM"),"");  
  }
  catch (ZlyFormatException *e)
  {
  	testTrue(1,"");
  }
  try
  {
  	testEqual(-1, kalkulacka.roman2decimal("XM"),"");  
  }
  catch (ZlyFormatException *e)
  {
  	testTrue(1,"");
  }
  try
  {
  	testEqual(-1, kalkulacka.roman2decimal("MMMM"),"");  
  }
  catch (ZlyFormatException *e)
  {
  	testTrue(1,"");
  }
  try
  {
  	testEqual(-1, kalkulacka.roman2decimal("IXI"),"");  
  }
  catch (ZlyFormatException *e)
  {
  	testTrue(1,"");
  }
  try
  {
  	testEqual(-1, kalkulacka.roman2decimal("IIV"),"");  
  }
  catch (ZlyFormatException *e)
  {
  	testTrue(1,"");
  }
  try
  {
  	testEqual(-1, kalkulacka.roman2decimal("MMDCCCIXVII"),"");  
  }
  catch (ZlyFormatException *e)
  {
  	testTrue(1,"");
  }
  try
  {
  	testEqual(-1, kalkulacka.roman2decimal("MCMCCII"),"");  
  }
  catch (ZlyFormatException *e)
  {
  	testTrue(1,"");
  }
  try
  {
  	testEqual(-1, kalkulacka.roman2decimal("MLIIC"),"");  
  }
  catch (ZlyFormatException *e)
  {
  	testTrue(1,"");
  }
  try
  {
  	testEqual(-1, kalkulacka.roman2decimal("DXXXIVV"),"");  
  }
  catch (ZlyFormatException *e)
  {
  	testTrue(1,"");
  }
  try
  {
  	testEqual(-1, kalkulacka.roman2decimal("CMD"),"");  
  }
  catch (ZlyFormatException *e)
  {
  	testTrue(1,"");
  }
  try
  {
  	testEqual(-1, kalkulacka.roman2decimal("XMDVIIXI"),"");  
  }
  catch (ZlyFormatException *e)
  {
  	testTrue(1,"");
  }
    try
  {
  	testEqual(-1, kalkulacka.roman2decimal("VIIVIMMMIM"),"");  
  }
  catch (ZlyFormatException *e)
  {
  	testTrue(1,"");
  }
  try
  {
  	testEqual(-1, kalkulacka.roman2decimal("DMIMIDMXXL"),"");  
  }
  catch (ZlyFormatException *e)
  {
  	testTrue(1,"");
  }
  try
  {
  	testEqual(-1, kalkulacka.roman2decimal(""),"");  
  }
  catch (ZlyFormatException *e)
  {
  	testTrue(1,"");
  }


  zhodnotenieVysledkov();
}
