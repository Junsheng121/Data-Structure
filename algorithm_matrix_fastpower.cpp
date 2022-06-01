#include <iostream>
using namespace std;
const int big = 1e9;
class Matrix
{
public:
    Matrix(int m,int n)
    {
        m0 = m;
        n0 = n;
        data=new double*[m];
        for(int i=0;i<m;i++)
        {
            data[i]=new double[n];
        }
        for(int i=0;i<m;i++)
            for(int j=0;j<n;j++)
                data[i][j]=0;
    }
    double** data;
    int m0,n0;
    static Matrix mm(Matrix& a,Matrix& b)
    {
        assert(a.n0 == b.m0);
        Matrix res(a.m0,b.n0);
        for(int i=0;i<a.m0;i++)
            for(int j=0;j<b.n0;j++)
            {
                double ans = 0;
                for(int p=0;p<a.n0;p++)
                {
                    ans += a.data[i][p] * b.data[p][j];
                }
                res.data[i][j] = ans;
            }
        return res;
    }
    static Matrix fastmatmm(Matrix&a, int b)
    {
        assert(a.m0==a.n0);
        Matrix res(a.m0,a.n0);
        for(int i=0;i<res.m0;i++)
            res.data[i][i]=1;

        while(b>0)
        {
            if(b%2==1)
            {
                res = mm(res,a);
                b--;
            }
            else
            {
                a = (mm(a,a));
                b = b/2;
            }
        }
        return res;

    }

};

class fastmm
{
public:
    void exec()
    {
        long long ans=1;
        long long a,b; //a^b:    a^b % big = ((a%big)^2) ^ b/2   ||  (a%big)*a)^(b-1)
        cin>>a>>b;
        while(b>0)
        {
            if(b%2==1)
            {
                ans = (ans * a)%big;
                b--;
            }
            else
            {
                a = (a*a)%big;
                b=b/2;
            }
        }
        cout<<ans<<endl;


    }
};
class phi
{
public:
    void exec()
    {
        int n;
        cin >> n;
        if (n == 1 || n == 2) {
            cout << 1 << endl;
            return;
        }
        Matrix init(2, 2);
        Matrix base(2, 2);
        init.data[0][0] = 2;
        init.data[0][1] = init.data[1][0] = init.data[1][1] = 1;
        base.data[0][0] = base.data[0][1] = base.data[1][0] = 1;
        base.data[1][1] = 0;


        Matrix res1 = Matrix::fastmatmm(base, n - 3);
        Matrix res2 = Matrix::mm(res1, init);
        cout << res2.data[0][0] << endl;


    }

};



