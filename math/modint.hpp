/*
ModInt
Description: Datatype to perform operations under MOD
Time: O(1)?
Source: Benq + my tweaks
*/

template<int _md> struct ModInt {
    const static int md = _md;
    int v; explicit operator int() const { return v; }
    ModInt():v(0){}
    ModInt(int _v){v=_v%md,v=(v+md)%md;}
    int raw() { return v; }
    bool operator==(const ModInt& o) const { return v==o.v; }
    friend bool operator!=(const ModInt& a,const ModInt& b){ return !(a==b); }
    friend bool operator<(const ModInt& a,const ModInt& b){ return a.v<b.v; }
    ModInt& operator+=(const ModInt& o){ v=(v+o.v)%md; return *this; }
    ModInt& operator-=(const ModInt& o){ v=(v-o.v)%md; v=(v+md)%md; return *this; }
    ModInt& operator*=(const ModInt& o){ v=(v*o.v)%md; return *this; }
    ModInt& operator/=(const ModInt& o){ return (*this)*=inv(o); }
    friend ModInt pow(ModInt a,int p){ ModInt ans=1; assert(p>=0); for(;p;p/=2,a*=a)if(p&1)ans*=a; return ans; }
    friend ModInt inv(const ModInt& a){ assert(a.v!=0); return pow(a,md-2); }
    ModInt operator-() const { return ModInt(-v); }
    ModInt& operator++() { return *this+=1; }
    ModInt& operator--() { return *this-=1; }
    friend ModInt operator+(ModInt a,const ModInt& b){ return a+=b; }
    friend ModInt operator-(ModInt a,const ModInt& b){ return a-=b; }
    friend ModInt operator*(ModInt a,const ModInt& b){ return a*=b; }
    friend ModInt operator/(ModInt a,const ModInt& b){ return a/=b; }
    friend istream& operator >> (istream& in, ModInt& o) { cin>>o.v; return in; }
    friend ostream& operator << (ostream& os, ModInt& o) { cout<<o.v; return os; }
};

using mint=ModInt<mod>;