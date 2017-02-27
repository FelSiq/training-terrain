//Not permited
/*static class myStaticAuxClass{

}*/

class MyAuxClass{
	int x;

	static void genericMethod(){
		System.out.print("This method can be called without any instance of MyAuxClass.\n");
	}

	MyAuxClass(){}
}

//Nor on main class of this source
class StaticStudy{
	//Works ok.
	static class MyStaticInnerClass{
		int k;

		MyStaticInnerClass(){}
	}

	static private void genericMethod(){
		MyAuxClass.genericMethod();
	}

	static public void main(String[] args){
		genericMethod();
	}
};


/*

Static method:
	Can be called from everywhere (even from a non-static scope), 
	without any of the respective class instance.

*/