#include <iostream>
#include <string>

//:: = "operador de resolução de escopo"

template <typename ...> class myNewClass;

template <typename T1, typename T2>
class myNewClass < T1, T2>{
	protected:
		T1 fstData;
		T2 sndData;

		myNewClass(){
			//std::cout << "initializing a person (?)..." << std::endl;
			fstData = -1;
			sndData = -1;
		}
	public:
		//Getters
		virtual T1 getFst() const{
			return (fstData < 0) ? 0 : fstData;
		}
		T2 getSnd() const{
			if (sndData > 0)
				return sndData;
			return 0;
		}
};

template <typename T>
struct myStruct{
	//Public por default
	T var1;
	private:
		T var2;
};

//Parametros/variaveis de uma classe é private por default.
class Person: public myNewClass <int, int>{
	//private:
		char *name;
		int age;
		double salary;
	public:
		//Constructor
		Person (char const newName [], int age, double salary);
		Person ();
		
		//Destructor
		virtual ~Person ();

		//Getters
		//Inline por default
		char *getName() const{
			return name;
		}
		int getFst() const{
			return fstData;
		}
};

class unknownData: public Person{
	public:
		unknownData() {

		};
};

//Forçar o "inline"
inline Person::Person(char const newName [], int age = 0, double salary = 0.0){
	std::string str(newName);
	name = new char [str.length()];
	str.copy(name, str.length(), 0);
	age = age;
	salary = salary;
};

//Sobrecarga de construtor, com inicialização automática
inline Person::Person(){
	std::string str("Desconhecido.");
	name = new char [str.length()];
	str.copy(name, str.length(), 0);
	age = 0;
	salary = 0.0;
};

inline Person::~Person(){
	delete [] name;
}

int main(int argc, char const *argv[]){
	Person const *felipe = new Person("Felipe", 21);
	unknownData *unk = new unknownData();

	struct myStruct <float>*ms = new myStruct<float> ();

	//public por default
	ms->var1 = 5.47;
	//ms->var2 = 22;

	//N funciona, pois "age" é private por default
	//felipe->age = 5;

	//"felipe->getName()" é uma MENSAGEM
	std::cout << felipe->getName() << std::endl;
	std::cout << felipe->getFst() << std::endl;
	std::cout << felipe->getSnd() << std::endl;

	delete felipe;
	delete unk;
	delete ms;
	return 0;
};