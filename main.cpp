#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

int main(){
    int choice{};
    while(1){
        system("cls");
        cout<<"\
===电脑生产装配销售模拟===\n\
Operations:\n\
1:采购 Select and Purchase\n\
2:工厂 Factories\n\
3:生产 Manufacture\n\
4:装配 Assembly\n\
5:检验 Examine\n\
6:物流 Transportation\n\
7:销售和售后 Sales\n\
0:退出 Exit\n\
[Choose operation]:";
        cin>>choice;
        if(!choice)
            break;
        if(choice<8){
            system("cls");
            system((string{"module\\"}+char(choice+48)+string{".exe"}).c_str());
            getchar();
        }
    }
    return 0;
}