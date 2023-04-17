CXX=g++
CXXFLAGS=-std=c++17 -Wall -pedantic -g -fsanitize=address
LDFLAGS=-fsanitize=address
TARGET=a.out

SRCS=Exercise_3.cpp
OBJS=$(SRCS:.cpp=.o)
DEPS=$(SRCS:.cpp=.d)

.PHONY: clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

clean:
	$(RM) $(TARGET) $(OBJS) $(DEPS)
