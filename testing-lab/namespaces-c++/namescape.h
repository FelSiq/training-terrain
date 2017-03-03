#pragma once
#ifndef __MY_NAMESPACE_LIB_
#define __MY_NAMESPACE_LIB_

#include <iostream>

using std::cout; 
using std::endl;

namespace myLib {
	class myClass{
		public:
			void genericFunc(){
				cout << "This is generic function from my lib!" << endl; 
			}
	};
};

#endif