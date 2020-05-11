#include<bits/stdc++.h>
using namespace std ;

template<  typename t >
class redblack
{    
     private:  
      struct Node
    {  
    bool black;
    t data ;
    Node *left,*right,*parent,*thisa ;

    Node(t data,Node * p)
    {      
         parent=p;
        this->data = data;
        left=right=NULL;
        black = false; 
    }
    };
     void preorder_helper(Node &n)
    { 
    s.push_back({n.data,!n.black});
     if(n.left!=NULL)
     preorder_helper(*n.left);
     if(n.right!=NULL)
     preorder_helper(*n.right);
     
    }
     void print_helper(const Node &curr)
    {     if(&curr==NULL)
            return ;
        print_helper(*curr.left);
        cout<<curr.data<<" ";
        print_helper(*curr.right);
        
    }
    void insert_helper(t data,Node & curr )
    {
        if(curr.data<data)
        {
            if(curr.right==NULL)
              { curr.right=new Node(data,&curr);fix_Violations(curr.right);}
            else 
            insert_helper(data,*curr.right);
        }
        else if(curr.data>data) 
        {
           if(curr.left==NULL)
              { curr.left=new Node(data,&curr);fix_Violations(curr.left);}
            else 
            insert_helper(data,*curr.left);
        
        }
    }
   
void fix_Violations(Node *n)
    {    
        if(n->parent==NULL){n->black=true ;return  ; }
        Node *parent = n->parent;
        if(parent->black) return ;
        Node *gp = parent->parent;
        Node *uncle = gp->right==parent?gp->left:gp->right;
        if(uncle!=NULL)
         if(!uncle->black)
        {   
            parent->black=true;
            uncle->black=true ;
            gp->black=false ;
            fix_Violations(gp);
            return ;
        }
           if(parent->right==n&&gp->right==parent)
              {
                  rotate_left(gp);
                 }
           else if (parent->left==n&&gp->left==parent)
           {
               rotate_right(gp);
             }
           else if(parent->right==n&&gp->left==parent)
            {
                  rotate_left(parent);
                  rotate_right(gp);
                  parent=n;
            }
            else if(parent->left==n&&gp->right==parent)
            {
             rotate_right(parent);     
             rotate_left(gp);
             parent=n;
            }
            else cout<<"erooor";
            swap(parent->black,gp->black);
    }
    void rotate_right(Node * leave )
    {  
        Node *parent =leave->parent;
        Node  *son =leave->left;
        if(parent!=NULL){
        if(parent->left==leave) parent->left=son;else parent->right=son;
        son->parent = parent;
        }
        else {son->parent=NULL;root=son;}
        leave->left=son->right;
        if(leave->left!=NULL)
        leave->left->parent=leave;
        son->right=leave;
        leave->parent =son;


    }
     bool find_helper(t e ,Node *n )
     {
         if(n==NULL)return false ;
         if(e==n->data ) return true ;
         if(e>n->data) return find_helper(e,n->right);
          return find_helper(e,n->left);
         
     }
    void rotate_left(Node * leave)
    {
        Node *parent =leave->parent;
        Node  *son =leave->right;
       if(parent!=NULL){
        if(parent->left==leave) parent->left=son;else parent->right=son;
        son->parent = parent;
      }
        else {son->parent=NULL;root=son;}
        leave->right=son->left;
        if(leave->right!=NULL)
        leave->right->parent=leave;
        son->left=leave;
        leave->parent =son;
    }
    Node *root;
     bool primitve;
     enum color{red,black};

  
    
    public :
    redblack()
    {   
        root=NULL;
           primitve=is_fundamental<t>::value;
            
    }
    bool isempty() {return root==NULL;}
    
    void insert( t data)
    {
          if(isempty())
          {
              root=new Node(data,NULL);
              root->black=true ;
          }
          else 
              insert_helper(data,*root);
          
    }
    Node * begin()
    {  Node *temp = root;
        while(temp->left!=NULL)
         temp=temp->left ;
        return temp ;
    } 
    Node * end()
    {  
        Node *temp = root;
        while(temp->right!=NULL)
         temp=temp->right ;
        return temp ;
    }
     vector<pair<string,bool>> s; 
   
    vector<pair<string,bool>> preorder() {s.empty(); preorder_helper(*root);return s ;}
    void print(){print_helper(*root);printf("\n");}
    int height_helper(Node *n)
    {
        if(n==NULL)
         return -1;
        int x=   1+max(height_helper(n->left),height_helper(n->right));
        return x;
    }
    int height(){ return height_helper(root);}
     t root_data()
     {
         return root->data;
     }
     int count_helper(Node *n)
     {  if(n==NULL) return 0;
         return 1 + count_helper(n->left)+count_helper(n->right);
     }
     bool find(t e ){return find_helper(e,root);}
 int count() { return count_helper(root);}
};

int main ()
{
  
    redblack<string> tree;
    int count=0 ;
    ios_base::sync_with_stdio(false); 
    ifstream infile;
      infile.open("English.txt");
    string x ;
    
    while (infile >> x)
    { count++;
        transform(x.begin(), x.end(), x.begin(), ::tolower);
        tree.insert(x);
    }
    cout<<tree.root_data()<<" \n";    
    //tree.print();
    infile.close();
    cout<<"height = "<<tree.height()<<"\n";
    cout << "number of words = " << count <<endl;
    while(1)
    {string s ;
    cin>>s;
    if(tree.find(s))
       cout<<"found\n";
       else cout<<"not found\n";
    }
}