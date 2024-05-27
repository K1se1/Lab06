#include "matrix.hpp"

namespace math
{
    template<class T>
    class SubDiscret: private Matrix<T>
    {
        private:
        SubDiscret();
        public:
        static Matrix<T> subdiscret(const Matrix<T>& mat);
    };
}


template<class T>
math::Matrix<T> math::SubDiscret<T>::subdiscret(const Matrix<T>& mat)
{
    T temp = mat.at(0, 0);
    math::Matrix<T> result(mat.get_height()-1, mat.get_width()-1);
     for(int i =0; i < mat.get_height()-1;++i)
     {
        for(int j =0; j < mat.get_width()-1; ++j)
        {
            for(int k =i; k < 2+i; ++k)
            {
                for(int l = j; l < 2+j; ++l) if(mat.at(k, l) >= temp) temp = mat.at(k, l);
            }
            result.at(i, j) = temp;
        }
     }
     return result;
}