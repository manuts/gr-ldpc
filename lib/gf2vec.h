#ifndef GF2VEC_H
#define GF2VEC_H
#include <vector>

class GF2Vec
{
    std::vector<char> vec;
    void resize(int size);

  public:

    GF2Vec() {}

    GF2Vec(int size);

    std::vector<char> get_vec(){
        return vec;
    }

    int size();

    void set_vec(std::vector<char>);

    char & operator [](int i);

    void operator=(GF2Vec x);

    GF2Vec sub_vector(int from, int to);

    friend GF2Vec operator+(GF2Vec a, GF2Vec b);

    friend char operator*(GF2Vec a, GF2Vec b);

    void print_vec();
};

#endif // #ifndef GF2VEC_H
