#include <cstdlib>
#include <iostream>

template <class T>
class vector {
	//private keyword here just for the sake of completeness,
	//members of a class are private by default.
	private: 
		const double DELTA = 0.0001;
		unsigned int size;
		T *data;

		T absVal(T A, T B){
			T C = A - B;
			return ((C) < 0 ? (-(C)) : (C));
		};
	public:
		//Constructor
		vector(){
			data = NULL;
			size = 0;
		};
		//Destructor
		~vector(){
			if (data != NULL)
				delete data;
		};

		unsigned int mySize(){
			return size;
		};

		//Common methods
		void add(T newVal){
			data = (T *) realloc(data, sizeof(T) * (1 + size));
			*(data + size) = newVal;
			++size;
		};

		void sort(){
			//BubbleSort just for test purposes.
			char FLAG = 1;
			for (long int i = 1; FLAG && i < size; ++i){
				FLAG = 0;
				for(long int j = 0; j < (size - i); ++j)
					if (*(data + j) > *(data + j + 1)){
						T aux = *(data + j);
						*(data + j) = *(data + j + 1);
						*(data + j + 1) = aux;
						FLAG = 1;
					};
			}
		};

		//Remove a value in a specif index of vector
		void remIndex(long int index){
			if (index >= 0){
				if (index < size){
					for (unsigned int i = (index - 1);
						i < (size - 1);
						*(data + i) = *(data + i + 1),
						++i);
					//!x, x > 0, equals 0 if-logic-wise.
					if (!size){
						delete data;
						data = NULL;
					} else
						data = (T *) realloc(data, sizeof(T) * (--size));
				} else std::cout << "error: \"index\" must be smaller than vector size." << std::endl;
			} else std::cout << "error: \"index\" must be higher or equal to 0."<< std::endl;
		};

		//remove all apareances of a specific value on vector
		void remVal(T val){
			if (data != NULL){
				for(long int i = 0; i < size; ++i)
					if (absVal(*(data + i), val) < DELTA){
						for (unsigned int j = (size - 1);
							j < (size - 1);
							*(data + i) = *(data + j + 1),
							++j);
						--size;
						--i;
					}
					
				if (!size){
					delete data;
					data = NULL;
				} else
					data = (T *) realloc(data, sizeof(T) * (size - 1));
			}
		};

		//print values on vector
		void print() const{
			if (data != NULL){
				for(unsigned int i = 0;
					i < size; 
					std::cout << *(data + i) << ' ',
					++i);
				std::cout << "\b\n";
			}
			else std::cout << "vector is empty." << '\n';
		};
};

#include <time.h>

inline int randomRange(int max, int min){
	return ((rand() % (max - min + 1)) + min);
}

int main(int argc, char const *argv[]){
	vector <double> *vec = new vector <double>();

	srand(time(NULL));

	for(int k = 10; k > 0; --k){
		vec->add(randomRange(1000, -1000));
	}
	//for (int i = vec->mySize(); i > 0; (--i)){
	vec->print();
	vec->sort();
	vec->print();
	//}

	delete vec;
	return 0;
}