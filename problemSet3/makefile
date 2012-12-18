CXX=g++
CXXFLAGS=-Wall -g

convergenceRate:
	$(CXX) $(CXXFLAGS) -c convergenceRate.cpp 
	$(CXX) $(CXXFLAGS) -o convergenceRate convergenceRate.o 

porous:
	$(CXX) $(CXXFLAGS) -c porous.cpp 
	$(CXX) $(CXXFLAGS) -o porous porous.o 

2d:
	$(CXX) $(CXXFLAGS) -c 2d.cpp 
	$(CXX) $(CXXFLAGS) -o 2d 2d.o 


clean:
	rm -f convergenceRate convergenceRate.o
	rm -f pointers
	rm -f 2d

