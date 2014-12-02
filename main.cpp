#include <iostream>
#include "CalculationLines.cpp"
#include "CalculationNestingLevel.cpp"
#include "ProcessingData.cpp"


//1
//данная программа уровень вложенности считает по {}. (2)

void f(){}

int main()
{
	f(/* 7 просто коммент */);
	CalculationLines * m = /* 8 
				извращенный 
				комментарий */ new CalculationLines();
	
	ProcessingData * p = new ProcessingData(m);
	p -> processData();
	p -> printStatistic();
	delete p;
	return 0;
}
