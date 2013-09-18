#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "cldpc.h"
#include "alist.h"
#include "xbp.h"
#include <time.h>

int main () {
    std::string fname = "/home/manu/repos/ldpc/gr-ldpc/python/alist-files/my_peg2";
    alist a(fname);
    srand(time(NULL));
    std::ifstream random("randoms");
    float trans_prob = 0.07;
    cldpc code(a);
    xbp spa(a, trans_prob);
    spa.set_max_iterations(100);
    int K = code.dimension();
    spa.set_K(K);
    int N = code.get_N();
    std::cout << K << std::endl;
    std::vector<char> in;
    in.resize(K);
    std::cout << std::endl;
    std::vector<char> out, rx, data, tx;
    std::vector<float> llr, rx_llr;
    std::stringstream ss;
    int niterations, nerr;
    bool match;
    int mat = 0;
    float X;
    std::string line;
    tx.resize(N);
    for ( int count = 0; count < 100; count++ ) {
        for ( int i = 0; i < K; i++ ) {
            in[i] = char(rand()%2);
        }
        nerr = 0;
        out = code.encode(in);
        float lim = trans_prob*10000;
        for ( int i = 0; i < N; i++ ) {
            X = rand()%10000;
            if ( X < lim ) {
                nerr++;
                if (out[i] == char(0))
                    tx[i] = char(1);
                else
                    tx[i] = char(0);
            }
            else
                tx[i] = out[i];
        }
        rx = spa.decode(tx, niterations);
        data = code.get_systematic_bits(rx);
        match = true;
        for ( int i = 0; i < K; i++ ) {
            if ( data[i] != in[i] ) {
                match = false;
                break;
            }
        }
        if ( match ){
            std::cout << count << "\t\tmat";
            mat++;
        }
        else {
            std::cout << count << "\t**" <<"\tmis";
        }
            std::cout << "\tnerr = " << nerr;
            std::cout << "\tniterations = " << niterations << std::endl;
    }
    std::cout << mat << std::endl;
}
