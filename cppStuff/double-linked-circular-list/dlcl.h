#ifndef __CPP_DLCLIST_H_
#define __CPP_DLCLIST_H_
#include "node.h"
#include <iostream>
#include <iomanip>

template <typename T>
class dlcList{
	//Privates in default
	private:
		specialNode <T> *sentinel;
		size_t nodeNum; 

		virtual void insertionSort(node<T> *newNode){

			#ifdef DEBUG
				std::cout << "will add key " << newNode->getKey() << "..."<< std::endl;
			#endif

			node <T> *traveller = sentinel->getNext();
			sentinel->setKey(newNode->getKey() + 1);

			while(newNode->getKey() > traveller->getKey()){
				#ifdef DEBUG
					std::cout << "comparing with " << traveller->getKey() << "..." << std::endl;
				#endif
				traveller = traveller->getNext();
			}

			newNode->setPrev(traveller->getPrev());
			newNode->setNext(traveller);
			(traveller->getPrev())->setNext(newNode);
			traveller->setPrev(newNode);
		}

	public:
		//Constructor
		dlcList(){
			sentinel = new specialNode <T>();
			nodeNum = 0;
		}
		//Destructor
		virtual ~dlcList(){
			node <T> *traveller = sentinel->getNext(), *aux;
			while(traveller != sentinel){
				aux = traveller;
				traveller = traveller->getNext();
				delete aux;
			}
			delete sentinel;
		}
		//Getter
		size_t size() const{return nodeNum;}
		//No setters.

		//Methods:
		virtual void add(int key, T value){
			node <T> *newNode = new node <T> (key, value, NULL, NULL);
			insertionSort(newNode);
			++nodeNum;
		}

		virtual T rem(int const key){
			node <T> *traveller = sentinel->getNext();
			sentinel->setKey(key);
			T value = traveller->getVal();

			while(traveller->getKey() < key)
				traveller = traveller->getNext();
			
			if (traveller != sentinel){
				value = traveller->getVal();
				(traveller->getPrev())->setNext(traveller->getNext());
				(traveller->getNext())->setPrev(traveller->getPrev());
				delete traveller;
				--nodeNum;
			}

			return value;
		}

		virtual void print() const{
			node <T> *traveller = sentinel->getNext();
			if (traveller != sentinel){
				while (traveller != sentinel){
					std::cout << traveller->getVal() 
						<< std::setw(30)
						<< std::setfill('.')
						<< " (key: " 
						<< traveller->getKey() << ")"
						<< std::endl;
					traveller = traveller->getNext();
				}
			} else std::cout << "list is empty." 
					<< std::endl;
		}

};

#endif