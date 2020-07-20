#include <iostream> 
#include <vector>
#include <fstream>
#include <ctype.h>
#include <sstream>
#include "search_engine.h"

//CREATE A NEW NODE WITH SAME CONTENTS AS OF ARGUMENT NODE{{{
url_node* create_new_node(url_node *ptr){
  url_node *temp = new url_node;
  temp->url = ptr->url; 
  temp->priority = ptr->priority;
  temp->link = NULL; 
  return temp;
}
//}}}

// FETCH URLS FROM THE GENERIC_SOLUTION.TXT FILE AND APPEND TO THE VECTOR{{{
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
// }}}

// GET USER INPUT AND APPEND EACH WORD TO THE VECTOR KEYWORDS{{{
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
// }}}

// SEARCH KEYWORDS THROUGH DATABASE AND UPDATE QUEUE{{{
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
// }}}

// UPDATE QUEUE IF URL ALREADY INSIDE A NODE ELSE APPEND A NEW NODE CONTAINING URL{{{
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
// }}}

// APPEND URL BY CREATING A NEW NODE AND UPDATE HEAD AND TAIL POINTERS{{{
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
// }}}

// SORT QUEUE ACCORDING TO PRIORITY{{{
void SEARCH_ENGINE::sort_queue(){
  url_node *new_head      = new url_node;
  url_node *new_tail      = new url_node;
  url_node *ptr           = new url_node;
  url_node *new_ptr       = new url_node;
  url_node *prev_url_node = new url_node;
  new_head = new_tail = new_ptr = prev_url_node = NULL;
  ptr = head;
  while(ptr != NULL){
    new_ptr = new_head;
    url_node *temp = create_new_node(ptr);
    if(new_head == NULL){
      new_head = new_tail = temp;
    }
    else{
      bool is_inserted = false;
      while(new_ptr != NULL){
        if( (new_ptr == new_head) && (temp->priority >= new_head->priority) ){
          temp->link = new_head;
          new_head = temp;
          is_inserted = true;
        } else if(temp->priority >= new_ptr->priority){
          temp->link = new_ptr;
          prev_url_node->link = temp;
          is_inserted = true;
        }
        prev_url_node = new_ptr;
        new_ptr = new_ptr->link;
        if(is_inserted){
          break;
        }
      }
      if(!is_inserted){
        prev_url_node->link = temp;
        new_tail = temp;
      }
    }
    ptr = ptr->link;
  }
  head = new_head; 
  tail = new_tail;
  return;
}
// }}}

// DISPLAY URLS ACCORDING TO PRIORITY{{{
std::string SEARCH_ENGINE::display_urls(){
  url_node *ptr = new url_node;
  ptr = head;
  for(int i = 1; ptr != NULL; i++){
    std::cout << " [" << i << "] " << ptr->url << "\n";
    ptr = ptr->link;
  }
  std::cout << "Choose an url number: ";
  char ch = getchar();
  if(!isdigit(ch) || ch == '0'){ // CHECK IF USER ENTERED A DIGIT OR NOT
    std::cout << ERROR;
    return ERROR;
  } else{
    int choice = ch - '0';
    ptr = head;
    for(int i = 1; ptr != NULL; i++){
      if(i == choice)
        return ptr->url;
      ptr = ptr->link;
    }
  }
}
// }}}

// WRITE SELECTED URL TO THE RUN.SH FILE{{{
void SEARCH_ENGINE::write_url(void){
  std::string choice = display_urls();
  if(choice != ERROR){
    std::cout << "YOU CHOOSE: " << choice;
  }
  std::ofstream fout; 
  fout.open("link.txt", std::ios::out);
  fout << choice;
  fout.close();
}
// }}}
