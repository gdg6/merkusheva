//~ 1. Написать программу для подсчета метрик размера программы: количества исполняемых операторов 
//~ в программе, числа функций, среднего объема функций.


//В С/C++ операторы оканчиваются на ";" Программа написана исходя из предположения что на вход идет корректно-правильная программа.
// т.е. int a  = 1;  - правильно, int a  = 1;; - не правильно


#include <iostream>
#include <memory>
#include <thread>

#define LENGHT_CLASS 5

class Machine
{
private:
	enum {
		  START_STATE, 
		  FINISH_STATE,
		  FUNCTION_STATE, 
		  CLASS_STATE
		  FOR_STATE,
		  WHILE_STATE,
		  DO_STATE, 
		  SWITCH_STATE, 
		  IF_STATE,
		  BETWEEN_STATE
		  OPERATOR_STATE
		  };
	//general
	int state;
	int countMetric;
	int countFunc;
	
	//helpers
	int lenght_word;
	bool prev_space;
	
	void stepClass(char c)
	{
		if()
	}
	
public: 
	Machine() : state(START_STATE), countMetric(0), countFunc(0),  lenght_word(0), prev_space(true)
	{
	}
	
	void processState(char c)
	{
		//step machine
		switch(c)
		{
			case START_STATE:
				if(c != ' '){
					prev_space = false;
				} else {
					prev_space = true;
					break;
				}
				if(c == 'c') state = CLASS_STATE;
				//int float double short
				if((c == 'i' || c == 'f' ||c == 'd' || c == 's') && prev_space) state = OPERATOR_STATE;
				
			break;
		}
	}
	
	void nextStep(char c)
	{
		processState(c);
	}
	
	int getCountMetric()
	{
		return countMetric;
	}
	
	int getCountFunc()
	{
		return countFunc;
	}
	
};


class Processing 
{
	Machine machine;
private: 

	
public:
	
	void Run()
	{
		char c;
		while((c = std::cin.get())!=EOF)
		{
			machine.nextStep(c);
		}
	}
	
	void printStatistic()
	{
		std::cout << "Count Metric: " <<  machine.getCountMetric() << std::endl; 
		std::cout << "Count Func: " <<  machine.getCountFunc() << std::endl; 
		std::cout << "the average volume: " << ((float)machine.getCountMetric())/machine.getCountFunc() << std::endl; 
	}
	
};


int main()
{
	Processing p;
	p.Run();
	p.printStatistic();
return 0;
}
