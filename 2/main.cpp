//программа для подсчета максимальной вложенности
//будем считать что все функции и циклы имеют {}

//программа работает след образом: на вход пуступают данные. Их рассматриваем как  данные с вершины стека.
//внутри программы есть свой стек который будет хранить {} и в  конечном итогде в этом стеке необходимо будет найти максимальную вложенность.

#include <iostream>
#include <list>
#include <algorithm>

using std::cout;
using std::endl;


class Machine
{
	enum {
		START_STATE, 
		FOR_STATE, 
		IF_STATE, 
		DO_STATE, 
		WHILE_STATE, 
		FUNCTION_STATE
	};
	
	//generals 
	int currentNestingLevel = 0;
	int maxNestingLevel = 0;
	
	//helpers
	std::
	
public:

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
