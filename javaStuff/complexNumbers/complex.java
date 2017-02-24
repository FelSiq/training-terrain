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
	public double r(){return re;}
	public double i(){return im;}

	//Methods
	private boolean abs(double val, double delta, char signal){
		if (val < 0)
			val *= (-1);
		if (signal == '-')
			return (val <= delta);
		return (val >= delta);
	}

	public void print(){
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

	public boolean isReal(){return this.abs(this.im, 0.0000001, '-');}

	public boolean pureIm(){return (this.abs(this.re, 0.0000001, '-') 
		&& this.abs(this.im, 0.0000001, '+'));}

	public boolean equals(complex z){
		return (abs(this.r() - z.r(), 0.0000001, '-') && 
			abs(this.i() - z.i(), 0.0000001, '-'));
	}

	public complex div(complex z){
		double aux = (z.r() * z.r()) + (z.i() * z.i());
		if (this.abs(aux, 0.0000001, '+')){
			double newR = (this.r()*z.r() + this.i()*z.i())/aux;
			double newI = (this.i()*z.r() - this.r()*z.i())/aux;
			return new complex(newR, newI);
		}
		return null;
	}

	public complex add(complex z){
		if (z != null)
			return new complex(this.r() + z.r(), this.i() + z.i());
		return null;
	}

	public complex sub(complex z){
		if (z != null)
			return new complex(this.r() - z.r(), this.i() - z.i());
		return null;
	}
	
	public complex mult(complex z){
		if(z != null)
		return new complex(this.r()*z.r() - this.i()*z.i(), 
			z.r()*this.i() + this.r()*z.i());
		return null;
	}

	public complex conj(){
		return new complex(this.r(), -this.i());
	}

	public complex mod(){
		return new complex(Math.sqrt(this.r()*this.r() + this.i()*this.i()), 0.0);
	}
};