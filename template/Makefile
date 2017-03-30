CXX=g++ -std=c++11
MAINFILE=code/main
STRATEGIES=naive
ALLOUTPUTS=$(foreach strategy, $(STRATEGIES), $(patsubst data/%.in, data/$(strategy).%.ans, $(wildcard data/*.in)))
ALLVISUALIZATIONS=$(foreach strategy, $(STRATEGIES), $(patsubst data/%.in, data/$(strategy).%.png, $(filter-out data/big.in, $(wildcard data/*.in))))

all: data visualizations

data: $(ALLOUTPUTS)

visualizations: $(ALLVISUALIZATIONS)

sample: $(foreach strategy, $(STRATEGIES), data/$(strategy).example.ans)

build: clean
	zip -r build.zip code visualizations README.md Makefile LICENSE .gitignore grader

clean:
	rm -f $(MAINFILE) $(ALLOUTPUTS) $(ALLVISUALIZATIONS) grader/main grades.html

grader/main: $(wildcard grader/*.cpp)
	$(CXX) -o grader/main grader/main.cpp

grades.html: grader/main $(ALLOUTPUTS) $(wildcard data/*.ans)
	grader/main > grades.html

$(MAINFILE): $(wildcard code/*.cpp)
	$(CXX) -o $(MAINFILE) $(MAINFILE).cpp

data/naive.%.ans: $(MAINFILE)
	$(MAINFILE) naive < $(@:data/naive.%.ans=data/%.in) > $@
	
## Visualization

# compile
visualize/%.class: $(@:%.class=%.java)
	javac -cp visualize $(@:%.class=%.java)

visualize/vis: $(wildcard visualize/*.cpp)
	$(CXX) -o visualize/vis visualize/AnswerToGnu.cpp

# pictures
data/%.in.dat: visualize/InputToGnu.class data/%.in
	java -cp visualize InputToGnu < $(@:%.dat=%) > $@

data/%.in.png: visualize/InputToGnu.class data/%.in.dat
	gnuplot -e "datafile='$(@:data/%.png=data/%.dat)';outputname='$@'" visualize/plot.plg

data/%.in.dat: visualize/InputToGnu.class
	java -cp visualize InputToGnu < $(@:%.dat=%) > $@

data/naive.%.ans.dat: data/naive.%.ans visualize/AnswerToGnu.class
	java -cp visualize AnswerToGnu $(@:data/naive.%.ans.dat=data/%.in) $(@:%.dat=%) > $@

data/naive.%.in.png: data/naive.%.ans.dat data/%.in.dat
	gnuplot -e "datafile='$(@:data/naive.%.png=data/%.in.dat)';datafile2='$(@:%.png=%.ans.dat)'; outputname='$@'" visualize/plot.plg
