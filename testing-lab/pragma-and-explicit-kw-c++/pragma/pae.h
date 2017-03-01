#pragma once
//This should be included only once
#if __GNUG__
#include <iostream>
#else
#include <stdio.h>
#endif

void genericFunc(){
	#if __GNUG__
	std::cout << "C++ test func." << std::endl;
	#else
	printf("C test func...\n");
	#endif
};