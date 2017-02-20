CXX=g++ -std=c++11
MAINFILE=code/main

all: $(patsubst data/%.in,data/dp.%.ans,$(wildcard data/*.in)) $(patsubst data/%.in,data/dptranspose.%.ans,$(wildcard data/*.in)) $(patsubst data/%.in,data/simplehorizontal.%.ans,$(wildcard data/*.in)) $(patsubst data/%.in,data/simplevertical.%.ans,$(wildcard data/*.in))

visualize: $(patsubst data/%.in,data/dp.%.png,$(wildcard data/*.in)) $(patsubst data/%.in,data/dptranspose.%.png,$(wildcard data/*.in)) $(patsubst data/%.in,data/simplehorizontal.%.png,$(wildcard data/*.in)) $(patsubst data/%.in,data/simplevertical.%.png,$(wildcard data/*.in))

sample: data/dp.example.ans data/simplehorizontal.example.ans data/simplevertical.example.ans

$(MAINFILE): $(wildcard code/*.cpp)
	$(CXX) -o $(MAINFILE) $(MAINFILE).cpp
	
visualize/%.class: $(@:%.class=%.java)
	javac -cp visualize $(@:%.class=%.java)

data/dp.%.ans: $(MAINFILE)
	$(MAINFILE) dp < $(@:data/dp.%.ans=data/%.in) > $@

data/dptranspose.%.ans: $(MAINFILE)
	$(MAINFILE) dptranspose < $(@:data/dptranspose.%.ans=data/%.in) > $@

data/simplehorizontal.%.ans: $(MAINFILE)
	$(MAINFILE) simplehorizontal < $(@:data/simplehorizontal.%.ans=data/%.in) > $@

data/simplevertical.%.ans: $(MAINFILE)
	$(MAINFILE) simplevertical < $(@:data/simplevertical.%.ans=data/%.in) > $@

data/%.in.dat: visualize/InputToGnu.class
	java -cp visualize InputToGnu < $(@:%.dat=%) > $@

data/%.ans.dat: data/%.ans visualize/AnswerToGnu.class
	java -cp visualize AnswerToGnu < $(@:%.dat=%) > $@

data/dp.%.png: data/dp.%.ans.dat data/%.in.dat
	gnuplot -e "datafile='$(@:data/dp.%.png=data/%.in.dat)';datafile2='$(@:%.png=%.ans.dat)'; outputname='$@'" visualize/plot.plg

data/dptranspose.%.png: data/dptranspose.%.ans.dat data/%.in.dat
	gnuplot -e "datafile='$(@:data/dptranspose.%.png=data/%.in.dat)';datafile2='$(@:%.png=%.ans.dat)'; outputname='$@'" visualize/plot.plg

data/simplehorizontal.%.png: data/simplehorizontal.%.ans.dat data/%.in.dat
	gnuplot -e "datafile='$(@:data/simplehorizontal.%.png=data/%.in.dat)';datafile2='$(@:%.png=%.ans.dat)'; outputname='$@'" visualize/plot.plg

data/simplevertical.%.png: data/simplevertical.%.ans.dat data/%.in.dat
	gnuplot -e "datafile='$(@:data/simplevertical.%.png=data/%.in.dat)';datafile2='$(@:%.png=%.ans.dat)'; outputname='$@'" visualize/plot.plg
