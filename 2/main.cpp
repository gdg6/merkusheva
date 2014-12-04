//программа для подсчета максимальной вложенности
//будем считать что все функции и циклы имеют {}
//программа для подсчета максимальной вложенности. 
// и программа не предусмотренна на обработку кода в строке, вроде: "void func(){}"
//и во входном листенге программы не учитываются комментарии. Т.к. не было сказано в задании.

#include <iostream>
#include <list>
#include <algorithm>
#include <vector>

using std::cout;
using std::endl;

#define FOR_LENGHT 3

class Machine
{
	enum {
		START_STATE, 
		FOR_STATE, 
		IF_STATE, 
		DO_STATE, 
		WHILE_STATE, 
		FUNCTION_STATE,
		CLASS_STATE,
		WAIT_OPEN_SCOBAL,
		WAIT_CLOSE_SCOBAL
		WAIT_OPEN_CIRC_SCOBAL,
		WAIT_close_CIRC_SCOBAL
	};
	
	//generals 
	int currentNestingLevel = 0;
	int maxNestingLevel = 0;
	int state;
	//контейней для скобок условной архитектуры вложенности. 
	std::vector<char> nestingScobals;
	
	//helpers
	int lenght_current_word = 0;
	char before_be_space = true;
	enum {BEFORE_SPACE};
	int state_help;
	
	void checkOnFor(char c)
	{
		if(lenght_current_word > 3 && state_help == BEFORE_SPACE ) state
	
	}
	
public:

	Machine() : state(START_STATE){}

	void processState(char c)
	{
		
	}
	
	int getMaxNestingLevel()
	{
		return maxNestingLevel;
	}
};

class Processing
{
	Machine machine;
public:
	void processData()
	{
		char c;
		while((c = std::cin.get())!=EOF)
		{
			machine.processState(c);
		}
	}

	void printStatistic()
	{
		std::cout << "Max nesting level: " << machine.getMaxNestingLevel();
	}

};

int main()
{
	Processing p;
	p.processData();
	p.printStatistic();
	return 0;
}
