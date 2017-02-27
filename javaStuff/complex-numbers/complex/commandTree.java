package complex;
import java.lang.reflect.Method;//To Method
import java.lang.reflect.Field;//To Field (variables)
import java.lang.reflect.Modifier;//To Modifier
import java.util.Scanner;//TO Scanner
import java.io.*; //To File/Reader/Writes

public class commandTree {
	private Node <complex> root;
	final public MyFlags flags;
	private complex lastResult;

	//Constructor in package must be public
	public commandTree(){
		this.flags = new MyFlags(false);
		this.lastResult = null;
	}

	public commandTree(boolean myDEBUG){
		this.flags = new MyFlags(myDEBUG);
		this.lastResult = null;
	}

	//Getter
	public complex lastRes(){return lastResult;}

	//Inner classes
	public static class MyFlags{
		//This flags ends the loop on program
		final private Field[] allflags; 
		private boolean endflag; //Private == 2
		private boolean debugflag;
		protected boolean helpflag; //Protected == 4
		protected boolean boolflag;
		protected boolean prevflag;

		//Constructor
		MyFlags(boolean myDEBUG){
			//Set end flag to false, only this time.
			this.endflag = false;
			this.debugflag = myDEBUG;
			//Get all declared methods on this class
			allflags = MyFlags.class.getDeclaredFields();
			//Clean up the flags
			this.resetFlags();
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
			File fp = new File("./help");
			//Checks if fp succeed on openning desired help file
			if (fp.exists()){
				try {
					BufferedReader myReader = new BufferedReader(new FileReader(fp));
					String myString = null;
					do {
						//readLine() does not read end-on-line "\n"
						myString = myReader.readLine();
						if (myString != null)
							System.out.print(myString + "\n");
					} while(myString != null);
					myReader.close();
				} catch (Exception e){
					e.printStackTrace();
				}
			} else System.out.print("Sorry, but I do not found a help file.\n");
		}

		private void flagPrev(){
			System.out.print("There's no previous result to operate (null or boolean).\n");
		}

		public boolean overallCheckup(){
			//Next flags should be modifying ONLY here due to reflection
			if (this.endflag) this.flagEnd();
			if (this.helpflag) this.flagHelp();
			if (this.prevflag) this.flagPrev();

			//Use reflection
			boolean myRet = false;
			for(Field k : this.allflags){
				if (Modifier.isProtected(k.getModifiers())){
					try {
						if(myRet = (boolean) k.get(this))
						 	break;
					} catch (Exception e){
						e.printStackTrace();
					}
				}
			}

			//endflag are taken into consideration on this return
			return (this.endflag || myRet);
		}

		public void resetFlags(){
			//Will not reset endflag (modified to be private)
			//Using reflection
			for (Field k : this.allflags){
				if (Modifier.isProtected(k.getModifiers())){
					try {
						k.setBoolean(this, false);
					} catch (Exception e){
						e.printStackTrace();
					}
				}
			}
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
					//There's three unary operations on our complex program.
					//"conj", "mod", "redo"
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
						case "redo":
							//This is a special keyword to recover last result.
							if (this.lastResult != null)
								myNode = new Node <complex>(this.lastResult);
							else
								this.flags.prevflag = true;
							//If don't exists a previous result, then null will be returned.
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
			boolean result = ((this.root = recConstruct(myInput, methodList)) != null);
			
			if (this.flags.debugflag){
				if (result){
					System.out.print("Final expression tree result:\n");
					this.print();
				} else System.out.print("d: can't create expression tree.\n");
			}
			return result;
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
		complex aux = recSolve(this.root);
		if (aux != null)
			this.lastResult = aux;
		return aux;
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