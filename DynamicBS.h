#ifndef DYNAMICBS__
#define DYNAMICBS__
#include <vector>
class DynamicBS{
public:
    DynamicBS(int);
    ~DynamicBS();

    void TableInit();
    void Print()const;
    std::vector<int> Search(int)const;
    void Insert(int);
    void Delete(int);
    void OpI(); //operation Interface

    int GetNumElement()const{ return numElement;}

private:
    int **table;
    int numElement = 0;
    int size = 0;
};
#endif // DYNAMICBS__

/*

k = 4 (n=8~15)
A_0 : *
A_1 : * *
A_2 : * * * *
A_3 : * * * * * * * *

*/