#include <iostream>
#include <math.h>
#include <cmath>
#include <string>
#include <cstdlib> 
#include <time.h>
#include <stdio.h>
#include <ctime>

using namespace std;

long double func(long double x){
	return pow(x,2) - 4*sin(x);
}

long double gfunc(long double x){
	return  pow(4*sin(x),0.5);
}




long double derivative_func(long double x){
	return 2*x - 4*cos(x);
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



long double bisection_search(double umin, double umax){
	double uguess, ymin, ymax, yguess;
	while (umax-umin>0.0000000000000003){
		uguess = (umin + umax)/2;

		ymin = func(umin);
		yguess = func(uguess);
		ymax = func(umax);

		if (yguess > 0){
			umax = uguess;
		} else if (yguess < 0){
			umin = uguess;
		} else if (yguess == 0){
			return uguess;
		}
	}
	
	return uguess;
}







int main(int argc, char **argv){
   int max_iterations = atoi(argv[1]);
	long double iterations[max_iterations];
	long double bisection_error[max_iterations];
	long double uguess, umax, umin;
	umax = 4;
	umin = 0.5;

	long double answer = bisection_search(0.5,4);
	
	long double ymin, ymax, yguess;
	for (int i=0; i<max_iterations;i++){
		iterations[i] = i;
		uguess = (umin + umax)/2;
		ymin = func(umin);
		yguess = func(uguess);
		ymax = func(umax);

		if (yguess > 0){
			umax = uguess;
		} else if (yguess < 0){
			umin = uguess;
		} else if (yguess == 0){
			bisection_error[i] = 0;
		}
		bisection_error[i] = abs(uguess-answer);
	
	}
	printarray (iterations, max_iterations, "iterations");
   printarray (bisection_error, max_iterations, "Bisection");

	//secant method
	long double xplus1,x, xminus1;
	long double f, fminus1;
	long double secant_error[max_iterations];
	xminus1 = 6;
	x = 5.9;

	for (int i=0; i<max_iterations;i++){
		f = func(x);
		fminus1 = func(xminus1);
		xplus1 = x -f*(x-xminus1)/(f-fminus1);
		if (secant_error[i-1] == secant_error[i-2] && i > 5){
			secant_error[i] = secant_error[i-1];
		}else{
			secant_error[i] = abs(xplus1 - answer);
		}
		xminus1 = x;
		x = xplus1;	
			
	}
   printarray (secant_error, max_iterations, "Secant");

	// netwon's Method
	long double newton_error[max_iterations];
	long double newton_xplus1, newton_x;
	newton_x = 4;
	for (int i=0; i<max_iterations;i++){
		newton_xplus1 = newton_x - func(newton_x)/derivative_func(newton_x);
		newton_error[i] = abs(newton_xplus1-answer);
		newton_x = newton_xplus1;
	}
   printarray (newton_error, max_iterations, "Newton");

	// FPI
	long double fpi_error[max_iterations];
	long double fpi_xplus1, fpi_x;
	fpi_x = 2;
	for (int i=0; i<max_iterations;i++){
		fpi_xplus1 = gfunc(fpi_x);
		fpi_error[i] = abs(fpi_xplus1-answer);
		fpi_x = fpi_xplus1;
	}
   printarray (fpi_error, max_iterations, "FPI");

	//FPI Aikten's Method
	long double aikten_error[max_iterations];
	long double aikten_xplus1, aikten_x,error_n,error_nplus1;
	aikten_x = 2;
	//cout << endl;
	for (int i=0; i<max_iterations;i++){
		error_n = gfunc(aikten_x)-aikten_x;
		//cout << "error_n " << error_n<< endl;
		aikten_xplus1 = gfunc(aikten_x);
		//cout << "aikten_xplus1 " << aikten_xplus1<< endl;
		error_nplus1 = gfunc(aikten_xplus1) -aikten_xplus1;
		//cout << "error_nplus1 " << error_nplus1<< endl;
		if (error_nplus1 - error_n == 0){
			aikten_error[i] = abs(aikten_x-answer);
		}else{
			aikten_xplus1 = aikten_x - pow(error_n,2)/(error_nplus1 - error_n);
			aikten_error[i] = abs(aikten_xplus1-answer);
		}

		aikten_x =aikten_xplus1; 
		//cout << "aikten_xplus1: " << aikten_xplus1<< endl;
	}
   printarray (aikten_error, max_iterations, "aikten");

	return 0;
}
