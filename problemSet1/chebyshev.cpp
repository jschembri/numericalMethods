#include <iostream>
#include <math.h>
#include <cstdlib> 
#include <string>
#include <iomanip>
#include <sstream>

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

double func(double x, string name){
	if (name == "sine") {
		return sin(x);
	} else if (name == "power") {
		return pow(x,6);
	}
}

double cheby_interpolation(double x, double x_values[], double y_values[], int length){
	double L = 0;
	double f_at_x;
	for(int i=0; i<= length; i++){
		f_at_x = y_values[i];
		for(int j=0; j<= length; j++){
			if (i != j){
				f_at_x  = f_at_x * (x-x_values[j])/(x_values[i] - x_values[j]);
			}
		}
		L = L + f_at_x;
		//cout << L << endl;
	}
	return L;
}

int main(int argc, char **argv){

	int degree = atof(argv[1]);
	double h = atof(argv[2]);
	string name = argv[3];
	
	double a = 0;
	double b = 10;
	int h_spaces = (b-a)/h;  //the amount of elements including 0
	double PI = 3.141592654;

	// Calculating the points
	double x_values[degree];
	double y_values[degree];
	double x_cheby[h_spaces];
	double y_cheby[h_spaces];
	

	for (int i=0; i <= (degree-1); i++){
		x_values[i] = (1.0/2)*((b-a)*cos( (degree+0.5-(i+1))*PI/(degree) )+a+b);
		//cout << "X Value is: " << x_values[i] << endl;
		y_values[i] = func(x_values[i],name);
	}

	// Calculating the Lagrangian Interpolation

	for (int i=0; i <= h_spaces; i++){
		x_cheby[i] = a + (b-a)/h_spaces*i;	
		y_cheby[i] = cheby_interpolation(x_cheby[i],x_values,y_values,(degree-1));
	}


//	printarray(x_values,degree,"X Points");
//	printarray(y_values,degree,"Y Points");
//	printarray(x_cheby,h_spaces+1,"X Lagrange");
//	printarray(y_cheby,h_spaces+1,"Y Lagrange");

	
	// Finding the maximum absolute Value
	double error[h_spaces];
	double max_error = 0;

	for (int i=0; i <= h_spaces; i++){
		error[i] = fabs( y_cheby[i] - func(x_cheby[i],name) );
		if (error[i] >= max_error){
			max_error = error[i];
		}
	}

/*
	printarray(x_values,degree+1,"X Points");
	printarray(y_values,degree+1,"Y Points");
	printarray(x_lagrange,h_spaces+1,"X Lagrange");
	printarray(error,h_spaces+1,"Y Lagrange");
*/

	cout.precision(10);
	cout << scientific << max_error << ",";
	return 0;
}
