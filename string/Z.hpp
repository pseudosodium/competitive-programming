/*
Z-function
Description: Z-function
Time: O(n)
Source: CP Algorithms
*/
vector<int> zfunc(string s){
    int n=sz(s);
    vector<int> z(n);
    int x=0,y=0;
    for(int i=1;i<n;i++){
        z[i]=max(0ll,min(z[i-x],y-i+1));
        while(i+z[i]<n&&s[z[i]]==s[i+z[i]])x=i,y=i+z[i]++;
    }
    return z;
}