#include <iostream>
namespace BestComImp1{
    void SimpleFunc(void);
}
namespace BestComImp1{
    void PrettyFunc(void);
}
namespace ProgComImp1{
    void SimpleFunc(void);
}  
int main(){
    BestComImp1::SimpleFunc();
    

    return 0;
}

void BestComImp1::SimpleFunc(){
    std::cout<<"BestCom이 정의한 함수" << std::endl;
    PrettyFunc();
    ProgComImp1::SimpleFunc();
}
void BestComImp1::PrettyFunc(){
    std::cout<< "So Pretty!!"<<std::endl;
}
void ProgComImp1::SimpleFunc(){
    std::cout<<"ProgComImp1이 정의한 함수" << std::endl;
}