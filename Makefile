CXX=g++ -std=c++11
MAINFILE=code/main

all: data/example.ans data/medium.ans data/big.ans

sample: data/example.ans

$(MAINFILE): $(MAINFILE).cpp
	$(CXX) -o $(MAINFILE) $(MAINFILE).cpp

data/example.ans: $(MAINFILE)
	$(MAINFILE) < data/example.in > $@

data/small.ans: 
	cp $@.static $@

data/medium.ans: $(MAINFILE)
	$(MAINFILE) simplehorizontal < data/medium.in > $@

data/big.ans: $(MAINFILE)
	$(MAINFILE) dp < data/big.in > $@
