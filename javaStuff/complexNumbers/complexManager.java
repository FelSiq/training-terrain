import java.util.*; 
import complex.*;

class complexManager{

	public static void main(String args[]){
		//Process args
		boolean myDebug = false;
		for(String s : args){
			myDebug = (s.equals("-DEBUG"));
		}
		//commandTree
		commandTree myProcessor = new commandTree(myDebug);

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
				//Solve the tree and show up the desired result
				myProcessor.solve();
				if (myProcessor.lastRes() != null)
					myProcessor.lastRes().print();
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
	}
};