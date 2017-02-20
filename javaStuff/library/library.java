import java.util.Scanner;

class item {
	Boolean reserved;
	String name;
	Integer id;

	item next;
	item prev;

	public void checkIn(){
		this.reserved = false;
	}
	public void checkOut(){
		this.reserved = true;
	}
	public void refreshName(String newName){
		this.name = newName;
	}
	public void refreshId(Integer newId){
		this.id = newId;
	}
	public void refreshNext(item newNext){
		this.next = newNext;
	}
	public void refreshPrev(item newPrev){
		this.prev = newPrev;
	}
}

class media extends item{
	String type;
}

class magazine extends item {
	String edition;
}

class book extends item{
	String author;
}

class clList {
	item sentinel;
	int itemNum;

	public void itemDump(){
		item traveller = this.sentinel.next;
		if (traveller != this.sentinel){
			System.out.print("ID:\tTYPE\tNAME:\tRESERVED:\n");
			while(traveller != this.sentinel){
				System.out.print(traveller.id + "\t" + traveller.getClass().getName() + 
					"\t"+ traveller.name + "\t" + traveller.reserved);
				if (traveller.reserved)
					System.out.print("\t(RESERVED)");
				System.out.print("\n");
				traveller = traveller.next;
			}
		} else System.out.print("List is empty.\n");
	}

	public item itemSearch(String itemName){
		item traveller = this.sentinel.next;
		while(traveller != this.sentinel){
			if (traveller.name.equals(itemName))
				return traveller;
			traveller = traveller.next;
		}
		return null;
	}

	public boolean itemCheckout(String itemName){
		item myCheckout = this.itemSearch(itemName);
		if (myCheckout != null && !myCheckout.reserved){
			myCheckout.checkOut();
			return true;
		}
		return false;
	}

	public boolean itemNew(String type, String name, int id){
		item newItem = null;
		switch(type){
			case "media": 
				newItem = new media();
				break;
			case "magazine": 
				newItem = new magazine();
				break;
			case "book": 
				newItem = new book();
				break;
			default: 
				System.out.print("Invalid type of new item.\n");
				return false;
		}
		newItem.refreshName(name);
		newItem.refreshId(id);
		newItem.checkIn();
		newItem.refreshNext(this.sentinel);
		newItem.refreshPrev(this.sentinel.prev);
		this.sentinel.prev.refreshNext(newItem);
		this.sentinel.refreshPrev(newItem);

		return true;
	}
}

public class library{
	private static clList initCLL(){
		clList cll = new clList();
		cll.sentinel = new item();
		cll.sentinel.next = cll.sentinel;
		cll.sentinel.prev = cll.sentinel;
		cll.itemNum = 0;
		return cll;
	}

	public static void main(String[] args) {
		//Set up a circular double linked list
		clList myList = initCLL();

		String token = null;
		Boolean flag = true;
		
		System.out.print("please enter a command:\n");

		while (flag){
			Scanner myCommand = new Scanner(System.in);
			
			System.out.print("> ");
			token = myCommand.next();

			switch(token){
				case "add": 
					if(myList.itemNew(myCommand.next(), myCommand.next(), Integer.parseInt(myCommand.next())))
						System.out.print("Successfully added new item on system.\n");
					else 
						System.out.print("Failed to add new item on system.\n");
					break;
				case "search": 
					item auxItem = myList.itemSearch(myCommand.next());
					if (auxItem != null)
						System.out.printf("Found selected item (ID: %d)\n", auxItem.id);
					else
						System.out.print("Can't find selected item.\n");
					break;
				case "dump":
					myList.itemDump();
					break;
				case "checkout":
					if(myList.itemCheckout(myCommand.next()))
						System.out.print("Item reserved Successfully. Thank you.\n");
					else
						System.out.print("Can't reserve item. Sorry.\n");
					break;
				case "exit":
					System.out.print("program is now exiting.\n");
					flag = false;
					break;
				default: 
					System.out.print("\""+ token +"\""+" are not a valid command.\n");
					break;
			}
		}
	}
}