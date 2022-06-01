#include <iostream>
#include <vector>
using namespace std;
class merge_sort
{
public:
    void sort(int s[],int begin,int end)
    {
        if(begin>=end)
        {
            return;
        }
        sort(s,begin,(end+begin)/2);
        sort(s,(end+begin)/2+1,end);
        vector<int>combine;
        int cur1 = begin;
        int cur2 = (end+begin)/2+1;
        while(cur1<=(end+begin)/2&&cur2<=end)
        {
            if(s[cur1]<s[cur2])
            {
                combine.push_back(s[cur1]);
                cur1++;
            }
            else
            {
                combine.push_back(s[cur2]);
                cur2++;
            }
        }
        while(cur1>(end+begin)/2&&cur2<=end)
        {
            combine.push_back(s[cur2]);
            cur2++;
        }
        while(cur1<=(end+begin)/2&&cur2>end)
        {
            combine.push_back(s[cur1]);
            cur1++;
        }
        for(int i=begin,j=0;i<=end&&j<combine.size();i++,j++)
        {
            s[i] = combine[j];
        }


    }
    void exec()
    {
        int s[10]= {1,7,3,4,9,2,6,8,5,5};
        sort(s,0,9);
        for(int i=0;i<10;i++)
        {
            cout<<s[i]<<endl;
        }
    }
};
