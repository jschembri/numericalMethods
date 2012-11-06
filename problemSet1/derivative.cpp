#include <iostream>
#include <Eigen/Dense>
#include <math.h>

using namespace Eigen;
using namespace std;

double func(double x, double y){
	return sin(x)*cos(y);
}

double func_X(double x, double y){
	return cos(x)*cos(y);
}

double func_Y(double x, double y){
	return sin(x)*sin(y);
}

double func_XY(double x, double y){
	return -cos(x)*sin(y);
}

double func_XXY(double x, double y){
	return sin(x)*sin(y);
}

double cubic(double x, double y, MatrixXd a){
	double H = 0;
	for (int i=0; i<=3; i++){
		for (int j=0; j<=3; j++){
			H = H + a(i,j)*pow(x, i)*pow(y,j);
		}
	}
	return H;	
}

double derivative(double x, double y, MatrixXd a){
	double H;
	H = 2*a(2,1) +6*a(3,1)*x+4*a(2,2)*y+12*a(3,1)*x*y + 6*a(2,3)*y*y+18*a(3,2)*x*y*y;
	return H;	
}



int main(int argc, char **argv){
	double h = atof(argv[1]);
	double PI = 3.141592654;
	double x_low = 0;
	double x_high = 1;
	double y_low = 0;
	double y_high = 1;

	int x_spaces = (x_high-x_low)/h;  //
	int y_spaces = (y_high-y_low)/h;
	double x_values[x_spaces];
	double y_values[y_spaces];

		
	double f00, f10, f01, f11, fx00, fx10, fx01, fx11, fy00, fy10, fy01, fy11, fxy00, fxy10, fxy01, fxy11;
	f00 = func(0,0);
	f10 = func(1,0);
	f01 = func(0,1);
	f11 = func(1,1);
	fx00 = func_X(0,0);
	fx10 = func_X(1,0);
	fx01 = func_X(0,1);
	fx11 = func_X(1,1);
	fy00 = func_Y(0,0);
	fy10 = func_Y(1,0);
	fy01 = func_Y(0,1);
	fy11 = func_Y(1,1);
	fxy00 = func_XY(0,0);
	fxy10 = func_XY(1,0);
	fxy01 = func_XY(0,1);
	fxy11 = func_XY(1,1);



	MatrixXd m(16,16);
	MatrixXd A(16,16);
	MatrixXd a(4,4);
	VectorXf f(16); f << f00, f10, f01, f11, fx00, fx10, fx01, fx11, fy00, fy10, fy01, fy11, fxy00, fxy10, fxy01, fxy11;

	// setting the X and Y values
	for (int i=0; i<x_spaces; i++){
		x_values[i] = x_low + (x_high-x_low)/x_spaces*i;
	}
	for (int i=0; i<x_spaces; i++){
		y_values[i] = y_low + (y_high-y_low)/y_spaces*i;	
	}

	//  00,10,20,30,01,02,03,11,21,31,12,22,32,13,23,33,	
	m << 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		  1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		  1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		  0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		  0, 1, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		  0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,
		  0, 1, 2, 3, 0, 0, 0, 1, 2, 3, 1, 2, 3, 1, 2, 3,
		  0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		  0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0,
		  0, 0, 0, 0, 1, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		  0, 0, 0, 0, 1, 2, 3, 1, 1, 1, 2, 2, 2, 3, 3, 3,
		  0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
		  0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 0, 0, 0, 0, 0, 0,
		  0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 2, 0, 0, 3, 0, 0,
		  0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 2, 4, 6, 3, 6, 9;

	A = m.inverse();
	//cout << A << endl;

	for (int row=0; row<16;row++){
		for (int col=0; col<16;col++){
			if (row==0){
				a(0,0) += A(row, col) * f(col);
			}else if(row==1){
				a(1,0) += A(row, col) * f(col);
			}else if (row==2){
				a(2,0) += A(row, col) * f(col); 
			}else if(row==3){
				a(3,0) += A(row, col) * f(col); 
			}else if (row==4){
				a(0,1) += A(row, col) * f(col);
			}else if (row==5){
				a(0,2) += A(row, col) * f(col);
			}else if (row==6){
				a(0,3) += A(row, col) * f(col);
			}else if (row==7){
				a(1,1) += A(row, col) * f(col);
			}else if (row==8){
				a(2,1) += A(row, col) * f(col);
			}else if (row==9){
				a(3,1) += A(row, col) * f(col);
			}else if (row==10){
				a(1,2) += A(row, col) * f(col);
			}else if (row==11){
				a(2,2) += A(row, col) * f(col);
			}else if (row==12){
				a(3,2) += A(row, col) * f(col);
			}else if (row==13){
				a(1,3) += A(row, col) * f(col);
			}else if (row==14){
				a(2,3) += A(row, col) * f(col);
			}else if (row==15){
				a(3,3) += A(row, col) * f(col);
			}
		}
	}

// Calculating the Maximum Error
double max_error = 0;
double error = 0;
double wherex;
double wherey;

for (int i=0; i<x_spaces;i++){
	for (int j=0;j<y_spaces;j++){
		error = abs(derivative(x_values[i], y_values[j], a)-func_XXY(x_values[i], y_values[j]));
		if (error >= max_error){
			max_error = error;
			wherex = x_values[i]; 
			wherey = y_values[i]; 

		}
	}
}

//cout << "Maximum Error: "<< max_error << endl;
cout << max_error<<endl;
//cout << a <<endl;
/*
cout << "X: "<< wherex << endl;
cout << "Y: "<< wherey << endl;
cout << "Cubic: "<< derivative(wherex, wherey, a) << endl;
cout << "Func: "<<func_XXY(wherex, wherey) << endl;
*/


	return 0;
}

