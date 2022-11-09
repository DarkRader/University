#include <fstream>
#include "CFloat.h"
#include "CFloatBig.h"
#include "CInteger.h"
#include "CIntegerBig.h"
#include "CParsData.h"
#include "CShuntYardAlg.h"

//function for history output
void greeting(void)
{
    std::cout << "Welcome to calculation with unlimited accuracy!" << std::endl;
    std::cout << std::endl;
    std::cout << "Rules for using the calculator: " << std::endl;
    std::cout << std::endl;
    std::cout << "You can use any of the following operators - '+', '-', '*', '/' and expressions inside brackets, that is, using - '(', ')'." << std::endl;
    std::cout << std::endl;
    std::cout << "You can also use variables and use the = sign to assign any expressions," << std::endl << "in the future you can use variables in your calculations, but for variables" << std::endl << "you can only use the letters 'A-Z' and 'a-z' the size of the letters plays a role," << std::endl << "you can also change values inside variables " << std::endl;
    std::cout << std::endl;
    std::cout << "Also pay attention to the use of a minus sign, you cannot write: '5 - -3'," << std::endl << "but you can write it using brackets: '5 - (-3)'" << std::endl;
    std::cout << std::endl;
    std::cout << "In the program, you cannot divide float decimal numbers," <<
    std::endl << "when using float decimal numbers, use a comma, for example '21525,2112'" << std::endl;
    std::cout << std::endl;
    std::cout << "The program has the ability to download and download the history of the calculator to download write 'download history' in small letters, without whitespaces, " << std::endl << "give a name to the file where you want to save the history." << std::endl;
    std::cout << std::endl;
    std::cout << "If you want to upload a story that you downloaded, write 'upload story' in small letters, without whitespaces,"  << std::endl << "write the name of the file where you downloaded it, in addition to the history of upload and variables that you assigned" << std::endl;
    std::cout << std::endl;
    std::cout << "To completit the program, write 'quit' in small letters" << std::endl;
    std::cout << std::endl;
}

//a function for transcoding the history from a standard file to a file that the user will create
void copyAnotherFile(const std::string & fileName)
{
    
    std::ofstream os;
    os.open(fileName);
    
    std::ifstream inFile("text.txt", std::ios::in);
    
    if(!inFile)
        return;
    
    std::string buffer;

    getline(inFile, buffer);
    while(!buffer.empty())
    {
        os << buffer << std::endl;
        buffer.clear();
        getline(inFile, buffer);
    }
    
    os.close();
}

//a function for displaying the history from the file that the user is trying to download
void uploadHistory(const std::string & fileName, CParsData & x)
{
    std::ifstream inFile(fileName, std::ios::in);
    
    if(!inFile) {
        std::cout << "There is no such file!" << std::endl;
        return;
    }
    
    std::string buffer;
    getline(inFile, buffer);
    while(!buffer.empty())
    {
        std::cout << buffer << std::endl;
        x.parsingDate(buffer);
        buffer.clear();
        getline(inFile, buffer);
    }
}

//a function that responds to a user's request to download or upload history
bool commandUser(std::string & commandUser, std::string & renamed, std::ofstream & os, CParsData & x)
{
    if(commandUser == "dowload history") {
        std::cout << "Write down what your file will be called" << std::endl;
        renamed = "Yes";
        return true;
    }
    
    if(renamed == "Yes") {
        os.close();
        commandUser += ".txt";
        copyAnotherFile(commandUser);
        os.open("text.txt");
        renamed = "No";
        return true;
    }
    
    if(commandUser == "upload history") {
        std::cout << "Enter the name of the file whose history you want to upload" << std::endl;
        renamed = "Ready";
        return true;
    }
    
    if(renamed == "Ready") {
        commandUser += ".txt";
        uploadHistory(commandUser, x);
        renamed = "No";
        return true;
    }
    
    return false;
}

int main() {
    greeting();
    
    std::string operaceCal;
    CParsData x;
    std::ofstream os;
    os.open("text.txt");
    std::string renamed = "No";
    
    while(operaceCal != "quit") {
        std::getline(std::cin, operaceCal);
        
        if(std::cin.eof()) {
            break;
        }
        
        if(commandUser(operaceCal, renamed, os, x) == true)
            continue;
        
        if(x.parsingDate(operaceCal) == false)
            continue;

        if(operaceCal != "quit")
            os << operaceCal << std::endl;

    }
    
    os.close();

    
    return EXIT_SUCCESS;
}
