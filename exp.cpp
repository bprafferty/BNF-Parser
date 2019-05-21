/************************************************************
 Name: Brian Rafferty -- cssc0475 -- redID: 816988452
 Project: Program Assignment 3 -- BNF Parser
 File: exp.cpp
 Notes: This file takes in the user's input from the
        command line and begins to process it. Each 
        line within file or single line of standard input
        is read in and tokenized. A copy of the line(s) is 
        made and analyzed to see if any edge-cases exist. 
        If there are, then spaces are added between tokens.
        After that, the copy is ran through a method to 
        classify each token: 
          - symbol == 0
          - equal sign == 1
          - operation == 2
          - parenthesis == 3
          - semicolon == 4
          - unknown character == 5
        Once classifications are made on the line, it
        is sent into a method to check BNF syntax, i.e. 
        make sure that certain tokens only exist once, 
        or one at a time, or only at the end, etc. Any
        errors in the BNF grammar will be added to a 
        string which will be printed at the end. If there
        are no errors present, then it will only add
        Correct Statement to the resulting string.
 
    to compile: 	 
        make 

    to evaluate contents of txt file for BNF grammar:
        1) type in the executable followed by the file
            ./exp <filename>.txt

    to evalute standard input line:
        1) type in executable alone and press enter:
            ./exp
        2) enter your statement following the prompt:
            Enter your statement: <your statement here>
*************************************************************/
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

/************************************************************
 FUNCTION: checkSyntax
 DESCRIPTION: Parses vector of classified tokens to see
                if any of the numbers appear in locations
                within the vector that they do not belong.
 I/O:   Input: vector of classified tokens
        Output: string of error(s) encountered within grammar
*************************************************************/
string checkSyntax(vector<int> classifiedLine) {
    string returnStatement;
    int leftParenthesisSum = 0;
    int rightParenthesisSum = 0;
    bool isAssignment = false;

    //loop to determine if vector order is incorrect
    for (int i = 0; i < classifiedLine.size(); i++) {

        //if equal sign is found
        if (classifiedLine[i] == 1) {
            isAssignment = true;
        }

        //if equal sign exists in incorrect index
        if (classifiedLine[i] == 1 && i != 1) {
            returnStatement.append("\n\tError: assignment operator (=) at incorrect index.");
        }

        //if illegal character used before the \n at end of line
        if (classifiedLine[i] == 5 && i != classifiedLine.size()-1){
            returnStatement.append("\n\tError: incorrect symbol/operation used.");
        }

        //if it is an expression and contains an illegal semicolon at the end
        if (isAssignment == false && classifiedLine[i] == 4 && i == classifiedLine.size()-2){
            returnStatement.append("\n\tError: expression contains semicolon");
        }

        //if semicolon is found somewhere other than the end of a line
        if (classifiedLine[i] == 4 && i != classifiedLine.size()-2) {
            returnStatement.append("\n\tError: line misuses semicolon.");  
        }

        //if the semicolon is missing -or- if there is not a space following the semicolon
        if (classifiedLine[i] != 4 && i == classifiedLine.size()-2 && isAssignment == true) {
            returnStatement.append("\n\tError: assignment missing semicolon. (if it is there, it needs one space following it)");   
        }

        //determine count of parenthesis
        if (classifiedLine[i] == 3) {
            leftParenthesisSum += 1;
        }
        if (classifiedLine[i] == 6) {
            rightParenthesisSum +=1;
        }
        

        //if the same type of token appears illegally in repitition
        if ((classifiedLine[i] != 3) && (classifiedLine[i] != 6) && (classifiedLine[i] == classifiedLine[i+1]) && (classifiedLine[i] != 5)){
            returnStatement.append("\n\tError: consecutive symbols/operations used."); 
        }
        
    }

    //must be even number of parenthesis to be true
    if (leftParenthesisSum != rightParenthesisSum) {
        returnStatement.append("\n\tError: line missing parenthesis."); 
    }
    
    return returnStatement;
}

/************************************************************
 FUNCTION: checkId
 DESCRIPTION: Parses tokens classified as ID and checks grammar.
                (Makes sure there are no illegal characters 
                located within the ID).
 I/O:   Input: token previously classified as an ID 
        Output: true or false
*************************************************************/
bool checkId(string token){
    for (int i = 1; i < token.length(); i++){
        if (token[i] <= 39 || (token[i] >= 42 && token[i] <= 47) || (token[i] >= 58 && token[i] <= 64) || (token[i] >= 91 && token[i] <= 96) || (token[i] >= 123) ){
            return false;
        }
    }
    return true;
}

/************************************************************
 FUNCTION: checkToken
 DESCRIPTION: Checks each token passed inside to see which
                int value it shall be classified as. Does 
                this by creating an intermediary vector and
                returns it after each word is classified.
 I/O:   Input: individual token taken from vector of current line 
        Output: vector containing int(s) that correspond to token
*************************************************************/
vector<int> checkToken(string token) {
    vector<int> stagingVector;
    char firstChar = token[0];
    char operations[] = {'+','-','*','/','%'};
    
    if ((firstChar >= 65 && firstChar <= 90) || (firstChar >= 97 && firstChar <=122)) {
        stagingVector.push_back(0);
        return stagingVector;
    }

    if (firstChar == '=') {
        stagingVector.push_back(1);
        return stagingVector;
    }

    for (int i = 0; i < 5; i++) {
        if(firstChar == operations[i]){
            stagingVector.push_back(2);
            return stagingVector;
        }
    }

    if (firstChar == '(') {
        stagingVector.push_back(3);
        return stagingVector;
    }

    if (firstChar == ')') {
        stagingVector.push_back(6);
        return stagingVector;
    }

    if (firstChar == ';') {
        stagingVector.push_back(4);
        return stagingVector;
    }
    
    stagingVector.push_back(5);
    return stagingVector;

}

/************************************************************
 FUNCTION: classifier
 DESCRIPTION: Iterates through the vector of tokens and
                passes them one at a time to be classified.
                The small vectors that are passed back
                contain ints that represent the syntax of 
                each token, which are then added to the end 
                of the entire types vector, which maintains
                correct order.
 I/O:   Input: vector of tokens from current line
        Output: vector of corresponding ints
*************************************************************/
vector<int> classifier(vector<string> tokens) {
    vector<int> types;
    //symbol == 0
    //equal sign == 1
    //operation == 2
    // ( == 3
    //semicolon == 4
    //unknown character == 5
    // ) == 6
    vector<int> result;

    for (int i = 0; i < tokens.size(); i++) {
        result = checkToken(tokens[i]);
        types.insert(types.end(), result.begin(), result.end());
    }
    return types;
}

/************************************************************
 FUNCTION: inputSplitter
 DESCRIPTION: Iterates through the current line passed in
                and splits it into tokens with a space 
                delimeter. Each token is added to the end
                of a vector to maintain order.
 I/O:   Input: current line from input input
        Output: vector containing every token from input line
*************************************************************/
vector<string> inputSplitter(string currentLine) {
    int head = 0;
    int tail;
    vector<string> tokens;

    while (true) {
        tail = currentLine.find(" ",head);
        string token;

        if (tail != string::npos) {
            token = currentLine.substr(head, tail - head);
            head = tail + 1;
        }
        else {
            token = currentLine.substr(head);
        }
        tokens.push_back(token);

        if (tail == string::npos) {
            break;
        }
    }
    return tokens;
}

/************************************************************
 FUNCTION: checkLine
 DESCRIPTION: It then reads in the input line and processes it. 
                The input is tested to see if it passes/fails BNF 
                grammar standards. At the end of the line, it will
                print either pass or fail, and if the line failed, 
                the reason for the incorrect grammar is also 
                printed. 
 I/O:   Input: user's statement from command line
        Output: printed statement of grammar pass/fail 
*************************************************************/
void checkLine(string input){
    string message = "";
    string symbolParseError = "";
    string opParseError = "";
    string output;
    
    int counter = 0;
    int sizeIncrement = 0;
    vector<string> inputVector;
    vector<int> type;
    
    string copy = input;
    //preprocessing -- split input if no spaces between closed
    //parenthesis or operations
    for (int i = 0; i < input.size() + sizeIncrement; i++){
        if (copy[i] == '(' && copy[i+1] != ' '){
            copy.insert(copy.begin() + i+1, ' ');
            sizeIncrement += 1;
        }
        if (copy[i] == ')' && copy[i-1] != ' '){
            copy.insert(copy.begin() + i, ' ');
            sizeIncrement += 1;
        }
        if ((copy[i] == '+' && copy[i+1] != ' ') || (copy[i] == '-' && copy[i+1] != ' ') || (copy[i] == '*' && copy[i+1] != ' ') || (copy[i] == '/' && copy[i+1] != ' ') || (copy[i] == '%' && copy[i+1] != ' ')){
            copy.insert(copy.begin() + i+1, ' ');
            sizeIncrement += 1;
        }
    }
            
    counter += 1;
    cout << "\nUser statement: " << input;
    inputVector = inputSplitter(copy);
    bool isValid = true;
    type = classifier(inputVector);
    message = checkSyntax(type);

    //parse every ID token to see if it contains illegal characters
    for (int i = 0; i < inputVector.size(); i++) {
        if (type[i] == 0) {
            if (checkId(inputVector[i]) == false){
                symbolParseError = "\n\tError: symbol contains incorrect characters.";
                message.append(symbolParseError);
            }
        }
    }  

    if (message.compare("") != 0){
        isValid = false;
    }

    if (isValid == false){
        cout << message << endl;
    }

    if (isValid == true) {
        cout << "\n\tCorrect Statement." << endl;
    }
    
    cout << endl;
    exit(0);
    
}

/************************************************************
 FUNCTION: checkFile
 DESCRIPTION: It then reads in the input file and processes one 
                line at a time until the end of the file. The 
                input is tested to see if it passes/fails BNF 
                grammar standards. At the end all the original 
                file lines, their line number, and if they 
                passed/failed are printed. If any lines failed, 
                the reason for their incorrect grammar is also 
                printed. 
 I/O:   Input: user's file from command line
        Output: printed statement of grammar pass/fail
*************************************************************/
void checkFile(string input){
    string currentLine;
    string message = "";
    string symbolParseError = "";
    string opParseError = "";
    string output;
    
    int counter = 0;
    int sizeIncrement = 0;
    vector<string> inputVector;
    vector<int> type;
    ifstream userFile(input.c_str());
    
    //check if file entered exists
    if (userFile.good() == 0){
        cout << "Error: file not found" << endl;
        exit(0);
    }


    while(getline(userFile,currentLine)){
        try {
            string copy = currentLine;
            //preprocessing -- split input if no spaces between closed
            //parenthesis or operations
            for (int i = 0; i < currentLine.size() + sizeIncrement; i++){
                if (copy[i] == '(' && copy[i+1] != ' '){
                    copy.insert(copy.begin() + i+1, ' ');
                    sizeIncrement += 1;
                }
                if (copy[i] == ')' && copy[i-1] != ' '){
                    copy.insert(copy.begin() + i, ' ');
                    sizeIncrement += 1;
                }
                if ((copy[i] == '+' && copy[i+1] != ' ' && copy[i-1] == ' ') || (copy[i] == '-' && copy[i+1] != ' ' && copy[i-1] == ' ') || (copy[i] == '*' && copy[i+1] != ' ' && copy[i-1] == ' ') || (copy[i] == '/' && copy[i+1] != ' ' && copy[i-1] == ' ') || (copy[i] == '%' && copy[i+1] != ' ' && copy[i-1] == ' ')){
                    copy.insert(copy.begin() + i+1, ' ');
                    sizeIncrement += 1;
                }
            }
            
            counter += 1;
            cout << "\nFile line #" << counter << ": " << currentLine;
            inputVector = inputSplitter(copy);
            bool isValid = true;
            type = classifier(inputVector);
            message = checkSyntax(type);

            //parse every ID token to see if it contains illegal characters
            for (int i = 0; i < inputVector.size(); i++) {
                if (type[i] == 0) {
                    if (checkId(inputVector[i]) == false){
                        symbolParseError = "\n\tError: symbol contains incorrect characters.";
                        message.append(symbolParseError);
                    }
                }
            }
            
            if (message.compare("") != 0){
                isValid = false;
            }

            if (isValid == false){
                cout << message << endl;
            }

            if (isValid == true) {
                cout << "\n\tCorrect Statement." << endl;
            }

        }
        catch(string error){
            cout << "Error: " << error << " while reading file."<< endl;
            exit(0);
        }
    }
    cout << endl;
    userFile.close();
}

/************************************************************
 FUNCTION: main
 DESCRIPTION: Reads in the user's input on the command line
                and then processes it. 
 I/O:   Input: users input from command line
        Output: ask user for statement if no file entered
*************************************************************/
int main(int argc,char *argv[]){
    string input;
    if (argc == 1) {
        cout << "Enter your statement: ";
        while (getline(cin, input)){
            checkLine(input);
        }
    }
    if (argc > 2) {
        cout << "\n\tError: incorrect usage of program, reference README.md for correct format.\n" << endl;
        exit(0);
    }
    else {
        input = argv[1];
        checkFile(input);
    }
}

/***********************[ EOF: exp.cpp ]*********************/