//программа для подсчета максимальной вложенности
//будем считать что все функции и циклы имеют {}
//программа для подсчета максимальной вложенности. 
// и программа не предусмотренна на обработку кода в строке, вроде: "void func(){}"
//и во входном листенге программы не учитываются комментарии. Т.к. не было сказано в задании.


#include <iostream>
#include <list>
#include <algorithm>
#include <vector>
#include <cstdio>

using std::cout;
using std::endl;

//lenght key words
#define FOR_LENGHT 3
#define WHILE_LENGHT 5
#define DO_LENGHT 2
#define IF_LENGHT 2
#define SWITCH_LENGHT 6
#define CLASS_LENGHT 5
#define ENUM_LENGH 4

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
		WAIT_CLOSE_SCOBAL,
		WAIT_OPEN_CIRC_SCOBAL,
		WAIT_CLOSE_CIRC_SCOBAL
	};
	
	//generals 
	int maxNestingLevel;
	int state;
	//контейней для скобок условной архитектуры вложенности. 
	std::vector<char> nestingScobals;
	
	//helpers
	int lenght_current_word;
	char before_be_space;
	enum {BEFORE_SPACE};
	int state_help;
	
	
	void checkOnFor(char c)
	{
		char word []  = "for";
		
		if(lenght_current_word > FOR_LENGHT) {
			state = START_STATE;
			return; //exception
		}
	
		if (word[lenght_current_word] == c && 
			FOR_LENGHT > lenght_current_word) {
			lenght_current_word ++;
			return;
		}
	
		// если уже нашли подстроку, проверка что это не часть слова.
		if (lenght_current_word == FOR_LENGHT && (c != ' ' || c != '(') ) {
			lenght_current_word = 0;
			state = START_STATE; //maybe oldstate
		} else {
		     if (c == ' ') {
				state = WAIT_OPEN_CIRC_SCOBAL;
				state_help = BEFORE_SPACE;
			 }
		     if (c == '(') state = WAIT_CLOSE_CIRC_SCOBAL;	
		}
		
	}
	
	void pushOpenScobal()
	{
		nestingScobals.push_back('{');
	}
	
	void pushCloseScobal()
	{
		nestingScobals.push_back('{');
	}
	
	void pushScobals()
	{
		pushOpenScobal();
		pushCloseScobal();
	}
	
public:

	Machine() : maxNestingLevel(0), 
				state(START_STATE), lenght_current_word(0),
				before_be_space(true) 
	{
	}

	void processState(char c)
	{
		switch(this -> state) 
		{
			case START_STATE: 
				if(c == 'f') { state = FOR_STATE; checkOnFor(c); break;}
				break;
			case FOR_STATE: 
				checkOnFor(c);
				break;
			case WAIT_CLOSE_CIRC_SCOBAL:
				if(c == ')') state = WAIT_OPEN_SCOBAL;
				break;
			case WAIT_OPEN_SCOBAL:
				if(c == ' ') break; //встретили пробел ничего не делаем. 
				//обработка типа: for(int a = 0; a < n; a++); 
				if (c == ';') {pushScobals(); state = START_STATE; break;}
				// обработка типа for(...) 
				//                    while(...) ...
				// и               for (...) {
				//                     while(...) { ...
				pushOpenScobal();
				state = WAIT_CLOSE_SCOBAL; 
				break;
				
		}
	}
	
	void postProcessing()
	{
		int currentNestingLevel = 0;
		int max = 0;
		//stupid way
		for(unsigned int i = 0; i < nestingScobals.size(); i++) {
			if(nestingScobals.at(i) == '{') currentNestingLevel++;
			if(max < currentNestingLevel) max = currentNestingLevel;
			if(nestingScobals.at(i) == '}') currentNestingLevel--;
		} 
		this -> maxNestingLevel = max;
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
		machine.postProcessing();
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
