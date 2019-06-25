//  AOA2 - PROJECT2 - 21.04.2019
//  Huma Kalayci
#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <sstream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <fstream>
using namespace std;

class binaryNumbers{
 public:
    string binNum;
    
    //Default Constructor
    binaryNumbers(){
        //cout << "Default Constructor called" << endl;
        binNum = "0";
    }

    //Parametrized Constructor which generates random binary numbers in order to given size
    binaryNumbers(int x){
        //cout << "Parametrized Constructor called" << endl;
        binNum = "1";
        for(int i=1; i<x; i++){
            int randNum = rand() % 2 ;
            char r1 = randNum +'0';
            binNum += r1;
        }
    }
};



string addBinary(string a, string b){
    string result = "";
    int s = 0;
    long int i = a.size() - 1;
    long int j = b.size() - 1;
    while (i >= 0 || j >= 0 || s == 1){
        s = s + ((i >= 0)? a[i] - '0': 0);
        s = s + ((j >= 0)? b[j] - '0': 0);
        result = char(s % 2 + '0') + result;
        s /= 2;
        i--; j--;
    }
    return result;
}


//CLASSICAL MULTIPLYING OF TWO BINARY NUMBERS BY SHIFTING AND ADDING
string classicalMultiply(string x, string y){
    string result;
    string results[y.size()];
    if(x == "0" || y=="0")
        return "0";
    for(long int i = y.size()-1; i >=0 ; i--){
        if(y[i]=='1')
            results[i] = x;
        else{
            for(long int j= 0; j<x.size(); j++)
                results[i] += '0';
        }
        for(long int j = i ;  j<  y.size()-1 ; j++ )
            results[i] += '0';
        //cout<<y[i]<<"   -> "<< results[i]<<endl;
    }
    string before = results[y.size()-1];
    for(long int i = y.size()-1; i >0 ; i--)
        before = addBinary(before, results[i-1]);
//    cout<<before<<endl;
    return before;
}



string product2(string str1, string str2){
    //cout<<"product2";
    if(str1 == "0" || str2=="0")
        return "0";
    int a[1000],b[1000];
    int ans[2000]={0};
    int i,j,tmp;
    char s1[1001],s2[1001];
    strcpy(s1 ,str1.c_str());
    strcpy(s2 ,str2.c_str());
    int l1 = strlen(s1);
    int l2 = strlen(s2);
    for(i = l1-1,j=0;i>=0;i--,j++)
        a[j] = s1[i]-'0';
    for(i = l2-1,j=0;i>=0;i--,j++)
        b[j] = s2[i]-'0';
    for(i = 0;i < l2;i++){
        for(j = 0;j < l1;j++)
            ans[i+j] += b[i]*a[j];
    }
    for(i = 0;i < l1+l2;i++){
        tmp = ans[i]/10;
        ans[i] = ans[i]%10;
        ans[i+1] = ans[i+1] + tmp;
    }
    for(i = l1+l2; i>= 0;i--){
        if(ans[i] > 0)
            break;
    }
    stringstream ret;
    

    for(;i >= 0;i--){
        
        ret<< ans[i];
    }

    return ret.str();
}

// Function for find difference of larger numbers
string findDiffof(string str1, string str2){
    string str = "";
    unsigned long int n1 = str1.length(), n2 = str2.length();
    reverse(str1.begin(), str1.end());
    reverse(str2.begin(), str2.end());
    int carry = 0;
    for (int i=0; i<n2; i++){
        int sub = ((str1[i]-'0')-(str2[i]-'0')-carry);
        if (sub < 0){
            sub = sub + 10;
            carry = 1;
        }
        else
            carry = 0;
        str.push_back(sub + '0');
    }
    for (int i=n2; i<n1; i++){
        int sub = ((str1[i]-'0') - carry);
        if (sub < 0){
            sub = sub + 10;
            carry = 1;
        }
        else
            carry = 0;
        
        str.push_back(sub + '0');
    }
    reverse(str.begin(), str.end());
    return str;
}



string findSumof(string str1, string str2){
    if (str1.length() > str2.length())
        swap(str1, str2);
    string str = "";
    int n1 = str1.length(), n2 = str2.length();
    reverse(str1.begin(), str1.end());
    reverse(str2.begin(), str2.end());
    
    int carry = 0;
    for (int i=0; i<n1; i++){
        int sum = ((str1[i]-'0')+(str2[i]-'0')+carry);
        str.push_back(sum%10 + '0');
        carry = sum/10;
    }
    for (int i=n1; i<n2; i++){
        int sum = ((str2[i]-'0')+carry);
        str.push_back(sum%10 + '0');
        carry = sum/10;
    }
    if (carry)
        str.push_back(carry+'0');
    reverse(str.begin(), str.end());
    return str;
}



string power(string s1, string s2){
    if (s2 != "0")
        return (product2(s1, power(s1, to_string(atoi(s2.c_str())-1)))   );
    else
        return "1";
}


string binToDec(string x){
    string decx ;
    long int j = 0;
    for(long int i = x.length()-1; i >= 0 ; i--){
        string xi(1,x[i]);
        decx = findSumof(decx, product2( xi , power("2", to_string( j)) ));
        j++;
    }
    return decx;
}



//GIVEN METHOD MULTIPLYING OF TWO BINARY NUMBERS
string multiplyA1(string x, string y){
    long double n = max(x.length(), y.length());
    long int m = (n/2);      //also keeping the half of the n for correct ceiling
    long int t = (n-m);
    //case for if their lengths are not equal, it basically adds a zero yoi the beginning of the string
    if(x.length() > y.length()){
        string reversed(y.rbegin(), y.rend());
        reversed += '0';
        string reversedy(reversed.rbegin(), reversed.rend());
        y = reversedy;
    }
    if(x.length() < y.length()){
        string reversed(x.rbegin(), x.rend());
        reversed += '0';
        string reversedx(reversed.rbegin(), reversed.rend());
        x = reversedx;
    }
    //case for if their length is equal to zero
    if(n == 0) return 0;
    //case to return their product if their size is 1, below operation turns them to a integer
    int xi = x[0] - '0';
    int yi = y[0] - '0';
    if(n == 1)  return to_string(xi * yi);
    
    string xL = x.substr(0, m);
    string xR = x.substr(m, t);
    string yL = y.substr(0, m);
    string yR = y.substr(m, t);
    
    string P1 = multiplyA1(xL, yL);
    string P2 = multiplyA1(xR, yR);
    string P3 = multiplyA1(addBinary(xL, xR), addBinary(yL,yR));

    string pw=power("2", to_string(2*t));
    //cout<<"im here0.5";
    string x1 = product2(P1,pw);
     //cout<<"im here1";
    string x2 = product2(findDiffof(findDiffof(P3, P1),P2),power("2", to_string(t)));
    // cout<<"im here2";
    string x3 = findSumof(x1, x2);
    // cout<<"im here3";
    string x4 = findSumof(x3, P2);
    //cout<<"im here4";
    
    string result = x4;
    //result= findSum(findSum(product2(P1,power("2", to_string(2*t))),product2(findDiff(findDiff(P3, P1),P2),power("2", to_string(t)))), P2)      ;
    P1.clear();
    P2.clear();
    P3.clear();
    return result;
}





int main( int argc, char** argv ){
    //cout<<argv[1]<<endl;
    ofstream myfile;
    myfile.open (argv[1]);
    //myfile << "Writing this to a file.\n";
    
    int sizes[10] = {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};
    srand (time(NULL));
    //int randSize = rand() % 6 ;
    //cout<<randNum<<endl<<sizes[randNum]<<endl;
    float resultsClassical[10];
    float resultsMultiplyA1[10];
    
    for(int i= 0; i<10; i++){
        //cout<<"SIZE: "<<sizes[i]<<endl;
        myfile<<"SIZE: "<<sizes[i]<<endl;
        binaryNumbers x(sizes[i]);
        srand (time(NULL));
        binaryNumbers y(sizes[i]);
        myfile<<"NUMBER 1: "<<x.binNum<<endl<<"NUMBER 2: "<<y.binNum<<endl;
        
        //Random binary numbers have generated.
        
        //Classical Multiplying
        clock_t t;
        t = clock();
        myfile<<"NUMBER1*NUMBER2:"<<endl;
        myfile<<" Classical Method: "<<binToDec(classicalMultiply( x.binNum, y.binNum))<<endl;
        t = clock() - t;
        myfile<<"   It took me " <<((float)t)/(CLOCKS_PER_SEC/1000)<<" milliseconds.\n\n";
        resultsClassical[i] = ((float)t)/CLOCKS_PER_SEC;
        
        //Multiply function given in Algorithm 1
        clock_t p;
        p = clock();
        myfile<<" Given Method: "<<multiplyA1( x.binNum, y.binNum)<<endl;
        p = clock() - p;
        myfile<<"   It took me " <<((float)p)/(CLOCKS_PER_SEC/1000)<<" milliseconds.\n\n";
        resultsMultiplyA1[i] = ((float)p)/CLOCKS_PER_SEC;
    }
    
    myfile.close();
    return 0;
}



