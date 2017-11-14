Modules Extension

For my modules assignement I have submitted three files:
	-list.c
	-list.h
	-libraryTester.c
The first two were supplied, libraryTester.c is used to run the testLists function and prints out how many passed. It can be compiled using the following command:
gcc -std=c99 -Wall -O3 -pedantic list.c libraryTester.c -o libraryTester
And run using ./libraryTester


For my modules extension, I wrote another API on trees, this comprises of a C source file (tree.c) and a C header file (tree.h), after doing this I decided to implement this API by creating a huffman tree. The basis of this is to gather frequencies of different characters in a cetain document, it then creates a tree using these frequencies to make sure the letters with the highest frequency, have the shortest binary string. As I have probably explained this poorly, a more in depth tutorial on huffman trees can be found at this link:
https://www.siggraph.org/education/materials/HyperGraph/video/mpeg/mpegfaq/huffman_tutorial.html

After my program is compiled using the following command:
gcc -std=c99 -Wall -pedantic -O3 tree.c huffman.c -o huffman

And run with ./huffman, it will print out the tree, NULL characters are represented by a '*'. Nodes are printed out in the form (character:frequency). The nodes are indented based on the parent/child relationship between them

If I had more time I would read the text from a file, however, at the moment it is hard coded in the main function. 
