#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _Person {
    int id;
    char name[128];
    char sex[3];
    char number[11];
}Person;

typedef struct Node{
    struct _Person data;
    struct Node *next;
}Node;

Node *headList;

void saveFile(){
    FILE *fp;
    fp=fopen("file.txt","w");
    Node *temp=headList;
    while(temp!=NULL){
        fprintf(fp,"%d %s %s %s\n",
            temp->data.id,temp->data.name,temp->data.sex
            ,temp->data.number);
        temp=temp->next;
    }
    fclose(fp);
}

void openFile(){
    FILE *fp=fopen("file.txt","r");
    if(fp==NULL){
        return;
    }
    Node* ls;
    while(!feof(fp)){
        Node *temp=(Node*)malloc(sizeof(Node));
        fscanf(fp,"%d %s %s %s\n",
            &temp->data.id,temp->data.name,temp->data.sex
            ,temp->data.number);
        if(headList==NULL){
            headList=temp;
            ls=temp;
        }else{
            ls->next=temp;
            ls=temp;
        }
    }
    
}

void addNode(Node *head,Person value){
    if(head==NULL){
        headList=(Node *) malloc(sizeof(Node));
        headList->data=value;
        headList->next=NULL;
        return;
    }
    Node *temp=head;
    while (temp->next){
        temp=temp->next;
    }
    temp->next=(Node *) malloc(sizeof(Node));
    temp=temp->next;
    temp->data=value;
    temp->next=NULL;
}
void deleateNode(Node *head,Node *node){
    Node *temp=head;
    if(temp==node){
        Node *del=head;
        headList=headList->next;
        free(del);
        return;
    }
    while (temp->next){
        if(temp->next==node){
            Node *del=temp->next;
            temp->next=temp->next->next;
            free(del);
            return;
        }
        temp=temp->next;
    }
}

void menu(){
    //
    printf("\t\t|-----------欢迎您使用通讯录管理系统-------------|\n");
    printf("\t\t|         1-添加信息      2-显示信息             |\n");
    printf("\t\t|         3-查找信息      4-删除信息             |\n");
    printf("\t\t|         5-修改信息      0-退出系统             |\n");
    printf("\t\t|------------------------------------------------|\n");

}

void addMessage(){
    char c ;
    Person person;
    printf("------------------ 请输入联系人信息 --------------------\n");
    printf("请输入id:");
    scanf("%d",&person.id);
    printf("输入联系人姓名:");
    scanf("%s",person.name);
    printf("输入联系人性别:");
    scanf("%s",person.sex);
    printf("输入联系人电话号码:");
    scanf("%s",person.number);
    addNode(headList,person);


    //getchar();
    printf("是否继续添加联系人?(Y/N):");
    //fflush(stdin);
    //if (getchar()=='y')
    //  addMessage();
    getchar();
    scanf("%c",&c);
    if(c == 'Y' || c == 'y') addMessage();
    return;
}

/*自己封装的strcmp函数
*功能：字符串ascii值比较
*参数：s1待比较字符串1 s2待比较字符串2
*返回值：字符串比较结果 相等返回0 s1 大于s2 返回正值 否则返回负值
*/
/*
s1:  cdfffaa
s2:  cdfffaab s2
*/
/**/
int myStrcmp(char s1[],char s2[]){
    while(1){
        if(*s1=='\0'){
            if(*s2=='\0'){
                return 0;
            }else{
                return -1;
            }
        }else if(*s2=='\0'){
            return 1;
        }
        if(*s1!=*s2){
            return *s1>*s2;
        }else{
            s1++;
            s2++;
        }
    }
}

void sortByName(){
    Node *i=headList;
    while (i){
        Node *j=i->next;
        while (j){
            if(i->data.name[0]>j->data.name[0]){
                Person tempPerson;
                tempPerson=i->data;
                i->data=j->data;
                j->data=tempPerson;
            }
            j=j->next;
        }
        i=i->next;
    }
}

//显示信息
void showMessage(){
    sortByName();//排序
    if(!headList){
        printf("当前没有联系人,请添加后查看\n");
        return;
    }
    printf("姓名\t性别\t电话号\n");
    Node *temp=headList;
    while (temp){
        printf("%s\t%s\t%s\n",temp->data.name,temp->data.sex,temp->data.number);
        temp=temp->next;
    }
}

void findMessage(){
    //printf("查找信息成功....\n");
    int choice,value,count=0;
    char name[128];
    printf("1.根据id查找\n");
    printf("2.根据用户名查找\n");
    scanf("%d",&choice);
    switch(choice){
        case 1:
            printf("请输入id:");
            scanf("%d",&value);
            break;
        case 2:
            printf("请输入用户名:");
            scanf("%s",name);
            break;
        default:
            printf("输入错误,退出");
            return;
    }
    Node *temp=headList;
    while (temp){
        if((choice==1&&temp->data.id==value)||(choice==2&&myStrcmp(name,temp->data.name)==0)){
            if(count==0){
                printf("姓名\t性别\t电话号\n");
            }
            count++;
            printf("%s\t%s\t%s\n",temp->data.name,temp->data.sex,temp->data.number);
        }
        temp=temp->next;
    }
    if(count==0){
        printf("未找到用户,请检查输入\n");
    }
    printf("是否继续查询(y/n)?:");
    getchar();
    choice=getchar();
    if(choice=='y'||choice=='Y') findMessage();
    return;
}

void deleteMessage(){
    //printf("删除信息成功....\n");
    //怎么删呢
    int id,count=0;
    printf("请输入要删除的id:");
    scanf("%d",&id);
    Node *temp=headList;
    while (temp){
        if(temp->data.id==id){
            Node *tempx=temp->next;
            deleateNode(headList,temp);
            temp=tempx;
            count++;
        } else{
            temp=temp->next;
        }
    }
    if(count==0)
        printf("未找到用户,删除失败!\n");
    else
        printf("删除成功,共删除%d个用户\n",count);

}

void writeMessage(){
    //printf("修改信息成功....\n");
    if(!headList){
        printf("当前没有联系人,请添加后再修改\n");
        return;
    }
    int id,count=0;
    char choice;
    printf("请选择你要修改的id:");
    scanf("%d",&id);
    Node *temp=headList;
    while (temp){
        if(temp->data.id==id){
            if(count==0){
                printf("姓名\t性别\t电话号\n");
            }
            count++;
            scanf("%s\t%s\t%s",temp->data.name,temp->data.sex,temp->data.number);
            printf("修改信息成功！\n");
            break;
        }
        temp=temp->next;
    }
    if(count==0){
        printf("未找到用户,请检查输入\n");
    }
    printf("是否继续修改是(y/n)?:");
    getchar();
    choice=getchar();
    if(choice=='y'||choice=='Y') writeMessage();
    return;
}

void chooseService(){
    int n;
    while(1){
        menu();
        printf("请输入你想选择的操作:");
        //fflush(stdin);
        scanf("%d",&n);
        switch (n) /*对于上边的选择项目*/
        {
            case 1:
                addMessage();
                break;
            case 2:
                showMessage();
                break;
            case 3:
                findMessage();
                break;
            case 4:
                deleteMessage();
                break;
            case 5:
                writeMessage();
                break;
            case 0:
                exit(0);
            default:
                printf("无效输入，请重新输入：");
                break;
        }
        saveFile();
        //fflush(stdin);
        //getchar();
        //system("clear");
    }
}

int main(){
    setbuf(stdout,NULL);
    headList=NULL;
    openFile();
    chooseService();
    return 0;
}
