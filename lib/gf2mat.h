#ifndef GF2MAT_H
#define GF2MAT_H
#include <vector>
#include "gf2vec.h"
#include "alist.h"

class GF2Mat
{
    std::vector < std::vector <char> > H;
    int M;
    int N;

  public:
    GF2Mat() {};
    GF2Mat(int m, int n);
    GF2Mat(alist _list);
    GF2Mat(std::vector <std::vector <char> > X);

    int get_M() {
        return M;
    }

    int get_N() {
        return N;
    }

    void set_element(int i, int j, char val);

    char get_element(int i, int j);

    GF2Vec get_row(int i);

    GF2Vec get_col(int i);

    GF2Vec operator[](int i);

    void print_matrix();

    void set_col(int row, GF2Vec vec);

    void set_row(int col, GF2Vec vec);

    void swap_cols(int i, int j);

    void add_cols(int i, int j);

    void add_rows(int i, int j);

    std::vector<std::vector<char> > get_H();

    GF2Mat get_G(std::vector<int> & p, int & rank);

};

#endif // #ifndef GF2MAT_H
