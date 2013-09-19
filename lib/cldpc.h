#ifndef LDPC_H
#define LDPC_H

#include <iostream>
#include <vector>

#include "gf2vec.h"
#include "gf2mat.h"
#include "alist.h"

class cldpc
{
  public:
    cldpc() {};
    cldpc(const GF2Mat X);
    cldpc(const alist _list);
    void print_permute();
    std::vector<char> encode(std::vector<char> dataword);
    int dimension();
    GF2Mat get_H();
    GF2Mat get_G();
    int get_M();
    int get_N();
    std::vector<char> syndrome(const std::vector<char> in);
    bool is_codeword(const std::vector<char> in);
    void set_alist(const alist _list);
    std::vector<char> get_systematic_bits(std::vector<char> in);

  private:
    GF2Mat H;
    GF2Mat G;
    std::vector<int> permute;
    int rank_H;
    int M, N, K;

};

#endif // ifndef LDPC_H
