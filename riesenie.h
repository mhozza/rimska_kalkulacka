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
