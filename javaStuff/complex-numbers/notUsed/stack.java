class stack <T>{
	private node <T> top;

	//Node declaration
	private class node<T>{
		node <T> prev;
		T item;

		node(T newItem, node <T> newPrev){
			this.item = newItem;
			this.prev = newPrev;
		}
	};

	//Constructor
	public stack(){
		this.top = null;
	}
	//Methods
	public T pop(){
		node <T> aux = this.top;
		this.top = this.top.prev;
		return aux.item;
	}

	public void push(T newItem){
		node<T> newTop = new node<T>(newItem, this.top);
		this.top = newTop;
	}

	public T top(){return this.top.item;}
	public boolean empty(){return (this.top == null);}
	public void purge(){this.top = null;}

};