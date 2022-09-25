#include "big_unsigned.hpp"
#include <iostream>
#include <string>
#include <vector>

BigUnsigned::BigUnsigned(std::string& s){
    digits = "";
    int n = s.size();
    for (int i = n - 1; i >= 0;i--){
        if(isdigit(s[i]))
        	digits.push_back(s[i] - '0');
    }
}

BigUnsigned& BigUnsigned::operator+=(BigUnsigned &a,const BigUnsigned& b){
    int t = 0, s, i;
    int n = Length(a), m = Length(b);
    if(m > n)
        a.digits.append(m - n, 0);
    n = Length(a);
    for (i = 0; i < n;i++){
        if(i < m)
            s = (a.digits[i] + b.digits[i]) + t;
        else
            s = a.digits[i] + t;
        t = s / 10;
        a.digits[i] = (s % 10);
    }
    if(t)
        a.digits.push_back(t);
    return a;
}

BigUnsigned BigUnsigned::operator+(const BigUnsigned &a, const BigUnsigned &b){
    BigUnsigned temp;
    temp = a;
    temp += b;
    return temp;
}

BigUnsigned& BigUnsigned::operator*=(BigUnsigned &a, const BigUnsigned &b)
{
    if(Null(a) || Null(b)){
        a = BigInt();
        return a;
    }
    int n = a.digits.size(), m = b.digits.size();
    vector<int> v(n + m, 0);
    for (int i = 0; i < n;i++)
        for (int j = 0; j < m;j++){
            v[i + j] += (a.digits[i] ) * (b.digits[j]);
        }
    n += m;
    a.digits.resize(v.size());
    for (int s, i = 0, t = 0; i < n; i++)
    {
        s = t + v[i];
        v[i] = s % 10;
        t = s / 10;
        a.digits[i] = v[i] ;
    }
    for (int i = n - 1; i >= 1 && !v[i];i--)
            a.digits.pop_back();
    return a;
}

BigUnsigned BigUnsigned::operator*(const BigUnsigned &a,const BigUnsigned &b){
    BigUnsigned temp;
    temp = a;
    temp *= b;
    return temp;
}

int main(){
	std::string a;
	std::cin>>a;
	std::string b;
	std::cin>>b;
	BigUnsigned aDig(a);
	BigUnsigned bDig(b);
return 0;
}
