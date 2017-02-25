import java.util.*; 

class complexManager{
	/*
	//Earlier version facilities
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
	*/

	public static void main(String args[]){
		//commandTree
		commandTree myProcessor = new commandTree();

		//my result holder.
		complex myResult = null;

		//Set a scanner to read the input on stdin.
		Scanner myInput = null;

		//Set the numeric float US STD representation,
		//on input and on output, involving this scan.
		System.out.print("Please insert a command: (type \"help\" for list)\n");
		myInput = new Scanner(System.in);

		while(!myProcessor.flags.getFlagEnd()){
			//Get system input
			System.out.print("> ");
			myInput.reset();

			//reset() removes the Locale setting.
			//Belive me, this was H-A-R-D to find out.
			myInput.useLocale(Locale.US); 

			//Procces inputs
			if(myProcessor.construct(myInput)){
				//Debbug
				//myProcessor.print();

				//Solve the tree and show up the desired result
				myResult = myProcessor.solve();
				if (myResult != null)
					myResult.print();
			} else {
				//Checkup for flags
				if(!myProcessor.flags.overallCheckup())
					System.out.print("error: invalid syntax on this command.\n");
			}	

			//Clean up the command tree of this call
			myProcessor.flags.resetFlags();
			myProcessor.purge();
		}

		//Deference the memory from last input
		myInput.close();
		myInput = null;

		myProcessor = null;
		myResult = null;
	}
};