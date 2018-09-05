#include<iostream>
#include<typeinfo>
#include<string>
#include<iomanip>
template<typename T, int N, int M>//N - row, M - column

class Matrix{
private:
    //T _matrix[N][M];
public:
    T _matrix[N][M];
    Matrix<T,N,M>()
    {
        std::cout << "constructor\n";
        std::srand(time(NULL));
        if(N == 0 || M == 0)
        {
            std::cout << "Cannot create matrix with no columns or rows\n";
        }
        else
        {
           myswitch((T)15);
        }
    }

    void myswitch(int t)
    {
        std::cout << "int\n";
        for(int i = 0; i < N; i++)
        {
            //std::cout << "Enter " << M << " values for matrix " << i+1  << " row:" << std::endl;
            for(int j = 0; j < M; j++)
            {
                //std::cin >> _matrix[i][j];
                _matrix[i][j] = std::rand () % 100 +1;
            }
        }
    }

    void myswitch(float t)
    {
        std::cout << "float\n";
        for(int i = 0; i < N; i++)
        {
            for(int j = 0; j < M; j++)
            {
            _matrix[i][j] = ((float)rand() / RAND_MAX) * 1000;
            }
        }
    }

    void myswitch(char t)
    {
        std::cout << "char\n";
        for(int i = 0; i < N; i++)
        {
            for(int j = 0; j < M; j++)
            {
            _matrix[i][j] = std::rand () % 10 +1;
            }
        }
    }

    void myswitch(double t)
    {
        std::cout << "double\n";
        for(int i = 0; i < N; i++)
        {
            for(int j = 0; j < M; j++)
            {
            _matrix[i][j] = ((double)rand() / RAND_MAX) * 1000;
            }
        }
    }

    T* operator[](int pos)
    {
        return _matrix[pos];
    }

    template<typename T1, int N1, int M1>
    Matrix<T,N,M>(Matrix<T1, N1, M1> m):_matrix{}
    {
        if(N == 0 || M == 0)
        {
            std::cout << "Cannot make matrix with no columns or rows\n";
        }
        else if(N1 != N || M1 != M)
        {
            std::cout << "Cannot create matrix when columns or rows are different\n";
        }
        else
        {
            std::cout << "copy constructor\n";
            for(int i = 0; i < N; i++)
            {
                for(int j = 0; j < M; j++)
                 {
                    _matrix[i][j] = m[i][j];
                }
            }
        }

    }

    void show()
    {

        std::cout << "Matrix " << this << ": " << std::endl;
        for(int i = 0; i < N; i++)
         {
             for(int j = 0; j < M; j++)
             {
                std::cout << std::fixed << std::setprecision(2) << _matrix[i][j] << "\t";
             }
             std::cout << "\n";
         }
         std::cout << "\n";
    }

    void scalarMultiply(T scalar)
    {
        for(int i = 0; i < N; i++)
        {
             for(int j = 0; j < M; j++)
             {
                _matrix[i][j] *= scalar ;
             }
        }
    }

    void scalarAdd(T scalar)
    {
        for(int i = 0; i < N; i++)
        {
            for(int j = 0; j < M; j++)
            {
                _matrix[i][j] += scalar ;
            }
        }
    }

    template<typename T1, int N1, int M1>
    Matrix<T,N,M> operator+(Matrix<T1, N1, M1> m)
    {
        if(N1 != N || M1 != M)
        {
            std::cout << "Cannot add matrixex when columns or rows are not equal\n";
        }
        else
        {
            Matrix<T,N,M> result(m);
            result.show();
            for(int i = 0; i < N; i++)
            {
                for(int j = 0; j < M; j++)
                {
                    result._matrix[i][j] = m._matrix[i][j] + _matrix[i][j];
                }
            }
            std::cout << "\n";
            return result;
        }
    }

    template<typename T1, int N1, int M1>
    Matrix<T,N,M> operator*(Matrix<T1, N1, M1> m)
    {
        if(N == 0 || M == 0 || N1 == 0 || M1 == 0)
        {
             std::cout << "Cannot multiply matrix with no columns or rows\n";
        }
        else if(M != N1)
        {
             std::cout << "Cannot multiply matrixex when first matrix has different number of columns that second matrix rows\n";
        }
        else
        {
            Matrix<T,N,M1> result(m);
            result.show();
            for(int i = 0; i < N; i++)
            {
                for(int j = 0; j < M1; j++)
                {
                    result._matrix[i][j] = 0;
                    for(int k = 0; k < N1; k++)
                    {
                        result._matrix[i][j] += _matrix[i][k]*m._matrix[k][j];
                    }
                }
            }
            std::cout << "\n";
            return result;
        }
    }
};

int main()
{
    Matrix<double,3,3> m1;
    Matrix<int,3,3> m2(m1);
    m1.show();
    m2.show();
    Matrix<double,3,3> m3 = m1 + m2;
    m3.show();
    Matrix<double,0,0> m4;
    Matrix<double,3,3> m7 = m3 + m2;
    m7.show();
    Matrix<char,4,3> m5;
    m5.show();
    Matrix<float,4,3> m8(m1);
    Matrix<double,3,3> m6 = m1 * m2;
    m6.show();
    m6.scalarMultiply(2);
    m6.show();
    m6.scalarAdd(2);
    m6.show();
    Matrix<int,4,3> m9 = m1 * m5;

}




