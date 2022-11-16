#ifndef __PROGTEST__
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <array>
#include <cassert>
using namespace std;
#endif /* __PROGTEST__ */

struct SSeznam
{
    SSeznam(string name, string surname, string number);
    string Name;
    string Surname;
    string Number;
};

SSeznam::SSeznam(string name, string surname, string number)
{
    this->Name = name;
    this->Surname = surname;
    this->Number = number;
}


bool controlNumber(const string & buffer)
{

    int t = 0;
    
    if( buffer[0] == '0' )
        return false;
    
    for( t = 0; buffer[t] != '\0'; t++) {
        
        if( buffer[t] < '0' || buffer[t] > '9' )
            return false;
    }
    
    if(t != 9)
        return false;

    
    
    return true;
}

bool report ( const string & fileName, ostream & out )
{
    vector <SSeznam> list;
    
    ifstream inFile (fileName, ios::in);
    
    if(!inFile)
        return false;
    
    
    string buffer;

    getline(inFile, buffer);
    
    int count = 0;

    while(!buffer.empty())
    {
        string name, surname, number, lap;
        istringstream my_stream(buffer);
        string foo;
        
        if(my_stream) {
            my_stream >> foo;
            name = foo;
        } else {
            return false;
        }
        if(my_stream) {
            my_stream >> foo;
            surname = foo;
        } else {
            return false;
        }
        if(my_stream) {
            my_stream >> foo;
            if(controlNumber(foo) == false)
                return false;
            number = foo;
            my_stream >> foo;
        } else {
            return false;
        }
        
        if(my_stream)
            return false;
        
        list.push_back(SSeznam(name, surname, number));
        count++;


        buffer.clear();
        getline(inFile, buffer);
    }
    

    while(getline(inFile, buffer)) {
        int same = 0;

        for(int i = 0; i < count; i++) {
            if(list[i].Name == buffer || list[i].Surname == buffer) {
                out << list[i].Name << " " << list[i].Surname << " " << list[i].Number << endl;
                same++;
            }
        }
        out << "->" << " " << same << endl;
        
        buffer.clear();
        
    }
    
    return true;
}

#ifndef __PROGTEST__
int main ()
{
  ostringstream oss;
  oss . str ( "" );
                    // need to write absolute path to test file
  assert ( report( "/Users/Artyom_1/University-/2. Semestr/1. Programming and algorithmic 1 (BI-PA2.21)/1. Progtest/2. Exercise/3. Exercise/tests/test0_in.txt", oss ) == true );
  assert ( oss . str () ==
    "John Christescu 258452362\n"
    "John Harmson 861647702\n"
    "-> 2\n"
    "-> 0\n"
    "Josh Dakhov 264112084\n"
    "Dakhov Speechley 865216101\n"
    "-> 2\n"
    "John Harmson 861647702\n"
    "-> 1\n" );
  oss . str ( "" );
  assert ( report( "/Users/Artyom_1/University-/2. Semestr/1. Programming and algorithmic 1 (BI-PA2.21)/1. Progtest/2. Exercise/3. Exercise/tests/test1_in.txt", oss ) == false );
  oss . str ( "" );
  assert ( report( "/Users/Artyom_1/University-/2. Semestr/1. Programming and algorithmic 1 (BI-PA2.21)/1. Progtest/2. Exercise/3. Exercise/tests/test2_in.txt", oss ) == true );
  assert ( oss . str () ==
    "Carly Johnson 355562144\n"
    "-> 1\n"
    "Christen Day 711567172\n"
    "-> 1\n" );
  return 0;
}
#endif /* __PROGTEST__ */

