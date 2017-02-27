package bt;
import java.util.Random;

class node <T>{
	node <T> sonL, sonR;
	int key;
	T item;

	//Getters
	public T getItem(){return item;}
	public int getKey(){return key;}
	public node<T> getSL(){return sonL;}
	public node<T> getSR(){return sonR;}

	//Setters
	public void setItem(T newItem){item = newItem;}
	public void setSL(node <T> newSon){ sonL = newSon;}
	public void setSR(node <T> newSon){ sonR = newSon;}

	//Constructor
	public node(int initKey, T initItem){
		key = initKey;
		setItem(initItem);
		sonL = null;
		sonR = null;
	};
};

public 	class bt <T>{
	node<T> root;
	int nodeNum;

	//Constructor
	public bt(){
		root = null;
		nodeNum = 0;
	};
	//Methods
	private int addRec(node<T> root, node<T> newNode){
		if (root.getKey() > newNode.getKey()){
			if(root.getSL() != null)
				return addRec(root.getSL(), newNode);
			else {
				root.setSL(newNode);
				return 1;
			}
		} else if (root.getKey() < newNode.getKey()){
			if(root.getSR() != null)
				return addRec(root.getSR(), newNode);
			else {
				root.setSR(newNode);
				return 1;
			}
		} else System.out.printf("Can't add a new node with an already existing key (%d).\n", newNode.getKey());
		return 0;
	}

	public void add(int newKey, T item){
		node<T> newNode = new node<T>(newKey, item);
		if (root != null)
			nodeNum += addRec(root, newNode);
		else {
			root = newNode;
			newNode = null;
		}
	}

	private T searchRec(node<T> root, int searchKey){
		if (root != null){
			if (root.getKey() == searchKey){
				return root.getItem();
			} else if (root.getKey() > searchKey){
				return searchRec(root.getSL(), searchKey);
			} else if (root.getKey() < searchKey){
				return searchRec(root.getSR(), searchKey);
			}
		}
		return null;
	}

	public T search(int searchKey){
		if (this.root != null)
			return searchRec(this.root, searchKey);
		return null;
	}

	public void remove(int remKey){
		//To be implemented...
	}

	private void printRec(node <T> root, int offset){
		if (root != null){
			System.out.print("["+offset/2+"] ");
			for (int i = 0; i < offset; 
				System.out.print(" "),
				++i);
			System.out.print("(Key: "+ root.getKey() + ") - Item:" + root.getItem() + "\n");
			printRec(root.getSL(), offset + 2);
			printRec(root.getSR(), offset + 2);
		}
	}

	public void print(){
		printRec(root, 0);
	}
};

/*class treeManager{
	static public void main(String args[]){
		bt <Float> tree = new bt <Float>();

		Random myRand = new Random();
		for (int i = 0; i < 10; ++i){
			tree.add(myRand.nextInt(999), (float) myRand.nextInt(999));
		}

		tree.print();
	}
};*/
