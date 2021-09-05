//
// Created by yang on 8/31/21.
//

//===----------------------------------------------------------------------===//
//
//
//
// p0_starter.h
//
// Identification: src/include/primer/p0_starter.h
//
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include <memory>
#include <stdexcept>
#include <vector>

//#include "common/exception.h"

namespace scudb {

/**
 * The Matrix type defines a common
 * interface for matrix operations.
 */
template <typename T>
class Matrix {

    protected:
    /**
     * TODO(P0): Add implementation
     *
     * Construct a new Matrix instance.
     * @param rows The number of rows
     * @param cols The number of columns
     *
     */
    Matrix(int rows, int cols):rows_(rows),cols_(cols) {
        linear_ = new T[rows*cols];
    }

    /** The number of rows in the matrix */
    int rows_;
    /** The number of columns in the matrix */
    int cols_;

    /**
     * TODO(P0): Allocate the array in the constructor.
     * TODO(P0): Deallocate the array in the destructor.
     * A flattened array containing the elements of the matrix.
     */
    T *linear_;

    public:
    /** @return The number of rows in the matrix */
    virtual int GetRowCount() const = 0;

    /** @return The number of columns in the matrix */
    virtual int GetColumnCount() const = 0;

    /**
     * Get the (i,j)th matrix element.
     *
     * Throw OUT_OF_RANGE if either index is out of range.
     *
     * @param i The row index
     * @param j The column index
     * @return The (i,j)th matrix element
     * @throws OUT_OF_RANGE if either index is out of range
     */
    virtual T GetElement(int i, int j) const = 0;

    /**
     * Set the (i,j)th matrix element.
     *
     * Throw OUT_OF_RANGE if either index is out of range.
     *
     * @param i The row index
     * @param j The column index
     * @param val The value to insert
     * @throws OUT_OF_RANGE if either index is out of range
     */
    virtual void SetElement(int i, int j, T val) = 0;

    /**
     * Fill the elements of the matrix from `source`.
     *
     * Throw OUT_OF_RANGE in the event that `source`
     * does not contain the required number of elements.
     *
     * @param source The source container
     * @throws OUT_OF_RANGE if `source` is incorrect size
     */
    virtual void FillFrom(const std::vector<T> &source) = 0;

    /**
     * Destroy a matrix instance.
     * TODO(P0): Add implementation
     */
    virtual ~Matrix(){
        delete [] linear_;
    }
};

/**
* The RowMatrix type is a concrete matrix implementation.
* It implements the interface defined by the Matrix type.
*/
template <typename T>
class RowMatrix : public Matrix<T> {
public:
    /**
     * TODO(P0): Add implementation
     *
     * Construct a new RowMatrix instance.
     * @param rows The number of rows
     * @param cols The number of columns
     */
    RowMatrix(int rows, int cols) : Matrix<T>(rows, cols) {
        data_ = new T *[rows];
        for(int i=0;i<rows;i++){
            data_[i] = new T[cols];
        }
        
        for(int i=0;i<rows;i++){
            for(int j=0;j<cols;j++){
                data_[i][j] = 0;
            }
        }
        
    }
    /**
     * TODO(P0): Add implementation
     * @return The number of rows in the matrix
     */
    int GetRowCount() const override {
        return this->rows_;
    }

    /**
     * TODO(P0): Add implementation
     * @return The number of columns in the matrix
     */
    int GetColumnCount() const override {
        return this->cols_;
    }

    /**
     * TODO(P0): Add implementation
     *
     * Get the (i,j)th matrix element.
     *
     * Throw OUT_OF_RANGE if either index is out of range.
     *
     * @param i The row index
     * @param j The column index
     * @return The (i,j)th matrix element
     * @throws OUT_OF_RANGE if either index is out of range
     */
    T GetElement(int i, int j) const override {

        if (i<0 || i>=this->rows_|| j<0 || j>=this->cols_){
            //throw NotImplementedException{"RowMatrix::GetElement() not implemented."};
            throw std::out_of_range("RowMatrix::GetElement() not implemented.");
        }
        else{
            return data_[i][j];
        }
        
    }

    /**
     * Set the (i,j)th matrix element.
     *
     * Throw OUT_OF_RANGE if either index is out of range.
     *
     * @param i The row index
     * @param j The column index
     * @param val The value to insert
     * @throws OUT_OF_RANGE if either index is out of range
     */
    void SetElement(int i, int j, T val) override {
        if (i<0 || i>this->rows_ || j<0 || j>this->cols_){
            //throw NotImplementedException{"RowMatrix::GetElement() not implemented."};
            throw std::out_of_range("RowMatrix::SetElement() not implemented.");

        }
        this->linear_[i*this->GetColumnCount() + j] = val;
        data_[i][j] = val;
    }

    /**
     * TODO(P0): Add implementation
     *
     * Fill the elements of the matrix from `source`.
     *
     * Throw OUT_OF_RANGE in the event that `source`
     * does not contain the required number of elements.
     *
     * @param source The source container
     * @throws OUT_OF_RANGE if `source` is incorrect size
     */
    void FillFrom(const std::vector<T> &source) override {

        if ((this->cols_)*(this->rows_)!=int(source.size())){
            //throw NotImplementedException{"RowMatrix::FillFrom() not implemented."};
            throw std::out_of_range("RowMatrix::FillFrom() not implemented.");
        }
       else{
           for(int i=0;i<this->rows_;i++){
               for(int j=0;j<this->cols_;j++){
                   data_[i][j] = source[i*this->cols_ + j];
                   this->linear_[i*this->cols_ + j] = source[i*this->cols_ + j];
            }
        }
       }
       
    }

    /**
     * TODO(P0): Add implementation
     *
     * Destroy a RowMatrix instance.
     */
    ~RowMatrix() override {
        for(int i=0;i<this->GetRowCount();i++){
            delete [] data_[i];
        }
        delete [] data_;
    }

    private:
    /**
     * A 2D array containing the elements of the matrix in row-major format.
     *
     * TODO(P0):
     * - Allocate the array of row pointers in the constructor.
     * - Use these pointers to point to corresponding elements of the `linear` array.
     * - Don't forget to deallocate the array in the destructor.
     */
    T **data_;
};

/**
* The RowMatrixOperations class defines operations
* that may be performed on instances of `RowMatrix`.
*/
template <typename T>
class RowMatrixOperations {
public:
    /**
     * Compute (`matrixA` + `matrixB`) and return the result.
     * Return `nullptr` if dimensions mismatch for input matrices.
     * @param matrixA Input matrix
     * @param matrixB Input matrix
     * @return The result of matrix addition
     */
    static std::unique_ptr<RowMatrix<T>> Add(const RowMatrix<T> *matrixA, const RowMatrix<T> *matrixB) {
        // TODO(P0): Add implementation
        if (matrixA->GetRowCount()!=matrixB->GetRowCount() || matrixA->GetColumnCount()!=matrixB->GetColumnCount()){
            return std::unique_ptr<RowMatrix<T>>(nullptr);
        }
        else{
            int row = matrixA->GetRowCount();
            int col = matrixA->GetColumnCount();

            auto matrix_sum = std::make_unique<RowMatrix<T>>(row,col);
            for(int i=0;i<row;i++){
                for(int j=0;j<col;j++){
                    matrix_sum->SetElement(i,j,matrixA->GetElement(i,j)+matrixB->GetElement(i,j));
                }
            }

            return matrix_sum;

        }

    }

    /**
     * Compute the matrix multiplication (`matrixA` * `matrixB` and return the result.
     * Return `nullptr` if dimensions mismatch for input matrices.
     * @param matrixA Input matrix
     * @param matrixB Input matrix
     * @return The result of matrix multiplication
     */
    static std::unique_ptr<RowMatrix<T>> Multiply(const RowMatrix<T> *matrixA, const RowMatrix<T> *matrixB) {
        // TODO(P0): Add implementation
        if (matrixA->GetColumnCount() != matrixB->GetRowCount()){
            return std::unique_ptr<RowMatrix<T>>(nullptr);
        }

        int row = matrixA->GetRowCount();
        int col = matrixB->GetColumnCount();
        
        auto matrix_mul = std::make_unique<RowMatrix<T>>(row,col);

        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                for(int k=0;k<matrixA->GetColumnCount();k++){
                    matrix_mul->SetElement(i,j,matrix_mul->GetElement(i,j)+matrixA->GetElement(i,k)*matrixB->GetElement(k,j));
                }
            }
        }
        return matrix_mul;
    }

    /**
     * Simplified General Matrix Multiply operation. Compute (`matrixA` * `matrixB` + `matrixC`).
     * Return `nullptr` if dimensions mismatch for input matrices.
     * @param matrixA Input matrix
     * @param matrixB Input matrix
     * @param matrixC Input matrix
     * @return The result of general matrix multiply
     */
    static std::unique_ptr<RowMatrix<T>> GEMM(const RowMatrix<T> *matrixA, const RowMatrix<T> *matrixB,
                                            const RowMatrix<T> *matrixC) {
        // TODO(P0): Add implementation
        if (matrixA->GetColumnCount() != matrixB->GetRowCount() || \
        matrixA->GetRowCount()!=matrixC->GetRowCount() || \
        matrixB->GetColumnCount()!=matrixC->GetColumnCount()){
            return std::unique_ptr<RowMatrix<T>>(nullptr);
        }
        return Add(Multiply(matrixA,matrixB).get(), matrixC);
    }
    static void Show(const RowMatrix<T> &matrix){
        for(int i=0;i<matrix.GetRowCount();i++){
            for(int j=0;j<matrix.GetColumnCount();j++){
                std::cout<<matrix.GetElement(i,j)<<" ";
            }
            std::cout<<std::endl;
        }
    }
};
}  // namespace scudb