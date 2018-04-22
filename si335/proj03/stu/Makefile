# These three variables control the target "Greedy".
GREEDYNAME=greedy
GREEDYMAINCLASS=Greedy
GREEDYSOURCES=Greedy.java


Greedy:
	javac $(GREEDYSOURCES)
	echo "Main-Class: $(GREEDYMAINCLASS)" > Manifest.txt
	jar cfm $(GREEDYNAME).jar Manifest.txt Greedy.class si335/*.class
	./jar2exec $(GREEDYNAME).jar $(GREEDYNAME)
	rm -f Manifest.txt
	rm -f $(GREEDYNAME).jar
