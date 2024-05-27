#include <iostream>
#include<vector>
#include<random>
#include "matrix.hpp"
#include "Convolution.hpp"
#include "Subdiscretization.hpp"
int main(int, char**){
    math::Matrix<int> someshit(3, 3);
    math::Matrix<int> othershit;
    math::Matrix<int> plusshit(3,3);
    std::cin >> plusshit;
    someshit = math::SubDiscret<int>::subdiscret(plusshit);
    std::cout << someshit << "\n";
    std::cout << othershit << "\n";
    std::cin >> someshit;
    std::cin >> othershit;
    plusshit = math::Convolution<int>::convolution(someshit, othershit);
    std::cout << plusshit;


}
