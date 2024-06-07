#include<iostream>
#include<vector>
#pragma once
namespace math
{
    template<class T>
    class Matrix
    {
        private:
        std::vector<std::vector<T>>* table;
        size_t height;
        size_t width;
        public:
        Matrix(size_t height =2, size_t width= 2); // решил оставить только один констуктор, просто с стандартными значениями аргументов
        Matrix(const Matrix<T>& mat);
        Matrix(Matrix<T>&& mat);
        ~Matrix();
        Matrix<T> operator+(const Matrix<T>& mat) const;
        Matrix<T> operator-(const Matrix<T>& mat) const;
        Matrix<T> operator*(const T& num) const;
        Matrix<T> operator*(const Matrix<T>& mat) const;
        Matrix<T> operator=(const Matrix<T>& mat);
        bool operator==(const Matrix<T>& mat) const;
        inline T& at(size_t x, size_t y) const; //Вместо оператора [] - с ним бы было немало трудностей...
        inline size_t get_height() const; // дописать
        inline size_t get_width() const; // дописать
    };
}

template<class T>
math::Matrix<T>::Matrix(const Matrix<T>& mat):  height{mat.height}, width{mat.width}
{
    table = new std::vector<std::vector<T>>(height);
    for ( int i = 0 ; i < height; i++ )
        table->at(i).resize(width, 0);
    for(int i =0; i < this->height; ++i)
    {
        for(int j =0; j < this->width; ++j)
        {
            this->at(i, j) = mat.at(i, j);
        }
    }
}

template<class T>
math::Matrix<T>::Matrix(size_t height, size_t width)
{
    this->height = height;
    this->width = width;
    table = new std::vector<std::vector<T>>(height);
    for ( int i = 0 ; i < height; i++ )
        table->at(i).resize(width, 0);
    
}

template<class T>
math::Matrix<T>::Matrix(Matrix<T>&& mat): height{mat.height}, width{mat.width}, table{mat.table}
{
    mat.height = 0;
    mat.width = 0;
    mat.table = nullptr;          
}

template<class T>
math::Matrix<T>::~Matrix()
{
    if(table)
    {
    delete table;
    table = nullptr;
    }
}

template<class T>
size_t math::Matrix<T>::get_height() const
{
    return height;
}

template<class T>
size_t math::Matrix<T>::get_width() const
{
    return width;
}

template<class T>
T& math::Matrix<T>::at(size_t x, size_t y) const
{
    return table->at(x).at(y);
}

template<class T>
bool math::Matrix<T>::operator==(const Matrix<T>& mat) const
{
    if(mat.get_height != height || mat.get_width != width) return false;
    for(size_t i =0; i < height; ++i)
    {
        for(size_t j = 0; j < width; ++j)
        {
            if(this->table[i][j] != mat.at(i, j)) return false;
        }
    }
    return true;
}

template<class T>
std::ostream& operator<<(std::ostream& os, const math::Matrix<T>& mat) 
{
    size_t height = mat.get_height();
    size_t width = mat.get_width();
    for(size_t i =0; i < height; ++i)
    {
        for(size_t j = 0; j < width; ++j)
        {
            os << mat.at(i, j) << " ";
        }
        os << "\n";
    }
    return os;
}

template<class T>
std::istream& operator>>(std::istream& in, const math::Matrix<T>& mat) 
{
    size_t height = mat.get_height();
    size_t width = mat.get_width();
    T data;
    for(int i = 0; i < height; ++i)
    {
        for(int j =0; j < width; ++j)
        {
            in >> data;
            mat.at(i, j) =  data;
        }
    }
    return in;
}


template<class T>
math::Matrix<T> math::Matrix<T>::operator+(const Matrix<T>& mat) const
{
    if(this->height !=  mat.get_height() || this->width != mat.get_width()) // бросаем исключение в случае несовпадения размерности матриц
        throw std::logic_error("Matrix dimensions must agree!!!"); 
    Matrix<T> temp_mat(this->height, this->width);
    for(int i =0; i < this->height; ++i)
    {
        for(int j = 0; j < this->width; ++j)
        {
            temp_mat.at(i, j) = this->at(i, j)+mat.at(i, j);
        }
    }
    return temp_mat;

}

//здесь жоский копипаст, хз как сделать иначе
template<class T>
math::Matrix<T> math::Matrix<T>::operator-(const Matrix<T>& mat) const
{
    if(this->height !=  mat.get_height() || this->width != mat.get_width())
        throw std::logic_error("Matrix dimensions must agree!!!");

    Matrix<T> temp_mat(this->height, this->widht);
    for(int i =0; i < this->height; ++i)
    {
        for(int j = 0; j < this->width; ++j)
        {
            temp_mat.at(i, j) =  this->at(i, j)-mat.at(i, j);
        }
    }
    return temp_mat;
}


template<class T>
math::Matrix<T> math::Matrix<T>::operator*(const T& num) const
{
    Matrix<T> temp_mat(this->height, this->width);
    for(int i =0; i < this->height; ++i)
    {
        for(int j = 0; j < this->width; ++j)
        {
            temp_mat.at(i, j) =  this->at(i, j)*num;
        }
    }
    return temp_mat;
}

template<class T>
math::Matrix<T> math::Matrix<T>::operator*(const Matrix<T>& mat) const
{
    if(this->width!=mat.get_width())
    {
        throw std::logic_error("Quantity of columns of second matrix must be equal quantity of strings of second matrix!!!");
    }
    else
    {
        Matrix<T> temp_mat(this->height, mat.get_width());
        for(int i =0; i < this->height;++i)
        {
            for(int j = 0; j < mat.get_width(); ++j)
            {
                for(int k =0; k < mat.get_height(); ++k){ 
                    temp_mat.at(i, j) += this->at(i,k) * mat.at(k, j);
                    }
            }
        }
        return temp_mat;
    }
}

template<class T>
math::Matrix<T> math::Matrix<T>::operator=(const Matrix<T>& mat)
{
    if(mat.get_height() != this->height ) // меняем размер в случаем несовпадения
    {
        table->resize(mat.get_height());
        height = mat.get_height();
    }
    if(mat.get_width() != this->width)
    {
        for(int i = 0; i < this->height; ++i)
        {
            table->at(i).resize(mat.get_width());
        }
        width = mat.get_width();
    }
    for(int i =0; i < this->height; ++i)
    {
        for(int j =0; j < this->width; ++j)
        {
            this->at(i, j) = mat.at(i, j);
        }
    }
    return *this;
}