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
    void get_search_query(void); // GET QUERY ARRAY CONTAINING KEYWORDS
    void fetch_urls(void);  // READ ALL URLS FROM URLS.TXT AND MAKE A VECTOR OF STRINGS
    
    // Return the vector containing urls or return not found as a first element of the array
    void search_engine(void);  

    void update_queue(std::string);   // MAKE A NEW NODE AND INSERT URL ACC. TO PRIORITY
    void write_url(void);   // WRITE SELECTED URL TO THE FILE: LINK.TXT
    int display_urls(void); // DISPLAY THE LIST OF URLS MATCHING THE KEYWORD AND RETURN THE OPTION SELECTED
    void append(std::string);
};

// FETCH URLS FROM THE GENERIC_SOLUTION.TXT FILE AND APPEND TO THE VECTOR
void SEARCH_ENGINE::fetch_urls(){
  std::ifstream fin;
  fin.open("Generic_Solution.txt", std::ios::in);
  while(fin){
    std::string url = "";
    getline(fin, url);
    list_of_urls.push_back(url);
  }
  fin.close();
  return;
}

// GET USER INPUT AND APPEND EACH WORD TO THE VECTOR KEYWORDS
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

// SEARCH KEYWORDS THROUGH DATABASE AND UPDATE QUEUE
void SEARCH_ENGINE::search_engine(){
  std::ifstream fin;
  std::string word, line;
  bool found = false;
  for(auto x:keywords){
    fin.open("Generic_Problem.txt", std::ios::in);
    int count = 0;
    while(!fin.eof()){
      getline(fin, line);
      count++;
      if(search_substring(x, line)){
        found = true;
        update_queue(list_of_urls[count]);
      }
    }
    fin.close();
  }
  if(!found){

  }
  return;
}

// UPDATE QUEUE IF URL ALREADY INSIDE A NODE ELSE APPEND A NEW NODE CONTAINING URL
void SEARCH_ENGINE::update_queue(std::string url){
  url_node *ptr = new url_node;
  ptr = head;
  bool node_exist = false;
  while(ptr != NULL){
    if(ptr->url == url){
      ptr->priority++;
      node_exist = true;
    }
    ptr = ptr->link;
  }
  if(!node_exist){
    append(url);
  }
}

// APPEND URL BY CREATING A NEW NODE AND UPDATE HEAD AND TAIL POINTERS
void SEARCH_ENGINE::append(std::string url){
  url_node *temp = new url_node;
  temp->url = url; 
  temp->priority = 1;
  temp->link = NULL;
  url_node *ptr = new url_node;
  ptr = head;
  if(ptr == NULL){
    head = temp; 
    tail = temp;
  }
  else{
    tail->link = temp;
    tail = temp;
  }
}

// MAIN FUNCTION
int main(){
  SEARCH_ENGINE S;
  S.get_search_query();
  S.fetch_urls();
  S.search_engine();
  return 0;
}
