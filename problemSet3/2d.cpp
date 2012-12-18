#include <iostream>
#include <math.h>
#include <cmath>
#include <string>
#include <cstdlib> 
#include <time.h>
#include <stdio.h>
#include <ctime>

using namespace std;
long double F1(long double x1, long double x2){
	return 2*x1-x2-exp(-x1);
}

long double F2(long double x1, long double x2){
	return -x1+2*x2-exp(-x2);
}


//derivatives
long double F1_x1(long double x1, long double x2){
	return 2+exp(-x1);
}

long double F1_x2(long double x1, long double x2){
	return -1;
}

long double F2_x1(long double x1, long double x2){
	return -1;
}

long double F2_x2(long double x1, long double x2){
	return 2+exp(-x2);
}

long double g1(long double x1, long double x2){
	return 0.5*(x2+exp(-x1));
}

long double g2(long double x1, long double x2){
	return 0.5*(x1+exp(-x2));
}



void printarray (long double arg[], int length, string input) {
  for (int i=0; i<length; i++)
      if (i==0){
         cout << input <<" Start" << "," << arg[i] << ",";
      }else if (i==length-1){
         cout << arg[i] << "," << input <<" End" << ",";
      }else{
         cout << arg[i] << ",";
      }
}



int main(int argc, char **argv){
   int max_iterations = atoi(argv[1]);
	long double iterations[max_iterations];
	long double newton_error[max_iterations];
	long double fpi_error[max_iterations];
	long double x1,x2,x1_plus1,x2_plus1, residual_x1,residual_x2;
	x1 = 5;
	x2 = 2;
	for (int i=0; i<10000;i++){
		x1 = g1(x1,x2);		
		x2 = g2(x1,x2);
	}
	long double answer_x1 = x1;
	long double answer_x2 = x2;


	x1 = 5;
	x2 = 2;
	//cout << "Newton's Method" << endl;
	//cout << "x1_plus1 , x2_plus1"<< endl;
	for (int i=0; i<max_iterations;i++){
		iterations[i] = i;
//		x1_plus1 = x1 + F1(x1,x2)/(x1*F1_x1(x1,x2) + x2*F1_x2(x1,x2));
//		x2_plus1 = x2 + F2(x1,x2)/(x1*F2_x1(x1,x2) + x2*F2_x2(x1,x2));
		long double a = F1_x1(x1,x2);
		long double b = F1_x2(x1,x2);
		long double c = F2_x1(x1,x2);
		long double d = F2_x2(x1,x2);
		long double s1,s2,det;
		det = a*d-b*c;

		s1 = 1.0/det*(-d*F1(x1,x2) + b*F2(x1,x2));
		s2 = 1.0/det*(c*F1(x1,x2) -a*F2(x1,x2));
		//calculating the max residualt
		residual_x1 = abs(x1 - answer_x1);		
		residual_x2 = abs(x2 - answer_x2);	
		if (residual_x1 >= residual_x2){
			newton_error[i] =residual_x1; 
		}else{
			newton_error[i] =residual_x2; 
		}

		if (newton_error[i] == 0 ){
			newton_error[i] = newton_error[i-1];
		}



		//cout << x1 << ", " << x2 << endl;
		x1 = x1 + s1;
		x2 = x2 + s2;
	}
	cout.precision(30);
	//cout << "FPI" << endl;
	//cout << "x1_plus1 , x2_plus1"<< endl;
	x1 = 5;
	x2 = 2;
	for (int i=0; i<max_iterations;i++){

		residual_x1 = abs(x1 - answer_x1);		
		residual_x2 = abs(x2 - answer_x2);	
		if (residual_x1 >= residual_x2){
			fpi_error[i] =residual_x1; 
		}else{
			fpi_error[i] =residual_x2; 
		}
		if (fpi_error[i] == 0 ){
			fpi_error[i] = fpi_error[i-1];
		}

		x1 = g1(x1,x2);		
		x2 = g2(x1,x2);

		//cout << x1 << ", " << x2 << endl;
	}
	printarray (iterations, max_iterations, "iterations");
   printarray (newton_error, max_iterations, "Newton");
   printarray (fpi_error, max_iterations, "fpi");
	return 0;
}
