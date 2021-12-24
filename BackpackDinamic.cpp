#include <iostream>
#include <cstdlib>
#include <cmath>
#include "ClassSeq.h"
#include <ctime>
#include <iomanip>
#include <chrono>
using namespace std;
class Item
{
private:
    int weight,
        price,
        index;
public:
    Item()
    {
       weight = 0;
       price = 0;
    }
    Item(int weight, int price, int index)
    {
       this -> weight = weight;
       this -> price = price;
       this -> index = index;
    }

    int getWeight()
    {
       return weight;
    }

    int getPrice()
    {
       return price;
    }

    int getIndex()
    {
       return index;
    }

    void Print()
    {
    cout <<"Index:  "<< index<<"  Weight  "<<weight<<"  Price:  "<<price<<endl;
    }
};

int BestSet(Item* items, int NumItems, int maxW, CLinkedList<Item>* Best)
{
    int table[NumItems+1][maxW+1];
    for (int i = 0 ; i<= maxW ; i++)
    {
          table[0][i] = 0;
    }

    for (int i = 0 ; i<= NumItems ; i++)
    {
          table[i][0] = 0;
    }                                              //Первые элементы приравниваем к 0
    for (int k = 1 ; k <= NumItems; k++)
    {
        for (int s = 1 ; s <= maxW; s++)
        {                                            //Перебираем для каждого k все вместимости
            if (s >= items[k-1].getWeight())           //Если текущий предмет вмещается в рюкзак
            {
                table[k][s] = max(table[k - 1][s], table[k - 1][s - items[k-1].getWeight()] + items[k-1].getPrice()); //Выбираем класть его или нет
            }
            else
            {
                table[k][s] = table[k - 1][s]; //Иначе, не кладем
            }
        }
    }

    for (int k = 0 ; k <= NumItems; k++)
    {
        for (int s = 0 ; s <= maxW; s++)
        {
            cout<< setw(4) <<table[k][s];
        }
        cout <<endl;
    }
    cout <<"-------------"<<endl;
    int k = NumItems;
    int s = maxW;
    int testP = 0, testW = 0;
    while (table[k][s] != 0)
    {
        if (table[k - 1][s] == table[k][s])
        {
            k--;
        }
        else
        {
            Best -> Append(items[k-1]);
            testP = testP + items[k-1].getPrice();
            testW = testW + items[k-1].getWeight();
            s = s - items[k-1].getWeight();
            k--;
        }
    }
    if (testP == table[NumItems][maxW] && testW <= maxW)
        cout<<"Test - OK"<< endl;
    else
        cout<<"Test - NO OK"<< endl;
    cout <<"-------------"<<endl;
    Best -> Print();
    return  table[NumItems][maxW];
}

int main()
{
//srand(time(NULL));
CLinkedList<Item> Best;
int Ans;
int N = 15;
int  W = 10;
cin>> N;
cin>> W;
Item AllItems[N];
//cout<<"number of items"<<endl;
//cin>>N;
//cout<<"maximum weight"<<endl;
//cin>>W;
for (int i = 0; i < N; i++)
{
    Item I(rand() % 9 + 1, rand() % 9 + 1, i+1);
    I.Print();
    AllItems[i] = I;

}
cout <<"-------------"<<endl;
auto begin = std::chrono::steady_clock::now();
Ans =  BestSet(AllItems, N, W, &Best);
auto end = std::chrono::steady_clock::now();
auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
int seconds = elapsed_ms.count();
cout <<"-------------"<<endl;
cout <<"MaxPrice: "<< Ans <<endl;
cout <<"The time: "<< seconds<<" milliseconds" <<endl;

return 0;
}
