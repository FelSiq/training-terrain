import java.util.*; 

class complexManager{
	private static complex getComplex(Scanner myScan){
		double r = 0, i = 0;
		if (myScan.hasNextDouble()){
			r = Double.parseDouble(myScan.next());
			if (myScan.hasNextDouble()){
				i = Double.parseDouble(myScan.next());
				return new complex(r, i);
			}
		}
		System.out.print("Can't create complex number. use \"add <r> <i>\"\n");
		return null;
	}

	public static void main(String args[]){
		//Set a scanner to read the input on stdin.
		Scanner myInput = null;
		//This flags ends the loop on program
		boolean endflag = true;

		//Create a linked list to keep the numbers
		clList myGroup = new clList();
		//Set the UNIQUE KEY COUNTER
		int keyKepper = 0;

		//Set the numeric float US STD representation,
		//on input and on output, involving this scan.

		System.out.print("Please insert a command: (type \"help\" for list)\n");
		while(endflag){
			//Get system input
			do {
				System.out.print("> ");
				myInput = new Scanner(System.in);
			} while (!myInput.hasNext());

			switch(myInput.next()){
				case "add":
					myInput.useLocale(Locale.US); 
					complex myNum = getComplex(myInput);
					myGroup.nodeNew(myNum, keyKepper++);
					myNum.print();
					break;
				case "exit":
					System.out.print("Program will now exit...\n");
					endflag = false;
					break;
				case "print":
					myGroup.nodeDump();
					break;
				default: 
					System.out.print("Unknown command.\n");
			}

			//Deference the memory from last input
			myInput = null;
		}
	}
};