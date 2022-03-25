TC_FOLDER = tests
EXT_IN = in
EXT_OUT = out
EXT_ANS = ans
EXECUTABLE_FILENAME = main
CLASS_FOLDER = class

TESTS := $(wildcard $(TC_FOLDER)/*.$(EXT_IN))
ALL_SRCS := $(wildcard $(CLASS_FOLDER)/*.cpp) $(wildcard *.cpp)
SRCS     := $(filter-out check.cpp, $(ALL_SRCS))

all: compile test check

# Compile all cpp files except check.cpp
compile:
	g++ -std=c++17 -o $(EXECUTABLE_FILENAME) $(SRCS)

# Test
test: $(TESTS) compile
	$(foreach inputfile, $(TESTS), .\$(EXECUTABLE_FILENAME) < $(inputfile) &&) echo.

# Check
check: FORCE check.cpp
	g++ -std=c++17 -o check check.cpp
	.\check

FORCE: ;
