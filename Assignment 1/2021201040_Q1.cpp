#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

string add(string a,string b);

string subtract(string a,string b){
    string ires="",res="";
    int j = b.length()-1;
    for(int i=a.length()-1;i>=0;i--){
        int ans = 9 -(j<b.length()?b[j--]-'0':0);
        ires = to_string(ans) + ires;
    }
    ires = add(ires , "1");
    res = add(a,ires);
    res.erase(res.begin());
    return res;
}

string multiply(string a, string b){
    if(a.length() == 0 || b.length() == 0 || a[0]=='0' || b[0]=='0')
        return "0";
    string res="", p="";  
    int c=0;
    if(b.length() == 1){
        for(int i = a.length()-1 ; i>=0 ; i--){
            int ans = (a[i] - '0')*(b[0] - '0') + c;
            c = ans/10;
            ans = ans%10;
            res = to_string(ans) + res;
        }
        if(c>0)
             res = to_string(c) + res;
        return res;
    }  
    for(int i=b.length()-1 ; i>=0 ; i--){
        string s(1, b[i]);
        res = add(res , (multiply(a, s) + p));
        p = p + "0";
    }
    return res;
}

int prec(char c) {
    if(c == 'x')
        return 2;
    else if(c == '+' || c == '-')
        return 1;
    else
        return -1;
}

string add(string a,string b){
    string res="";
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    int carry = 0;
    int i=0,j=0;
    while(i<a.length() || j<b.length() || carry){
        int sum = carry;
        sum = sum + (i<a.length()?a[i++]-'0':0);
        sum = sum + (j<b.length()?b[j++]-'0':0);
        carry = sum/10;
        sum = sum%10;
        res = to_string(sum%10) + res;
    }
    return res;
}


string calc(string a){
    string s[a.length()] , op[a.length()];
    string curr = "";
    int j=-1, k=-1;
    for(int i=0; i<a.length(); i++){
        if(a[i]!= 'x' && a[i]!= '-' && a[i]!= '+')
            curr = curr + to_string(a[i]-'0');
        else{
            s[++j] = curr;
            char ss = a[i];
            while(k>=0){
                if(prec(ss) <= prec(op[k][0]))
                    s[++j] = op[k--];
                else
                    break;
            }
            op[++k] = ss;
            curr = "";
        }
    }
    s[++j] = curr;
    while(k>=0){
        s[++j] = op[k--];
    }
    string res[a.length()];
    k = -1;
    for(int i=0; i<=j; i++){
        if(s[i][0] != 'x' && s[i][0] != '-' && s[i][0] != '+')
            res[++k] = s[i];
        else{
            if(s[i][0] == '+')
                res[k-1] = add(res[k-1], res[k]);
            else if (s[i][0] == '-')
                res[k-1] = subtract(res[k-1], res[k]);
            else if (s[i][0] == 'x')
                res[k-1] = multiply(res[k-1], res[k]);
            k = k-1;
        }
    }
    return res[0];
}

string exponent(string b,unsigned long long int p){
    string res= "1", val = b;
    while(p > 0){
        if((p&1) == 1)
            res = multiply(res,val);
        val = multiply(val, val);
        p = p>>1;
    }
    return res;
}


bool isSmaller(string str1, string str2)
{
    int n1 = str1.length(), n2 = str2.length();
    if (n1 < n2)
        return true;
    if (n2 < n1)
        return false;
    for (int i = 0; i < n1; i++)
        if (str1[i] < str2[i])
            return true;
        else if (str1[i] > str2[i])
            return false;
 
    return false;
}
string div(string a,int b){
    string res="";
    int k=0,c=0;
    bool flag=true;
    for(int i=0;i<a.length();i++){
        
        k=(c*10+(a[i]-'0'))/2;
        c=(a[i]-'0')%2;
        
        if(k!=0 || flag==false)
        {res+=to_string(k);
         flag=false;}
        //cout<<res;
        
    }
    return res;
}
bool comp(string a,string b){
    if(a.length()!=b.length())
        return false;
    for(int i=0;i<a.length();i++){
        if(a[i]!=b[i]){
            return false;
        }
    }return true;
}
string gcd(string a, string b)
{
    //cout<<a<<" "<<b<<"\n";
    if(comp(a,b)==true){
        return a;
    }
    if (a.length()==1 && a[0] == '0')
        return b;
    if (b.length()==1 && b[0] == '0')
        return a;
 
    if ((a[a.length()-1]-'0')%2==0)
    {//cout<<"a is even";
        if ((b[b.length()-1]-'0')%2==1) 
            return gcd(div(a,2), b);
        else
        {//cout<<"B is even";
         string m=div(a,2);
         string n=div(b,2);
         //cout<<m<<n;
            string res=gcd(m,n);
            return multiply(res,"2");
        }
    }
    if ((b[b.length()-1]-'0')%2==0) 
        return gcd(a, div(b,2));
    if (isSmaller(b,a))
        return gcd(div(subtract(a,b),2), b);
    return gcd(div(subtract(b,a),2), a);
}
 

string factorial(int a){
    string res="1";
    for(int i=2; i<=a ; i++){
        res = multiply(res ,to_string(i));
    }
    return res;
}


int main(){
    //cout<<div("23423432",2)<<" ";
    string a,b,c;
    int f;
    unsigned long long int exp;
    int tof;
    cin >> tof;

    if(tof==1){
        cin >> a >> exp;
        cout << exponent(a,exp) << "\n";
    }
    else if(tof==2){
        cin >> a >> b;
        cout<<gcd(a,b)<<"\n";
    }
    else if(tof==3){
        cin >> f;
        cout << factorial(f) << "\n";
    }
    else{
        cin >> a;
        cout << calc(a) <<"\n";
    }
}
