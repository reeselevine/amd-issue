CXX = g++
CXXFLAGS = -std=c++17

.PHONY: clean easyvk

all: build easyvk kernel

build:
	mkdir -p build

clean:
	rm -r build

easyvk: easyvk/src/easyvk.cpp easyvk/src/easyvk.h
	$(CXX) $(CXXFLAGS) -Ieasyvk/src -c easyvk/src/easyvk.cpp -o build/easyvk.o

kernel: kernel.cpp kernel.spv
	$(CXX) $(CXXFLAGS) -Ieasyvk/src build/easyvk.o kernel.cpp -lvulkan -o build/kernel

%.spv: %.wgsl
	tint $< -o build/$@
