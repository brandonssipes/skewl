# These three variables control the target "Greedy".
GREEDYNAME=sol1
GREEDYMAINCLASS=Sol1
GREEDYSOURCES=Sol1.java


Sol1:
	javac $(GREEDYSOURCES)
	echo "Main-Class: $(GREEDYMAINCLASS)" > Manifest.txt
	jar cfm $(GREEDYNAME).jar Manifest.txt $(GREEDYMAINCLASS).class si335/*.class
	./jar2exec $(GREEDYNAME).jar $(GREEDYNAME)
	rm -f Manifest.txt
	rm -f $(GREEDYNAME).jar


GREEDYNAME=sol2
GREEDYMAINCLASS=Sol2
GREEDYSOURCES=Sol2.java


Sol2:
	javac $(GREEDYSOURCES)
	echo "Main-Class: $(GREEDYMAINCLASS)" > Manifest.txt
	jar cfm $(GREEDYNAME).jar Manifest.txt $(GREEDYMAINCLASS).class si335/*.class
	./jar2exec $(GREEDYNAME).jar $(GREEDYNAME)
	rm -f Manifest.txt
	rm -f $(GREEDYNAME).jar


GREEDYNAME=sol3
GREEDYMAINCLASS=Sol3
GREEDYSOURCES=Sol3.java


Sol3:
	javac $(GREEDYSOURCES)
	echo "Main-Class: $(GREEDYMAINCLASS)" > Manifest.txt
	jar cfm $(GREEDYNAME).jar Manifest.txt $(GREEDYMAINCLASS).class si335/*.class
	./jar2exec $(GREEDYNAME).jar $(GREEDYNAME)
	rm -f Manifest.txt
	rm -f $(GREEDYNAME).jar

