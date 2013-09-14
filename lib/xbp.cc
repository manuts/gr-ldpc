#include "xbp.h"

xbp::xbp ( const GF2Mat & X, float sgma) {
    H = X;
    M = H.get_M();
    N = H.get_N();
    Q.resize(M);
    R.resize(M);
    sigma = sgma;
    for (int i = 0; i < M; i++) {
        Q[i].resize(N);
        R[i].resize(N);
    }
    lr.resize(N);
    estimate.resize(N);
}

xbp::xbp ( alist & _list, float sgma) {
    H = GF2Mat(_list);
    mlist = _list.get_mlist();
    nlist = _list.get_nlist();
    num_mlist = _list.get_num_mlist();
    num_nlist = _list.get_num_nlist();
    M = H.get_M();
    N = H.get_N();
    Q.resize(M);
    R.resize(M);
    sigma = sgma;
    for (int i = 0; i < M; i++) {
        Q[i].resize(N);
        R[i].resize(N);
    }
    lr.resize(N);
    estimate.resize(N);
}

void xbp::set_alist_sigma(alist & _list, float sgma) {
    H = GF2Mat(_list);
    mlist = _list.get_mlist();
    nlist = _list.get_nlist();
    num_mlist = _list.get_num_mlist();
    num_nlist = _list.get_num_nlist();
    M = H.get_M();
    N = H.get_N();
    Q.resize(M);
    R.resize(M);
    sigma = sgma;
    for (int i = 0; i < M; i++) {
        Q[i].resize(N);
        R[i].resize(N);
    }
    lr.resize(N);
    estimate.resize(N);
}

std::vector< std::vector<double> > xbp::get_Q() {
    return Q;
}

std::vector< std::vector<double> > xbp::get_R() {
    return R;
}

GF2Mat xbp::get_H() {
    return H;
}

void xbp::rx_lr_calc(std::vector<char> codeword) {
    rx_lr.resize(N);
    for ( int i = 0; i < N; i++){
        if ( codeword[i] == char(0) )
            rx_lr[i] = double(sigma/(1 - sigma));
        else 
            rx_lr[i] = double((1 - sigma)/sigma);
    }
}

std::vector<double> xbp::get_rx_lr() {
    return rx_lr;
}

std::vector<double> xbp::get_lr() {
    return lr;
}

void xbp::spa_initialize() {
    int row;
    for ( int var = 0; var < N; var++ ) {
        for ( int i = 0; i < num_nlist[var]; i++ ) {
            row = nlist[var][i] - 1;
            Q[row][var] = rx_lr[var];
        }
    }
//    std::cout << "returning from spa_initialize()\n";
}

void xbp::update_chks() {
    double product, _prdct;
    int v;
    for ( int chk = 0; chk < M; chk++ ) {
        product = double(1.0);
        for (int i = 0; i < num_mlist[chk]; i++) {
            v = mlist[chk][i] - 1;
            product = product*double( 2/(1 + Q[chk][v]) - 1 );
        }
        for ( int i = 0; i < num_mlist[chk]; i++ ) {
            v = mlist[chk][i] - 1;
            _prdct = product/double( 2/(1 + Q[chk][v]) - 1);
            R[chk][v] = double((1 - _prdct)/(1 + _prdct));
//            if ( R[chk][v] != R[chk][v] )
//                std::cout << chk << "\t" << v << "\t" << R[chk][v] << "\n";
//            std::cout << _prdct << "\t";
        }
//        std::cout << "\n";
    }
}

void xbp::update_vars() {
    double _sum, __sum;
    int c;
//    std::cout << lr.size() << "\n";
    for ( int var = 0; var < N; var++ ) {
        _sum = rx_lr[var];
        for ( int i = 0; i < num_nlist[var]; i++ ) {
            c = nlist[var][i] - 1;
//            if ( R[c][var] != R[c][var] ) 
//                std::cout << "nan ";
            _sum = _sum * double(R[c][var]);
        }
        lr[var] = _sum;
        for ( int i = 0; i < num_nlist[var]; i++ ) {
            c = nlist[var][i] - 1;
            __sum = _sum/R[c][var];
            Q[c][var] = __sum;
        }
    }
}

std::vector<char> xbp::get_estimate() {
    return estimate;
}

void xbp::compute_init_estimate(std::vector<float> rx_word) {
//    std::cout << "inside compute_init_estimate len rx = " << rx_word.size();
//    std::cout << std::endl;
    for ( int i = 0; i < rx_word.size(); i++ ) {
        if (rx_word[i] < 0)
            estimate[i] = char(1);
        else
            estimate[i] = char(0);
    }
//    for ( int i = 0; i < N; i++ ) {
//        std::cout << int(estimate[i]);
//    }
//    std::cout << std::endl;
}

void xbp::decision() {
    for ( int i = 0; i < N; i++ ){
        if ( lr[i] > 1 )
            estimate[i] = char(1);
        else
            estimate[i] = char(0);
    }
}

void xbp::set_K(int k) {
    K = k;
}

int xbp::get_K() {
    return K;
}

std::vector<char> xbp::get_syndrome(std::vector<char> codeword) {
    std::vector<char> synd;
    synd.resize(N - K);
    GF2Vec in_bvec;
    in_bvec.set_vec(codeword);
    for ( int i = 0; i < N - K; i++ ) {
        synd[i] = H[i]*in_bvec;
    }
    return synd;
}

std::vector<char> xbp::get_syndrome() {
//    std::cout << "inside get_syndrome()\n";
    std::vector<char> synd;
//    std::cout << N - K << " = N - K\n";
//    std::cout << M << " = M\n";
//    std::cout << N << " = N\n";
//    std::cout << K << " = K\n";
    synd.resize(N - K);
    GF2Vec in_bvec;
    in_bvec.set_vec(estimate);
    for ( int i = 0; i < N - K; i++ ) {
        synd[i] = H[i]*in_bvec;
    }
//    std::cout << "prining syndrome\n";
//    for (int i = 0; i < N - K; i++ )
//        std::cout << int(synd[i]);
//    std::cout << std::endl;
    return synd;
}

bool xbp::is_codeword(std::vector<char> codeword) {
    std::vector<char> synd;
    synd = get_syndrome(codeword);
    bool is_code;
    is_code = true;
    for ( int i = 0; i < N - K; i++ ) {
        if ( synd[i] != char(0) ) {
            is_code = false;
        }
    }
    return is_code;
}

bool xbp::is_codeword() {
//    std::cout << "inside is_codeword\n";
    std::vector<char> synd;
    synd = get_syndrome();
//    std::cout << "inside is_codeword(), computed syndrome\n";
    bool is_code;
    is_code = true;
    for ( int i = 0; i < N - K; i++ ) {
        if ( synd[i] != char(0) ) {
            is_code = false;
        }
    }
//    std::cout << "returning from is_codeword\n";
    return is_code;
}

void xbp::set_max_iterations(int k) {
    max_iterations = k;
}

int xbp::get_max_iterations() {
    return max_iterations;
}

std::vector<char> xbp::decode(std::vector<char> rx_word,
        int & niteration) {
//    std::cout << "inside decode function, initializing ntieration\n";
    niteration = 0;
//    std::cout << "inside decode function, initialized ntieration\n";
//    compute_init_estimate(rx_word);
//    std::cout << "inside decode function, computed initial estimate\n";
    if (is_codeword(rx_word)) {
//        std::cout << "branched at is codeword\n";
        return rx_word;
    }
    else {
//        std::cout << "branched at not a codeword\n";
        rx_lr_calc(rx_word);
        spa_initialize();
        while (niteration < max_iterations) {
            niteration += 1;
            update_chks();
            update_vars();
            decision();
            if (is_codeword()) {
                break;
            }
        }
//        std::cout << "inside decode function, returing\n";
        return estimate;
    }
}
