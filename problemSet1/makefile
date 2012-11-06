CXX=g++
CXXFLAGS=-Wall -g

make bicubic:
	$(CXX) $(CXXFLAGS) -I /usr/local/include/eigen -c bicubicMatrix.cpp 
	$(CXX) $(CXXFLAGS) -o bicubicMatrix bicubicMatrix.o

make twoD:
	$(CXX) $(CXXFLAGS) -I /usr/local/include/eigen -c twoD.cpp 
	$(CXX) $(CXXFLAGS) -o twoD twoD.o

make derivative:
	$(CXX) $(CXXFLAGS) -I /usr/local/include/eigen -c derivative.cpp 
	$(CXX) $(CXXFLAGS) -o derivative derivative.o


