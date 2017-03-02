class lambda <T>{

	//These are a FUNCTIONAL INTERFACE, i.e a interface with a single abstract method
	interface BinaryOp <T> {
		//Can only have a single abstract method
		public T operation(T a, T b); 
	}

	interface UnaryOp <T> {
		public T operation(T a);
	}

	private T BinOperation (T a, T b, BinaryOp <T> myOp){
		return myOp.operation(a, b);
	}

	private T UnOperation (T a, UnaryOp <T> myOp){
		return myOp.operation(a);
	}

	static public void main (String [] args){

		lambda <Integer> myCalc = new lambda <Integer>();

		BinaryOp <Integer> add = (a, b) -> a + b;
		BinaryOp <Integer> mult = (a, b) -> a * b;
		UnaryOp <Integer> opposite = (a) -> a * (-1);

		System.out.println(myCalc.BinOperation(5, 10, add));
		System.out.println(myCalc.BinOperation(5, 10, mult));
		System.out.println(myCalc.UnOperation(5, opposite));
	}
}