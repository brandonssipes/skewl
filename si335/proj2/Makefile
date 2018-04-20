build:	build-greedy build-optval build-opt

build-greedy:
	g++ -O4 -o gog part1.cpp

comm-greedy:
	@echo "./gog"

build-optval:
	g++ -O4 -o gov maxpot.cc

comm-optval:
	@echo "./gov"

build-opt:
	g++ -O4 -o goo bestpath.cc

comm-opt:
	@echo "./goo"

users:
	@echo "Bodeman, Maas, Paris, Sipes"

clean:
	rm -f gog gov goo rcheck
