CXX=g++ -std=c++11
MAINFILE=code/main
STRATEGIES=dp dptranspose simplehorizontal simplevertical diagonal
ALLOUTPUTS=$(foreach strategy, $(STRATEGIES), $(patsubst data/%.in, data/$(strategy).%.ans, $(wildcard data/*.in)))
ALLVISUALIZATIONS=$(foreach strategy, $(STRATEGIES), $(patsubst data/%.in, data/$(strategy).%.png, $(filter-out data/big.in, $(wildcard data/*.in))))

all: data visualizations

data: $(ALLOUTPUTS)

visualizations: $(ALLVISUALIZATIONS)

sample: $(foreach strategy, $(STRATEGIES), data/$(strategy).example.ans)

build: clean
	zip build.zip code visualizations README.md Makefile LICENSE .gitignore

clean:
	rm -f $(MAINFILE) $(ALLOUTPUTS) $(ALLVISUALIZATIONS)

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

data/diagonal.%.ans: $(MAINFILE)
	$(MAINFILE) diagonal < $(@:data/diagonal.%.ans=data/%.in) > $@

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

data/diagonal.%.png: data/diagonal.%.ans.dat data/%.in.dat
	gnuplot -e "datafile='$(@:data/diagonal.%.png=data/%.in.dat)';datafile2='$(@:%.png=%.ans.dat)'; outputname='$@'" visualize/plot.plg
