# Author: Austin Voecks

keyview: keyview.h keyview.cpp
	clang++ -Wall -Wextra -o keyview keyview.cpp

clean:
	@rm keyview
	@echo Done
