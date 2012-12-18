#include <iostream>
#include <math.h>
#include <cmath>
#include <string>
#include <cstdlib> 
#include <time.h>
#include <stdio.h>
#include <ctime>

using namespace std;


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

//long double gfunc(long double u_minus1, long double u_i, long double u_plus1, long double delta_x){
//	return u_minus1 + (pow((u_i+u_plus1),2)*(u_plus1-u_i)-4*pow(delta_x,2))/(pow((u_i+u_minus1),2));
//}

//long double gfunc(long double u_minus1, long double u_i, long double u_plus1, long double delta_x){
//	return u_plus1 - (pow((u_i+u_minus1),2)*(u_i-u_minus1)+4*pow(delta_x,2))/(pow((u_i+u_plus1),2));
//}


//long double gfunc(long double u_minus1, long double u_i, long double u_plus1, long double delta_x){
//	long double equation = pow((u_i+u_plus1),2)*(u_plus1-u_i)-4*pow(delta_x,2)-pow(u_i,2)*u_minus1+u_i*pow(u_minus1,2)+pow(u_minus1,3);
//	return pow(equation,1.0/3.0);
//}

//long double gfunc(long double u_minus1, long double u_i, long double u_plus1, long double delta_x){
//	long double equation = -pow(u_i,2)*u_minus1+u_i*pow(u_plus1,2)+pow(u_plus1,3)-4*pow(delta_x,2)-pow(u_minus1+u_i,2)*(u_i-u_minus1);
//	return pow(equation,1.0/3.0);
//}



//long double gfunc(long double u_minus1, long double u_i, long double u_plus1, long double delta_x){
//	return pow((pow(u_i+u_plus1,2)*(u_plus1-u_i)-4*pow(delta_x,2))/(u_i-u_minus1),0.5)+u_minus1;
//}

//long double gfunc(long double u_minus1, long double u_i, long double u_plus1, long double delta_x){
//	return pow((delta_x/(u_plus1-u_minus1)),2)*(1 - u_i*(u_plus1-2*u_i+u_minus1)/(pow(delta_x,2)));
//}

//long double gfunc(long double u_minus1, long double u_i, long double u_plus1, long double delta_x){
//	return pow((2*delta_x/(u_plus1-u_i)),2)*(1 - u_i*(u_plus1-2*u_i+u_minus1)/(pow(delta_x,2)));
//}

//long double gfunc1(long double u_minus1, long double u_i, long double u_plus1, long double delta_x){
//	return (1.0/pow(u_plus1,2))*(2*pow(u_i,2)*u_plus1-u_i*pow(u_minus1,2)+ (2.0/pow(delta_x,2))*(1-u_i*(u_plus1-2*u_i+u_minus1)/(pow(delta_x,2))));
//}

//long double gfunc2(long double u_minus1, long double u_i, long double u_plus1, long double delta_x){
//	return (1.0/pow(u_minus1,2))*(2*pow(u_i,2)*u_plus1-u_i*pow(u_plus1,2)+ (2.0/pow(delta_x,2))*(1-u_i*(u_plus1-2*u_i+u_minus1)/(pow(delta_x,2))));
//}

//long double gfunc(long double u_minus1, long double u_i, long double u_plus1, long double delta_x){
//	return 0.5/pow(u_plus1-u_i,2)*(pow(delta_x,2)-pow(u_i,2)*(u_plus1-2*u_i+u_minus1));
//}

//long double gfunc(long double u_minus1, long double u_i, long double u_plus1, long double delta_x){
//	return -0.25*(2*pow(delta_x,2)/u_i - pow(u_plus1-u_minus1,2)-2*u_plus1-2*u_minus1); 
//}

long double gfunc(long double u_minus1, long double u_i, long double u_plus1, long double delta_x){
	return pow(-0.25*(2*pow(delta_x,2) - u_i*pow(u_plus1-u_minus1,2)-u_i*2*u_plus1-u_i*2*u_minus1),0.5); 
}

long double max_error(long double u_plus1[], long double answer[], int N){
	double long error = -1;
	for (int i=0;i<N;i++){
		if (abs(u_plus1[i] - answer[i]) >= error){
			error = abs(u_plus1[i] - answer[i]);
		}
	}
	return error;
} 



int main(int argc, char **argv){
   int max_iterations = atoi(argv[1]);
	int N = 100;
	long double iterations[N];
	long double actual_iterations[max_iterations+1];
	long double uguess[N];
	long double u_plus1[N];
	long double answer[N];
	long double error[max_iterations+1];
	long double a, b;
	a = 0;
	b = 0;
	long double delta_x = 1.0/(N-1);


	for (int i=0;i<N;i++){
		iterations[i] = delta_x*i;
		uguess[i] = 0.5;
	}
		uguess[0] = 0;
		uguess[N-1] = 0;


	for(int j=0; j<=max_iterations; j++){
		for (int i=1;i<N-1;i++){
			u_plus1[i] = gfunc(uguess[i-1],uguess[i],uguess[i+1],delta_x);
		}
		for (int i=1;i<N-1;i++){
			uguess[i] = u_plus1[i];
		}
	}
	for (int i=0;i<N;i++){
		answer[i] = u_plus1[i];
	}	



	for (int i=0;i<N;i++){
		iterations[i] = delta_x*i;
		//uguess[i] = -(pow((iterations[i]-0.5),2)+0.25)*0.5;
		//uguess[i] = i;
		uguess[i] = -0.5;
//		if (i %2 == 0){
//			uguess[i] = 20;
//		}else{
//			uguess[i] = 1;
//		}
		uguess[0] = 0;
		uguess[N-1] = 0;
	}

	for(int j=0; j<=max_iterations; j++){
		actual_iterations[j] = j;
		for (int i=1;i<N-1;i++){
			u_plus1[i] = gfunc(uguess[i-1],uguess[i],uguess[i+1],delta_x);
//			if (i == N-2){
//				u_plus1[i] = gfunc2(uguess[i-1],uguess[i],uguess[i+1],delta_x);
//			}else if (i ==1){
//				u_plus1[i] = gfunc1(uguess[i-1],uguess[i],uguess[i+1],delta_x);
//			}else{
//				u_plus1[i] = 0.5*(gfunc1(uguess[i-1],uguess[i],uguess[i+1],delta_x)+gfunc2(uguess[i-1],uguess[i],uguess[i+1],delta_x));
//			}
		}
		for (int i=1;i<N-1;i++){
			uguess[i] = u_plus1[i];
		}
		error[j] = max_error(u_plus1, answer, N);
		
	}



	printarray (iterations, N, "iterations");
   printarray (uguess, N, "fpi");
	printarray (error, max_iterations+1, "error");
	printarray (actual_iterations, max_iterations+1, "actual");
	return 0;
}
