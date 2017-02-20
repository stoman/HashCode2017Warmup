CXX=g++ -std=c++11
MAINFILE=code/main

all: $(patsubst data/%.in,data/dp.%.ans,$(wildcard data/*.in)) $(patsubst data/%.in,data/simplehorizontal.%.ans,$(wildcard data/*.in)) $(patsubst data/%.in,data/simplevertical.%.ans,$(wildcard data/*.in))

sample: data/dp.example.ans data/simplehorizontal.example.ans data/simplevertical.example.ans

$(MAINFILE): $(MAINFILE).cpp
	$(CXX) -o $(MAINFILE) $(MAINFILE).cpp
	
visualize/%.class: $(@:%.class=%.java)
	javac -cp visualize $(@:visualize/%.class=%)

data/dp.%.ans: $(MAINFILE)
	$(MAINFILE) dp < $(@:data/dp.%.ans=data/%.in) > $@

data/simplehorizontal.%.ans: $(MAINFILE)
	$(MAINFILE) simplehorizontal < $(@:data/simplehorizontal.%.ans=data/%.in) > $@

data/simplevertical.%.ans: $(MAINFILE)
	$(MAINFILE) simplevertical < $(@:data/simplevertical.%.ans=data/%.in) > $@

data/%.in.dat: $(@:%.dat=%) visualize/InputToGnu.class
	java -cp visualize InputToGnu < $(@:%.dat=%) > $@
