#include <iostream>
#include <vector>
#include <fstream>
#include <ctype.h>
#include <sstream>
#include "search_engine.h"

int main(){
  SEARCH_ENGINE S;
  S.get_search_query();
  S.fetch_urls();
  S.search_engine();
  S.sort_queue();
  S.write_url();
  return 0;
}
