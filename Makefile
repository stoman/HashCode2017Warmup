CXX=g++ -std=c++11
MAINFILE=code/main

all: $(patsubst data/%.in,data/dp.%.ans,$(wildcard data/*.in)) $(patsubst data/%.in,data/simplehorizontal.%.ans,$(wildcard data/*.in)) $(patsubst data/%.in,data/simplevertical.%.ans,$(wildcard data/*.in))

sample: data/dp.example.ans data/simplehorizontal.example.ans data/simplevertical.example.ans

$(MAINFILE): $(MAINFILE).cpp
	$(CXX) -o $(MAINFILE) $(MAINFILE).cpp
	
visualize/%.class: $(@:%.class=%.java)
	javac -cp visualize $(@:%.class=%.java)

data/dp.%.ans: $(MAINFILE)
	$(MAINFILE) dp < $(@:data/dp.%.ans=data/%.in) > $@

data/simplehorizontal.%.ans: $(MAINFILE)
	$(MAINFILE) simplehorizontal < $(@:data/simplehorizontal.%.ans=data/%.in) > $@

data/simplevertical.%.ans: $(MAINFILE)
	$(MAINFILE) simplevertical < $(@:data/simplevertical.%.ans=data/%.in) > $@

data/%.in.dat: $(@:%.dat=%) visualize/InputToGnu.class
	java -cp visualize InputToGnu < $(@:%.dat=%) > $@

data/%.ans.dat: $(@:%.dat=%) visualize/AnswerToGnu.class
	java -cp visualize AnswerToGnu < $(@:%.dat=%) > $@

data/dp.%.png: $(@:%.png=%.ans.dat) $(@:data/dp.%.png=data/%.in.dat)
	gnuplot -e "datafile='$(@:data/dp.%.png=data/%.in.dat)';datafile2='$(@:%.png=%.ans.dat)'; outputname='$@'" visualize/plot.plg

data/simplehorizontal.%.png: $(@:%.png=%.ans.dat) $(@:data/simplehorizontal.%.png=data/%.in.dat)
	gnuplot -e "datafile='$(@:data/simplehorizontal.%.png=data/%.in.dat)';datafile2='$(@:%.png=%.ans.dat)'; outputname='$@'" visualize/plot.plg

data/simplevertical.%.png: $(@:%.png=%.ans.dat) $(@:data/simplevertical.%.png=data/%.in.dat)
	gnuplot -e "datafile='$(@:data/simplevertical.%.png=data/%.in.dat)';datafile2='$(@:%.png=%.ans.dat)'; outputname='$@'" visualize/plot.plg

visualize: $(patsubst data/%.in,data/dp.%.png,$(wildcard data/*.in)) $(patsubst data/%.in,data/simplehorizontal.%.png,$(wildcard data/*.in)) $(patsubst data/%.in,data/simplevertical.%.png,$(wildcard data/*.in))