#include <iostream>
#include <math.h>
#include <cmath>
#include <Eigen/Dense>
#include <string>
#include <cstdlib> 
#include <time.h>
#include <stdio.h>
#include <ctime>


using namespace std;
using namespace Eigen;
double maximum_array( VectorXf answer,VectorXf guess, int length){
	double max;
	
	for(int i=0;i<length;i++){
		if (i==0){
			max = abs(answer(i)-guess(i) );
		}

		if (abs(answer(i)-guess(i)) > max){
			max = abs(answer(i)-guess(i) );
		}
	}

	return max;
}

double stdeviation( VectorXf answer,VectorXf guess, int length){

	double stdev = 0;
	
	for(int i=0;i<length;i++){
		stdev += pow(answer(i)-guess(i),2);
	}

	return pow(1.0/length*stdev,0.5);


}



double func(double x){
	double pi = 3.141592654;
	return (pow(pi,2)*(sin(pi*x)+pow(4,2)*sin(pi*4*x)+pow(9,2)*sin(pi*9*x)));
}


VectorXf gauss_seidel(VectorXf xk, MatrixXf A,VectorXf b, int n, double max_error,VectorXf xc){
   VectorXf  xkplus1 (n,1);
   MatrixXf I = MatrixXf::Zero(n,n);
	double error = 100*max_error;



	//Setting the pre-conditioner part
	MatrixXf P = MatrixXf::Zero(n,n);
	MatrixXf Pinverse = MatrixXf::Zero(n,n);
	for (int i=0; i<n;i++){
   	P(i,i) = A(i,i);
		for (int j=0; j<i;j++){
			P(i,j) = A(i,j); 
		}
	}


	Pinverse = P.inverse();

   for (int i=0; i<n;i++){
      //xk(i) = 0;
		I(i,i) = 1;
   }


	while(error >= max_error){
		xkplus1 = (I-Pinverse*A)*xk+Pinverse*b;
		xk = xkplus1;
		error = maximum_array(xkplus1,xc,n); 
	}

   return xkplus1; 
}

int main(int argc, char **argv){
   int n = atof(argv[1]);
	int rows;
	string method = argv[2];

	if (method=="simple"){
		rows = (n-1)/2;
	} else if (method=="average" || method=="weighted" || method=="random" || method=="mean"){
		rows = (n+1)/2;
		n=n+2;
	} else if (method=="quadratic"){
		rows = (n-1)/2;
	}
   double h = 1.0/(n+1.0);
	//int loop = 3; // number of iterations
   time_t t_start,t_end;
   VectorXf  f (n,1);
   VectorXf  x (n,1);
   VectorXf  rh(n,1),r2h(rows,1),Eh(n,1);
   VectorXf E2h = VectorXf::Zero(rows,1);
   VectorXf zeroes = VectorXf::Zero(rows,1);
   MatrixXf A = MatrixXf::Zero(n,n);
	MatrixXf A2h(rows,rows);
   VectorXf  b (n,1);
   VectorXf xc (n,1);
	double  dif_iterative, dif_matrix;
  
   MatrixXf I = MatrixXf::Zero(n,rows);
	MatrixXf R = MatrixXf::Zero(rows,n);
	MatrixXf In = MatrixXf::Random(n, rows); 


   for (int i=0; i<n;i++){
      x(i) = h*(i+1);
		f(i) = func(x(i));
   }

	for (int i=0;i<n;i++){
		A(i,i) = 1.0/pow(h,2)*2;
		if (i!=n-1){
			A(i,i+1) = 1.0/pow(h,2)*-1.0;
			A(i+1,i) = 1.0/pow(h,2)*-1.0;
		} 
	}
	b = f;

	if (method=="simple"){
		for (int i=0;i<rows;i++){
			I(2*i,i) = 1.0/2.0*1.0;
			I(2*i+1,i) = 1.0/2.0*2.0;
			I(2*i+2,i) = 1.0/2.0*1.0;
		}
	} else if (method=="average"){
		for (int i=0;i<n;i++){

			if (i==0){
				I(i,i) = 0.5*1.0;
			} else if (i+1==n){
				I(i,rows-1) = 0.5*1.0;
			} else if (i%2==0 && i+3 < n){
				I(i,i/2-1) = 0.5*1;
				I(i,i/2+1) = 0.5*1;
			} else if (i+3 == n){
				I(i,i/2-1) = 0.5*1;
				I(i,i/2) = 0.5*1;
			} else if (i %2==1){
				I(i,(i-1)/2) = 0.5*2;
			}

		}
	} else if (method=="weighted"){
		for (int i=0;i<n;i++){
			if (i%2==0){
				if (i >= 4){
					I(i,(i-4)/2) = 1.0/8.0*1;
				}
				if (i >=2){
					I(i,(i-4)/2+1) = 1.0/8.0*3;
				}

				if ((i-4)/2+3<rows){
					I(i,(i-4)/2+3) = 1.0/8.0*1;
				}
				if ((i-4)/2+2<rows){
					I(i,(i-4)/2+2) = 1.0/8.0*3;
				}

				if (i+1==n){
					I(i,rows-1) = 1.0/8.0*3;
					I(i,rows-2) = 1.0/8.0*1;
					I(i,rows-3) = 1.0/8.0*0;
				}

			} else if (i %2==1){
				I(i,(i-1)/2) = 1;
			}
				//I = 1.0/8.0*I;
		}

	} 	else if (method=="random"){
		I = In+0.5*MatrixXf::Ones(n,rows);

	} else if (method=="quadratic"){
		for (int i=0;i<n;i++){
			if (i %2==1){
				I(i,(i-1)/2) = 1;
			} else if (i%2==0 && i < (n+1)/2){
				if (i/2-1 >= 0){
					I(i,i/2-1) = 1.0/8.0*3;
				}
				if (i/2 >= 0){
					I(i,i/2) = 1.0/8.0*8;
				}
				I(i,i/2+1) = 1.0/8.0*-1;
			} else if (i%2==0 && i >= (n+1)/2){
				if (i/2 <= rows-1){
					I(i,i/2) = 1.0/8.0*3;
				}
				if (i/2-1 <= rows-1){
					I(i,i/2-1) = 1.0/8.0*8;
				}
				I(i,i/2-2) = 1.0/8.0*-1;
			}
		}

	} 	else if (method=="mean"){
		I = 1.0/rows*MatrixXf::Ones(n,rows);

	}
	R = 1.0/2.0*I.transpose();


	// Solving the equation
   t_start = time(0);
   xc = A.colPivHouseholderQr().solve(b); //the actual answer
  	t_end=time(0);
  	dif_matrix = difftime (t_end,t_start);

   t_start = time(0);
	// Solving the equation using a vgrid
	A2h = R*A*I;
	x = gauss_seidel(x,A,b,n,pow(10,-2),xc);
	//cout << "x with no interpolation is \n" << x <<endl;
	rh = b - A*x;
	r2h = R*rh;
	

	E2h= gauss_seidel(E2h,A2h,r2h,rows,pow(10,-2),zeroes);
	//cout << "E2h: \n" << E2h <<endl;
	Eh = I*E2h;
	//cout << "Eh: \n" << Eh <<endl;
	x = gauss_seidel(x+Eh,A,b,n,pow(10,-2),xc);
	//cout << "x iterative: \n" << x <<endl;
	//cout << "x answer: \n" << xc <<endl;

  	t_end=time(0);
  	dif_iterative = difftime (t_end,t_start);

	//cout << "Implicit time: " << dif_matrix  <<endl;
	cout <<	dif_iterative;

//	cout << "Maximum residual \n" << maximum_array(x,xc,n) <<endl;
	//cout << "Std: \n" << stdeviation(x,xc,n) <<endl;
	//cout << "R is \n" << R <<endl;
	//cout << "I is \n" << I <<endl;
	//cout << "In is \n" << In <<endl;


	return 0;
}



