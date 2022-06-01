#include "util.h"
/*tree*/
struct treenode {
    int data;
    int height;
    int tag;   //only for right_order
    int isred;
    int doublered;        //Only used in Red_Black Tree
    int childdirection;        //Only used in LR/RL_RB_rotate
    treenode *leftchild;
    treenode *rightchild;

    treenode(int d)
    {
        tag=0;
        data=d;
        height=1;
        leftchild=0;
        rightchild=0;
        childdirection=0;
        isred=0;
        doublered=0;
    }
    int get_height()
    {
        return height;
    }

};
class tree{
public:
    treenode* rootnode;

    /*Basic Function*/
    void insertnode(int num);   //非递归插入
    void deletenode(int num);   //非递归删除
    void left_order();
    void mid_order();
    void right_order();
    int get_height();
    treenode* findnode(int num,treenode*&,int&);
    tree(){rootnode=NULL;}

    /*AVL Function*/
    treenode* minimum(treenode*);//找到某节点的最左值，提取后直接变成被删除的节点（用于左右子树均存在）
    treenode* balance_insertnode(treenode* node, int num);  //递归
    treenode* balance_deletenode(treenode* node, int num);  //递归
    int get_balanceFact(treenode* node);
    treenode* left_rot(treenode* node);
    treenode* right_rot(treenode* node);

    /* Red_Black Function */
    treenode* redblack_insertnode(treenode* node, treenode* fathernode, int num);
    treenode* redblack_deletenode(treenode* node ,int num);
    treenode* RB_left_rot(treenode*);
    treenode* RB_right_rot(treenode*);
};
/*Basic Function*/
void tree::insertnode(int num)
{
    treenode* newptr = new treenode(num);
    if(rootnode==0)
    {
        rootnode=newptr;
        return;
    }
    treenode* curptr= rootnode;
    treenode* lastptr = NULL;
    int direction=1;
    while(curptr)
    {
        if (curptr->data > num)
        {
            lastptr=curptr;
            curptr=curptr->leftchild;
            direction=1;
        }
        else if(curptr->data<=num)
        {
            lastptr=curptr;
            curptr=curptr->rightchild;
            direction=2;
        }
    }
    if(direction==1)
        lastptr->leftchild=newptr;
    else
        lastptr->rightchild=newptr;
    get_height();
}
treenode* tree::findnode(int num, treenode*& fathernode, int& direction)
{
    if(rootnode==NULL) {
        cout << "empty tree" << endl;
        return NULL;
    }
    treenode* curptr= rootnode;
    treenode* lastptr= NULL;
    while(curptr&&curptr->data!=num)
    {
        if(curptr->data>num)
        {
            lastptr = curptr;
            direction = 1;
            curptr=curptr->leftchild;
        }
        else if(curptr->data<num)
        {
            lastptr = curptr;
            direction = 2;
            curptr=curptr->rightchild;
        }
    }
    if(curptr==NULL)
    {
        cout<<"Not Found!"<<endl;
        return NULL;
    }
    else
    {
        cout<<"Found!"<<endl;
        fathernode = lastptr;
        return curptr;
    }


}
void firstdfs(treenode* rootnode)
{
    if(rootnode==0)
    {
        cout<<"empty!"<<endl;
        return;
    }
    stack<treenode*> explorednodes;
    treenode* curptr = rootnode;
    while(curptr||!explorednodes.empty())
    {
        while(curptr)
        {
            cout<<curptr->data;
            explorednodes.push(curptr);
            curptr = curptr->leftchild;
        }
        curptr = explorednodes.top();
        explorednodes.pop();
        curptr = curptr->rightchild;
    }
    cout<<endl;
}
void tree::mid_order()
{
    if(rootnode==0)
    {
        cout<<"empty tree"<<endl;
        return;
    }
    stack<treenode*>explorednodes;
    treenode* curptr=rootnode;
    while(curptr||!explorednodes.empty())
    {
        while (curptr)
        {
            explorednodes.push(curptr);
            curptr = curptr->leftchild;
        }
        curptr = explorednodes.top();
        explorednodes.pop();
        cout << curptr->data << " ";
        curptr = curptr->rightchild;

    }
    cout<<endl;
}
void tree::right_order()
{
    if(rootnode==0)
    {
        cout<<"empty tree"<<endl;
        return;
    }
    stack<treenode*>explorednodes;
    treenode* curptr=rootnode;
    while(curptr||!explorednodes.empty())
    {
        while(curptr)
        {
            explorednodes.push(curptr);
            curptr->tag=0;
            curptr=curptr->leftchild;
        }
        curptr=explorednodes.top();
        explorednodes.pop();
        if(curptr->tag==0)
        {
            explorednodes.push(curptr);
            curptr->tag=1;
            curptr=curptr->rightchild;
        }
        else
        {
            cout<<curptr->data<<" ";
            curptr=0;
        }
    }
    cout<<endl;


}
int tree::get_height()
{
    return rootnode->get_height();
}
void tree::deletenode(int num)
{

    int direction = 0;
    treenode *fatherptr = NULL;
    treenode *curptr = findnode(num, fatherptr, direction);
    if(curptr==NULL)
    {
        cout<<"not found!"<<endl;
        return;
    }
    if(curptr->leftchild==NULL && curptr->rightchild==NULL)
    {
        if(fatherptr==NULL)
        {
            rootnode=NULL;
            return;
        }
        if(direction==1)

            fatherptr->leftchild=NULL;
        else if(direction==2)
            fatherptr->rightchild=NULL;
        delete curptr;
    }
    else if(curptr->leftchild && curptr->rightchild==NULL)
    {
        if(fatherptr==NULL)
        {
            rootnode=curptr->leftchild;
            return;
        }
        if(direction==1)
        {
            fatherptr->leftchild = curptr->leftchild;
            delete curptr;
        }
        else if(direction==2)
        {
            fatherptr->rightchild = curptr->leftchild;
            delete curptr;
        }

    }
    else if(curptr->leftchild==NULL && curptr->rightchild)
    {
        if(fatherptr==NULL)
        {
            rootnode=curptr->rightchild;
            return;
        }
        if(direction==1)
        {
            fatherptr->leftchild = curptr->rightchild;
            delete curptr;
        }
        else if(direction==2)
        {
            fatherptr->rightchild = curptr->rightchild;
            delete curptr;
        }
    }
    else
    {

        treenode* lastptr,*tempptr;
        tempptr = curptr->rightchild;
        while(tempptr->leftchild)
        {
            lastptr = tempptr;
            tempptr=tempptr->leftchild;
        }
        if(tempptr==curptr->rightchild)
        {
            curptr->data= tempptr->data;
            curptr->rightchild=tempptr->rightchild;
            delete tempptr;
        }
        else
        {
            curptr->data= tempptr->data;
            curptr->rightchild->leftchild=tempptr->rightchild;
            delete tempptr;
        }
    }

}
/*AVL Function*//*Learned from https://blog.csdn.net/qq_25343557/article/details/89110319 */
int tree::get_balanceFact(treenode *node)
{
    return (node->leftchild?node->leftchild->get_height():0) - (node->rightchild?node->rightchild->get_height():0);
}
treenode* tree::balance_insertnode(treenode* node,int num)
{
    treenode* newptr=0;
    if(node==0)
    {
        newptr = new treenode(num);
        node=newptr;
        return node;
    }
    if(node->data>num)
        node->leftchild=balance_insertnode(node->leftchild,num);
    else if(node->data<=num)
        node->rightchild=balance_insertnode(node->rightchild,num);
    node->height=1+max(node->leftchild?node->leftchild->get_height():0,node->rightchild?node->rightchild->get_height():0);
    int balanceFact = get_balanceFact(node);
    if(balanceFact>1 && get_balanceFact(node->leftchild)>0)
    {
        node=right_rot(node);
    }
    else if(balanceFact>1 && get_balanceFact(node->leftchild)<0)
    {
        node->leftchild=left_rot(node->leftchild);
        node=right_rot(node);
    }
    else if(balanceFact<-1 && get_balanceFact(node->rightchild)<0)
    {
        node=left_rot(node);
    }
    else if(balanceFact<-1 && get_balanceFact(node->rightchild)>0)
    {
        node->rightchild=right_rot(node->rightchild);
        node=left_rot(node);
    }
    return node;



}
treenode* tree::minimum(treenode*node)
{
    treenode* curptr= node;
    if(node==NULL)
        return NULL;
    while(curptr->leftchild)
    {
        curptr=curptr->leftchild;
    }
    return curptr;
}
treenode* tree::balance_deletenode(treenode* node,int num){
    treenode* retnode;
    if(node==0)
    {
        cout<<"Not Found"<<endl;
        return NULL;
    }
    if(node->data>num) {
        node->leftchild = balance_deletenode(node->leftchild, num);
        retnode = node;
    }
    else if(node->data<num)
    {
        node->rightchild = balance_deletenode(node->rightchild, num);
        retnode = node;
    }
    else
    {
        if (node->leftchild == NULL && node->rightchild == NULL) {
            retnode = NULL;
        }
        else if (node->leftchild == NULL && node->rightchild) {
            treenode *rightnode = node->rightchild;
            retnode = rightnode;
        }
        else if (node->leftchild && node->rightchild == NULL) {
            treenode *leftnode = node->leftchild;
            retnode = leftnode;
        }
        else {
            treenode *successor = minimum(node->rightchild);
            successor->rightchild = balance_deletenode(node->rightchild, successor->data);
            successor->leftchild = node->leftchild;

            node->leftchild = node->rightchild = NULL;
            retnode = successor;

        }
    }
    if(retnode==NULL)
        return NULL;
    retnode->height = 1+max(retnode->leftchild?(retnode->leftchild->get_height()):0,retnode->rightchild?(retnode->rightchild->get_height()):0);
    //计算平衡因子
    int balanceFactor = get_balanceFact(retnode);
    if(balanceFactor > 1 && get_balanceFact(retnode->leftchild)>=0) {
        //右旋LL
        return right_rot(retnode);
    }
    if(balanceFactor < -1 && get_balanceFact(retnode->rightchild)<=0) {
        //左旋RR
        return left_rot(retnode);
    }
    //LR
    if(balanceFactor > 1 && get_balanceFact(retnode->leftchild) < 0){
        node->leftchild =left_rot(retnode->leftchild);
        return right_rot(retnode);
    }
    //RL
    if(balanceFactor < -1 && get_balanceFact(retnode->rightchild) > 0){
        node->rightchild = right_rot(retnode->rightchild);
        return left_rot(retnode);
    }
    return retnode;

}//retnode:存储的父节点 node:当前节点
treenode* tree::left_rot(treenode* node)
{
    //root(node)善后
    treenode* tempright = node->rightchild;
    treenode* templeft = tempright->leftchild;
    node->rightchild=templeft;
    node->height=1+max(node->leftchild?node->leftchild->get_height():0,node->rightchild?node->rightchild->get_height():0);

    //child(tempright)交接
    tempright->leftchild=node;
    node = tempright;
    node->height=1+max(node->leftchild?node->leftchild->get_height():0,node->rightchild?node->rightchild->get_height():0);
    return node;
}
treenode* tree::right_rot(treenode* node)
{
    //root(node)善后
    treenode* templeft = node->leftchild;
    treenode* tempright = templeft->rightchild;
    node->leftchild=tempright;
    node->height=1+max(node->leftchild?node->leftchild->get_height():0,node->rightchild?node->rightchild->get_height():0);

    //child(templeft)交接
    templeft->rightchild=node;
    node = templeft;
    node->height=1+max(node->leftchild?node->leftchild->get_height():0,node->rightchild?node->rightchild->get_height():0);
    return node;
}
/*Red_Black Function*/
treenode *tree::redblack_insertnode(treenode *node, treenode* fathernode, int num) {
    treenode* newptr=0;
    treenode* receivedptr=0;
    if(node==NULL)
    {
        newptr = new treenode(num);
        newptr->isred = 1;
        if(rootnode==0)
        {
            newptr->isred=0;
        }
        return newptr;
    }
    if(node->data>=num)
        receivedptr = node->leftchild = redblack_insertnode(node->leftchild,node,num);
    else if(node->data<num)
        receivedptr = node->rightchild = redblack_insertnode(node->rightchild,node,num);
    if(node->isred==1&&receivedptr->isred==1)//说明此时自己是父节点，且孩子红自己红，双红
    {
        node->doublered=1;      //双红，告知爷节点旋转或变色
        if(node->rightchild==receivedptr)
            node->childdirection=2;
        else if(node->leftchild==receivedptr)
            node->childdirection=1;

        return node;
    }
    if(receivedptr->doublered)  //说明此时自己是爷节点（一定是黑色）且需要旋转或变色
    {
        if(node->leftchild==receivedptr)
        {
            node->leftchild->doublered=0;
            if(node->rightchild==NULL || node->rightchild->isred==0)
            {
                if(receivedptr->childdirection==1)
                {
                    node = RB_right_rot(node);
                }
                else if(receivedptr->childdirection==2)
                {
                    node->leftchild = RB_left_rot(node->leftchild);
                    node = RB_right_rot(node);
                }
            }
            else if(node->rightchild->isred==1)
            {
                if(node!=rootnode)
                    node->isred=1;
                node->leftchild->isred=0;
                node->rightchild->isred=0;
            }
        }
        else if(node->rightchild==receivedptr)
        {
            node->rightchild->doublered=0;
            if(node->leftchild==NULL || node->leftchild->isred==0)
            {
                if(receivedptr->childdirection==2)
                {
                    node = RB_left_rot(node);
                }
                else if(receivedptr->childdirection==1)
                {
                    node->rightchild = RB_right_rot(node->rightchild);
                    node = RB_left_rot(node);
                }
            }
            else if(node->leftchild->isred==1)
            {
                if(node!=rootnode)
                    node->isred=1;
                node->leftchild->isred=0;
                node->rightchild->isred=0;
            }
        }


    }
    return node;








}
treenode *tree::redblack_deletenode(treenode *node, int num) {

}
treenode *tree::RB_left_rot(treenode *node)
{
    //root(node)善后
    treenode* tempright = node->rightchild;
    treenode* templeft = tempright->leftchild;
    node->rightchild=templeft;
    node->isred = 1;
    //child(tempright)交接
    tempright->leftchild=node;
    node = tempright;
    node->isred = 0;
    return node;


}
treenode* tree::RB_right_rot(treenode *node)
{
    //root(node)善后
    treenode* templeft = node->leftchild;
    treenode* tempright = templeft->rightchild;
    node->leftchild=tempright;
    node->isred=1;
    //child(templeft)交接
    templeft->rightchild=node;
    node = templeft;
    node->isred=0;
    return node;


}