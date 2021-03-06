#ifndef _PROC_DATA
#define _PROC_DATA

#include <cstdio>

class ProcessingData {
private: 
	CalculationLines * machine;
	CalculationNestingLevel * nestingLevelMachine = NULL;
	
public: 
	ProcessingData(CalculationLines * machine)
	{
		this->machine = machine;	
	}

	ProcessingData(CalculationLines * machine, CalculationNestingLevel * nestingLevelMachine)
	{
		this -> machine = machine;
		this -> nestingLevelMachine = nestingLevelMachine;
	}

	void processData()
	{
		char c;
		while((c = std::cin.get())!=EOF)
		{
			machine -> nextStep(c);
			if(nestingLevelMachine != NULL)
				nestingLevelMachine -> processStateFromChar(c);
		}
	}
	
	void printStatistic()
	{
		std::cout << "Lines: " <<  machine -> getCountLine() << std::endl; 
		std::cout << "Empty lines: " <<  machine -> getCountEmptyLines() << std::endl; 
		std::cout << "Not empty lines: " << machine -> getCountLine() - machine -> getCountEmptyLines() << std::endl; 
		std::cout << "Count comment: " << machine -> getCountComments() << std::endl; 	
		std::cout << "Max nesting level: " << machine -> getMaxNestingLevel() << std::endl; 	
	}
	
	~ProcessingData() 
	{
		delete machine;
		if(nestingLevelMachine != NULL)
			delete nestingLevelMachine;
	}
};

#endif
