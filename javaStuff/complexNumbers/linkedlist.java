class node{
	complex item;
	Integer key;

	node next;
	node prev;

	node(){
		this.item = null;
		this.key = -1;
	};

	void printItem(){
		item.print();
	}

	void refreshNext(node newNext){
		this.next = newNext;
	}
	void refreshPrev(node newPrev){
		this.prev = newPrev;
	}

	void refreshItem(complex newItem){
		this.item = newItem;
	}

	void refreshKey(int newKey){
		this.key = newKey;
	}
};


class clList {
	node  sentinel;
	int nodeNum;

	//Constructor
	clList(){
		this.sentinel = new node ();
		this.sentinel.next = this.sentinel;
		this.sentinel.prev = this.sentinel;
		this.nodeNum = 0;
	}

	public void nodeDump(){
		node  traveller = this.sentinel.next;
		if (traveller != this.sentinel){
			while(traveller != this.sentinel){
				traveller.printItem();
				traveller = traveller.next;
			}
		} else System.out.print("List is empty.\n");
	}

	public node nodeSearch(int key){
		node  traveller = this.sentinel.next;
		while(traveller != this.sentinel){
			if (traveller.key.equals(key))
				return traveller;
			traveller = traveller.next;
		}
		return null;
	}

	public boolean nodeNew(complex item, int key){
		node newItem = new node();
		newItem.refreshItem(item);


		newItem.refreshNext(this.sentinel);
		newItem.refreshPrev(this.sentinel.prev);
		this.sentinel.prev.refreshNext(newItem);
		this.sentinel.refreshPrev(newItem);

		return true;
	}
};