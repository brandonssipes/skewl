# These three variables control the target "Greedy".
GREEDYNAME1=sol1
GREEDYMAINCLASS1=Sol1
GREEDYSOURCES1=Sol1.java


Sol1:
	javac $(GREEDYSOURCES1)
	echo "Main-Class: $(GREEDYMAINCLASS1)" > Manifest.txt
	jar cfm $(GREEDYNAME1).jar Manifest.txt $(GREEDYMAINCLASS1).class si335/*.class
	./jar2exec $(GREEDYNAME1).jar $(GREEDYNAME1)
	rm -f Manifest.txt
	rm -f $(GREEDYNAME1).jar


GREEDYNAME2=sol2
GREEDYMAINCLASS2=Sol2
GREEDYSOURCES2=Sol2.java


Sol2:
	echo "\033[0;31mMemo.java needs to be in si335\033[0;30m"
	javac $(GREEDYSOURCES2)
	echo "Main-Class: $(GREEDYMAINCLASS2)" > Manifest.txt
	jar cfm $(GREEDYNAME2).jar Manifest.txt $(GREEDYMAINCLASS2).class si335/*.class
	./jar2exec $(GREEDYNAME2).jar $(GREEDYNAME2)
	rm -f Manifest.txt
	rm -f $(GREEDYNAME2).jar


GREEDYNAME=sol3
GREEDYMAINCLASS=Sol3
GREEDYSOURCES=Sol3.java


Sol3:
	echo "\033[0;31mMemo.java needs to be in si335\033[0;30m"
	javac $(GREEDYSOURCES)
	echo "Main-Class: $(GREEDYMAINCLASS)" > Manifest.txt
	jar cfm $(GREEDYNAME).jar Manifest.txt $(GREEDYMAINCLASS).class si335/*.class
	./jar2exec $(GREEDYNAME).jar $(GREEDYNAME)
	rm -f Manifest.txt
	rm -f $(GREEDYNAME).jar
