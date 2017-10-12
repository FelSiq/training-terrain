import java.util.Locale;

public enum MyEnum{
	FELIPE (1, 4.1e+10),
	TIBET (2, 3.4),
	MARIA (3, 0.2),
	AURORA (4, 0.3);

	private final int aValue;
	private final double fValue;

	//Must be non-labelled (private/package) or private-only.
	MyEnum(int newaValue, double newfValue){
		//Constructor
		/*
			"Note: The constructor for an enum type must be package-private or private access. 
			It automatically creates the constants that are defined at the beginning of the enum body. 
			You cannot invoke an enum constructor yourself. "
		*/
		this.aValue = newaValue;
		this.fValue = newfValue;
	}

	//To recover number of Enum parameters
	//static public int getLength(){return values().length;}

	static public void main (String args[]){
		//Enum cannot be instantiated
		//But it can have a constructor
		//MyEnum inst = new MyEnum();

		for(MyEnum e : MyEnum.values()){
			Locale.setDefault(Locale.US);
			System.out.printf("%s\t%d\t%e\n", e, e.aValue, e.fValue);
		}
	}
};