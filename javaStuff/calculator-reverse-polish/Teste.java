import java.util.*;

class Element {
	Double value;
	Element prev;
}

class Stack {
	Element item;
	
	public double popElem(){
		Double myVal = this.item.value;
		this.item = this.item.prev;
		return myVal;
	}

	public void pushElem(double myVal){
		Element myElem = new Element();
		myElem.value = myVal;
		myElem.prev = this.item;
		this.item = myElem;
	}
}

class Expression{
	String exp;
}

public class Teste {
	public static void main(String []args){
		Stack calc = new Stack();

		Expression myExp = new Expression();

		myExp.exp = args[0];
		for(int i = 1; i < args.length; ++i)
			myExp.exp += (" " + args[i]);

		Scanner scan = new Scanner(myExp.exp);
		
		scan.useLocale(Locale.US);

		while(scan.hasNext()){
			if (scan.hasNextDouble())
				calc.pushElem(Double.parseDouble(scan.next()));
			else {
				String operator = scan.next();
				//System.out.print(operator);
				switch(operator){
					case "+": 
						calc.pushElem(calc.popElem() + calc.popElem());
						break;
					case "-": 
						calc.pushElem(-calc.popElem() + calc.popElem());
						break;
					case "*": 
						calc.pushElem(calc.popElem() * calc.popElem());
						break;
					case "/": 
						calc.pushElem(1/calc.popElem() * calc.popElem());
						break;
					default: 
						System.out.print("Invalid operator.\n"); 
						break;
				}
			}
		}
		System.out.print(calc.popElem()+"\n");
		scan.close();
	}
}
