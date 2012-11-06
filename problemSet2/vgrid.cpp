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

		if (answer(i)-guess(i) > max){
			max = abs(answer(i)-guess(i) );
		}
	}

	return max;
}

double func(double x){
	double pi = 3.141592654;
	return (pow(pi,2)*(sin(pi*x)+pow(4,2)*sin(pi*4*x)+pow(9,2)*sin(pi*9*x)));
}


VectorXf gauss_seidel(VectorXf xk, MatrixXf A,VectorXf b, int n, int loop){
   VectorXf  xkplus1 (n,1);
   MatrixXf I = MatrixXf::Zero(n,n);



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
      xk(i) = 0;
		I(i,i) = 1;
   }


	for(int i=0; i < loop;i++){
		xkplus1 = (I-Pinverse*A)*xk+Pinverse*b;
		xk = xkplus1;
	}

   return xkplus1; 
}

int main(int argc, char **argv){
   int n = atof(argv[1]);
   double h = 1.0/(n+1.0);
	int loop = 3; // number of iterations
   time_t t_start,t_end;
   VectorXf  f (n,1);
   VectorXf  x (n,1);
   VectorXf  rh(n,1),r2h((n-1)/2,1),Eh(n,1);
   VectorXf E2h = VectorXf::Zero((n-1)/2,1);
   MatrixXf A = MatrixXf::Zero(n,n);
	MatrixXf A2h((n-1)/2,(n-1)/2);
   VectorXf  b (n,1);
   VectorXf xc (n,1);
	double  dif_iterative, dif_matrix;
  
   MatrixXf I = MatrixXf::Zero(n,(n-1)/2);
	MatrixXf R = MatrixXf::Zero((n-1)/2,n);


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

	for (int i=0;i<(n-1)/2;i++){
		I(2*i,i) = 1.0/2.0*1.0;
		I(2*i+1,i) = 1.0/2.0*2.0;
		I(2*i+2,i) = 1.0/2.0*1.0;
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
	x = gauss_seidel(x,A,b,n,loop);
	rh = b - A*x;
	r2h = R*rh;
	

	E2h= gauss_seidel(E2h,A2h,r2h,(n-1)/2,loop);
	Eh = I*E2h;

	x = gauss_seidel(x+Eh,A,b,n,loop);

  	t_end=time(0);
  	dif_iterative = difftime (t_end,t_start);

	cout << "Maximum residual \n" << maximum_array(x,xc,n) <<endl;
	//cout << "R is \n" << R <<endl;
	//cout << "I is \n" << I <<endl;


	return 0;
}



