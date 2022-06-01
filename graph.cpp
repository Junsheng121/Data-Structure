#include "util.h"
/*Map*/
struct mapnode
{
    int num;
    int data;

    vector<mapnode*> beside;
    mapnode(int n,int d){
        num=n;
        data=d;

    }
};
class mymap         //无向图
{
public:
    int totalnode=0;
    bool visited[100];
    map<int,int>mapping;    //from data to num
    mapnode* allnodes[100]; //from num to address
    int matrix[100][100];   //num的邻接矩阵
    void linknode(int,int,int);
    void displaymap_dfs();
    void displaymap_bfs();
    void displaymatrix();
    mymap()
    {
        for(int i=0;i<100;i++)
        {
            for (int j=0;j<100;j++)
            {
                matrix[i][j]=65535;
            }
        }
    }

};
void mymap::linknode(int a, int b, int weight){
    if(mapping.find(a)==mapping.end())
    {
        allnodes[totalnode]=new mapnode(totalnode,a);
        mapping[a]=totalnode;
        totalnode++;
    }
    if(mapping.find(b)==mapping.end())
    {
        allnodes[totalnode]=new mapnode(totalnode,b);
        mapping[b]=totalnode;
        totalnode++;
    }
    allnodes[mapping[b]]->beside.push_back(allnodes[mapping[a]]);
    allnodes[mapping[a]]->beside.push_back(allnodes[mapping[b]]);
    matrix[mapping[b]][mapping[a]]=weight;
    matrix[mapping[a]][mapping[b]]=weight;
}      //data a attach to data b
void mymap::displaymap_bfs() {
    for(int i=0;i<100;i++)
        visited[i]=0;
    if(totalnode==0)
    {
        cout<<"empty map"<<endl;
        return;;
    }
    mapnode* startptr=allnodes[0];
    queue<mapnode*>mapnodes;
    mapnodes.push(startptr);
    while(!mapnodes.empty())
    {
        mapnode* head=mapnodes.front();
        cout<<"nodenum:"<<head->num<<" data:"<<head->data<<endl;
        mapnodes.pop();
        visited[head->num]=1;
        for(int i=0;i<head->beside.size();i++)
        {
            if(visited[head->beside[i]->num]==0)
                mapnodes.push(head->beside[i]);
        }
    }
}
void mymap::displaymatrix() {
    cout<<"\t";
    for(int i=0;i<totalnode;i++)
    {
        cout<<setw(5)<<allnodes[i]->data<<"\t";
    }
    cout<<endl;
    for(int i=0;i<totalnode;i++)
    {
        cout<<allnodes[i]->data<<"\t";
        for(int j=0;j<totalnode;j++)
        {
            cout<<setw(5)<<matrix[i][j]<<"\t";
        }
        cout<<endl;
    }


}




