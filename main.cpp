#include <iostream>
#include<stdlib.h>
using namespace std;
int total_bank_work_time=0;
class Client
{
public:
    static int count_client;
    int ID = count_client;
    int Arrival;
    int Transaction;
    int Waiting;
    int Finished;
    Client()
    {
        Waiting = 0;
        Finished = Arrival + Transaction+ Waiting;


    }
    int operator == (Client client)
    {
        if(this->ID == client.ID )
        {
            return 1;
        }
        else
            return 0;
    }
    void operator =(Client &client)
    {
        this->ID=client.ID;

        this->Arrival=client.Arrival;
        this->Transaction=client.Transaction;
        this->Waiting=client.Waiting;
    }

    friend ostream & operator <<(ostream&out,Client&client);
    friend istream & operator >>(istream&in,Client &client);
};
int Client::count_client=1;
ostream & operator << (ostream&out,Client &client)
{
    out<<"\t\t\t\t\t\tID :"<<client.ID<<endl;
    out<<"\t\t\t\t\t\tArrival Time :"<<client.Arrival<<endl;
    out<<"\t\t\t\t\t\tTransaction time :"<<client.Transaction<<endl;
    out<<"\t\t\t\t\t\tWait time :"<<client.Waiting<<endl;
    out<<"\t\t\t\t\t\tFinish time : "<<client.Finished<<endl;

    return out;
}
istream & operator >> (istream&in,Client &client)
{
    cout<<"\t\t\t\t\t\tEnter Arrive time : ";
    in>>client.Arrival;
    cout<<"\t\t\t\t\t\tEnter Transaction time : ";
    in>>client.Transaction;
    client.ID=Client::count_client++;
    return in;
}
struct Node
{
    Client client;
    Node * Next;
    Node * Prev;
};
typedef struct Node Node;
class Linked_List
{
public:
    Node *First,*Last;
    Linked_List()
    {
        First=Last=NULL;
    }
    Node *Create(Client client)
    {
        Node*node=new Node();
        node->client=client;
        node->Prev=node->Next=NULL;
        return node;
    }
    void Add(Node *newNode)
    {
        if(First==NULL)
        {
            First=Last=newNode;
        }
        else
        {
            Last->Next=newNode;
            newNode->Prev=Last;
            Last=newNode;
        }

    }
    void Display()
    {
        Node *PDisplay=First;
        while(PDisplay!=NULL)
        {
            cout<<PDisplay->client;
            cout<<"\n";
            PDisplay=PDisplay->Next;
        }
    }
    void SwapClients(Client & client,Client & client2)
    {
        Client temp;
        temp=client;
        client=client2;
        client2=temp;
    }
    void SortID()
    {
        Node * node=First;
        int counter_ID=1;
        while(node!=NULL)
        {
            node->client.ID=counter_ID;
            counter_ID++;
            node=node->Next;
        }
    }
    void selected_sort()
    {
        Node *index=First;
        char ch;
        Node *curent;
        Node *minindex;
        while(index!=NULL)
        {
            curent=index;
            minindex=index;
            while(curent!=NULL)
            {
                if(minindex->client.Arrival > curent->client.Arrival)
                {
                    minindex=curent;
                }
                curent=curent->Next;
            }
            SwapClients(index->client,minindex->client);
            index=index->Next;
        }
        SortID();
    }
};
class Queue
{
public:
    struct Node* Front = NULL;
    struct Node* Rear = NULL;
    struct Node* temp;
    int counter=0;
    int Num_Served_Clients = 0;
    int Total_Waiting=0;
    int Total_Working=0;
    void Enqueue(Node *n)
    {
        //counter++;
        if(isempty())
        {
            Front=Rear=n;
        }
        else
        {
            Rear->Next=n;
            Rear=n;
        }
    }
    int isempty()
    {
        return (Front==NULL);
    }
    void Dequeue()
    {
        temp = Front;
        if (Front == NULL)
        {
            cout<<"Underflow"<<endl;
            return;
        }
        else if (temp->Next != NULL)
        {
            temp = temp->Next;
            cout<<"Element deleted from queue is : "<<Front->client<<endl;
            free(Front);
            Front = temp;
        }
        else
        {
            cout<<"Element deleted from queue is : "<<Front->client<<endl;
            free(Front);
            Front = NULL;
            Rear = NULL;
        }
    }
    int Is_Finished(Node *n,int time)
    {

        n->client.Finished=n->client.Arrival+n->client.Transaction+n->client.Waiting;
        if(n->client.Finished<=time)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    //before enqueue
    int duration_Sum(int time)
    {
        if(isempty())
        {
            return 0;
        }
        int sum=(Front->client.Arrival+ Front->client.Transaction + Front->client.Waiting ) - time;
        Node *p=Front->Next;

        while(p!=NULL)
        {
            sum+=p->client.Transaction;
            p=p->Next;
        }
        return sum;
    }
    void Display()
    {
        temp = Front;
        if ((Front == NULL) && (Rear == NULL))
        {
            cout<<"Queue is empty"<<endl;
            return;
        }
        cout<<"Queue elements are: ";
        while (temp != NULL)
        {
            cout<<temp->client<<" ";
            temp = temp->Next;
        }
        cout<<endl;
    }
    void queue_clear(int time)
    {
        Node *nod;
        if(counter!=0)
        {
            int flage=0;
            nod=Front;// node *nod;
            while(nod!=NULL&&flage!=1)
            {
                flage=1;
                nod=Front;
                if(Is_Finished(nod,time))
                {
                    if(nod->client.Finished>=total_bank_work_time)
                    {
                        total_bank_work_time=nod->client.Finished;
                    }
                    flage=0;
                    counter--;
                    Dequeue();
                }
                nod=nod->Next;
            }
        }
    }
    void Add_Node(Node *n)
    {
        n->client.Waiting=duration_Sum(n->client.Arrival);
        counter++;
        Num_Served_Clients++;
        Total_Waiting+=n->client.Waiting;
        Total_Working+=n->client.Transaction;
        n->Next=NULL;
        Enqueue(n);
    }
    void Report()
    {
        cout<<"\t\t\t\t\t\tTotal Client number :"<<Num_Served_Clients<<"\n";
        cout<<"\t\t\t\t\t\tTotal Wait Time :"<<Total_Waiting<<"\n";
        cout<<"\t\t\t\t\t\tTotal Work Time :"<<Total_Working<<"\n";
        if(Num_Served_Clients>0)
        {
           cout<<"\t\t\t\t\t\tAverage Waiting  : "<<(float)Total_Waiting/ (float)Num_Served_Clients<<endl;
           cout<<"\t\t\t\t\t\tAverage Working : "<<(float)Total_Working / (float)Num_Served_Clients<<endl;
        }


    }
};
class Bank
{
public:
    Queue q1,q2,q3;
    int Bank_Wait_Time;
    int Bank_Work_Time;
    int Total_Num_Served_Clients;
    void Bank_Report()
    {
        cout<<"\n\t\t\t\t\t\tReport for Queue 1 \n\n";
        q1.Report();
        cout<<"\n\t\t\t\t\t\tReport for Queue 2 \n\n";
        q2.Report();
        cout<<"\n\t\t\t\t\t\tReport for Queue 3 \n\n";
        q3.Report();
         Total_Num_Served_Clients = q1.Num_Served_Clients + q2.Num_Served_Clients + q3.Num_Served_Clients;
        Bank_Wait_Time=max (max(q1.Total_Waiting,q2.Total_Waiting),q3.Total_Waiting);
        Bank_Work_Time=total_bank_work_time;
        cout<<"\n\t\t\t\t\t\t====Bank Report====   \n";
        cout<<"\n\t\t\t\t\t\tBank Wait Time :"<<Bank_Wait_Time<<endl;
        cout<<"\t\t\t\t\t\tBank Work Time :"<<Bank_Work_Time<<endl;
         if(Total_Num_Served_Clients>0)
        {
           cout<<"\t\t\t\t\t\tBank Average Wait : "<< (float)Bank_Wait_Time /(float)Total_Num_Served_Clients<<endl;
           cout<<"\t\t\t\t\t\tBank Average work : "<< (float)Bank_Work_Time /(float)Total_Num_Served_Clients<<endl;
        }

    }
};
int min_number(Queue q1,Queue q2,Queue q3)
{
    int minimum_queue=min(min(q1.counter,q2.counter),q3.counter);
    if(q1.counter==minimum_queue)
    {
        return 1;
    }
    else if( q2.counter==minimum_queue)
    {
        return 2;
    }
    else
    {
        return 3;
    }
}
int main()
{
    int choice;
    Linked_List List;
    int flag =1;
    Client client;
    Bank bank;
    int min_num;
    while(flag!=0)
    {
        cout<<"\t\t\t\t\t    ================================\n";
        cout<<"\t\t\t\t\t\t1.Enter new Client\n";
        cout<<"\t\t\t\t\t\t2.Display Entered data List\n";

        cout<<"\t\t\t\t\t\t3.End of day\n";
        cout<<"\t\t\t\t\t    ================================\n";
        cout<<"\t\t\t\t\t\tEnter your choice : ";
        cin>>choice;
        switch (choice)
        {
        case 1:
        {
            cout<<"\t\t\t\t\t\tEnter client data \n";
            cin>>client;
            Node * node=List.Create(client);

            List.Add(node);
            flag=1;
            break;
        }
        case 2:
        {
            system("cls");
            List.Display();
            flag=1;
            break;
        }
        case 3:
        {
            flag=0;
            break;
        }
        }
    }
    List.selected_sort();
    Node * n1=List.First;
    Node *second;
    while(n1!=NULL)
    {
        second=n1->Next;
        bank.q1.queue_clear(n1->client.Arrival);
        bank.q2.queue_clear(n1->client.Arrival);
        bank.q3.queue_clear(n1->client.Arrival);
        min_num=min_number(bank.q1,bank.q2,bank.q3);
        if(min_num==1)
        {
            bank.q1.Add_Node(n1);
            cout<<"Queue 1\n";
        }
        else if(min_num==2)
        {
            bank.q2.Add_Node(n1);
            cout<<"Queue 2\n";
        }
        else
        {
            bank.q3.Add_Node(n1);
            cout<<"Queue 3\n";
        }
        n1=second;
    }
    int totalbanktime=100;
    bank.q1.queue_clear(totalbanktime);
    bank.q2.queue_clear(totalbanktime);
    bank.q3.queue_clear(totalbanktime);

    cout<<"End of ADD \n";
    cout<<"\t\t\t\t\t\tQueue 1 elements\n\n";
    bank.q1.Display();
    cout<<"\t\t\t\t\t\tQueue 2 elements\n\n";
    bank.q2.Display();
    cout<<"\t\t\t\t\t\tQueue 3 elements\n\n";
    bank.q3.Display();
    system("cls");
    cout<<"\n\t\t\t\t\t\t ====Report====         \n";
    bank.Bank_Report();
    return 0;
}
