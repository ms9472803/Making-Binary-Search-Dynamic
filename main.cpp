#include "DynamicBS.h"
#include <iostream>
using namespace std;
int main()
{
    constexpr int defaultSize = 100;
    DynamicBS *DyBS = new DynamicBS(defaultSize);
    DyBS->Insert(1);
    DyBS->Insert(2);
    DyBS->Insert(3);
    DyBS->Insert(4);
    DyBS->Insert(5);
    DyBS->Insert(6);
    DyBS->Insert(7);
    DyBS->Insert(8);
    DyBS->Insert(9);
    DyBS->Insert(10);
    DyBS->Insert(11);
    DyBS->Insert(12);
    DyBS->Delete(11);
    DyBS->Print();
    DyBS->OpI();
    delete DyBS;
    return 0;
}
