#ifndef AWGN_BP_H
#define AWGN_BP_H

#include <vector>
#include <cmath>
#include <iostream>
#include "gf2mat.h"
#include "alist.h"

class awgn_bp
{
  public:
    awgn_bp () {};
    awgn_bp (const GF2Mat & X, float sgma);
    awgn_bp (alist & _list, float sgma);
    void set_alist_sigma(alist & _list, float sgma);
    std::vector< std::vector<double> > get_Q();
    std::vector< std::vector<double> > get_R();
    GF2Mat get_H();
    void rx_lr_calc(std::vector<float> codeword);
    std::vector<double> get_rx_lr();
    std::vector<double> get_lr();
    void spa_initialize();
    void update_chks();
    void update_vars();
    std::vector<char> get_estimate();
    void compute_init_estimate(std::vector<float> rx_word);
    void decision();
    std::vector<char> get_syndrome();
    std::vector<char> get_syndrome(const std::vector<char> codeword);
    bool is_codeword();
    bool is_codeword(const std::vector<char> codeword);
    void set_K(int k);
    int get_K();
    void set_max_iterations(int k);
    int get_max_iterations();
    std::vector<char> decode (std::vector<float> rx_word,
            int & niterations);

  private:
    int M, N, K, max_iterations;
    GF2Mat H;
    float sigma;
    std::vector< std::vector<double> > Q, R;
    std::vector<double> rx_lr;
    std::vector<double> lr;
    std::vector < std::vector<int> > mlist, nlist;
    std::vector <int> num_mlist, num_nlist;
    std::vector<char> estimate;
};
#endif // ifndef AWGN_BP_H
