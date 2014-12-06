#include <vector>
#include <iostream>



int main() 
{
	
	std::vector<char> list;
	
	list.push_back('{');
	list.push_back('}');
	for(int i = 0; i < list.size(); i++)
	std::cout << " " << list.at(i);
	
	return 0;
}
