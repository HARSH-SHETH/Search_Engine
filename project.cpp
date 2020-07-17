#include <iostream>
#include <vector>
#include <fstream>
#include <ctype.h>
#include <sstream>

std::string lowercase(std::string &s){
  for(int i = 0; i < s.length(); i++){
    s[i] = std::tolower(s[i]);
  }
  return s;
}

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

struct url_node{ 
  std::string url;
  int priority;
  url_node *link;
};
class SEARCH_ENGINE{
  private: 
    url_node *head, *tail;
    std::vector<std::string> list_of_urls;
    std::vector<std::string> url_matched;
    std::vector<std::string> keywords;
  public: 
    SEARCH_ENGINE(): head{NULL}, tail{NULL}, list_of_urls{""}, url_matched{""}, keywords{""} {}
    void get_search_query(); // GET QUERY ARRAY CONTAINING KEYWORDS
    void fetch_urls();  // READ ALL URLS FROM URLS.TXT AND MAKE A VECTOR OF STRINGS
    
    // Return the vector containing urls or return not found as a first element of the array
    std::vector<std::string> search_engine(std::vector<std::string>);  

    void insert_url(std::string, int);   // MAKE A NEW NODE AND INSERT URL ACC. TO PRIORITY
    void write_url();   // WRITE SELECTED URL TO THE FILE: LINK.TXT
    int display_urls(); // DISPLAY THE LIST OF URLS MATCHING THE KEYWORD AND RETURN THE OPTION SELECTED
};

void SEARCH_ENGINE::fetch_urls(){
  std::ifstream fin;
  fin.open("Generic_Solution.txt", std::ios::in);
  while(fin){
    std::string url = "";
    getline(fin, url);
    list_of_urls.push_back(url);
    std::cout << url << "\n";
  }
  fin.close();
  return;
}
void SEARCH_ENGINE::get_search_query(){
  std::string s = ""; 
  getline(std::cin, s);
  std::string keyword = "";
  for(int i = 0; i <= s.size(); i++){
    if(s[i] != ' ' && s[i] != '\0'){
      keyword += tolower(s[i]);
    }else{
      keywords.push_back(keyword);
      keyword = "";
    }
  }
}
std::vector<std::string> SEARCH_ENGINE::search_engine(std::vector<std::string> query){
  std::ifstream fin;
  std::string word, line;
  for(auto x:keywords){
    fin.open("Generic_Problem.txt", std::ios::in);
    while(!fin.eof()){
      getline(fin, line);
      if(search_substring(x, line)){
        std::cout << line << "\n";
      }
    }
    fin.close();
  }
  return query;
}
int main(){
  SEARCH_ENGINE S;
  S.get_search_query();
  S.search_engine({"harsh"});
/*  S.fetch_urls();*/
  return 0;
}
