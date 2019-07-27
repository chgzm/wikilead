PROGRAM := wikilead
OBJS := Main.o WikiParser.o
CXX := g++
INCLUDES := -I./include
FLGS := -std=c++14 
CXXFLAGS := -Wall -O2

.PHONY: all
$(PROGRAM): $(OBJS)
	$(CXX) $(FLGS) $(CXXFLAGS) -o $(PROGRAM) $(OBJS) -lcurl

.cpp.o:
	$(CXX) $(FLGS) $(CXXFLAGS) $(INCLUDES) -c $< -o $@ -lcurl

.PHONY: clean
clean:
	$(RM) $(OBJS) $(PROGRAM)
