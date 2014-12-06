#ifndef _CALC_NEST_LEVEL
#define _CALC_NEST_LEVEL
#include <iostream>

class CalculationNestingLevel
{
private:

	enum {
		START_STATE,
		BETWEEN_STATE,
		IF_EXPECTANCY_STATE,
		FOR_EXPECTANCY_STATE,
		WHILE_EXPECTANCY_STATE,
		WAIT_CLOSE_NESTING_LEVEL,
		WAIT_CLOSE_ROUND_BREACKET_STATE,
		WAIT_OPEN_ROUND_BREACKET_IF_STATE,
		WAIT_CLOSE_ROUND_BREACKET_IF_STATE,
	};

	int state;
	int currenNesingtLevel = 0;
	int maxNestingLevel = 0;

	char lastChar = 0;
	
public:
	CalculationNestingLevel()
	{
		this->state = START_STATE;
	}
	
	int getMaxNestingLevel()
	{
		return this->maxNestingLevel;
	}
	
	void processStateFromChar(char c)
	{
		switch(this -> state)
		{
			
			case START_STATE:
			case BETWEEN_STATE:
				if(c == 'i') state = IF_EXPECTANCY_STATE;
				if(c == 'f') state = FOR_EXPECTANCY_STATE;
				if(c == 'w') state = WHILE_EXPECTANCY_STATE;
				break;		
				
			case IF_EXPECTANCY_STATE:
				if(c == 'f') state = WAIT_OPEN_ROUND_BREACKET_IF_STATE;
				else state = BETWEEN_STATE;
				break;
				
			case WAIT_OPEN_ROUND_BREACKET_IF_STATE:
				if(( lastChar == ' ' || lastChar == 'f') && c == '(')
				{ 
						state = WAIT_CLOSE_ROUND_BREACKET_STATE;
				} else state = BETWEEN_STATE;
				break;
				
			case WAIT_CLOSE_ROUND_BREACKET_STATE:
				if(c == ')') state = BETWEEN_STATE;
				currenNesingtLevel ++;
				break;
				
			//В прошлый раз закончил здесь.
		}
		lastChar = c;
	}
};

#endif

void f()
{
		if(1) 
{
			if(1)
			{
				int a = 1;
//				std::cout << a;
			}
}	
}







