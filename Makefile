CXX=g++ -std=c++11
MAINFILE=code/main

all: $(patsubst data/%.in,data/dp.%.ans,$(wildcard data/*.in)) $(patsubst data/%.in,data/simplehorizontal.%.ans,$(wildcard data/*.in)) $(patsubst data/%.in,data/simplevertical.%.ans,$(wildcard data/*.in))

sample: data/dp.example.ans data/simplehorizontal.example.ans data/simplevertical.example.ans

$(MAINFILE): $(MAINFILE).cpp
	$(CXX) -o $(MAINFILE) $(MAINFILE).cpp

data/dp.%.ans: $(MAINFILE)
	$(MAINFILE) dp < data/$(@:data/dp.%.ans=%.in) > $@

data/simplehorizontal.%.ans: $(MAINFILE)
	$(MAINFILE) simplehorizontal < data/$(@:data/simplehorizontal.%.ans=%.in) > $@

data/simplevertical.%.ans: $(MAINFILE)
	$(MAINFILE) simplevertical < data/$(@:data/simplevertical.%.ans=%.in) > $@
