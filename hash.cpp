#include <iostream>
using namespace std;

class Hash{
private:
    static const int SIZE = 10;
    int table[SIZE];
public:
    Hash(){
        for(int i=0;i<SIZE;i++)
            table[i]=-1;
    }
    int hashFunction(int key){
        return key%SIZE;
    }
    void insert(int key){
        int index = hashFunction(key);
        int tmp = index;
        while(table[index]!=-1){
           index = (index+1)%SIZE;
            if(index==tmp){
                cout<<"la tabla esta llena"<<endl;
                return;
            }
        }
        table[index] = key;
    }
    void print(){
        for(int i=0;i<SIZE;i++)
            cout<<i<<" --> "<<table[i]<<endl;
    }


};

int main()
{
    Hash tablitahash;
    tablitahash.insert(15);
    tablitahash.insert(25);
    tablitahash.insert(35);
    tablitahash.insert(45);
    tablitahash.insert(55);
    tablitahash.insert(65);
    tablitahash.print();
    cout<<endl<<endl;
    tablitahash.insert(75);
    tablitahash.insert(85);
    tablitahash.insert(95);
    tablitahash.insert(105);
    tablitahash.insert(115);
    tablitahash.insert(125);
    tablitahash.print();
    return 0;
}
