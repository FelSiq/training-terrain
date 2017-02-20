class bar{
	public int a;
		//Visible in anywhere
	private int b;
		//Visible only on "bar" dominion
	protected int c;
	protected int somethingRare(){return b;}
		//both visible only on bar and its sons and on packages
};

class foo extends bar {
	//c is protected, therefore inherintable
	public int getB(){return c;}
	//SomethingRare is a method inherintable
	//Now we created a public path
	public int somethingUseful(){return somethingRare();}
};

class qux{
	static public void main(String args[]){
		foo myinst = new foo();
		//a is public
		myinst.a = 5;

		//SomethingUseful is public
		myinst.somethingUseful();
	}
};