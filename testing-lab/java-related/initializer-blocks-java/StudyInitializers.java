class StudyInitializers{
	private int x;
	private static long a;
	protected static float k;

	//Initiates all static variables.
	//These belong to this class and are executed as long the class is loaded in JVM¹ 
	static {
		a = 777; 	//(1) has priority.
		k = (float) 2.9; //(2)
		//Cannot init non-static variables on static init block
		//x = 3;
	}

	StudyInitializers(){
		a = 999; //Priority over (1)
	}

	//Initiates all non-static variables.
	{
		x = 1;
		//Can init static variables on common init block
		a = 99; //(1)
		k = (float) 3.3; //Even if the static init block come first,
			//This block has "higher priotity" (i.e is executed later), b
			//ut still "lower priority" than the constructors.
			//Then, K will be init as 3.3, unless StudyInitializers(int) is called.
	}

	StudyInitializers(int n){
		//Values on constructor itself has priority on init block, i.e
		//they're all called after init block.
		//The init block is created, by the compiler, here.
		k = (float) 1.9; //Priotity over (2)
	}

	public int getX(){return x;}

	static public void main(String args[]){
		StudyInitializers myInst = new StudyInitializers();

		System.out.printf("%d/%f\n", StudyInitializers.a, StudyInitializers.k);
	}
};


/*
"
	¹font: http://www.thejavageek.com/2013/07/21/initialization-blocks-constructors-and-their-order-of-execution/
    Initialization blocks run in the order they appear in the program.
    Static initialization blocks run when the class is first loaded into JVM
    Instance initialization blocks run whenever a new instance of class is created.
"
*/