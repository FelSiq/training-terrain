class foo <T> {
	private T myVar;
}

class bar extends foo {
	protected int myVar;
}


class temp <T> {
	private T variable;
	


	public T myFunc(){
		System.out.print("Returning variable...\n");
		return variable;
	}

	public void setSomething(T newData){
		variable = newData;
	}

	public static void main (String args[]) {
		temp <Double> instance = new temp <Double> ();
		instance.setSomething(1.23421);
		System.out.print(instance.myFunc() + "\n");
		System.out.print(instance.variable + "\n");

		instance = null;

		bar testBar = new bar();
		testBar.myVar = 5;

		testBar = null;
	}
}