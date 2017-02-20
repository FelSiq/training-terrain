#ifndef __CPP_DLCL_NODE_
#define __CPP_DLCL_NODE_

template <typename T>
class node{
	//All private by default
	protected:
		int key;
		node <T> *prev, *next;
		T value;

	public:
		//Constructors
		node(){
			key = -1;
			value = 0.0;
			prev = this;
			next = this;
		}

		node(int newKey, T newValue, node *newNext, node *newPrev){
			key = newKey;
			value = newValue;
			next = newNext;
			prev = newPrev;
		}

		//Destructor
		virtual ~node(){}
		//Getters
		virtual int getKey() const{return key;}
		T getVal() const{return value;}
		node *getPrev() const{return prev;}
		node *getNext() const{return next;}
		//Setters.
		void setPrev(node *newPrev){prev = newPrev;}
		void setNext(node *newNext){next = newNext;}
};

template <typename T>
class specialNode: public node <T>{
	int key;
	public:
		void setKey(int newKey){key = newKey;}
		virtual int getKey() const{return key;}
		virtual ~specialNode(){}
};

#endif