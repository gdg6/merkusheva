//программа для подсчета кол-ва строк, непустых строк, однострочных и многострочных комментариев.

#include <iostream>
#include <memory>
#include <thread>

//класс для подсчета кол-ва строк.на базе конечного автомата.
class CalculationLines {
	
	 enum {
		START_STATE, 
		FINISH_STATE,
		BETWEEN_STATE, 
		ONE_BACK_STATE,
		ONELINE_COMMENT_STATE,
		ONE_BREACKET_STATE,
		DOUBLE_BREACKET_STATE,
		MULTILINE_COMMENT_STATE,
		MULTILINE_COMMENT_START_STATE,
		MULTILINE_COMMENT_FINISH_STATE,
		ONE_SYMBOL_SKIP_STATE
	};
	
	int state;
	int oldState;
	int countLine = 0;
	int countEmptyLine = 0;
	int countComments = 0;
	bool flagMultiComment;
	bool flagEnter = false;
	int maxNestingLevel = 0;
	int currentNestingLevel = 0;
	
	void checkOnEmptyLine(char c)
	{
		if(c == '\n' && flagEnter)
		{
			this -> countEmptyLine++;
		} else flagEnter = false;
		
		if(c == '\n') {
			countLine++;
			flagEnter = true;
		}
	}
	
	void processState(char c)
	{
		switch(this->state)
			{
				case START_STATE: 
				case BETWEEN_STATE: 
					if(c == '/') this -> state = ONE_BACK_STATE;
					if(c == '"') this -> state = DOUBLE_BREACKET_STATE;
					if(c == '\'') this -> state = ONE_BREACKET_STATE;
					break;
					
				case ONE_SYMBOL_SKIP_STATE: 
					state = oldState;
					break; //3
					
				case DOUBLE_BREACKET_STATE: 
					if(c == '"') this -> state = BETWEEN_STATE;
					break;
			
				case ONE_BREACKET_STATE: 
					if( c == '\\')  
					{
						oldState = state;
						state = ONE_SYMBOL_SKIP_STATE;
					}
					if(c == '\'') this -> state = BETWEEN_STATE;
					break;
							
				case ONE_BACK_STATE: 
					if(c == '/') this -> state = ONELINE_COMMENT_STATE;
					if(c == '*') this -> state = MULTILINE_COMMENT_START_STATE;
					if( c != '/' &&  c != '*') this -> state = BETWEEN_STATE;
					break;
			
				case ONELINE_COMMENT_STATE:
					if(c == '\n') {
						this -> state = BETWEEN_STATE;
						countComments++;
						//4
					}
					break;
			
				case MULTILINE_COMMENT_START_STATE:
					if(c == '*')
						this -> state = MULTILINE_COMMENT_FINISH_STATE;
					break;
			
				case MULTILINE_COMMENT_FINISH_STATE: 
					if(c == '/')
					{
						this -> state = BETWEEN_STATE;
						countComments ++;
					} else {
						this -> state = MULTILINE_COMMENT_START_STATE;
					}
					break;					
			}
	}
	
public: 
	CalculationLines()
	{
	 this->state = START_STATE;
	}

	void nextStep(char c)
	{
		checkOnEmptyLine(c);
		processState(c);
	}
	
	int getCountLine()
	{
		return this -> countLine;
	}	
	
	int getCountComments()
	{
		return this -> countComments;
	}
	
	int getCountEmptyLines()
	{
		return this -> countEmptyLine;
	}		
	
	int getMaxNestingLevel(){
		return this -> maxNestingLevel;
	}
};


class ProcessingData {
private: 
	CalculationLines * machine;
	
public: 
	ProcessingData(CalculationLines * machine)
	{
		this->machine = machine;	
	}

	void processData()
	{
		char c;
		while((c = std::cin.get())!=EOF)
		{
			machine -> nextStep(c);
		}
	}
	
	void printStatistic()
	{
		std::cout << "Lines: " <<  machine -> getCountLine() << std::endl; 
		std::cout << "Empty lines: " <<  machine -> getCountEmptyLines() << std::endl; 
		std::cout << "Not empty lines: " << machine -> getCountLine() - machine -> getCountEmptyLines() << std::endl; 
		std::cout << "Count comment: " << machine -> getCountComments() << std::endl; 	
	}
	
	~ProcessingData() 
	{
		delete machine;
	}
};

int main()
{
	CalculationLines * m = /* 8 
				извращенный 
				комментарий */ new CalculationLines();
	
	ProcessingData * p = new ProcessingData(m);
	p -> processData();
	p -> printStatistic();
	delete p;
	return 0;
}
