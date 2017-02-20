CXX=g++ -std=c++11
MAINFILE=code/main

all: data/example.dp.ans data/small.dp.ans data/medium.dp.ans data/big.dp.ans data/example.simplehorizontal.ans data/small.simplehorizontal.ans data/medium.simplehorizontal.ans data/big.simplehorizontal.ans data/example.simplevertical.ans data/small.simplevertical.ans data/medium.simplevertical.ans data/big.simplevertical.ans

sample: data/example.dp.ans data/example.simplehorizontal.ans data/example.simplevertical.ans

$(MAINFILE): $(MAINFILE).cpp
	$(CXX) -o $(MAINFILE) $(MAINFILE).cpp

data/example.dp.ans: $(MAINFILE)
	$(MAINFILE) dp < data/example.in > $@

data/small.dp.ans: $(MAINFILE)
	$(MAINFILE) dp < data/small.in > $@

data/medium.dp.ans: $(MAINFILE)
	$(MAINFILE) dp < data/medium.in > $@

data/big.dp.ans: $(MAINFILE)
	$(MAINFILE) dp < data/big.in > $@

data/example.simplehorizontal.ans: $(MAINFILE)
	$(MAINFILE) simplehorizontal < data/example.in > $@

data/small.simplehorizontal.ans: $(MAINFILE)
	$(MAINFILE) simplehorizontal < data/small.in > $@

data/medium.simplehorizontal.ans: $(MAINFILE)
	$(MAINFILE) simplehorizontal < data/medium.in > $@

data/big.simplehorizontal.ans: $(MAINFILE)
	$(MAINFILE) simplehorizontal < data/big.in > $@

data/example.simplevertical.ans: $(MAINFILE)
	$(MAINFILE) simplevertical < data/example.in > $@

data/small.simplevertical.ans: $(MAINFILE)
	$(MAINFILE) simplevertical < data/small.in > $@

data/medium.simplevertical.ans: $(MAINFILE)
	$(MAINFILE) simplevertical < data/medium.in > $@

data/big.simplevertical.ans: $(MAINFILE)
	$(MAINFILE) simplevertical < data/big.in > $@

