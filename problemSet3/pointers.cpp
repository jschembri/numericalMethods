#include <iostream>

using namespace std;

int main(){
	double andy, ted, fred;

	andy = 25;
	fred = andy;
	ted = &andy;
	
	cout << "Andy: " << andy << endl;
	cout << "Fred: " << fred << endl;
	cout << "ted: " << ted << endl;
}
