#ifndef ALIST_H
#define ALIST_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdlib.h>

class alist
{
  public:
    alist() : data_ok(false) {}
    alist(const char * fname);
    void read(const char * fname);
    void write(const char * fname) const;
    int get_N();
    int get_M();
    std::vector< std::vector<int> > get_mlist();
    std::vector< std::vector<int> > get_nlist();
    std::vector<int> get_num_mlist();
    std::vector<int> get_num_nlist();
    int get_max_num_nlist();
    int get_max_num_mlist();
    void print_nlist_i(int i);
    void print_mlist_i(int i);
    std::vector<std::vector<char> > get_matrix();

  protected:
    bool data_ok;
    int N, M;
    int max_num_mlist;
    int max_num_nlist;
    std::vector<int> num_nlist;
    std::vector<int> num_mlist;
    std::vector< std::vector<int> > mlist;
    std::vector< std::vector<int> > nlist;
};
#endif // ifndef ALIST_H
