import java.util.*; 

class complex{
	private double re, im;
	//Constructors
	complex(double paramR, double paramI){
		re = paramR;
		im = paramI;
	}

	complex(){
		re = 0;
		im = 0;
	}

	//Getters
	double r(){return re;}
	double i(){return im;}

	//Methods
	private boolean abs(double val, double delta, char signal){
		if (val < 0)
			val *= (-1);
		if (signal == '-')
			return (val <= delta);
		return (val >= delta);
	}

	void print(){
		if (this != null){
			if (re == 0 && im == 0)
				System.out.print("0");
			else {
				if (re != 0){
					System.out.print(re);
					if (im > 0)
						System.out.print("+");
				}
				if (im != 0)
					System.out.print(im + "i");
			}
			System.out.print("\n");
		}
	}

	boolean isReal(){return this.abs(this.im, 0.0000001, '-');}

	boolean pureIm(){return (this.abs(this.re, 0.0000001, '-') 
		&& this.abs(this.im, 0.0000001, '+'));}
};