CXX=g++
CXXFLAGS=-Wall -g

make jacob:
	$(CXX) $(CXXFLAGS) -I /usr/local/include/eigen -c jacob.cpp
	$(CXX) $(CXXFLAGS) -o jacob jacob.o

make iterative:
	$(CXX) $(CXXFLAGS) -I /usr/local/include/eigen -c iterative.cpp
	$(CXX) $(CXXFLAGS) -o iterative iterative.o

make sor:
	$(CXX) $(CXXFLAGS) -I /usr/local/include/eigen -c sor.cpp
	$(CXX) $(CXXFLAGS) -o sor sor.o

make test:
	$(CXX) $(CXXFLAGS) -I /usr/local/include/eigen -c test.cpp
	$(CXX) $(CXXFLAGS) -o test test.o

make vgrid:
	$(CXX) $(CXXFLAGS) -I /usr/local/include/eigen -c vgrid.cpp
	$(CXX) $(CXXFLAGS) -o vgrid vgrid.o

make resolution:
	$(CXX) $(CXXFLAGS) -I /usr/local/include/eigen -c resolution.cpp
	$(CXX) $(CXXFLAGS) -o resolution resolution.o

make time_resolution:
	$(CXX) $(CXXFLAGS) -I /usr/local/include/eigen -c time_resolution.cpp
	$(CXX) $(CXXFLAGS) -o time_resolution time_resolution.o

make residual:
	$(CXX) $(CXXFLAGS) -I /usr/local/include/eigen -c residual.cpp
	$(CXX) $(CXXFLAGS) -o residual residual.o

