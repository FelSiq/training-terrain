#include <iostream>
#include <initializer_list>

//Variadic template
template <typename T>
class point{
	//Private by default
	private:
		T *coord;
		unsigned int myDim;

		point(unsigned int dimNum, T *coords){
			this->myDim = dimNum;
			this->coord = new T[dimNum];
			for (unsigned int k = 0; k < dimNum; ++k)
				*(k + this->coord) = *(coords + k); 
		}

	public:
		//Constructor
		point(std::initializer_list<const T> args){
			this->myDim = 0;
			this->coord = new T[args.size()]();

			for (auto k : args)
				*(coord + this->myDim++) = k;
		}
		//destructor
		~point(){
			delete coord;
		}
		// point - x overload
		point <T> *operator - (T x) const {
			point <T> *aux = new point<T>(this->myDim, this->coord);
			for(unsigned int k = 0; k < myDim; ++k)
				*(aux->coord + k) -= x;
			return aux;
		}

		// point + x overload
		point <T> *operator + (T x) const {
			point <T> *aux = new point<T>(this->myDim, this->coord);
			for(unsigned int k = 0; k < myDim; ++k)
				*(aux->coord + k) += x;
			return aux;
		}

		//Another overload on pairs + and -
		point <T> *operator + (point <T> p) const {
			if ((this)->myDim == p.dim()){
				point <T> *aux = new point<T>((this)->myDim, (this)->coord);
				for(unsigned int k = 0; k < myDim; ++k)
					*(aux->coord + k) += *(p.coord + k);
				return aux;
			}
			std::cout << "error: both points needs to be on the same dimension." << std::endl;
			return new point<T>({0});
		}

		point <T> *operator - (point <T> p) const {
			if ((this)->myDim == p.dim()){
				point <T> *aux = new point<T>((this)->myDim, (this)->coord);
				for(unsigned int k = 0; k < myDim; ++k)
					*(aux->coord + k) -= *(p.coord + k);
				return aux;
			}
			std::cout << "error: both points needs to be on the same dimension." << std::endl;
			return new point<T>({0});
		}

		//++point pre-fixed operator overload
		point <T> operator ++(){
			for(unsigned int k = 0; k < this->myDim; ++k)
				++(*(this->coord + k));
			return point(this->myDim, this->coord);
		}

		//Samer with -- prefixed
		point <T> operator --(){
			for(unsigned int k = 0; k < this->myDim; ++k)
				--(*(this->coord + k));
			return point(this->myDim, this->coord);
		}

		//point++ pos-fixed operator overload

		point <T> operator ++(int){
			for(unsigned int k = 0; k < this->myDim; ++k)
				++(*(this->coord + k));
			return (point(this->myDim, this->coord) - 1);
		}

		//Same with -- pos-fixed
		point <T> operator --(int){
			for(unsigned int k = 0; k < this->myDim; ++k)
				--(*(this->coord + k));
			return (point(this->myDim, this->coord) + 1);
		}

		//Getter
		unsigned int dim() const{return this->myDim;}

		//Methods
		void print(){
			for(unsigned int k = 0; k < this->myDim; 
				std::cout << *(this->coord + k) << " ",
				++k);
			std::cout << std::endl;
		}
};

int main(int argc, char const *argv[]){
	
	point <float> *a = new point<float>({1.0,2.0,3.0});
	point <float> *b = new point<float>({3.0,2.0,1.0});

	point <float> *f = *a - 1;
	f->print();

	f = *a - *b; 
	f->print();

	delete a;
	delete b;
	delete f;

	return 0;
}