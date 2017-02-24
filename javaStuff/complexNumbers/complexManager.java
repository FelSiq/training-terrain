import java.util.*; 

class complexManager{
	private static complex getComplex(Scanner myScan){
		double r = 0, i = 0;
		if (myScan.hasNext()){
			r = Double.parseDouble(myScan.next());
			if (myScan.hasNext()){
				i = Double.parseDouble(myScan.next());
				return new complex(r, i);
			}
		}
		System.out.print("Can't create complex number. \n");
		return null;
	}

	private static int getIndex(Scanner myInput, clList <clList<complex>> myGroup){
		int index = 0;
		if (myInput.hasNextInt())
			index = Integer.parseInt(myInput.next());
		while (myGroup.size() <= index)
			myGroup.insert(new clList <complex> (), myGroup.size());

		return index;
	}

	public static void main(String args[]){
		//Set a scanner to read the input on stdin.
		Scanner myInput = null;
		//This flags ends the loop on program
		boolean endflag = true;

		//Create a linked list to keep the numbers
		clList <clList<complex>> myGroup = new clList<clList<complex>> ();
		//Set the UNIQUE KEY COUNTER
		int keyKepper = 0;

		//Pointers do instances
		complex myNumX = null, 
		myNumY = null, 
		myNum = null;

		//Set the numeric float US STD representation,
		//on input and on output, involving this scan.
		System.out.print("Please insert a command: (type \"help\" for list)\n> ");
		myInput = new Scanner(System.in);
		myInput.useLocale(Locale.US); 

		while(endflag){
			if (myInput.hasNext()){
				switch(myInput.next()){
					case "insert":
						myNum = getComplex(myInput);
						if (myNum != null){
							myGroup.search(getIndex(myInput, myGroup)).insert(myNum, keyKepper++);
							myNum.print();
						}
						myNum = null;
						break;
					case "add":
						myNumX = getComplex(myInput); 
						myNumY = getComplex(myInput);
						if (myNumX != null && myNumY != null)
							/*stackComplex.push(*/myNumX.add(myNumY).print()/*)*/;
						myNumX = null;
						myNumY = null;
						break;
					case "div":
						myNumX = getComplex(myInput); 
						myNumY = getComplex(myInput);
						if (myNumX != null && myNumY != null)
							/*stackComplex.push(*/myNumX.div(myNumY).print()/*)*/;
						myNumX = null;
						myNumY = null;
						break;
					case "mult":
						myNumX = getComplex(myInput); 
						myNumY = getComplex(myInput);
						if (myNumX != null && myNumY != null)
							/*stackComplex.push(*/myNumX.mult(myNumY).print()/*)*/;
						myNumX = null;
						myNumY = null;
						break;
					case "sub":
						myNumX = getComplex(myInput); 
						myNumY = getComplex(myInput);
						if (myNumX != null && myNumY != null)
							/*stackComplex.push(*/myNumX.sub(myNumY).print()/*)*/;
						myNumX = null;
						myNumY = null;
						break;
					case "mod":
						myNum = getComplex(myInput);
						if (myNum != null)
							/*stackComplex.push(*/myNum.mod().print()/*)*/;
						myNum = null;
						break;
					case "conj":
						myNum = getComplex(myInput);
						if (myNum != null)
							/*stackComplex.push(*/myNum.conj().print()/*)*/;
						myNum = null;
						break;
					case "equals":
						myNumX = getComplex(myInput); 
						myNumY = getComplex(myInput);
						if (myNumX != null && myNumY != null)
							System.out.print(myNumX.equals(myNumY) + "\n");
						myNumX = null;
						myNumY = null;
						break;
					case "exit":
						System.out.print("Program will now exit...\n");
						endflag = false;
						break;
					case "printAll":
						myGroup.print();
						break;
					case "printList":
						if (myInput.hasNext()){
							clList <complex> aux = myGroup.search(Integer.parseInt(myInput.next()));
							if (aux != null)
								aux.print();
							else 
								System.out.print("List not found.\n");
						}
						break;
					case "size":
						System.out.print("My database size is: "+ myGroup.size() +"\n");
						break;
					default: 
						System.out.print("Unknown command.\n");
						break;
				}
			}
			//Get system input
			System.out.print("> ");
			myInput.reset();
		}

		//Deference the memory from last input
		myInput.close();
		myInput = null;
	}
};