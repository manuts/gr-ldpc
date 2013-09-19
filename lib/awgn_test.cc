#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "cldpc.h"
#include "alist.h"
#include "awgn_bp.h"
#include <time.h>

int main () {
    std::string fname = "/home/manu/repos/ldpc/gr-ldpc/python/alist-files/96.3.963";
    alist a(fname.c_str());
    srand(time(NULL));
    std::ifstream random("randoms");
    float trans_prob = 0.6;
    cldpc code(a);
    awgn_bp spa(a, trans_prob);
    spa.set_max_iterations(100);
    int K = code.dimension();
    spa.set_K(K);
    int N = code.get_N();
    std::cout << K << std::endl;
    std::vector<char> in;
    in.resize(K);
    std::cout << std::endl;
    std::vector<char> out, rx, data;
    std::vector<float> llr, rx_llr, tx;
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
        for ( int i = 0; i < N; i++ ) {
            getline(random, line);
            ss << line;
            ss >> X;
            ss.seekg(0, std::ios::end);
            ss.clear();
            if (out[i] == char(0)) {
                tx[i] = 1.0 + X;
                if ( X < -1.0)
                    nerr++;
            }
            else {
                tx[i] = -1.0 + X;
                if ( X > 1.0)
                    nerr++;
            }
        }
        rx = spa.decode(tx, &niterations);
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
