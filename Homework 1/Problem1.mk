plot1.png : averages.dat Plot1.py
	python Plot1.py
      
averages.dat : Problem1.cpp
	g++ Problem1.cpp
	./a.out