//программа для подсчета максимальной вложенности
//будем считать что все функции и циклы имеют {}
//программа для подсчета максимальной вложенности. 
// и программа не предусмотренна на обработку кода в строке, вроде: "void func(){}"
//и во входном листенге программы не учитываются комментарии. Т.к. не было сказано в задании.

// Фирма гарантирует правильную работу при правильных входных данных. Т.е. листинг программы должен быть корректен.

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
#define ENUM_LENGHT 4

#define INT_LENGHT 3
#define CHAR_LENGHT 4
#define VOID_LENGHT 4
#define FLOAT_LENGHT 5
#define DOUBLE_LENGHT 6
#define SHORT_LENGHT 5

class Machine
{
	enum {
		START_STATE, 
		FOR_STATE, 
		IF_STATE, 
		DO_STATE, 
		WHILE_STATE, 
		FUNCTION_STATE,
		INT_STATE, 
		VOID_STATE, 
		DOUBLE_STATE, 
		FLOAT_STATE,
		SHORT_STATE,
		CHAR_STATE,
		CLASS_STATE, 
		WAIT_OPEN_SCOBAL, //фигурный скобки
		WAIT_CLOSE_SCOBAL, 
		WAIT_OPEN_CIRC_SCOBAL, 
		WAIT_CLOSE_CIRC_SCOBAL, 
		WAIT_VARIABLE_OR_NAME_FUNCTION
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
	int count_functions;
	
// =============== BEGIN CHECKS ========================================

	void ciclCheck(char c, int size, char * word) {
		if(lenght_current_word < size) {
			if(word[lenght_current_word] == c) {
				lenght_current_word++;
				return;
			} else {
				lenght_current_word = 0;
				state = START_STATE;
				return;
			}
		} else {
			if(lenght_current_word == size) {
				if (c == ' ') {
					state = WAIT_OPEN_CIRC_SCOBAL;				
				} else if(c=='('){
					state = WAIT_CLOSE_CIRC_SCOBAL;
				} else {
					state = START_STATE;
				}
				lenght_current_word = 0;
				return;
			}
		}
	}

	void checkOnFor(char c)	{	
		if (c == 'f' && !lenght_current_word) {
			lenght_current_word++;
			return;
		}
		if(c == 'o' && lenght_current_word == 1) {
			lenght_current_word++;
			return;
		}		
		if(c == 'r' && lenght_current_word == 2) {
			state = WAIT_OPEN_CIRC_SCOBAL;
			lenght_current_word = 0;
			return;
		}
		if(c == 'l' && lenght_current_word == 1) {
			state = FLOAT_STATE;
			lenght_current_word++;
			return;
		}
		//надо обработать f o r ()
		if(lenght_current_word >= FOR_LENGHT) {
			if(c == ' ' ) return;
			if(c == '(') {
				state = WAIT_CLOSE_CIRC_SCOBAL;
				lenght_current_word = 0;
				return;
			}
		}
		state = START_STATE;
		lenght_current_word = 0;
	}
	
  	void checkOnIf(char c) {
		if(c == 'i' &&  lenght_current_word == 0) {
			lenght_current_word ++;
			return;
		}
		if(c == 'f' && lenght_current_word == 1) {
			state = WAIT_OPEN_CIRC_SCOBAL;
			lenght_current_word = 0;
			return;
		}
		if(c ==  'n' && lenght_current_word == 1) {
			state = INT_STATE;
			lenght_current_word++;
			return;
		}
		state = START_STATE;
		lenght_current_word = 0;
	}
	
	void checkOnWhile(char c) {
		char word[] = "while";
		ciclCheck(c, WHILE_LENGHT, word);
	}
	
// ======================= CHECK VARIABLE OR FUNCTION ==================	
   //последний раз остановился здесь. Не срабатывает проверка на функцию (объявление)
	void checkOnInt(char c ) {
		char word[] = "int";
		if(lenght_current_word < INT_LENGHT) {
			if(word[lenght_current_word] == c) {
				lenght_current_word++;
				return;
			} else {
				if(c == 'f' && lenght_current_word == 1) {
					state = IF_STATE;
					lenght_current_word++;
					return;
				} else { // это не ключевое слово. 
					lenght_current_word = 0;
					state = START_STATE;
				} 
			}
		} else { 
			if (c == ' ' && lenght_current_word == INT_LENGHT) {
				state = WAIT_VARIABLE_OR_NAME_FUNCTION;
				return;
			} else { // это не ключевое слово. 
				state = START_STATE;
				lenght_current_word = 0;
				return;
			}
		}
	}

    void varCheck(char c, int lenght, char * word) {
		if(lenght_current_word < lenght) {
			if(word[lenght_current_word] == c) {
				lenght_current_word++;
				return;
			} else {
				lenght_current_word = 0;
				state = START_STATE;
				return;
			}
		} else {
			if(lenght_current_word == lenght && c == ' ') {
				state = WAIT_VARIABLE_OR_NAME_FUNCTION;
				return;
			} else {
				state = START_STATE;
				lenght_current_word = 0;
				return;
			}
		}	
	} 

	void checkOnVoid(char c) {
		char word[] = "void";
		varCheck(c, VOID_LENGHT, word);
	}
	
	void checkOnFloat(char c) {
		char word[]  = "float";
		varCheck(c, FLOAT_LENGHT, word);
	}
	
	void checkOnDouble(char c) {
		char word[] = "double";
		varCheck(c, DOUBLE_LENGHT, word);
    }
	
	void checkOnShort(char c) {
		char word[]  = "short";
		varCheck(c, SHORT_LENGHT, word);
	}
	
	void checkOnChar(char c) {
		char word[] = "char";
		varCheck(c, CHAR_LENGHT, word);
	}
	
	void checkOnVeriableOrFunction(char c) {
		if (c == ' ') return;
		if (c == '=' || c == ';') {
			state = START_STATE; //это объявление переменной
			return;
		}
		if(c == '(') {
			state = WAIT_CLOSE_CIRC_SCOBAL; //объявление функции
			count_functions++;
			return;
		}
	}
	
// ======================= END CHECK VARIABLE OR FUNCTION ==================	
	
// ========================== END CHECK ================================
	
	void pushOpenScobal()
	{
		nestingScobals.push_back('{');
	}
	
	void pushCloseScobal()
	{
		nestingScobals.push_back('}');
	}
	
	void pushScobals()
	{
		pushOpenScobal();
		pushCloseScobal();
	}
	
public:

	Machine() : maxNestingLevel(0), 
				state(START_STATE), lenght_current_word(0),
				before_be_space(true), count_functions(0)
	{
	}

	void processState(char c)
	{
		switch(this -> state) 
		{
			case START_STATE: 
				if (c == 'f' ) {state = FOR_STATE; checkOnFor(c); break;}
				if (c == 'i' ) {state = IF_STATE; checkOnIf(c); break;}
				if (c == 'w' ) {state = WHILE_STATE; checkOnWhile(c); break;}
				if (c == 'c') {state = CHAR_STATE; checkOnChar(c);break;}
				if (c == 's' ) {state = SHORT_STATE; checkOnShort(c);break;}
				if (c == 'd' ) {state = DOUBLE_STATE; checkOnDouble(c); break;}
				break;
			case FOR_STATE: 
				checkOnFor(c);
				break;
			case IF_STATE:
			    checkOnIf(c);
			    break;
			case WHILE_STATE:
			    checkOnWhile(c);
			    break;
			case CHAR_STATE:
				checkOnChar(c);
			case SHORT_STATE:
			    checkOnShort(c);
			    break;
			case INT_STATE:
			    checkOnInt(c);
			    break;
			case VOID_STATE:
			    checkOnVoid(c);
			    break;
			case FLOAT_STATE:
				checkOnFloat(c);
			case DOUBLE_STATE:
			    checkOnDouble(c);
			    break;
			case WAIT_OPEN_CIRC_SCOBAL:
				if(c == '(') {
					state = WAIT_CLOSE_CIRC_SCOBAL;
				}
				break;
			case WAIT_CLOSE_CIRC_SCOBAL:
				if(c == ')') state = WAIT_OPEN_SCOBAL;
				break;
			case WAIT_OPEN_SCOBAL:
				if(c == ' ') break; //встретили пробел ничего не делаем. 
				if (c == '{') {
					pushOpenScobal();
					state = WAIT_CLOSE_SCOBAL;
				} else {
					if(c == ';') {
							pushScobals();
							state = START_STATE;
							break;
						}
				}							
				break;
			case WAIT_CLOSE_SCOBAL:
			    if(c == '}') {
					pushCloseScobal();
					state = START_STATE;
					break;
				}
				if(c != ' ') {
					state = START_STATE;
					processState(c);
					break;
				}
			case WAIT_VARIABLE_OR_NAME_FUNCTION:
				checkOnVeriableOrFunction(c);
				break;
			default: 
			    if(c == '{') {
					pushOpenScobal();
				}
			    if(c == '}') {
					pushCloseScobal();
				}
		}
		
	}
	
	void postProcessing()
	{
		int currentNestingLevel = 0;
		int max = 0;
		for(unsigned int i = 0; i < nestingScobals.size(); i++) {
			if(nestingScobals.at(i) == '{') currentNestingLevel++;
			if(max < currentNestingLevel) max = currentNestingLevel;
			if(nestingScobals.at(i) == '}') currentNestingLevel--;
		} 
		this -> maxNestingLevel = max;
	}
	
	void printScobals() {
		for(unsigned int i = 0; i < nestingScobals.size(); i++) {
			std::cout << nestingScobals.at(i) << " ";
		}
		std::cout<<std::endl;
	}
	
	int getMaxNestingLevel() {
		return maxNestingLevel;
	}
	
	int getCountFunction() {
		return count_functions;
	}
	
};

class Processing
{
	Machine machine;
public:
	void processData()	{
		char c;
		while((c = std::cin.get())!=EOF)
		{
			machine.processState(c);
		}
		machine.printScobals();
		machine.postProcessing();
	}

	void printStatistic() {
		std::cout << "Max nesting level: " << machine.getMaxNestingLevel() << std::endl;
		std::cout << "Count function: " << machine.getCountFunction() << std::endl;
	}

};

int main()
{
	Processing p;
	p.processData();
	p.printStatistic();
	return 0;
}
