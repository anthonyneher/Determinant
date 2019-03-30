#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

struct Matrix
{//this matrix class holds the information about the matrix
    struct Node{
        Node * next;
        int row;
        int column;
        int value;
        Node(int row, int col, int val);
    };
    //values
    Node * head = nullptr;
    Node * tail = nullptr;
    int size = 0;
    //methods
    void addNode(int row,int column,int value);
};

Matrix::Node::Node(int row, int col, int val){
    this->row = row;
    column = col;
    value = val;
    next = nullptr;
}

void Matrix::addNode(int row, int column, int value){

    Node * newnode = new Node(row, column, value);

    if(head == nullptr){
        head = newnode;
        tail = newnode;
    }
    else{
        tail->next = newnode;
        tail = newnode;
    }
}

bool ReadInput(Matrix * matrix)
{
    string line;
    getline(cin, line);
    string token;
    int rowNum=0;
    int size=0;
    int colNum;
    int test;
    //get size
    stringstream lineStream(line);
    while(lineStream >> token)
    {
        size++;
    }
    //initialize 2D vector
    //read lines
    for (int k = 0; k<size-1; k++)
    {
        stringstream lineStream2(line);
        if(line.empty()){
            cout<<"Error! Non-square matrix!\n";
            return false;
        }
        colNum = 0;
        while(lineStream2 >> token)
        {
            test = stoi(token);
            if(test != 0){
                matrix->addNode(rowNum,colNum, test);
            }
            colNum++;
        }
        rowNum++;
        line.clear();
        getline(cin, line);
    }
    //do the last line
    if(line.empty()){
        cout<<"Error! Non-square matrix!\n";
        return false;
    }
    stringstream lineStream2(line);
    colNum = 0;
    while(lineStream2 >> token)
    {
        test = stoi(token);
        if(test != 0){
            matrix->addNode(rowNum,colNum, test);
        }
        colNum++;
    }
    rowNum++;
    matrix->size = rowNum;
    if(colNum != rowNum){
        cout<<"Error! Non-square matrix!\n";
        return false;
    }
    return true;
}



int determinant(Matrix * matrix){
    auto minormatrix = [](Matrix * mat, int col){//helper function
        auto * submatrix = new Matrix;
        Matrix::Node * iter = mat->head;
        while(iter!= nullptr){

            if((iter->row!=0) && (iter->column != col)){
                if(iter->column<col){
                    submatrix->addNode(iter->row-1,iter->column,iter->value);
                }else{
                    submatrix->addNode(iter->row-1,iter->column-1,iter->value);
                }
            }

            iter = iter->next;
        }
        submatrix->size = mat->size-1;
        return submatrix;
    };
    auto twobytwo = [](Matrix::Node * head){
        auto iter = head;
        int topleft = 0;
        int topright = 0;
        int bottomleft = 0;
        int bottomright = 0;
        while(iter != nullptr){

            if((iter->row == 0) && (iter->column == 0)){
                topleft = iter->value;
            }
            if((iter->row==1) && (iter->column == 1)){
                bottomright = iter->value;
            }
            if((iter->row == 0) && (iter->column == 1)){
                topright = iter->value;
            }
            if((iter->row == 1) && (iter->column == 0)){
                bottomleft = iter->value;
            }
            iter = iter->next;

        }
        return (topleft*bottomright - topright*bottomleft);
    };
    auto * iterator = matrix->head;
    if(matrix->head==nullptr){
        return 0;
    }else if(matrix->size == 2){
        return twobytwo(matrix->head);
    }else{
        int det =0;
        int sign;
        while(iterator->row == 0){
            if(iterator->column%2 == 0){
                sign = 1;
            }else{sign = -1;}

            det += iterator->value*sign*determinant(minormatrix(matrix,iterator->column));

            iterator = iterator->next;
        }
        return det;
    }
}


int main() {
    auto * matrix = new Matrix;
    if(ReadInput(matrix)){
        int num = determinant(matrix);
        cout<<num<<endl;
    }
    return 0;
}
