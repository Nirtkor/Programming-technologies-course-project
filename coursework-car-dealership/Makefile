CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic

SRCS = main.cpp Car.cpp NewCar.cpp UsedCar.cpp \
       Manager.cpp Client.cpp Sale.cpp \
       Dealership.cpp View.cpp

OBJS   = $(SRCS:.cpp=.o)
TARGET = dealership

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET) dealership.dat

.PHONY: all clean
