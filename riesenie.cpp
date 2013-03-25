#include <iostream>
#include <sstream>
#include <cmath>
#include <vector>

using namespace std;

// #include "riesenie.h"

#if !defined( _RIESENIE_H_ )
#define _RIESENIE_H_

#include <string>

using namespace std;

class ZlyFormatException{};

class CisloMimoException{};

struct TVyraz
{
	long long prvy, druhy;
	char op;
	TVyraz(long long prvy, long long druhy, long long op) : prvy(prvy), druhy(druhy), op(op) {}
};

class RIMSKA_KALKULACKA {	
 public:
	TVyraz parsuj(string vyraz);
	string kalkulackaRimska(string vyraz);
	long long roman2decimal(string s);
	string decimal2roman(long long c);
	long long part2dec(string c, string oft);
	string part2roman(long long a, string oft);
};

const string CISLO_MIMO = "Cislo mimo povolenych hodnot";
const string ZLY_VYRAZ = "Zly vstupny vyraz";

#endif

const string trojice[] = {"IVX", "XLC", "CDM", "MPQ", "QRS", "STU", "UWY", "YZE", "EFG"};
const long long POCET_TROJIC = 9;
const long long MAX_CISLO = 3999999999;
const long long MIN_CISLO = -3999999999;
const char NAJVACSIE_PISMENO = 'G';
const long long HODNOTA_NAJVACSIEHO_PISMENA = 1000000000;

string RIMSKA_KALKULACKA::kalkulackaRimska(string vyr) {
	string ret = "";
	try
	{
		TVyraz v = parsuj(vyr);
		long long result;
		switch (v.op)
		{
			case '+': result = v.prvy + v.druhy;
				break;
			case '-': result = v.prvy - v.druhy;
				break;
			case '*': result = v.prvy * v.druhy;
				break;
			case '/': 
				if(v.druhy == 0) throw new CisloMimoException();
				result = v.prvy / v.druhy;
				break;
			case '&': result = v.prvy && v.druhy;
				break;
			case '|': result = v.prvy || v.druhy;
				break;
			case '>': result = v.prvy > v.druhy;
				break;
			case '<': result = v.prvy < v.druhy;
				break;
			case '=': result = v.prvy == v.druhy;
				break;

		}
		ret = decimal2roman(result);
	}
	catch (ZlyFormatException *e)
	{
		ret = ZLY_VYRAZ;
	}
	catch (CisloMimoException *e)
	{
		ret = CISLO_MIMO;
	}
  	return ret;
}

TVyraz RIMSKA_KALKULACKA::parsuj(string v)
{
	//nastav povolene znaky
	/* mame pole povolene znaky kde:
	 *	0 - su nepovolene znaky
	 *	1 - su cislice
	 *	2 - su operatory
	 */
	char povoleneZnaky[255];
	for (long long i = 0; i < 255; ++i) povoleneZnaky[i]=0;
	char cislice[] = {'O','I','V','X','L','C','D','M','P','Q','R','S','T','U','W','Y','Z','E','F','G'};
	char operatory[] = {'+','-','*','/'	,'&', '|', '>','<','='};
	for (long long i = 0; i < sizeof(cislice); ++i) povoleneZnaky[cislice[i]]=1;
	for (long long i = 0; i < sizeof(operatory); ++i) povoleneZnaky[operatory[i]]=2;

	//rozdel string na 3 casti
	string s[2];
	char op;

	long long part = 0;

	string vv;
	for (long long i = 0; i < v.size(); ++i)
	{
		if(v[i]==' ') continue;
		vv+=v[i];
	}

	v = vv;
	long long prve_minus = (v[0] == '-') ? 1 : 0;
	long long druhe_minus = 0;
	for (long long i = prve_minus; i < v.size(); ++i)
	{
		if ( povoleneZnaky[v[i]]==0)
		{
			throw new ZlyFormatException();
		}		
		if(povoleneZnaky[v[i]]==1) s[part]+=v[i];
		if(povoleneZnaky[v[i]]==2) 
		{	
			part++;
			op = v[i];
			if (v[i+1] == '-') 
			{
				druhe_minus = 1;
				i++;
			}
		}
		if (part>1)		
		{
			throw new ZlyFormatException();
		}
	}	

	//skonvertuj cisla a vrat vyraz + skontroluj spravny format rimskeho cisla
	TVyraz vyraz = TVyraz(roman2decimal(s[0]),roman2decimal(s[1]),op);
	if (prve_minus == 1)
	{
		vyraz.prvy *= -1;
	}
	if (druhe_minus == 1)
	{
		vyraz.druhy *= -1;
	}
	return vyraz;
}

long long RIMSKA_KALKULACKA::roman2decimal(string s)
{
	if (s == "") throw new ZlyFormatException();

	if (s=="O") return 0;

	vector<long long> kon(POCET_TROJIC+1, s.size());
	
	long long part = 0;
	for (long long i = 0; i < s.size(); ++i)
	{
		if (part == 0 && s[i] != NAJVACSIE_PISMENO) 
		{
			kon[0] = i;
			part++; // fixne DM
		}
		
		for (long long j = 1; j < POCET_TROJIC; ++j)
		{
			if (part == j && s[i] != trojice[POCET_TROJIC-j][0] && s[i] != trojice[POCET_TROJIC-j][1] && s[i] != trojice[POCET_TROJIC-j][2]) 
			{
				kon[j] = i;
				part++;
			}	
		}
		
		if (part == POCET_TROJIC && s[i] != 'I' && s[i] != 'V' && s[i] != 'X') 
		{
			throw new ZlyFormatException();
		}
	}
	long long result;

	if (kon[0]>3) throw new ZlyFormatException();

	result = (kon[0])*HODNOTA_NAJVACSIEHO_PISMENA;
	for (long long i = 0; i < POCET_TROJIC; ++i)
	{
		result += part2dec(s.substr(kon[i], kon[i+1]-kon[i]), trojice[POCET_TROJIC-i-1])*pow(10, POCET_TROJIC-i-1);
	}
	return result;
}

long long RIMSKA_KALKULACKA::part2dec(string s, string oft)
{
	char one = oft[0];
	char five = oft[1];
	char ten = oft[2];

	long long dlzka = s.size();
	if (dlzka > 4) throw new ZlyFormatException();
	if (dlzka == 2)
	{
		if (s[0] == one)
		{
			if (s[1] == five)
			{
				return 4;
			}
			if (s[1] == ten)
			{
				return 9;
			}
			return 2;
		}
	}
	long long r = 0, i = 0;
	if (s[0] == five)
	{
		r = 5;
		i++;
	}
	if (s.size() - i >3) throw new ZlyFormatException();
	while (i<s.size())
	{
		if (s[i] != one) throw new ZlyFormatException();
		r++;		
		i++;
	}
	return r;
}

string RIMSKA_KALKULACKA::decimal2roman(long long c)
{
	if (c > MAX_CISLO || c < MIN_CISLO) throw new CisloMimoException();
	if (c==0) return "O";
	string ret = "";
	
	int cc = c<0;
	c=abs(c);

	for (long long i = 0; i < POCET_TROJIC; ++i)
	{
		ret = part2roman(c % 10, trojice[i]) + ret;
		c /= 10;		
	}

	for(long long i=0; i<c; i++)
	{
		ret = NAJVACSIE_PISMENO + ret;
	}

	if(cc) ret = "-" + ret;

	return ret;
}

string RIMSKA_KALKULACKA::part2roman(long long a, string oft)
{	
	char one = oft[0];
	char five = oft[1];
	char ten = oft[2];

	if (a == 4) {
		string s = "";
		s+= one;
		s+=five;
		return s;
	}
	if (a == 9) {
		string s = "";
		s+= one;
		s+=ten;
		return s;
	}
	string ret = "";
	if (a >= 5) 
	{
		ret = five;
		a-=5;
	}
	for(long long i=0; i<a; i++)
	{
		ret += one;
	}
	return ret;
}



