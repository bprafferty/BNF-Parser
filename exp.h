/************************************************************
 Name: Brian Rafferty -- cssc0475 -- redID: 816988452
 Project: Program Assignment 3 -- BNF Parser
 File: exp.h
 Notes: This is the header file for exp.cpp which defines
        the methods to be used throughout parsing the data
        of an input file for correct BNF grammar.
*************************************************************/
#ifndef EXP_H
#define EXP_H

#include <vector>
#include <string>

using namespace std;

string checkSyntax(vector<int> classifiedLine);
bool checkId(string token);
vector<int> checkToken(string token);
vector<int> classifier(vector<string> tokens);
vector<string> inputSplitter(string currentLine);
void checkLine(string input);
void checkFile(string input);


#endif

/***********************[ EOF: exp.h ]*********************/