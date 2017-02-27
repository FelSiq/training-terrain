/*

	Objectives: construct a simple hashing table...
	-> somehow using inheritance concept somewhere.
	-> colisions must create a binary tree (already codded) (import) (ok)
	-> hashtable must have 3 different hashing functions ()

*/

import bt.*;
import java.util.ArrayList;
import java.util.Random;

class hashTable <T>{
	ArrayList <bt <T>> boulevard; 
	String method;
	int size;

	private void fillBoulevard(){
		for (int i = 0; i < size; ++i)
			this.boulevard.add(new bt<T>());
	}

	//Constructor
	public hashTable(){
		this.boulevard = new ArrayList <bt <T>>();
		this.method = "mod";
		this.size = 10;

		this.fillBoulevard();
		
	}
	public hashTable(int newSize, String newMethod){
		if (newSize <= 1){
			System.out.printf("Invalid new size. Setting to default (%d).\n", 10);
			newSize = 10;
		}
		this.size = newSize;
		this.boulevard = new ArrayList <bt <T>>(newSize);
		this.method = newMethod;
		
		this.fillBoulevard();

		switch(method){
			case "mod": break;
			case "mult": break;
			case "logi": break;
			default: this.method = "mod";
		}
	}
	//Hashing functions
	//Visible only by the Hashtable
	private int hashingMod(int key){
		if (key < 0)
			return 0;
		return key % size;
	}

	private int hashingLogi(int key){
		//To be worked...
		if (key < 0)
			return 0;
		return key % size;
	}

	private int hashingMult(int key){
		//To be worked...
		if (key < 0)
			return 0;
		return key % size;
	}

	//Getter
	public int size(){return this.boulevard.size();}

	//No setters.

	//Methods
	public void add(int key, T value){
		switch(this.method){
			case "mod":
				this.boulevard.get(hashingMod(key)).add(key, value);
				break;
			case "mult":
				this.boulevard.get(hashingMult(key)).add(key, value);
				break;
			case "logi":
				this.boulevard.get(hashingLogi(key)).add(key, value);
				break;
			default:
				System.out.print("Method invalid. opts: (mod, mult, logi)\n");
				break;
		}
	}

	//Polymorphims function 'print'
	public void print(int index){
		if (index < this.size)
			this.boulevard.get(index).print();
		else System.out.print("Index out of bounds.\n");
	}

	public void print(){
		System.out.print("Dumping all hashTable content:\n");
		for (int i = 0; i < this.size; ++i){
			System.out.printf("-- Tree #%d:\n", i);
			this.boulevard.get(i).print();
			System.out.print("\n");
		}
	}

	public void expand(int newSize){
		if (newSize > this.size){
			if (this.boulevard.isEmpty()){
				for(int i = (size - 1); i < newSize; ++i)
					this.boulevard.add(new bt<T>());
				this.size = newSize;
			} else System.out.print("Can't expand hashtable because its not empty anymore.\n");
		} else System.out.printf("NewSize must be higher than current size (%d).\n", this.size);
	}

	public T search(int key){
		switch(this.method){
			case "mod":
				return this.boulevard.get(hashingMod(key)).search(key);
			case "mult":
				return this.boulevard.get(hashingMult(key)).search(key);
			case "logi":
				return this.boulevard.get(hashingLogi(key)).search(key);
			default:
				System.out.print("Method invalid. opts: (mod, mult, logi)\n");
				return null;
		}	
	}
};

class htManager{
	static public void main(String args[]){
		hashTable <Double> myHT = new hashTable <Double> (25, "mod");
		System.out.printf("%d\n", myHT.size());

		Random myRand = new Random();

		for(int i = 0; i < 900; ++i)
			myHT.add(myRand.nextInt(999), 1.03 * myRand.nextInt(9999));

		myHT.print();

		System.out.printf("%f\n", myHT.search(974));
		myHT.expand(36);

	} 
}