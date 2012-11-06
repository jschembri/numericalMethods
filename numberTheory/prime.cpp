#include <iostream>
#include <string>
#include <cstdlib> 
#include <cmath>


using namespace std;

void printarray (double arg[], int length, string input) {
  for (int i=0; i<length; i++)
      if (i==0){
         cout << input <<" Start" << "," << arg[i] << ",";
      }else if (i==length-1){
         cout << arg[i] << "," << input <<" End" << ",";
      }else{
         cout << arg[i] << ",";
      }
}

double func(double x, int prime){
	double PI = 3.141592654;
	return cos(2*PI*x)*cos(2*PI*prime/x);

}

double lagrange_interpolation(double x, double x_values[], double y_values[], int degree){
	double L = 0;
	double f_at_x;
	for(int i=0; i<= degree; i++){
		f_at_x = y_values[i];
		for(int j=0; j<= degree; j++){
			if (i != j){
				f_at_x  = f_at_x * (x-x_values[j])/(x_values[i] - x_values[j]);
			}
		}
		L = L + f_at_x;
	}
	return L;
}




int main(int argc, char **argv){

	int x_spaces = 100;
	int degree = 25;
   int prime = atof(argv[1]);
	int x_start = 1;
	int x_end = prime;
	double x_values[x_spaces+1];
	double y_values[x_spaces+1];
	double x_lagrange[x_spaces+1];
	double y_lagrange[x_spaces+1];
	double x_lagrange_values[degree+1];
	double y_lagrange_values[degree+1];

	// This is for the analytical answer
	for(int i=0;i<x_spaces;i++){
		x_values[i] = x_start + (x_end-x_start) / (1.0*x_spaces-1.0) *(i);
		y_values[i] = func(x_values[i], prime);
	}
	
	// the points to be used for Lagrangian
	for(int i=0;i<degree+1;i++){
		x_lagrange_values[i] = x_start + (x_end-x_start) / (1.0*degree) *(i);
		y_lagrange_values[i] = func(x_lagrange_values[i],prime);
	}

	for(int i=0;i<x_spaces;i++){
		x_lagrange[i] = x_values[i];
		y_lagrange[i] = lagrange_interpolation(x_lagrange[i],x_lagrange_values,y_lagrange_values,degree);
	}



	printarray(x_values, x_spaces, "X Values");
	printarray(y_values, x_spaces, "Y Values");
	printarray(x_lagrange_values, degree+1, "X Lagrange Values");
	printarray(y_lagrange_values, degree+1, "Y Lagrange Values");
	printarray(x_lagrange, x_spaces, "X Lagrange");
	printarray(y_lagrange, x_spaces, "Y Lagrange");


   return 0; 


}

