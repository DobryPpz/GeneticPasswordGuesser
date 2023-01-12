all:
	gcc `find . -type f -iname "*.c"` -I . -Wall -o guesser