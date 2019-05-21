Brian Rafferty -- cssc0475 -- redID: 816988452
---------------------
CS 530 Systems Programming, Spring 2019
---------------------
Program Assignment #3
---------------------
README.md
---------------------
BNF Grammar:
    Accepts:
        - Assignment
        - Expression

    Example Assignment:
        - id = exp ; 

    Example Expressions:
        - id op id 
        - id op (id op id) 
        - (id op id) op id 
---------------------
Manifest:
    README.md
    exp.cpp
    exp.h
    Makefile
    ex.txt
----------------------
Compiling executable:
    make
----------------------
to evaluate contents of txt file for BNF grammar:
    1) type in the executable followed by the file
        ./exp <filename>.txt
----------------------
to evaluate standard input line (nonfile):
    1) type in executable alone and press enter:
        ./exp
    2) type your statement following the prompt:
        Enter your statement: <your statement here>
----------------------
List/description of novel/significant design decisions:
I split the program up into different methods that each
handled a small part of the necessary classification
and/or calculation.
----------------------
List/description of any extra features/algorithms/functionality 
you included which were not required:
Added if statement to detect if any file entered actually
exists. I also used a try/catch block while working with 
the file that ensures that the file can be read error free.
If there are any issues reading the file, it will print why.
----------------------
List/description of all known deficiencies or bugs:
Standard input can only read in a single line from
the terminal, ran into bash errors if multiple lines
are copy/pasted in.
----------------------
Lessons Learned:
If there were no spaces on the closing side of parenthesis 
or multiple operations in a row without spaces then it 
threw off my indexes. I would have extra indexes
in the vector of classified tokens than the actual line
within the file. I had to preprocess the file line and
insert spaces manually if any spaces were absent.