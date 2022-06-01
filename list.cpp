#include "util.h"
using namespace std;
/*list*/
struct listnode{
    int data;
    listnode* nextnode;
    listnode(int d, listnode* ptr)
    {
        data = d;
        nextnode = ptr;
    }
};
class list{
    listnode* startnode;
    int len;
public:
    void insertnode(int num,int pos);
    void deletenode(int num);
    void shownode();
    void findnode(int num);
    list(){startnode=NULL;len=0;}
};
void list::insertnode(int num,int pos=-1)
{
    if(pos>len)
    {
        cout<<"exceed len"<<endl;
        return;
    }
    listnode* newptr = new listnode(num,NULL);
    if(startnode==0)
    {
        startnode = newptr;
        len++;
        return;
    }
    listnode *curptr = startnode;
    listnode* lastptr = NULL;
    if(pos==0)
    {
        newptr->nextnode=startnode;
        startnode=newptr;
        return;
    }
    else if(pos==-1)
    {
        while (curptr != 0)
        {
            lastptr = curptr;
            curptr = curptr->nextnode;
        }
        lastptr->nextnode = newptr;
        len++;
        return;
    }

    else
    {
        while(pos--)
        {
            lastptr = curptr;
            curptr = curptr->nextnode;
        }
        lastptr->nextnode = newptr;
        newptr->nextnode = curptr;
        len++;
    }



}
void list::deletenode(int pos)
{
    listnode* tempptr=0;
    listnode* curptr;
    listnode* lastptr=0;
    if(startnode==0)
    {
        cout<<"empty list"<<endl;
        return;
    }
    if(pos>len)
    {
        cout<<"exceed len"<<endl;
        return;
    }
    if(pos==0)
    {
        tempptr = startnode;
        startnode=startnode->nextnode;
        delete tempptr;
        len--;
        return;
    }
    curptr=startnode;
    while(pos--)
    {
        lastptr=curptr;
        curptr=curptr->nextnode;
    }
    tempptr=curptr;
    lastptr->nextnode=curptr->nextnode;
    delete curptr;
    len--;


}
void list::findnode(int num)
{
    int pos=0;
    listnode* curptr= startnode;
    if(len==0)
    {
        cout<<"empty list"<<endl;
    }
    while(curptr)
    {
        if(curptr->data!=num)
        {
            curptr = curptr->nextnode;
            pos++;
        }
        else
        {
            cout<<pos<<endl;
        }

    }

}
void list::shownode()
{
    listnode* curptr= startnode;
    if(len==0)
    {
        cout<<"empty list"<<endl;
    }
    while(curptr)
    {
        cout<<curptr->data<<" ";
        curptr=curptr->nextnode;
    }
    cout<<endl;
}