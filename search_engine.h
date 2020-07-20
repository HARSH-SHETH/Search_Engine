#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H
#define ERROR "BAD INPUT"
#include "functions.h"
#include "structure.h"

class SEARCH_ENGINE{
  private: 
    url_node *head, *tail;
    std::vector<std::string> list_of_urls;
    std::vector<std::string> keywords;
  public: 
    SEARCH_ENGINE(): head{NULL}, tail{NULL}, list_of_urls{""}, keywords{""} {}
    // GET QUERY ARRAY CONTAINING KEYWORDS
    void get_search_query(void); 

    // READ ALL URLS FROM URLS.TXT AND MAKE A VECTOR OF STRINGS
    void fetch_urls(void);      

    // RETURN THE VECTOR CONTAINING URLS OR 
    // RETURN NOT FOUND AS A FIRST ELEMENT OF THE VECTOR
    void search_engine(void);  

    // MAKE A NEW NODE AND INSERT URL ACC. TO PRIORITY
    void update_queue(std::string);   

    // APPEND NODE 
    void append(std::string);         

    // SORT QUEUE ACCORDING TO PRIORITy
    void sort_queue(void);            

    // WRITE SELECTED URL TO THE FILE: LINK.TXT
    void write_url(void);   

    // DISPLAY THE LIST OF URLS MATCHING 
    // THE KEYWORD AND RETURN THE OPTION SELECTED
    std::string  display_urls(void); 
};

#endif
