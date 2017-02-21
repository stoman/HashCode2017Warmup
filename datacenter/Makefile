CXX=g++ -std=c++11
MAINFILE=code/main
STRATEGIES=full mockplacement
ALLOUTPUTS=$(foreach strategy, $(STRATEGIES), $(patsubst data/%.in, data/$(strategy).%.ans, $(wildcard data/*.in)))
ALLVISUALIZATIONS=$(foreach strategy, $(STRATEGIES), $(patsubst data/%.in, data/$(strategy).%.png, $(filter-out data/big.in, $(wildcard data/*.in))))

all: data visualizations

data: $(ALLOUTPUTS)

visualizations: $(ALLVISUALIZATIONS)

sample: $(foreach strategy, $(STRATEGIES), data/$(strategy).example.ans)

build: clean
	zip build.zip code visualizations README.md Makefile LICENSE .gitignore grader

clean:
	rm -f $(MAINFILE) $(ALLOUTPUTS) $(ALLVISUALIZATIONS) grader/main grades.html

grader/main: $(wildcard grader/*.cpp)
	$(CXX) -o grader/main grader/main.cpp

grades.html: grader/main $(ALLOUTPUTS) $(wildcard data/*.ans)
	grader/main > grades.html

$(MAINFILE): $(wildcard code/*.cpp)
	$(CXX) -o $(MAINFILE) $(MAINFILE).cpp
	
visualize/%.class: $(@:%.class=%.java)
	javac -cp visualize $(@:%.class=%.java)

data/full.%.ans: $(MAINFILE)
	$(MAINFILE) full < $(@:data/full.%.ans=data/%.in) > $@

data/mockplacement.%.ans: $(MAINFILE)
	$(MAINFILE) mockplacement < $(@:data/mockplacement.%.ans=data/%.in) > $@

data/%.in.dat: visualize/InputToGnu.class
	java -cp visualize InputToGnu < $(@:%.dat=%) > $@

data/full.%.ans.dat: data/full.%.ans visualize/AnswerToGnu.class
	java -cp visualize AnswerToGnu $(@:data/full.%.ans.dat=data/%.in) $(@:%.dat=%) > $@

data/full.%.png: data/full.%.ans.dat data/%.in.dat
	gnuplot -e "datafile='$(@:data/full.%.png=data/%.in.dat)';datafile2='$(@:%.png=%.ans.dat)'; outputname='$@'" visualize/plot.plg

data/mockplacement.%.ans.dat: data/mockplacement.%.ans visualize/AnswerToGnu.class
	java -cp visualize AnswerToGnu $(@:data/mockplacement.%.ans.dat=data/%.in) $(@:%.dat=%) > $@

data/mockplacement.%.png: data/mockplacement.%.ans.dat data/%.in.dat
	gnuplot -e "datafile='$(@:data/mockplacement.%.png=data/%.in.dat)';datafile2='$(@:%.png=%.ans.dat)'; outputname='$@'" visualize/plot.plg

