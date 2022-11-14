//============================================================================
// Name        : Server.cpp
// Author      : Artem Kuznetsov
// Version     : 4
// Copyright   : kuznear1
// Description : TCP server
//============================================================================
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <sys/socket.h> // socket(), bind(), connect(), listen()
#include <unistd.h> // close(), read(), write()
#include <netinet/in.h> // struct sockaddr_in
#include <strings.h> // bzero()
#include <sstream>
//#include <wait.h> // waitpid()

#define BUFFER_SIZE 10240
#define TIMEOUT 1
#define TIMEOUT_RECHARGING 5

const int server[5] = {23019, 32037, 18789, 16443, 18189};
const int client[5] = {32037, 29295, 13603, 29533, 21952};
    
bool login(std::string & username, int & bytesRead, int & key_id, char & auten, int c, std::string tmp)
{
    if(bytesRead == 20 && username[19] != '\b' && username[18] != '\a') {
        std::cout << "301 SYNTAX ERROR\a\b" << std::endl;
        std::string buffer = "301 SYNTAX ERROR\a\b";
        send(c, buffer.c_str(), buffer.size(), 0);
        return false;
    }
    
    if(bytesRead > 20) {
        std::cout << "301 SYNTAX ERROR\a\b" << std::endl;
        std::string buffer = "301 SYNTAX ERROR\a\b";
        send(c, buffer.c_str(), buffer.size(), 0);
        return false;
    } else if (bytesRead > 2) {
        if(username[bytesRead - 1] == '\b' && username[bytesRead -2] == '\a') {
            for(int i = 0; i < bytesRead - 2; i++) {
                key_id += (int)username[i];
            }
            key_id = (key_id * 1000) % 65536;
            auten = 'y';
            if(tmp != "") {
            username = tmp;
            bytesRead = tmp.size();
            } else {
                username = "";
                bytesRead = 0;
            }
            std::cout << "107 KEY REQUEST\a\b" << std::endl;
            std::string buffer = "107 KEY REQUEST\a\b";
            send(c, buffer.c_str(), buffer.size(), 0);
            return true;
        }
    }
    return true;
}

bool sentKey(std::string & symbols, int & key_size, int & key_id, char & aunt, int & id, int c, std::string tmp)
 {
    if(key_size > 5) {
        std::cout << "301 SYNTAX ERROR\a\b" << std::endl;
        std::string buffer = "301 SYNTAX ERROR\a\b";
        send(c, buffer.c_str(), buffer.size(), 0);
        return false;
    } else if(key_size > 2) {
        if(symbols[key_size - 1] == '\b' && symbols[key_size -2] == '\a') {

            for(int i = 0; i < key_size - 2; i++) {
                if((int)symbols[i] > 57 || (int)symbols[i] < 48) {
                    std::cout << "301 SYNTAX ERROR\a\b" << std::endl;
                    std::string buffer = "301 SYNTAX ERROR\a\b";
                    send(c, buffer.c_str(), buffer.size(), 0);
                    return false;
                }
                if(i == 0)
                    id = (int)symbols[i] - 48;
                if(i == 1) {
                    id = (symbols[i - 1] - '0') * 10 + (symbols[i] - '0');
                }
                if(i == 2)
                    id = ((symbols[i - 2] - '0') * 100) + ((symbols[i - 1] - '0')  * 10)
                    + (symbols[i] - '0');
            }
            if(id > 4 || id < 0) {
                std::cout << "86 303 KEY OUT OF RANGE\a\b" << std::endl;
                std::string buffer = "303 KEY OUT OF RANGE\a\b";
                send(c, buffer.c_str(), buffer.size(), 0);
                return false;
            }
            aunt = 'c';
            if(tmp != "") {
                symbols = tmp;
                key_size = tmp.size();
            } else {
                symbols = "";
                key_size = 0;
            }
            std::cout << (key_id + server[id]) % 65536 << std::endl;
            std::string buffer = std::to_string((key_id + server[id]) % 65536) + "\a\b";
            send(c, buffer.c_str(), buffer.size(), 0);
            return true;
        }
    }
    return true;
 }

bool controlKey(std::string & symbols, int & key_confirm, int key_id, char & aunt, int & id, int c, std::string tmp)
{
    if(key_confirm > 7) {
        std::cout << "301 SYNTAX ERROR\a\b" << std::endl;
        std::string buffer = "301 SYNTAX ERROR\a\b";
        send(c, buffer.c_str(), buffer.size(), 0);
        return false;
    } else if (key_confirm > 2) {
        if(symbols[key_confirm - 1] == '\b' && symbols[key_confirm -2] == '\a') {
            
            std::string id_klient;
            
            for(int i = 0; i < key_confirm - 2; i++) {
                if((int)symbols[i] > 57 || (int)symbols[i] < 48) {
                    std::cout << "301 SYNTAX ERROR\a\b" << std::endl;
                    std::string buffer = "301 SYNTAX ERROR\a\b";
                    send(c, buffer.c_str(), buffer.size(), 0);
                    return false;
                }
                id_klient.push_back(symbols[i]);
            }
            
            int kod = std::stoi(id_klient);
            
            if(((key_id + client[id]) % 65536) == kod) {
                aunt = 'p';
                if(tmp != "") {
                    symbols = tmp;
                    key_confirm = tmp.size();
                } else {
                    symbols = "";
                    key_confirm = 0;
                }
                id = 0;
                std::cout << "200 OK\a\b" << std::endl;
                std::string buffer = "200 OK\a\b";
                send(c, buffer.c_str(), buffer.size(), 0);
                std::cout << "102 MOVE\a\b" << std::endl;
                buffer = "102 MOVE\a\b";
                send(c, buffer.c_str(), buffer.size(), 0);
                return true;
            } else {
                std::cout << "300 LOGIN FAILED\a\b" << std::endl;
                std::string buffer = "300 LOGIN FAILED\a\b";
                send(c, buffer.c_str(), buffer.size(), 0);
                return false;
            }
        }
    }
    
    return true;
}

bool autentizace(std::string & symbols, int & bytesRead, int & key_id, char & aunt, int & id, int c, struct timeval & timeout, char & rechar)
{
    //this template is used if several commands come at once at a time
    std::string tmp = "";
    for(int i = 0; i < bytesRead; i++) {
       if(i + 2 != bytesRead && symbols[i] == '\a' && symbols[i + 1] == '\b') {
           for(int j = i + 2, t = 0; j < bytesRead; j++, t++) {
               tmp.push_back(symbols[j]);
           }
           std::string Symbtmp = symbols;
           symbols = "";
           for(int j = 0; j < i + 2; j++) {
               symbols.push_back(Symbtmp[j]);
           }
           bytesRead = i + 2;
           break;
       }
    }
    
    //for control username
    if(aunt == 'n') {
        if(login(symbols, bytesRead, key_id, aunt, c, tmp) == false) {
            return false;
        } else if(tmp != "" && aunt == 'y') {
            tmp = "";
            for(int i = 0; i < bytesRead; i++) {
               if(i + 2 != bytesRead && symbols[i] == '\a' && symbols[i + 1] == '\b') {
                   for(int j = i + 2, t = 0; j < bytesRead; j++, t++) {
                       tmp.push_back(symbols[j]);
                   }
                   std::string Symbtmp = symbols;
                   symbols = "";
                   for(int j = 0; j < i + 2; j++) {
                       symbols.push_back(Symbtmp[j]);
                   }
                   bytesRead = i + 2;
                   break;
               }
            }
        } else
            return true;
    }
    
    //this template is used for recharging
    if(symbols == "RECHARGING\a\b") {
        if(rechar == 'N') {
            timeout.tv_sec = TIMEOUT_RECHARGING;
            rechar = 'R';
            bytesRead = 0;
            symbols = "";
            return true;
        } else {
            std::cout << "302 LOGIC ERROR\a\b" << std::endl;
            std::string buffer = "302 LOGIC ERROR\a\b";
            send(c, buffer.c_str(), buffer.size(), 0);
            return false;
        }
    }

    //this template is used for full power energy
    if(symbols == "FULL POWER\a\b") {
        if(rechar == 'R') {
            timeout.tv_sec = TIMEOUT;
            rechar = 'N';
            bytesRead = 0;
            symbols = "";
            return true;
        } else {
            std::cout << "302 LOGIC ERROR\a\b" << std::endl;
            std::string buffer = "302 LOGIC ERROR\a\b";
            send(c, buffer.c_str(), buffer.size(), 0);
            return false;
        }
    }
      
    //for control client key id
    if(aunt == 'y') {
        if(sentKey(symbols, bytesRead, key_id, aunt, id, c, tmp) == false) {
            return false;
        } else if(tmp != "" && aunt == 'c') {
            tmp = "";
            for(int i = 0; i < bytesRead; i++) {
               if(i + 2 != bytesRead && symbols[i] == '\a' && symbols[i + 1] == '\b') {
                   for(int j = i + 2, t = 0; j < bytesRead; j++, t++) {
                       tmp.push_back(symbols[j]);
                   }
                   std::string Symbtmp = symbols;
                   symbols = "";
                   for(int j = 0; j < i + 2; j++) {
                       symbols.push_back(Symbtmp[j]);
                   }
                   bytesRead = i + 2;
                   break;
               }
            }
        } else
            return true;
    }
    
    if(symbols == "RECHARGING\a\b") {
        if(rechar == 'N') {
            timeout.tv_sec = TIMEOUT_RECHARGING;
            rechar = 'R';
            bytesRead = 0;
            symbols = "";
            return true;
        } else {
            std::cout << "302 LOGIC ERROR\a\b" << std::endl;
            std::string buffer = "302 LOGIC ERROR\a\b";
            send(c, buffer.c_str(), buffer.size(), 0);
            return false;
        }
    }

    if(symbols == "FULL POWER\a\b") {
        if(rechar == 'R') {
            timeout.tv_sec = TIMEOUT;
            rechar = 'N';
            bytesRead = 0;
            symbols = "";
            return true;
        } else {
            std::cout << "302 LOGIC ERROR\a\b" << std::endl;
            std::string buffer = "302 LOGIC ERROR\a\b";
            send(c, buffer.c_str(), buffer.size(), 0);
            return false;
        }
    }
    
    //for control client confirmation
    if(aunt == 'c')
    {
        if(controlKey(symbols, bytesRead, key_id, aunt, id, c, tmp) == false) {
            return false;
        } else if(tmp != "" && aunt == 'p') {
            tmp = "";
            for(int i = 0; i < bytesRead; i++) {
               if(i + 2 != bytesRead && symbols[i] == '\a' && symbols[i + 1] == '\b') {
                   for(int j = i + 2, t = 0; j < bytesRead; j++, t++) {
                       tmp.push_back(symbols[j]);
                   }
                   std::string Symbtmp = symbols;
                   symbols = "";
                   for(int j = 0; j < i + 2; j++) {
                       symbols.push_back(Symbtmp[j]);
                   }
                   bytesRead = i + 2;
                   break;
               }
            }
        } else
            return true;
    }
    
    return true;
}

bool movingRobots(std::string & symbols, int & lenghtCommand, int & id, std::pair<int, int> & cord, std::pair<int, int> & lastCord, int & flag, std::pair<char, char> & poz, int c)
{
    if(lenghtCommand > 12) {
        std::cout << "301 SYNTAX ERROR\a\b" << std::endl;
        std::string buffer = "301 SYNTAX ERROR\a\b";
        send(c, buffer.c_str(), buffer.size(), 0);
        return false;
    }
    
    int i = 0;
    std::string x = "";
    std::string y = "";
    for(i = 3; symbols[i] != ' '; i++) {
        x.push_back(symbols[i]);
    }
    for(int j = i + 1; symbols[j] != '\a'; j++) {
        y.push_back(symbols[j]);
    }
    
    cord.first = std::stoi(x);
    cord.second = std::stoi(y);
    
    if(cord.first == 0 && cord.second == 0) {
        if(symbols[3] != '0' || symbols[5] != '0' || symbols[6] != '\a' || symbols[7] != '\b') {
            std::cout << "301 SYNTAX ERROR\a\b" << std::endl;
            std::string buffer = "301 SYNTAX ERROR\a\b";
            send(c, buffer.c_str(), buffer.size(), 0);
            return false;
        }
        std::cout << "105 GET MESSAGE\a\b" << std::endl;
        std::string buffer = "105 GET MESSAGE\a\b";
        send(c, buffer.c_str(), buffer.size(), 0);
        flag = 10;
        symbols = "";
        return true;
    }
    
    if(flag == 0) {
        lastCord.first = cord.first;
        lastCord.second = cord.second;
        flag = 1;
        std::cout << "102 MOVE\a\b" << std::endl;
        std::string buffer = "102 MOVE\a\b";
        send(c, buffer.c_str(), buffer.size(), 0);
        symbols = "";
        return true;
    }
    
    if(flag == 5) {
        std::cout << "104 TURN RIGHT\a\b" << std::endl;
        std::string buffer = "104 TURN RIGHT\a\b";
        send(c, buffer.c_str(), buffer.size(), 0);
        flag = 3;
        symbols = "";
        return true;
    }
    
    if(flag != 1 && flag != 3 && (lastCord.first == cord.first && lastCord.second == cord.second)) {
        
        
        if(cord.first == 0 || cord.second == 0) {
            std::cout << "104 TURN RIGHT\a\b" << std::endl;
            std::string buffer = "104 TURN RIGHT\a\b";
            send(c, buffer.c_str(), buffer.size(), 0);
            flag = 0;
            symbols = "";
            return true;
        }
        
        if(poz.second == 'x') {
            if(poz.first == '2' || poz.first == '4') {
                std::cout << "103 TURN LEFT\a\b" << std::endl;
                std::string buffer = "103 TURN LEFT\a\b";
                send(c, buffer.c_str(), buffer.size(), 0);
            }
            else {
                std::cout << "104 TURN RIGHT\a\b" << std::endl;
                std::string buffer = "104 TURN RIGHT\a\b";
                send(c, buffer.c_str(), buffer.size(), 0);
            }
            poz.second = 'y';
        } else if(poz.second == 'y') {
            if(poz.first == '2' || poz.first == '4') {
                std::cout << "104 TURN RIGHT\a\b" << std::endl;
                std::string buffer = "104 TURN RIGHT\a\b";
                send(c, buffer.c_str(), buffer.size(), 0);
            }
            else {
                std::cout << "103 TURN LEFT\a\b" << std::endl;
                std::string buffer = "103 TURN LEFT\a\b";
                send(c, buffer.c_str(), buffer.size(), 0);
            }
            poz.second = 'x';
        }
        
        flag = 3;
        symbols = "";
        return true;
    }
    
    if(flag == 2  || flag == 3) {
        
        if(flag == 3) {
            std::cout << "102 MOVE\a\b" << std::endl;
            std::string buffer = "102 MOVE\a\b";
            send(c, buffer.c_str(), buffer.size(), 0);
            flag = 2;
            symbols = "";
            return true;
        }
        
        if(cord.first == 0 && lastCord.first != 0) {
            if((poz.first == '2' || poz.first == '4') && poz.second == 'y') {
                std::cout << "104 TURN RIGHT\a\b" << std::endl;
                std::string buffer = "104 TURN RIGHT\a\b";
                send(c, buffer.c_str(), buffer.size(), 0);
            }
            else {
                std::cout << "103 TURN LEFT\a\b" << std::endl;
                std::string buffer = "103 TURN LEFT\a\b";
                send(c, buffer.c_str(), buffer.size(), 0);
            }
            flag = 3;
        } else if(cord.second == 0 && lastCord.second != 0) {
            if((poz.first == '1' || poz.first == '3') && poz.second == 'x') {
                std::cout << "104 TURN RIGHT\a\b" << std::endl;
                std::string buffer = "104 TURN RIGHT\a\b";
                send(c, buffer.c_str(), buffer.size(), 0);
            }
            else {
                std::cout << "103 TURN LEFT\a\b" << std::endl;
                std::string buffer = "103 TURN LEFT\a\b";
                send(c, buffer.c_str(), buffer.size(), 0);
            }
            flag = 3;
        } else {
            std::cout << "102 MOVE\a\b" << std::endl;
            std::string buffer = "102 MOVE\a\b";
            send(c, buffer.c_str(), buffer.size(), 0);
        }
        
        lastCord.first = cord.first;
        lastCord.second = cord.second;
        symbols = "";
        return true;
    }

    if(flag == 1) {
            
        if(cord.second == 0 && ((cord.first > 0 && lastCord.first < cord.first) ||
                               (cord.first < 0 && lastCord.first > cord.first))) {
            std::cout << "104 TURN RIGHT\a\b" << std::endl;
            std::string buffer = "104 TURN RIGHT\a\b";
            send(c, buffer.c_str(), buffer.size(), 0);
            flag = 5;
            symbols = "";
            return true;
        } else if (cord.first == 0 && ((cord.second > 0 && lastCord.second < cord.second) || (cord.second < 0 && lastCord.second > cord.second))) {
            std::cout << "104 TURN RIGHT\a\b" << std::endl;
            std::string buffer = "104 TURN RIGHT\a\b";
            send(c, buffer.c_str(), buffer.size(), 0);
            flag = 5;
            symbols = "";
            return true;
        }
        
        if(lastCord.first == cord.first && lastCord.second == cord.second) {
            std::cout << "103 TURN LEFT\a\b" << std::endl;
            std::string buffer = "103 TURN LEFT\a\b";
            send(c, buffer.c_str(), buffer.size(), 0);
            flag = 0;
            symbols = "";
            return true;
        }
        
        if(lastCord.second == cord.second) {
            if(cord.first > 0) {
                if(cord.second > 0) {
                    if(cord.first > lastCord.first) {
                        poz.second = 'x';
                        std::cout << "104 TURN RIGHT\a\b" << std::endl;
                        std::string buffer = "104 TURN RIGHT\a\b";
                        send(c, buffer.c_str(), buffer.size(), 0);
                        flag = 3;
                    }
                    else {
                        poz.second = 'y';
                        std::cout << "102 MOVE\a\b" << std::endl;
                        std::string buffer = "102 MOVE\a\b";
                        send(c, buffer.c_str(), buffer.size(), 0);
                        flag = 2;
                    }
                    poz.first = '1';
                } else {
                    if(cord.first > lastCord.first) {
                        poz.second = 'x';
                        std::cout << "103 TURN LEFT\a\b" << std::endl;
                        std::string buffer = "103 TURN LEFT\a\b";
                        send(c, buffer.c_str(), buffer.size(), 0);
                        flag = 3;
                    }
                    else {
                        poz.second = 'y';
                        std::cout << "102 MOVE\a\b" << std::endl;
                        std::string buffer = "102 MOVE\a\b";
                        send(c, buffer.c_str(), buffer.size(), 0);
                        flag = 2;
                    }
                    poz.first = '4';
                }
            } else {
                if(cord.second > 0) {
                    if(cord.first > lastCord.first) {
                        poz.second = 'y';
                        std::cout << "102 MOVE\a\b" << std::endl;
                        std::string buffer = "102 MOVE\a\b";
                        send(c, buffer.c_str(), buffer.size(), 0);
                        flag = 2;
                    }
                    else {
                        poz.second = 'x';
                        std::cout << "103 TURN LEFT\a\b" << std::endl;
                        std::string buffer = "103 TURN LEFT\a\b";
                        send(c, buffer.c_str(), buffer.size(), 0);
                        flag = 3;
                    }
                    poz.first = '2';
                } else {
                    if(cord.first > lastCord.first) {
                        poz.second = 'y';
                        std::cout << "102 MOVE\a\b" << std::endl;
                        std::string buffer = "102 MOVE\a\b";
                        send(c, buffer.c_str(), buffer.size(), 0);
                        flag = 2;
                    }
                    else {
                        poz.second = 'x';
                        std::cout << "104 TURN RIGHT\a\b" << std::endl;
                        std::string buffer = "104 TURN RIGHT\a\b";
                        send(c, buffer.c_str(), buffer.size(), 0);
                        flag = 3;
                    }
                    poz.first = '3';
                }
            }
        } else if(lastCord.first == cord.first) {
            if(cord.second > 0) {
                if(cord.first > 0) {
                    if(cord.second > lastCord.second) {
                        poz.second = 'y';
                        std::cout << "103 TURN LEFT\a\b" << std::endl;
                        std::string buffer = "103 TURN LEFT\a\b";
                        send(c, buffer.c_str(), buffer.size(), 0);
                        flag = 3;
                    }
                    else {
                        poz.second = 'x';
                        std::cout << "102 MOVE\a\b" << std::endl;
                        std::string buffer = "102 MOVE\a\b";
                        send(c, buffer.c_str(), buffer.size(), 0);
                        flag = 2;
                    }
                    poz.first = '1';
                } else {
                    if(cord.second > lastCord.second) {
                        poz.second = 'y';
                        std::cout << "104 TURN RIGHT\a\b" << std::endl;
                        std::string buffer = "104 TURN RIGHT\a\b";
                        send(c, buffer.c_str(), buffer.size(), 0);
                        flag = 3;
                    }
                    else {
                        poz.second = 'x';
                        std::cout << "102 MOVE\a\b" << std::endl;
                        std::string buffer = "102 MOVE\a\b";
                        send(c, buffer.c_str(), buffer.size(), 0);
                        flag = 2;
                    }
                    poz.first = '2';
                }
            } else {
                if(cord.first > 0) {
                    if(cord.second > lastCord.second) {
                        poz.second = 'x';
                        std::cout << "102 MOVE\a\b" << std::endl;
                        std::string buffer = "102 MOVE\a\b";
                        send(c, buffer.c_str(), buffer.size(), 0);
                        flag = 2;
                    }
                    else {
                        poz.second = 'y';
                        std::cout << "104 TURN RIGHT\a\b" << std::endl;
                        std::string buffer = "104 TURN RIGHT\a\b";
                        send(c, buffer.c_str(), buffer.size(), 0);
                        flag = 3;
                    }
                    poz.first = '4';
                } else {
                    if(cord.second > lastCord.second) {
                        poz.second = 'x';
                        std::cout << "102 MOVE\a\b" << std::endl;
                        std::string buffer = "102 MOVE\a\b";
                        send(c, buffer.c_str(), buffer.size(), 0);
                        flag = 2;
                    }
                    else {
                        poz.second = 'y';
                        std::cout << "103 TURN LEFT\a\b" << std::endl;
                        std::string buffer = "103 TURN LEFT\a\b";
                        send(c, buffer.c_str(), buffer.size(), 0);
                        flag = 3;
                    }
                    poz.first = '3';
                }
            }
        }
        
        symbols = "";
        lastCord.first = cord.first;
        lastCord.second = cord.second;
        return true;
    }
    
    symbols = "";
    return true;
}

bool command (std::string & symbols, int & lenghtCommand, int & id, std::pair<int, int> & cord, std::pair<int, int> & lastCord, int & flag, std::pair<char, char> & poz, int c, struct timeval & timeout, char & rechar)
{
    std::string tmp = "";
    for(int i = 0; i < lenghtCommand; i++) {
       if(i + 2 != lenghtCommand && symbols[i] == '\a' && symbols[i + 1] == '\b' && lenghtCommand > 12) {
           for(int j = i + 2, t = 0; j < lenghtCommand; j++, t++) {
               tmp.push_back(symbols[j]);
           }
           std::string Symbtmp = symbols;
           for(int j = 0; j < lenghtCommand; j++) {
               Symbtmp.push_back(symbols[j]);
           }
           symbols = "";
           for(int j = 0; j < i + 2; j++) {
               symbols.push_back(Symbtmp[j]);
           }
           lenghtCommand = i + 2;
           break;
       }
    }
    
    if(lenghtCommand > 12) {
        std::cout << "ha 301 SYNTAX ERROR\a\b" << std::endl;
        std::string buffer = "301 SYNTAX ERROR\a\b";
        send(c, buffer.c_str(), buffer.size(), 0);
        return false;
    }
    
    if(lenghtCommand > 2) {
        if(symbols[lenghtCommand - 1] == '\b' && symbols[lenghtCommand -2] == '\a') {
            
            if(symbols[0] == 'R' && symbols[1] == 'E' && symbols[2] == 'C' &&
               symbols[3] == 'H' && symbols[4] == 'A' && symbols[5] == 'R' &&
               symbols[6] == 'G' && symbols[7] == 'I' && symbols[8] == 'N' &&
               symbols[9] == 'G' && symbols[10] == '\a' && symbols[11] == '\b') {
                if(rechar == 'N') {
                    timeout.tv_sec = TIMEOUT_RECHARGING;
                    rechar = 'R';
                    lenghtCommand = 0;
                    symbols = "";
                    return true;
                } else {
                    std::cout << "302 LOGIC ERROR\a\b" << std::endl;
                    std::string buffer = "302 LOGIC ERROR\a\b";
                    send(c, buffer.c_str(), buffer.size(), 0);
                    return false;
                }
            }
            
            if(symbols[0] == 'F' && symbols[1] == 'U' && symbols[2] == 'L' &&
               symbols[3] == 'L' && symbols[4] == ' ' && symbols[5] == 'P' &&
               symbols[6] == 'O' && symbols[7] == 'W' && symbols[8] == 'E' &&
               symbols[9] == 'R' && symbols[10] == '\a' && symbols[11] == '\b') {
                if(rechar == 'R' && tmp == "") {
                    timeout.tv_sec = TIMEOUT;
                    rechar = 'N';
                    lenghtCommand = 0;
                    symbols = "";
                    return true;
                } else if (rechar == 'R' && tmp != "") {
                    timeout.tv_sec = TIMEOUT;
                    rechar = 'N';
                    symbols = tmp;
                    lenghtCommand = symbols.size();
                    if(symbols[lenghtCommand - 1] != '\b' && symbols[lenghtCommand - 2] != '\a') {
                        return true;
                    }
                } else {
                    std::cout << "302 LOGIC ERROR\a\b" << std::endl;
                    std::string buffer = "302 LOGIC ERROR\a\b";
                    send(c, buffer.c_str(), buffer.size(), 0);
                    return false;
                }
            }
           
            //for to transfer to a function whose task is to guide the robot in the coordinate
           if(symbols[0] == 'O' && symbols[1] == 'K') {
               if(rechar == 'R') {
                   std::cout << "302 LOGIC ERROR\a\b" << std::endl;
                   std::string buffer = "302 LOGIC ERROR\a\b";
                   send(c, buffer.c_str(), buffer.size(), 0);
                   return false;
               }
               if(movingRobots(symbols, lenghtCommand, id, cord, lastCord, flag, poz, c) == true)
                   symbols = "";
               lenghtCommand = 0;
                   return true;
           } else {

               return false;
           }
                 
           }
    }

    return true;
}

int main(int argc, char **argv) {

    if(argc < 2){
        std::cerr << "Usage: server port" << std::endl;
        return -1;
    }

    // Endpoint connection
    int l = socket(AF_INET, SOCK_STREAM, 0);
    if(l < 0){
        perror("Nemohu vytvorit socket: ");
        return -1;
    }

    int port = atoi(argv[1]);
    if(port == 0){
        std::cerr << "Usage: server port" << std::endl;
        close(l);
        return -1;
    }

    struct sockaddr_in adresa;
    bzero(&adresa, sizeof(adresa));
    adresa.sin_family = AF_INET;
    adresa.sin_port = htons(port);
    adresa.sin_addr.s_addr = htonl(INADDR_ANY);

    // Socket to interface
    if(bind(l, (struct sockaddr *) &adresa, sizeof(adresa)) < 0){
        perror("Problem s bind(): ");
        close(l);
        return -1;
    }

    // Mark socket as passive
    if(listen(l, 10) < 0){
        perror("Problem s listen()!");
        close(l);
        return -1;
    }

    struct sockaddr_in vzdalena_adresa;
    socklen_t velikost;

    while(true){
        // Looking forward to joining us
        int c = accept(l, (struct sockaddr *) &vzdalena_adresa, &velikost);
        if(c < 0){
            perror("Problem s accept()!");
            close(l);
            return -1;
        }
        pid_t pid = fork();
        if(pid == 0){
            // The copy of the main train has its own reference to the listening socket.
            // The thread that serves the client does not need this reference, so it is good
            // delete this reference. In the main train of course references to listening
            // the socket remains.
            close(l);

            struct timeval timeout;
            timeout.tv_sec = TIMEOUT;
            timeout.tv_usec = 0;

            fd_set sockets;

            int retval;
            char buffer[BUFFER_SIZE];
            char aunt = 'n';
            char tmp = '0';
            char rechar = 'N';
            int key_id = 0;
            int id = 0;
            std::pair <int, int> cord;
            std::pair <int, int> lastCord;
            int flag = 0;
            std::pair <char, char> poz;
            std::string symbols = "";
            int userRead = 0;
            while(true){
                FD_ZERO(&sockets);
                FD_SET(c, &sockets);
                // The first parameter is the number of the highest socket in 'sockets' increased by one.
                // (The great simplicity and efficiency of the function is balanced by the wrong
                // ergonomics for the user.)
                // The last of the parameters is the timeout itself. It is a structural type of 'struct timeval',
                // which allows timing with microsecond accuracy (+/ -). Function is sold
                // a link to a variable and a function can modify it. In most implementations
                // subtracts the function from the timeout value of the diet timeout. According to the manual on
                // it cannot be trusted on all platforms and in all implementable functions
                // select()!!!
                retval = select(c + 1, &sockets, NULL, NULL, &timeout);
                if(retval < 0){
                    perror("Chyba v select(): ");
                    close(c);
                    return -1;
                }
                if(!FD_ISSET(c, &sockets)){
                    // Here it is clear that the select () function stopped waiting due to timeout.
                    std::cout << "Connection timeout!" << std::endl;
                    close(c);
                    return 0;
                }
                int bytesRead = recv(c, buffer, BUFFER_SIZE - 1, 0);
                if(bytesRead <= 0){
                    perror("Chyba pri cteni ze socketu: ");
                    close(c);
                    return -3;
                }
                buffer[bytesRead] = '\0';
                
                //everything about authorization is implemented in the function call of this if
                if(aunt != 'p') {
                    userRead = userRead + bytesRead;
                    for(int i = userRead - bytesRead, j = 0 ; i < userRead; i++, j++) {
                        symbols.push_back(buffer[j]);
                    }
                    
                    if(autentizace(symbols, userRead, key_id, aunt, id, c,
                                   timeout, rechar) == false) {
                        break;
                    } else if(symbols != "" && aunt == 'p') {
                        tmp = 't';
                    } else
                        continue;
                }
                
                //to receive the message, this if plus multiple checks for control
                if(flag == 10) {
                    userRead = userRead + bytesRead;
                    for(int i = userRead - bytesRead, j = 0 ; i < userRead; i++, j++) {
                        symbols.push_back(buffer[j]);
                    }
                    
                    if(symbols[0] == 'R' && symbols[1] == 'E' && symbols[2] == 'C' &&
                       symbols[3] == 'H' && symbols[4] == 'A' && symbols[5] == 'R' &&
                       symbols[6] == 'G' && symbols[7] == 'I' && symbols[8] == 'N' &&
                       symbols[9] == 'G' && symbols[10] == '\a' && symbols[11] == '\b') {
                        if(rechar == 'N') {
                            timeout.tv_sec = TIMEOUT_RECHARGING;
                            rechar = 'R';
                            flag = 0;
                            symbols = "";
                            userRead = 0;
                            continue;
                        } else {
                            std::cout << "302 LOGIC ERROR\a\b" << std::endl;
                            std::string buffer = "302 LOGIC ERROR\a\b";
                            send(c, buffer.c_str(), buffer.size(), 0);
                            break;
                        }
                    }
                    
                    if(bytesRead == 100 && symbols[userRead - 1] != '\b' &&
                                           symbols[userRead - 2] != '\a') {
                        std::cout << "301 SYNTAX ERROR\a\b" << std::endl;
                        std::string buffer = "301 SYNTAX ERROR\a\b";
                        send(c, buffer.c_str(), buffer.size(), 0);
                        break;
                    }
                    
                    if(userRead > 100) {
                        std::cout << "301 SYNTAX ERROR\a\b" << std::endl;
                        std::string buffer = "301 SYNTAX ERROR\a\b";
                        send(c, buffer.c_str(), buffer.size(), 0);
                        break;
                    }
                    
                    if(symbols[userRead - 1] == '\b' &&
                        symbols[userRead - 2] == '\a') {
                    std::cout << "106 LOGOUT\a\b" << std::endl;
                    std::string buffer = "106 LOGOUT\a\b";
                    send(c, buffer.c_str(), buffer.size(), 0);
                    break;
                    } else
                        continue;

                }
                
                //everything about the robot's movement is implemented in the function call of this if
                if(aunt == 'p') {
                    if(tmp != 't') {
                        userRead = userRead + bytesRead;
                        for(int i = userRead - bytesRead, j = 0 ; i < userRead; i++, j++) {
                            symbols[i] = buffer[j];
                        }
                    }
                    
                    tmp = '0';

                    if(command(symbols, userRead, id, cord, lastCord, flag, poz, c, timeout, rechar) == false)
                        break;
                    else {
                        continue;
                    }
                }
            }
            close(c);
            return 0;
        }

        // So that we do not have zombie processes in the system, we will serve the client every time,
        // it is necessary to test whether a thread has already been terminated.
        // The first argument says, wait for any process descendant, the third argument ensures,
        // it's a non-blocking feature (standard blocking is what we really don't want now).
        int status = 0;
        waitpid(0, &status, WNOHANG);

        close(c); // The newly created socket is necessarily closed in the main process, because it would not in the system
        // keeping the reference and closing it in the new trial would have no effect.
    }

    close(l);
    return 0;
}
