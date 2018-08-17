//Abygail Stiekman
//11.20.2016 
//COP4530 Proj5


#include "passserver.h"
#include <unistd.h>
#include <crypt.h>
#include <cstring>
using namespace cop4530;

//Constructor calls HashTable inheritance of Constructor with given size
PassServer::PassServer(size_t size = 101) : HashTable<std::string,std::string>(size){}

//Destructor
PassServer::~PassServer(){}

//bool load() calls Parent hashtable version of load()
bool PassServer::load(const char *filename){
    return HashTable<std::string,std::string>::load(filename);
}

//bool AddUser adds an ecrypted password based on incoming KV value
bool PassServer::addUser(std::pair<std::string, std::string> &kv){
    std::pair<std::string,std::string> eKV = std::make_pair(kv.first,encrypt(kv.second));
    return HashTable<std::string,std::string>::insert(eKV);
}

//bool AddUser Move version of insert
bool PassServer::addUser(std::pair<std::string, std::string> &&kv){
    return false;
}

//bool removeUser calls Parent HashTable version of remove()
bool PassServer::removeUser(const std::string &k){
    return HashTable<std::string,std::string>::remove(k);
}
//encrypts the pw before inserting 
//returns false if user is not inside of the table, if the second value
//that is passed in is equal to the current one, it returns the bool of insert

bool PassServer::changePassword(const std::pair<std::string, std::string> &p, const std::string & newpassword){
    if(find(p.first)){  //If user is in table
        std::pair<std::string,std::string> oldEKV = std::make_pair(p.first,encrypt(p.second));
        if(HashTable<std::string,std::string>::match(oldEKV)){  //if p.second matches
            std::pair<std::string,std::string> eKV = std::make_pair(p.first,encrypt(newpassword));
            if(!HashTable<std::string,std::string>::match(eKV)) //if p.second != newPassword
                return HashTable<std::string,std::string>::insert(eKV);
            else return false;
        }
        else return false;
    }
    else return false;
}

//bool find() Calls Parent HashTable member contains()
bool PassServer::find(const std::string &user){
    return HashTable<std::string,std::string>::contains(user);
}

//bool dump() Calls Parent HashTable version of dump()
void PassServer::dump(){
    HashTable<std::string,std::string>::dump();
}

//bool write_to_file() Calls Parent HashTable version of write_to_file()
bool PassServer::write_to_file(const char *filename){
    return HashTable<std::string,std::string>::write_to_file(filename);
}

//member size() calls HashTable helper function getSize()
size_t PassServer::size(){
    return HashTable<std::string,std::string>::getSize();
}


std::string PassServer::encrypt(const std::string &str){
    char salt[] = "$1$########";   //can't get this to work
    char * pass = new char [ 100 ];
    std::strcpy(pass, crypt(str.c_str(), salt));
    std::string ret(pass);
    return ret;
}