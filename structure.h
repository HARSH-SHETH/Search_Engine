#ifndef STRUCTURE_H
#define STRUCTURE_H

struct url_node{ 
  std::string url;
  int priority;
  url_node *link;
};

#endif
