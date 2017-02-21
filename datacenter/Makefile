CXX=g++ -std=c++11
MAINFILE=code/main
STRATEGIES=full-1 full-1-2 full-2-3 full-3-4 mockplacement
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

data/full-1.%.ans: $(MAINFILE)
	$(MAINFILE) full-1 < $(@:data/full-1.%.ans=data/%.in) > $@

data/full-1-2.%.ans: $(MAINFILE)
	$(MAINFILE) full-1-2 < $(@:data/full-1-2.%.ans=data/%.in) > $@

data/full-2-3.%.ans: $(MAINFILE)
	$(MAINFILE) full-2-3 < $(@:data/full-2-3.%.ans=data/%.in) > $@

data/full-3-4.%.ans: $(MAINFILE)
	$(MAINFILE) full-3-4 < $(@:data/full-3-4.%.ans=data/%.in) > $@

data/mockplacement.%.ans: $(MAINFILE)
	$(MAINFILE) mockplacement < $(@:data/mockplacement.%.ans=data/%.in) > $@

data/%.in.dat: visualize/InputToGnu.class
	java -cp visualize InputToGnu < $(@:%.dat=%) > $@

data/full-1.%.ans.dat: data/full-1.%.ans visualize/AnswerToGnu.class
	java -cp visualize AnswerToGnu $(@:data/full-1.%.ans.dat=data/%.in) $(@:%.dat=%) > $@

data/full-1.%.png: data/full-1.%.ans.dat data/%.in.dat
	gnuplot -e "datafile='$(@:data/full-1.%.png=data/%.in.dat)';datafile2='$(@:%.png=%.ans.dat)'; outputname='$@'" visualize/plot.plg

data/full-1-2.%.ans.dat: data/full-1-2.%.ans visualize/AnswerToGnu.class
	java -cp visualize AnswerToGnu $(@:data/full-1-2.%.ans.dat=data/%.in) $(@:%.dat=%) > $@

data/full-1-2.%.png: data/full-1-2.%.ans.dat data/%.in.dat
	gnuplot -e "datafile='$(@:data/full-1-2.%.png=data/%.in.dat)';datafile2='$(@:%.png=%.ans.dat)'; outputname='$@'" visualize/plot.plg

data/full-2-3.%.ans.dat: data/full-2-3.%.ans visualize/AnswerToGnu.class
	java -cp visualize AnswerToGnu $(@:data/full-2-3.%.ans.dat=data/%.in) $(@:%.dat=%) > $@

data/full-2-3.%.png: data/full-2-3.%.ans.dat data/%.in.dat
	gnuplot -e "datafile='$(@:data/full-2-3.%.png=data/%.in.dat)';datafile2='$(@:%.png=%.ans.dat)'; outputname='$@'" visualize/plot.plg

data/full-3-4.%.ans.dat: data/full-3-4.%.ans visualize/AnswerToGnu.class
	java -cp visualize AnswerToGnu $(@:data/full-3-4.%.ans.dat=data/%.in) $(@:%.dat=%) > $@

data/full-3-4.%.png: data/full-3-4.%.ans.dat data/%.in.dat
	gnuplot -e "datafile='$(@:data/full-3-4.%.png=data/%.in.dat)';datafile2='$(@:%.png=%.ans.dat)'; outputname='$@'" visualize/plot.plg

data/mockplacement.%.ans.dat: data/mockplacement.%.ans visualize/AnswerToGnu.class
	java -cp visualize AnswerToGnu $(@:data/mockplacement.%.ans.dat=data/%.in) $(@:%.dat=%) > $@

data/mockplacement.%.png: data/mockplacement.%.ans.dat data/%.in.dat
	gnuplot -e "datafile='$(@:data/mockplacement.%.png=data/%.in.dat)';datafile2='$(@:%.png=%.ans.dat)'; outputname='$@'" visualize/plot.plg

