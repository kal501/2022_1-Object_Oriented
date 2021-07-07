#include <iostream>
namespace BestComImp1{
    void SimpleFunc(void){
        std::cout<<"BestCom이 정의한 함수"<<std::endl;
    }
}

namespace ProgComImp1{
    void SimpleFunc(void){
        std::cout<<"ProgComImp이 정의한 함수"<<std::endl;
    }
int main(){
    BestComImp1::SimpleFunc();
    ProgComImp1::SimpleFunc();

    return 0;
}