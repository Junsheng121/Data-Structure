#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
class bag01
{
    int dp[1005];
public:
    void exec()
    {
        int N,V,v,w;
        cin>>N>>V;
        for(int i=1;i<=N;i++)
        {
            cin>>v>>w;
            for(int j=V;j>=v;j--)
            {
                dp[j] = max(dp[j-v]+w,dp[j]);
            }
        }
        cout<<dp[V]<<endl;
    }
};

class bagcomplete
{
    int dp[1005];
public:
    void exec()
    {
        for(int i=0;i<1005;i++)
        {
            dp[i]=0;
        }

        int N,V,v,w;
        cin>>N>>V;
        for(int i=1;i<=N;i++)
        {
            cin>>v>>w;
            //int times[1005]={0};
            for(int j=v;j<=V;j++)
            {
                if(dp[j-v]+w > dp[j])
                {
                    dp[j] = dp[j-v]+w;
                    //times[j]=times[j-v]+1;
                }
            }
            //cout<<"Object"<<i<<":"<<times[V]<<endl;
        }
        cout<<dp[V]<<endl;
    }
};

class multibag
{
    int dp[20005];
public:
    void exec()
    {
        for(int i=0;i<20005;i++)
        {
            dp[i]=0;
        }
        int N,V,v,w,n;
        cin>>N>>V;
        for(int i=1;i<=N;i++)
        {
            cin>>v>>w>>n;
            int init;
            for(init=1;init<=n;init*=2)
            {
                for (int j=V;j>=v*init;j--)
                {
                    dp[j] = max(dp[j-v*init]+w*init,dp[j]);
                }
                n -= init;
            }
            for (int j=V;j>=v * n;j--)
            {
                dp[j] = max(dp[j-v*n]+w*n,dp[j]);
            }
        }
        cout<<dp[V]<<endl;

    }
};
class mixedbag
{
    int dp[1005];
public:void exec()
    {
        for(int i=0;i<1005;i++)
        {
            dp[i]=0;
        }
        int N,V,v,w,n;
        cin>>N>>V;
        for(int i=0;i<N;i++)
        {
            cin>>v>>w>>n;
            if(n == -1)
            {
                for(int j=V;j>=v;j--)
                {
                    dp[j]=max(dp[j-v]+w,dp[j]);
                }
            }
            else if(n==0)
            {
                for(int j=v;j<=V;j++)
                {
                    dp[j]=max(dp[j-v]+w,dp[j]);
                }
            }
            else
            {
                int init;
                for(init=1;init<=n;init*=2)
                {
                    for (int j=V;j>=v*init;j--)
                    {
                        dp[j] = max(dp[j-v*init]+w*init,dp[j]);
                    }
                    n -= init;
                }
                for (int j=V;j>=v * n;j--)
                {
                    dp[j] = max(dp[j-v*n]+w*n,dp[j]);
                }
            }

        }
        cout<<dp[V]<<endl;


    }



};

class bag2D
{
    int dp[1005][1005];
public:
    void exec()
    {
        int N,V,M,v,m,w;
        cin>>N>>V>>M;
        for(int i=1;i<=N;i++)
        {
            cin>>v>>m>>w;
            for(int j=V;j>=v;j--)
            {
                for(int k=M;k>=m;k--)
                {
                    dp[j][k] = max(dp[j-v][k-m]+w,dp[j][k]);
                }
            }
        }
        cout<<dp[V][M]<<endl;
    }
};

class groupbag
{
    int dp[1005];
    int groupsize[105];
    vector<int>vs[105];
    vector<int>ws[105];
public:
    void exec()
    {
        memset(dp,0,1005*sizeof(int));
        int N,V,S,v,w;
        cin>>N>>V;
        for(int i=1;i<=N;i++)
        {
            cin>>S;
            groupsize[i]=S;
            for(int j=1;j<=S;j++)
            {
                cin>>v>>w;
                vs[i].push_back(v);
                ws[i].push_back(w);
            }
        }
        for(int i=1;i<=N;i++)
        {

            for(int j=V;j>=0;j--)
            {
                int max=dp[j];
                for(int k=0;k<groupsize[i];k++)
                {
                    if(j>=vs[i][k]&&dp[j-vs[i][k]]+ws[i][k]>max)
                    {
                        max = dp[j-vs[i][k]]+ws[i][k];
                    }

                }
                dp[j] = max;
            }
        }
        cout<<dp[V]<<endl;
    }



};





struct treenode
{
    treenode(int v0,int w0)
    {
        v = v0; w= w0;
        memset(dp,0,1005*sizeof(int));
    }

    int v,w;
    int dp[1005];   //含义：传入该节点多少V，传出对应W
    vector<treenode*> child;

};

class treebag
{
    int N,V,v,w,p;
    int dp[1005][1005];
    int vs[1005];
    int ws[1005];
    vector<int>next[1005];
    int head;
public:
    void dfs(int x)
    {
        for(int i=vs[x];i<=V;i++)
        {
            dp[x][i] = ws[x];
        }                                           //先序初始化
        for(int i=0;i<next[x].size();i++)
        {
            dfs(next[x][i]);
        }
        for(int i=0;i<next[x].size();i++)        //分组背包中的组
        {
            int son = next[x][i];
            for(int j=V;j>=vs[x];j--)         //01体积从大到小
            {
                for(int k=0;k<=j-vs[x];k++)       //体积当然不能全给儿子
                {
                    dp[x][j] = max(dp[x][j], dp[x][j-k]+dp[son][k]);
                }
            }
        }
    }
    void exec()
    {
        memset(dp,0,1005*1005*sizeof(int));
        memset(dp,0,1005*sizeof(int));
        memset(dp,0,1005*sizeof(int));


        cin>>N>>V;
        for(int i=1;i<=N;i++)
        {
            cin>>v>>w>>p;
            vs[i] = v;
            ws[i] = w;
            if(p == -1)
                head = i;
            else
            {
                next[p].push_back(i);
            }
        }
        dfs(head);
        cout<<dp[head][V]<<endl;

    }
};

class dancedp
{
    int dp[8005][2];
    int hs[8005];
    vector<int>next[8005];
    int headnum[8005];
    int head;
public:void dfs(int root)
    {
        dp[root][0] = 0;
        dp[root][1] = hs[root];
        for(int i=0;i<next[root].size();i++)
        {
            dfs(next[root][i]);
        }
        for(int i=0;i<next[root].size();i++)
        {
            int son = next[root][i];
            dp[root][0] += max(dp[son][0],dp[son][1]);
            dp[root][1] += dp[son][0];
        }
    }
    void exec()
    {
        memset(headnum,0,8005*sizeof(int));
        memset(dp,0,8005*2*sizeof(int));
        memset(hs,0,8005*sizeof(int));
        int N,h,a,b;
        cin>>N;
        for(int i=1;i<=N;i++)
        {
            cin>>h;
            hs[i]=h;
        }
        for(int i=1;i<=N-1;i++)
        {
            cin>>a>>b;
            next[b].push_back(a);
            headnum[a]++;
        }
        for(int i=1;i<=N;i++)
        {
            if(headnum[i]==0)
                head=i;
        }
        dfs(head);
        cout<<max(dp[head][0],dp[head][1])<<endl;

    }
};

class dpnum
{
    int N,V,v,w;
    int dp[1005],cnt[1005];
public:void exec()
    {
        memset(dp,0,sizeof(int)*1005);
        for(int i=0;i<=1005;i++)
        {
            cnt[i]=1;
        }
        cin>>N>>V;
        for(int i=1;i<=N;i++)
        {
            cin>>v>>w;
            for(int j=v;j<=V;j++)
            {
                if(dp[j-v]+w>dp[j])
                {
                    dp[j] = dp[j-v]+w;
                    cnt[j] = cnt[j-v];
                }
                else if(dp[j-v]+w ==dp[j])
                {
                    cnt[j] = (cnt[j] + cnt[j-v])%1000000007;
                }
            }
        }
        cout<<cnt[V]<<endl;
    }

};
