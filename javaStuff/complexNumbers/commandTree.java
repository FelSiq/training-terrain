import java.lang.reflect.Method;
import java.util.Scanner;

class commandTree {
	private Node <complex> root;

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
	};

	private class UnaryNode <T> extends Node <T>{

		boolean isRoot(){return (this.sonL == null);}

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

	private class BinaryNode <T> extends UnaryNode <T>{

		boolean isRoot(){return (super.isRoot() && this.sonR == null);}

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

	private Node <complex> recConstruct(Scanner myInput, Method[] methodList){
		Node <complex> myNode = null;
		if (myInput.hasNext()){
			//First check if this node is a Unary or Binary node
			if (myInput.hasNextDouble()){
				myNode = new UnaryNode <complex> (
					new complex(Double.parseDouble(myInput.next()), 
						Double.parseDouble(myInput.next())));
				//Ready to return a brand-new leaf.
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
					
					//Not much too proud of hardcoded stuff. 
					if (myMethod.equals("conj") || myMethod.equals("mod")){
						UnaryNode <complex> pointer =  new UnaryNode <complex> (m);
						pointer.setSonL(recConstruct(myInput, methodList));
						myNode = pointer;
						pointer = null;
					} else{
						//All other methods are a binary operation.
						BinaryNode <complex> pointer = new BinaryNode <complex> (m);
						pointer.setSonL(recConstruct(myInput, methodList));
						pointer.setSonR(recConstruct(myInput, methodList));
						myNode = pointer;
						pointer = null;
					}
				} else {
					System.out.print("error: invalid syntax on this command.\n");
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

	public complex solve(){

		//return null by default
		return null;
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