#include "Matrix.hpp"
#pragma once
namespace math
{
// Решил написать класс без реализации конструктора, потому что сам по себе, помимо метода сверстки, логики он никакой не несет
template<class T>
class Convolution: private Matrix<T>
{
    private:
    Convolution();
    public:
    /**
     * @brief метод сверстки
     * 
     * @param mat  - входная матрица
     * @param weights - матрица весов
     * @return Matrix<T>  - результирующая матрица
     */
    static Matrix<T> convolution(const Matrix<T>& mat, const Matrix<T>& weights);
};
}

namespace math
{
template<class T>
Matrix<T> Convolution<T>::convolution(const Matrix<T>& mat, const Matrix<T>& weights)
{
    if(mat.get_height() < weights.get_height() || mat.get_width() < weights.get_height()) throw std::logic_error("Wrong sizes!!!");
    Matrix<T> result(1+mat.get_height()-weights.get_height(), 1+mat.get_width()-weights.get_width());
    T sum =0;
    for(int i =0; i <= mat.get_height()-weights.get_height(); ++i)
    {
        for(int j =0; j <= mat.get_width()-weights.get_width(); ++j)
        {
            for(int k = i; k < i+weights.get_height(); ++k)
            {
                for(int l = j; l < j+weights.get_width(); ++l)
                     sum+=mat.at(k, l)*weights.at(k-i, l-j);
            }
            result.at(i, j) = sum;
            sum =0;
        }
    }
    return result;
}
}