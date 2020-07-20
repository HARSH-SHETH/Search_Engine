#include "functions.h"


// convert string to lowercase 
std::string lowercase(std::string &s){
  for(int i = 0; i < s.length(); i++){
    s[i] = std::tolower(s[i]);
  }
  return s;
}

// SEARCH A SUBSTRING INSIDE A STRING
bool search_substring(std::string sub_string, std::string main_string){
  std::stringstream ss(main_string);
  std::string word;
  while(ss >> word){
    lowercase(word);
    if(word == sub_string)
      return true;
  }
  return false;
}
