import java.lang.reflect.Method;

class clList <T> {
	private node <T> sentinel;
	private int nodeNum;

	//Node class
	class node <T>{
		T item;
		int key;

		node <T> next;
		node <T> prev;

		//Constructors
		node(){this.item = null; this.key = -1;}
		node(int newKey){this.item = null; this.key = newKey;}
		node(T newItem, int newKey){this.item = newItem; this.key = newKey;}

		//Getter
		T getItem(){return this.item;}
		int getKey(){return this.key;}

		//Methods
		void refreshNext(node <T> newNext){this.next = newNext;}
		void refreshPrev(node <T> newPrev){this.prev = newPrev;}
		void refreshItem(T newItem){this.item = newItem;}
		void refreshKey(int newKey){this.key = newKey;}
	};
	//getter
	int size(){return nodeNum;}

	//Constructor
	clList(){
		this.sentinel = new node <T>();
		this.sentinel.next = this.sentinel;
		this.sentinel.prev = this.sentinel;
		this.nodeNum = 0;
	}
	//Methods
	boolean empty(){return (this.nodeNum == 0);}

	public void print(){
		node <T> traveller = this.sentinel.next;

		if (traveller != this.sentinel){
			
			while(traveller != this.sentinel){
				T myItem = traveller.getItem();

				boolean hasPrint = false;
				Method[] methodList = myItem.getClass().getMethods();
				for(Method m : methodList){
					if (m.getName().equals("print")){
						hasPrint = true;
						try {m.invoke(myItem);} 
						catch (Exception e){
							//DO nothing...
						}

						break;
					}
				}

				if (!hasPrint)
					System.out.print(myItem + "\n");
				
				//Go to the next node
				traveller = traveller.next;
			}
		} else System.out.print("List is empty.\n");
	}

	public T search(int key){
		node <T> traveller = this.sentinel.next;
		while(traveller != this.sentinel){
			if (traveller.getKey() == key)
				return traveller.getItem();
			traveller = traveller.next;
		}
		return null;
	}

	public boolean insert(T newItem, int newKey){
		node <T> newNode = new node<T>(newItem, newKey);

		newNode.refreshNext(this.sentinel);
		newNode.refreshPrev(this.sentinel.prev);
		this.sentinel.prev.refreshNext(newNode);
		this.sentinel.refreshPrev(newNode);

		(this.nodeNum) += 1;
		return true;
	}
};