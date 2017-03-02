import java.util.Scanner;
import java.util.Locale;

class anonclass{

	//Inner class: non-static inside class
	//Nested static class: static inside class
	interface Arithmetic <T> {
		public T operator(T arg);
	};

	public static void main(String [] args){
		Scanner myInput = new Scanner(System.in);
		myInput.useLocale(Locale.US);

		//One can implement the anonymous class, and then instantiate it
		class myAnon2 implements Arithmetic <Double>{
			Double myVal = 0.0;
			public Double operator(Double arg){
				this.myVal += arg;
				return this.myVal;
			}

			myAnon2(){}
		}

		myAnon2 myInst = new myAnon2();

		//Or implement and instantiate right on the ways
		Arithmetic <Integer> myAnon = new Arithmetic <Integer> (){
			Integer myVal = 0;
			public Integer operator(Integer arg){
				this.myVal += arg;
				return this.myVal;
			}
		};

		while(myInput.hasNext()){
			if (myInput.hasNextInt())
				System.out.println(myAnon.operator(Integer.parseInt(myInput.next())));
			else if (myInput.hasNextDouble())
				System.out.println(myInst.operator(Double.parseDouble(myInput.next())));
			else break;
		}

	}
};