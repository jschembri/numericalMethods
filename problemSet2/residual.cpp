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


int main(int argc, char **argv){
   int n = atof(argv[1]);
	string method = argv[2];
	int max_loop = atof(argv[3]);
   double h = 1.0/(n+1.0);
	//double max_error = pow(10,-6);
	double error =1;
   time_t t_start,t_end;
	double  dif_iterative, dif_matrix;
   VectorXf  x (n,1);
   VectorXf  xk (n,1);
   VectorXf  xkplus1 (n,1);
   VectorXf  f (n,1);
   MatrixXf A = MatrixXf::Zero(n,n);
   MatrixXf I = MatrixXf::Zero(n,n);
   VectorXf  b (n,1);
   VectorXf xc (n,1);

   for (int i=0; i<n;i++){
      x(i) = h*(i+1);
		f(i) = func(x(i));
   }

	for (int i=0;i<n;i++){
		A(i,i) = 2;
		if (i!=n-1){
			A(i,i+1) = -1;
			A(i+1,i) = -1;
		} 
	}
	b = f*pow(h,2);

	//Solving the Equation
   t_start = time(0);
   xc = A.colPivHouseholderQr().solve(b);
  	t_end=time(0);
  	dif_matrix = difftime (t_end,t_start);

/*
   cout << "Here is the matrix A:\n" << A << endl;
   cout << "Here is the vector x:\n" << x << endl;
   cout << "Here is the vector b:\n" << b << endl;
   cout << "Here is the vector uc:\n" << xc << endl;
*/
	//Jacobin part
	MatrixXf P = MatrixXf::Zero(n,n);
	MatrixXf Pinverse = MatrixXf::Zero(n,n);

	if (method == "Jacobian"){
		for (int i=0; i<n;i++){
      	P(i,i) = A(i,i);
   	}
	} else if (method=="Gauss-Seidel"){
		for (int i=0; i<n;i++){
      	P(i,i) = A(i,i);
			for (int j=0; j<i;j++){
				P(i,j) = A(i,j); 
			}
   	}
	} else if (method=="SOR"){
		double omega = atof(argv[3]);
		for (int i=0; i<n;i++){
      	P(i,i) = A(i,i);
			for (int j=0; j<i;j++){
				P(i,j) = omega*A(i,j); 
			}
   	}

	} else {
		return 1;
	}

	Pinverse = P.inverse();

   for (int i=0; i<n;i++){
      xk(i) = 0;
		I(i,i) = 1;
   }


   t_start = time(0);
	double repeat_error=100*n;
	for(int loop=0; loop<max_loop; loop++){
		xkplus1 = (I-Pinverse*A)*xk+Pinverse*b;
		xk = xkplus1;
		error = maximum_array(xc,xkplus1,n);
		//cout << loop<<endl;
		//cout << error<<endl;
		repeat_error = error;
		if (loop % 50==0 && loop != 0){
			cout <<loop<<","<<error<<endl;
		}
	}
  t_end=time(0);
	dif_iterative = difftime (t_end,t_start);


   return 0; 


}



