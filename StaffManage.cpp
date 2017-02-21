//
//  main.cpp
//
//  Created by 郭成成 on 2016/11/20.
//  Copyright © 2016年 郭成成. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include "stdio.h"
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class Staff
{
public:
    char id[20]; //工号
    char name[20]; //姓名
    char sex[10];
    char dept[20];
    
    Staff *next; //指向下一个员工节点
    
    void input()//手动输入
    {
        cout<<"/t请输入新职工的档案数据"<<endl;
        cout<<"/t工号："; cin>>id;
        cout<<"/t姓名："; cin>>name;
        cout<<"/t性别："; cin>>sex;
        cout<<"/t部门："; cin>>dept;
    }
    
    void readfile(istream &in)//从文件中读取信息
    {
        in>>id>>name>>sex>>dept;//读到当前员工的成员变量里
    }
    
    void show()
    {
        cout<<"/t工号/t姓名/t性别/t部门"<<endl;
        cout<<"/t"<<id<<"/t"<<name<<"/t"<<sex<<"/t"<<dept<<endl;
    }
};

class StaffManage
{
public:
    StaffManage();
    ~StaffManage();
    void ShowMenu();
    void Find();
    void Save();
    void ModifyItem();
    void RemoveItem();
    void Swap(Staff*,Staff*);
    void Sort();
    void Display();
    void AddItem();
    Staff *FindItem(char *name);
    Staff *FindId(char *id);
    int ListCount();
private:
    Staff *Head,*End;
    ifstream in;
    ofstream out;
};

Staff *StaffManage::FindItem(char *name)
{
    for(Staff*p=Head;p->next!=End;p=p->next)
    {
        if(!strcmp(p->next->name, name))
            return p;//返回对应职工的前一个节点
    }
    return nullptr;
}

Staff *StaffManage::FindId(char *id)
{
    for(Staff*p=Head;p->next!=End;p=p->next)
    {
        if(!strcmp(p->next->id, id))
            return p;//返回对应职工的前一个节点
    }
    return nullptr;
}

StaffManage::StaffManage()
{
    Head=new Staff;
    Head->next=new Staff;
    End=Head->next; //新建两个员工，建立头节点和尾节点
    in.open("sort.txt");
    if(!in)
        cout<<"系统无任何职工档案数据，请先进行数据录入"<<endl;
    else{
        while(!in.eof())
        {
            End->readfile(in);//头节点无内容
            if(End->name[0]=='\0') break;
            End->next=new Staff;
            End=End->next;
        }
    }
}

void StaffManage::Save()
{
    //通过文本文件的数据保存
    out.open("sort.txt");
    for(Staff *p=Head->next;p!=End;p=p->next)
    {
        out<<p->id<<"/t"<<p->name<<"/t"<<p->sex<<"\t"<<p->dept<<endl;
    }
    out.close();
}

StaffManage::~StaffManage()
{
    Save();
    for(Staff *temp;Head->next!=End;)
    {
        temp=Head->next;
        Head->next=temp->next;
        delete temp;
    }
    delete Head;
    delete End;
}

void StaffManage::Display()
{
    for(Staff *p=Head->next;p!=End;p=p->next)
    {
        p->show();
    }
    cout<<"/t输入任意字符继续。。";
    getchar();
}

void StaffManage::AddItem()
{
    End->input();
    End->next=new Staff;
    End=End->next;//输入，把新建的赋值到最后
    cout<<"/t添加成功"<<endl;
    cout<<"输入任意字符继续。。";
    getchar();
}

void StaffManage::ShowMenu()
{
    cout<<"/t            ------------------            "<<endl;
    cout<<"/t ----------     职工管理系统     -----------"<<endl;
    cout<<"/t            ------------------            "<<endl;
    cout<<"/t      1.增加职工档案数据    4.查找职工档案数据  "<<endl;
    cout<<"/t      2.显示职工档案数据    5.删除职工档案数据  "<<endl;
    cout<<"/t      3.排序统计档案数据    6.修改职工档案数据  "<<endl;
    cout<<"/t      0.安全推出档案系统                     "<<endl;
    cout<<"/t------------------------------------------"<<endl;
    cout<<"/n/t 请选择：";
}

void StaffManage::Find()
{
    char name[20],id[10];
    int x;
    Staff *p=nullptr;
    cout<<"/n/t------------------------/n";
    cout<<"/t 1.按照职工的姓名查找 2.按照职工工号查找";
    cout<<"/n/t------------------------/n/t 请选择";
    switch (x) {
        case 1:
        {
            cout<<"/t 请输入要查找的职工的姓名：";
            cin>>name;
            if(FindItem(name)!=nullptr)
            {
                p=FindItem(name);
                p->next->show();
                cout<<"/t输入任意字符继续";
                getchar();
            }
            else{
                cout<<"/t没有找到该职工"<<endl;
                cout<<"/t输入任意字符继续";
                getchar();
            }
        }
            break;
        case 2:
        {
            cout<<"/t 请输入要查找的职工的工号：";
            cin>>id;
            if(FindId(id)!=nullptr)
            {
                p=FindId(id);
                p->next->show();
                cout<<"/t输入任意字符继续";
                getchar();
            }
            else{
                cout<<"/t没有找到该职工"<<endl;
                cout<<"/t输入任意字符继续";
                getchar();
            }
        }
        default:
            break;
    }
}

void StaffManage::ModifyItem()
{
    char name[20];
    cout<<"/t请输入要修改的职工姓名：";
    cin>>name;
    Staff *p=nullptr;
    if(FindItem(name)!=nullptr)
    {
        p=FindItem(name);
        p->next->input();
        cout<<"/t修改成功，输入任意字符继续";
        getchar();
    }
    else{
        cout<<"/t没有找到该职工"<<endl;
        cout<<"/t输入任意字符继续";
        getchar();
    }

}

void StaffManage::RemoveItem()
{
    char name[20];
    cout<<"/t请输入要修改的职工姓名：";
    cin>>name;
    Staff *p=nullptr;
    if(FindItem(name)!=nullptr)
    {
        p=FindItem(name);
        Staff *temp=p->next;
        p->next=temp->next;
        delete temp;
        cout<<"/t删除成功，输入任意字符继续";
        getchar();
    }
    else{
        cout<<"/t没有找到该职工"<<endl;
        cout<<"/t输入任意字符继续";
        getchar();
    }

}

int StaffManage::ListCount()
{
    if(!Head)
        return 0;
    int n=0;
    for(Staff *p=Head->next;p!=End;p=p->next)
    {
        n++;
    }
    return n;
}

void StaffManage::Swap(Staff *p, Staff *q)
{
    //类元素的交换，以便于进行排序,指向不变，内容交换
    Staff *temp=new Staff;
    strcpy(temp->id, p->id);
    strcpy(temp->name, p->name);
    strcpy(temp->sex, p->sex);
    strcpy(temp->dept, p->dept);
    
    strcpy(p->id, q->id);
    strcpy(p->name, q->name);
    strcpy(p->sex, q->sex);
    strcpy(p->dept, q->dept);
    
    strcpy(q->id, temp->id);
    strcpy(q->name, temp->name);
    strcpy(q->sex, temp->sex);
    strcpy(q->dept,temp->dept);
    
//    temp=p;
//    p=q;
//    q=temp;
    
}

void StaffManage::Sort()
{
    cout<<"正在排序。。"<<endl;
    Staff *p=nullptr;
    Staff *k=nullptr;
    int n=ListCount();
    if(n<2)
        return;
    for(p=Head->next;p!=End;p=p->next)
    {
        for(k=p->next;k!=End;k=k->next)
        {
            if(p->id<k->id)
                Swap(p, k);
        }
    }
    cout<<"/t 排序完成！"<<endl;
    getchar();
}

int main()
{
    cout<<"欢迎进入职工档案管理系统"<<endl;
    StaffManage grade;
    int x;
    bool quit=false;
    while(!quit)
    {
        system("cls");
        grade.ShowMenu();
        cin>>x;
        switch (x) {
            case 0:
                quit=true;
                break;
            case 1:
                grade.AddItem();
                break;
            case 2:
                grade.Display();
                break;
            case 3:
                grade.Sort();
                break;
            case 4:
                grade.Find();
                break;
            case 5:
                grade.RemoveItem();
                break;
            case 6:
                grade.ModifyItem();
                break;
            default:
                break;
        }
    }
    return 0;
}
