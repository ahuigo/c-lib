class myclass{
public:
    myclass(int i,int j, std::string k){
        a=i;
        b=j;

    }
private:
    std::string s{"Constructor run"};

    int a = 0;
    int b = 0;
};
int main(){
//myclass mc(1,2);     // warning C4930: prototyped function not called (was a variable definition intended?)
myclass a = myclass(1,2);
}

