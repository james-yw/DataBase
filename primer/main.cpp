#include <iostream>
#include <vector>
#include "p0_starter.h"

std::vector<int> Generated_vector(int length){
    std::vector<int> v(length);
    for(int i =0;i<length;i++){
        v[i] = rand()%10;
    }
    return v;
}

int main(int argc, const char * argv[])
{
    std::cout<<"TEST for p0_start.h"<<std::endl;
    std::cout<<"-------------------"<<std::endl;


    std::cout<<"RANDOM INITIALIZE..."<<std::endl;

    scudb::RowMatrix<int> mat_1(4,5);
    scudb::RowMatrix<int> mat_2(5,4);
    scudb::RowMatrix<int> mat_3(4,4);
    scudb::RowMatrix<int> mat_4(4,4);



    std::vector<int> source_1 = Generated_vector(4*5);
    std::vector<int> source_2 = Generated_vector(5*4);
    std::vector<int> source_3 = Generated_vector(4*4);
    std::vector<int> source_4 = Generated_vector(4*4);

    mat_1.FillFrom(source_1);
    mat_2.FillFrom(source_2);
    mat_3.FillFrom(source_3);
    mat_4.FillFrom(source_4);

    std::cout<<"matrix_1:"<<std::endl;
    scudb::RowMatrixOperations<int>::Show(mat_1);
    std::cout<<"matrix_2:"<<std::endl;
    scudb::RowMatrixOperations<int>::Show(mat_2);
    std::cout<<"matrix_3:"<<std::endl;
    scudb::RowMatrixOperations<int>::Show(mat_3);
    std::cout<<"matrix_4:"<<std::endl;
    scudb::RowMatrixOperations<int>::Show(mat_4);

    std::cout<<"TEST_ONE:Add    matrix_3+matrix_4"<<std::endl;
    auto mat_sum = scudb::RowMatrixOperations<int>::Add(&mat_3,&mat_4);
    scudb::RowMatrixOperations<int>::Show(*mat_sum);

    std::cout<<"TEST_TWO:Multiply   matrix_1*matrix_2"<<std::endl;
    auto mat_mul = scudb::RowMatrixOperations<int>::Multiply(&mat_1,&mat_2);
    scudb::RowMatrixOperations<int>::Show(*mat_mul);

    std::cout<<"TEST_TWO:GEMM   matrix_1*matrix_2+matrix_3"<<std::endl;
    auto mat_GEMM = scudb::RowMatrixOperations<int>::GEMM(&mat_1,&mat_2,&mat_3);
    scudb::RowMatrixOperations<int>::Show(*mat_GEMM);

    return 0;
}