
// BY Vraj Dobariya 
// Date: 30th May 2024
#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
typedef long double lld;
typedef unsigned long long ull;

#define int ll
// just to scan input from input.txt and print output in output.tx
// void init_code()
// {
//     #ifndef ONLINE_JUDGE
//     freopen("input.txt", "r", stdin);
//     freopen("output.txt", "w", stdout);
//     #endif // ONLINE_JUDGE
// }


class Node{
     
     public:
     int key;
     int val;
     Node* next;
     Node* prev;

     // default constructor
     Node()
     {
        this->next=NULL;
        this->prev=NULL;
     }
    // new node constructor
     Node(int key,int val)
     {
        this->key = key;
        this->val = val;
        this->next=NULL;
        this->prev=NULL;
     }
};
// just for printing purpose
string s(21,'-');

class LRU_CACHE{
public:
    Node* head;
    Node* tail;
    int LRU_MAX_CACHE_SIZE;
    int curr_size;
    unordered_map<int,Node*>hashmap;
    // default constructor
    LRU_CACHE()
    {
        head=new Node(-1,-1);
        tail=new Node(-1,-1);
        head->next=tail;
        tail->prev=head;
        LRU_MAX_CACHE_SIZE=0;
        curr_size=0;
 //    head ------> tail
 //    head <------ tail
    }
    LRU_CACHE(int LRU_MAX_CACHE_SIZE)
    {
        head=new Node(-1,-1);
        tail=new Node(-1,-1);
        head->next=tail;
        tail->prev=head;
        this->LRU_MAX_CACHE_SIZE=LRU_MAX_CACHE_SIZE;
        this->curr_size=0;
        hashmap.clear();
// initialization by constructor
 //    head ------> tail
 //    head <------ tail
    }
    

    void setCacheSize(int size_)
    {
            LRU_MAX_CACHE_SIZE=size_;
    }
    void PrintCurrentCache()
    {
        
        cout<<"\n";
        for(int i=0;i<LRU_MAX_CACHE_SIZE+1;i++)
        cout<<s;
        cout<<"\n";
        
        Node* curr = head;
        
        while(curr!=tail)
        {
            if(curr==head)
            {
                cout<<"   => { head <--->";
            }
            else
            cout<<" [k:"<<curr->key<<", v:"<<curr->val<<"] <--->";
            
            curr=curr->next;
        }
           
        
        cout<<" tail } <=";
        cout<<"\n";
        for(int i=0;i<LRU_MAX_CACHE_SIZE+1;i++)
        cout<<s;
        cout<<"\n";
    }

    
    void insertafterHead(int key,int value)
    {

        /*

        before insertion after head
        head ---> nextnode .... ---> tail
        head <--- nextnode .... <--- tail

        after insertion after head
        head ---> newNode ---> nextnode .... ---> tail
        head <--- newNode <--- nextnode .... <--- tail

        */
        
        curr_size++;

        Node* nextnodeafterhead=head->next;
       
        Node* newNode = new Node(key,value);

        // inserting or updating in hashmap with key
        hashmap[key]=newNode;

        head->next = newNode;
        newNode->prev=head;
        newNode->next=nextnodeafterhead;
        nextnodeafterhead->prev=newNode;
        
      
    }


    void deletebeforeTail()
    {
         
        /*

        tail before deletion 
        head ---> .... prevnode ---> deleteNode ---> tail
        head <--- .... prevnode <--- deleteNode <--- tail

        tail after deletion
        head ---> .... prevnode ---> tail
        head <--- .... prevnode <--- tail

        */


       curr_size--;
       Node* deleteNode = tail->prev;
       Node* prevNode = deleteNode->prev;

       int key = deleteNode->key;

       // removing key from hashmap
       hashmap.erase(hashmap.find(key));

       
       // assigning pointers correctly
       prevNode->next = tail;
       tail->prev= prevNode;

       delete deleteNode;


      
    }

    void deleteNode(int key)
    {
        /*
        before deletion 

        .... prevNode ---> deleteNode ---> nextNode ....
        .... prevNode <--- deleteNode <--- nextNode ....


        after  deletion

        .... prevNode ---> nextNode ....
        .... prevNode <--- nextNode ....
        
        */

        // this function is called only when we are sure that our key node is present so will not lead to any ambiguity.

        // removing key from hashmap
        
        curr_size--;
        // getting prevnode of the node to be deleted
       

        Node* deleteNode = hashmap[key];

        Node* prevNode = deleteNode->prev;
        
        // assigning pointers
        Node* afterdeleteNode = deleteNode->next;
        prevNode->next = afterdeleteNode;
        afterdeleteNode->prev = prevNode;
        hashmap.erase(hashmap.find(key));

        delete deleteNode;

       
    }

    int get(int key)
    {
        /*

        LRU before get

        head --> ..... keynode ... --> tail
        head <-- ..... keynode ... <-- tail

        LRU after get 
        1)gets deleted from original position
        2)gets inserted after head making the most recently used

        head --> keynode ... --> tail
        head <-- keynode ... <-- tail



        */
        
        if(hashmap.find(key)==hashmap.end())
        {
            // if key not found in hashmap return -1 as not present in LRU
            return -1;
        }
        else
        {
          
            // if key found in hashmap then we need to update the LRU.
            // => delete key value and insert the same after head

            int returnval = hashmap[key]->val;
            // delete and insert to get updated LRU
            deleteNode(key);
            
            insertafterHead(key,returnval);

           return returnval;

        }
        
        
    }


    void put(int key,int value)
    {
            if(hashmap.find(key)!=hashmap.end())
            {
                // if already present in hashmap then delete node and insert at head as last recent used
                deleteNode(key);
                insertafterHead(key,value);
            }
            else{
               
                if(curr_size<LRU_MAX_CACHE_SIZE)
                {
                    // if current size if less than max size then insert after head directly
                    insertafterHead(key,value);
                }
                else
                {
                    // size if maximized so delete least recently used and insert new node after head
                    deletebeforeTail();
                    insertafterHead(key,value);
                }
            }
    }







};
void solve(){
  

   int LRU_MAX_CACHE_SIZE;
   cout<<"ENTER THE MAXIMUM CACHE SIZE OF LRU CACHE: ";
   cin>>LRU_MAX_CACHE_SIZE;
   cout<<"\n";


   LRU_CACHE MyLRU(LRU_MAX_CACHE_SIZE);
   
//     if you want limited queries
//     cout<<"ENTER THE TOTAL NUMBER OF INTIAL QUERIES: ";
//     int TOTAL_QUERIES;
//     cin>>TOTAL_QUERIES;
//     cout<<"\n";
 // infinite queries
   while(1){

    int WHICH_QUERY;
    // 1 for put and 2 for get
    cout<<"Enter 1 for PUT or 2 for GET query or -1 to stop queries: ";
    cin>>WHICH_QUERY;
    cout<<"\n";


    if(WHICH_QUERY==1)
    {
        cout<<"ENTER KEY AND VALUE FOR THE PUT QUERY: ";
        
        int Put_Key,Put_Value;
        
        cin>>Put_Key>>Put_Value;
        cout<<"\n";

        MyLRU.put(Put_Key,Put_Value);
      

    }
    else if(WHICH_QUERY==2)
    {
        cout<<"ENTER KEY FOR THE GET QUERY: ";
        int Get_Key;
        cin>>Get_Key;
        cout<<"\n";

        cout<<"\nValue: "<<MyLRU.get(Get_Key)<<"\n";
        
    }
    else if(WHICH_QUERY==-1)
    {
        // remaining cache:
         MyLRU.PrintCurrentCache();
         // stop recieving queries
         break;
    }
    else
    {   
        // not a valid query
        cout<<"INVALID QUERY! \n";
        continue;
    }
    // printing CURRENT LRU CACHE
    MyLRU.PrintCurrentCache();
    cout<<"\n";
   }
}


signed main() {
   
    
// init_code();
int t=1;
// cin>>t;
while(t--)
solve();

}
