all:main.c
	gcc main.c -o a
	./a -d 1e4 -q 1e3 -arr -bs -ll -bst -hash