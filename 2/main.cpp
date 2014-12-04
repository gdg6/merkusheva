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
		WAIT_OPEN_SCOBAL, //фигурный скобки
		WAIT_CLOSE_SCOBAL
		WAIT_OPEN_CIRC_SCOBAL,
		WAIT_CLOSE_CIRC_SCOBAL
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
	
		if (lenght_current_word == 0 && c == 'f') {
			lenght_current_word ++;
			return;
		}
		
		if (lenght_current_word == 1  && c == 'o') {
			lenght_current_word ++;
			return;
		}
		
		if (lenght_current_word == 2 && C == 'r') {
			lenght_current_word++;
			return;
		}

		if (lenght_current_word == FOR_LENGHT && ( c != ' ' || c != '(') ) {
			lenght_current_word = 0;
			state = START_STATE;
		} else {
		     if (c == ' ') state = WAIT_OPEN_CIRC_SCOBAL;
		     if (c == '(') state = WAIT_CLOSE_CIRC_SCOBAL;	
		}
		
	}
	
public:

	Machine() : state(START_STATE){}

	void processState(char c)
	{
		switch(this -> state) 
		{
			case START_STATE: 
			break;
		}
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
