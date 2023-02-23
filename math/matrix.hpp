/*
Matrix
Description: Matrix with expo/pow
Source: Benq
*/
template<class T> struct Mat {
    int r,c; vector<vector<T>> d;
    Mat(int _r, int _c) : r(_r), c(_c) { 
        d.assign(r,vector<T>(c)); }
    Mat() : Mat(0,0) {} 
    Mat(const vector<vector<T>>&_d) : 
        r(sz(_d)), c(sz(_d[0])) { d = _d; }
    Mat& operator+=(const Mat& m) {
        // assert(r == m.r && c == m.c);
        for(int i=0;i<r;i++) for(int j=0;j<c;j++) d[i][j] += m.d[i][j];
        return *this; }
    Mat& operator-=(const Mat& m) {
        // assert(r == m.r && c == m.c);
        for(int i=0;i<r;i++) for(int j=0;j<c;j++) d[i][j] -= m.d[i][j];
        return *this; }
    Mat operator*(const Mat& m) {
        assert(c == m.r); Mat x(r,m.c);
        for(int i=0;i<r;i++) for(int j=0;j<c;j++) for(int k=0;k<m.c;k++) 
            x.d[i][k] += d[i][j]*m.d[j][k];
        return x; }
    Mat operator+(const Mat& m) { return Mat(*this)+=m; }
    Mat operator-(const Mat& m) { return Mat(*this)-=m; }
    Mat& operator*=(const Mat& m) { return *this = (*this)*m; }
    friend Mat pow(Mat m, long long p) {
        assert(m.r == m.c && p >= 0);
        Mat res(m.r,m.c); for(int i=0;i<m.r;i++) res.d[i][i] = 1;
        for (; p; p /= 2, m *= m) if (p&1) res *= m;
        return res;
    }
};