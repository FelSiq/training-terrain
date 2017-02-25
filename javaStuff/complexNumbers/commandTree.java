import java.lang.reflect.Method;
import java.util.Scanner;

class commandTree {
	private Node <complex> root;
	public MyFlags flags;

	//Constructor
	commandTree(){
		this.flags = new MyFlags();
	}

	//Inner classes
	public static class MyFlags{
		//This flags ends the loop on program
		protected boolean endflag;
		protected boolean helpflag;
		protected boolean boolflag;

		//Constructor
		MyFlags(){
			this.endflag = false;
			this.helpflag = false;
			this.boolflag = false;
		}

		//Getters
		public boolean getFlagEnd(){return this.endflag;}
		public boolean getFlagHelp(){return this.helpflag;}

		//Method
		private void flagEnd(){
			System.out.print("program will now exit. see ya later!\n");
		}

		private void flagHelp(){
			//Read from a help text file...
			System.out.print("...\n");
		}

		public boolean overallCheckup(){
			if (this.endflag) this.flagEnd();
			if (this.helpflag) this.flagHelp();

			//Maybe use reflection to create a general approach...
			return (this.endflag || this.helpflag || this.boolflag);
		}

		public void resetFlags(){
			//Will not reset endflag
			this.helpflag = false;
			this.boolflag = false;
		}
	};

	private class Node <T>{
		protected T value;
		protected Method myCommand;
		protected Node <T> sonL;
		protected Node <T> sonR;

		//Constructors
		Node(T newValue){
			this.value = newValue; 
			this.myCommand = null;
		}
		
		Node(Method newCommand){
			this.myCommand = newCommand; 
			this.value = null;
		}

		//Getters
		public T getVal(){return value;}
		public Method getCommand(){return myCommand;}
		protected Node <T> getSonL(){return this.sonL;} 
		protected Node <T> getSonR(){return this.sonR;} 

		//Method
		boolean isRoot(){return (this.sonL == null && this.sonR == null);}
	};

	private class UnaryNode <T> extends Node <T>{
		//Constructors
		UnaryNode(T newValue) {
			//Call on respective constructor of superclass Node
			super(newValue);
			this.sonL = null;
		}
		UnaryNode(Method newCommand) {
			super(newCommand);
			this.sonL = null;
		}

		//Setter
		protected void setSonL(Node <T> newSonL){this.sonL = newSonL;}
	};

	private class BooleanUnaryNode <T> extends UnaryNode <T>{
		boolean myResult;

		//Constructor
		BooleanUnaryNode(Method newCommand){
			super(newCommand);
			this.myResult = false;
		}
	};

	private class BinaryNode <T> extends UnaryNode <T>{
		//Constructors
		BinaryNode (T newValue){
			super(newValue);
			this.sonR = null;
		}
		BinaryNode (Method newCommand){
			super(newCommand);
			this.sonR = null;
		}

		//Setter
		protected void setSonR(Node <T> newSonR){this.sonR = newSonR;}

	}; 

	private class BooleanBinaryNode <T> extends BinaryNode <T>{
		boolean myResult;

		//Constructor
		BooleanBinaryNode(Method newCommand){
			super(newCommand);
			this.myResult = false;
		}
	};

	private Node <complex> recConstruct(Scanner myInput, Method[] methodList){
		Node <complex> myNode = null;
		if (myInput.hasNext()){
			//First check if this node is a Unary or Binary node
			if (myInput.hasNextDouble()){
				double newReal = Double.parseDouble(myInput.next());
				if (myInput.hasNextDouble()){
					myNode = new UnaryNode <complex> (
						new complex(newReal, Double.parseDouble(myInput.next())));
					//Ready to return a brand-new leaf.
				}
				//If false, null will be returned.
			} else {
				//We are sure that the next node will be a method,
				//if not a illegal command.
				Method m = null;
				String myMethod = myInput.next();
				for (Method k : methodList)
					if(k.getName().equals(myMethod)){
						//We found our method.
						m = k;
						//Break point here because its rational
						break;
					}

				if (m != null){
					//There's two unary operations on our complex program.
					//"conj" and "mod"
					//And two unary boolean verification
					//"isReal", "pureIm"
					//And one binary boolean verificarion
					//"equals"
					
					//Not much too proud of hardcoded stuff. 
					if (myMethod.equals("conj") || myMethod.equals("mod") ||
						myMethod.equals("pureIm") || myMethod.equals("isReal")){
						//Its unary...
						UnaryNode <complex> pointer = null;
						if ((myMethod.equals("pureIm") || myMethod.equals("isReal")) 
							&& !this.flags.boolflag){
							//Its a boolean operator, and its allowed (because boolflag = 0)
							pointer = new BooleanUnaryNode <complex> (m);
							this.flags.boolflag = true;
						} else pointer = new UnaryNode <complex> (m);

						pointer.setSonL(recConstruct(myInput, methodList));

						//Check if everything worked on last recursive call
						if (pointer.getSonL() != null)
							myNode = pointer;
						pointer = null;
					} else{
						//All other methods are a binary operation.
						BinaryNode <complex> pointer = null;
						if (myMethod.equals("equals") && !this.flags.boolflag){
							//Its a boolean operator, and its allowed (because boolflag = 0)
							pointer = new BooleanBinaryNode <complex> (m);
							this.flags.boolflag = true;
						} else pointer = new BinaryNode <complex> (m);

						pointer.setSonL(recConstruct(myInput, methodList));
						pointer.setSonR(recConstruct(myInput, methodList));

						//Check everything works fine
						if (pointer.getSonL() != null && pointer.getSonR() != null)
							myNode = pointer;
						pointer = null;
					}
				} else {
					//CHeck both for "exit" and "help" special commands,
					//But only if they're alone in the "expression"
					switch(myMethod){
						case "exit":
							this.flags.endflag = true;
							break;
						case "help":
							this.flags.helpflag = true;
							break;
						default:
							System.out.printf("what do you mean with \"%s\"?\n", myMethod);
							break;
					}
				}
				//Probably something went wrong at this point.
				//null will be returned by default.
			}
		}
		//Return root by default
		return myNode;
	};

	public boolean construct(Scanner myInput){
		if (myInput != null){
			//There must have a nicer way to do this...
			complex javaSucks = new complex(0.0, -0.0);
			Method[] methodList = javaSucks.getClass().getMethods();
			return ((this.root = recConstruct(myInput, methodList)) != null);
		}
		//Return false by default
		return false;
	};

	private complex recSolve(Node <complex> root){
		if (root.isRoot())
			return root.getVal();
		else if (root instanceof BinaryNode /*|| root instanceof BooleanBinaryNode*/){
			//Binary method
			try {
				Object dummy = root.getCommand().invoke(recSolve(root.getSonL()), 
					recSolve(root.getSonR()));
				if (!(root instanceof BooleanBinaryNode))
					return (complex) dummy;
				else 
					System.out.print((Boolean) dummy + "\n");
			} catch (Exception e){
				e.printStackTrace();
			}
		} else {
			//Unary method
			try {
				Object dummy = root.getCommand().invoke(recSolve(root.getSonL()));
				if (!(root instanceof BooleanUnaryNode))
					return (complex) dummy;
				else
					System.out.print((Boolean) dummy + "\n");
			} catch (Exception e){
				e.printStackTrace();
			}
		}
		return null;
	};

	public complex solve(){
		return recSolve(this.root);
	};

	public void purge(){this.root = null;}

	public boolean empty(){return (this.root == null);}

	private void printStuff(Node <complex> root, int offset){
		//Clean it up...
		for (int i = 0; i < offset; ++i)
			System.out.print(" ");

		if (root.getCommand() != null)
			System.out.print(root.getCommand().getName() + "\n");
		else 	
			root.getVal().print();
		
	}

	//Overload the recPrint
	private void recPrint (Node <complex> root, int offset){
		if (root != null){
			//Print
			printStuff(root, offset);

			recPrint(root.getSonL(), 3 + offset);
			if (root instanceof BinaryNode)
				recPrint(root.getSonR(), 3 + offset);
		}
	}

	public void print(){
		recPrint(this.root, 0);
	}
};