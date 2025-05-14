#include <iostream>
#include <vector>
#define ll long long
using namespace std;

template<typename T1, typename T2> 
class Node
{
public:
    T1 key;
    T2 val;
    ll height;
    Node* left;
    Node* right;

    Node(T1 x, T2 y)
    {
        key = x;
        val = y;
        left = NULL;
        right = NULL;
        height = 1;
    }
};

template<typename T1, typename T2> 
class Map
{
public:
    ll cnt = 0;
    Node<T1,T2>* root = NULL;

    // Function for calculating maximum of 2
    ll max(ll a, ll b)
    {
        if(a > b)
            return a;
        else
            return b;
    }

    // Function for calculating height
    ll calcHeight(Node<T1,T2>* node)
    {
        if(node!=NULL)
            return 1+max(calcHeight(node->left),calcHeight(node->right));
        else
            return 0;
    }

    // Left rotation
    Node<T1,T2>* LeftRotate(Node<T1,T2>* node)
    {
        Node<T1,T2>* temp1 = node->right;
        Node<T1,T2>* temp2 = temp1->left;
        temp1->left = node;
        node->right = temp2;
        node->height = 1 + max(calcHeight(node->left),calcHeight(node->right));
        temp1->height = 1 + max(calcHeight(temp1->left),calcHeight(temp1->right));
        return temp1;
    }

    // Right Rotation
    Node<T1,T2>* RightRotate(Node<T1,T2>* node)
    {
        Node<T1,T2>* temp1 = node->left;
        Node<T1,T2>* temp2 = temp1->right;
        temp1->right = node;
        node->left = temp2;
        node->height = 1 + max(calcHeight(node->left),calcHeight(node->right));
        temp1->height = 1 + max(calcHeight(temp1->left),calcHeight(temp1->right));
        return temp1;
    }

    // Function to calculate balancefactor
    ll balanceFactor(Node<T1,T2>* node)
    {
        if(node==NULL)
            return 0;
        return calcHeight(node->left)-calcHeight(node->right);
    }

    // function to insert a node
    Node<T1,T2>* insertNode(Node<T1,T2>* root, T1 x, T2 y, bool &f)
    {
        if(root==NULL)
        {
            f = true;
            return new Node(x,y);
        }
            
        if(x > root->key)
            root->right = insertNode(root->right,x,y,f);
        else if(x < root->key)
            root->left = insertNode(root->left,x,y,f);
        else
        {
            root->val = y;
            f = false;
            return root;
        }
        root->height = 1 + max(calcHeight(root->left),calcHeight(root->right));

        ll b = balanceFactor(root);

        if(b<-1 && x > root->right->key)
            return LeftRotate(root);
        if(b>1 && x < root->left->key)
            return RightRotate(root);

        if(b<-1 && x < root->right->key)
        {
            root->right = RightRotate(root->right);
            return LeftRotate(root);
        }
        if(b>1 && x > root->left->key)
        {
            root->left = LeftRotate(root->left);
            return RightRotate(root);
        }
        f = true;
        return root;
    }

    // Function to search a key
    void search(Node<T1,T2>* root, T1 x, bool &f)
    {
        if(root==NULL)
        {
            f = false;
            return ;
        }
        if(x > root->key)
            search(root->right, x, f);
        else if(x < root->key)
            search(root->left, x, f);
        else
        {
            f = true;
            return ;
        }
    }

    // Function to search a key and return its key,val pair
    Node<T1,T2>* search2(Node<T1,T2>* root, T1 x)
    {
        if(root==NULL)
            return new Node(x, T2());
        if(x > root->key)
            search2(root->right,x);
        else if(x < root->key)
            search2(root->left,x);
        else
        {
            return new Node(root->key,root->val);
        }
    }

    // function to find minNode
    Node<T1,T2>* minNode(Node<T1,T2>* node)
    {
        Node<T1,T2>* mx = node;
        while(mx->left!=NULL)
        mx = mx->left;
        return mx;
    }

    // function to delete a node
    Node<T1,T2>* deleteNode(Node<T1,T2>* root, T1 x, T2 y)
    {
        if(root==NULL)
            return root;
        if(x > root->key)
            root->right = deleteNode(root->right,x,y);
        else if(x < root->key)
            root->left = deleteNode(root->left,x,y);

        else
        {
            if(root->left!=NULL && root->right!=NULL)
            {
                Node<T1,T2>* temp = minNode(root->right);
                root->key = temp->key;
                root->val = temp->val;
                root->right = deleteNode(root->right,temp->key,temp->val);
            }
            else if(root->left!=NULL)
            {
                Node<T1,T2>* temp = root->left;
                *root = *temp;
                free(temp);
            }   
            else if(root->right!=NULL)
            {
                Node<T1,T2>* temp = root->right;
                *root = *temp;
                free(temp);
            }
            else
            {
                Node<T1,T2>* temp = root;
                root = NULL;
                free(temp);
            }
        }   

        if(root==NULL)
            return root;

        root->height = 1 + max(calcHeight(root->left),calcHeight(root->right));

        ll b = balanceFactor(root);

        if(b < -1)
        {
            if(balanceFactor(root->right) > 0)
            {
                root->right = RightRotate(root->right);
                return LeftRotate(root);
            }
            else
                LeftRotate(root);
        } 

        if(b > 1)
        {
            if(balanceFactor(root->left) < 0)
            {
                root->left = LeftRotate(root->left);
                return RightRotate(root);
            }
            else
                RightRotate(root);
        } 
        return root;
    }

    // Inorder traversal function
    void inorder(Node<T1,T2>* node, vector<T1>& ans)
    {
        if(node==NULL)
            return;
        inorder(node->left, ans);
        ans.push_back(node->key);
        inorder(node->right, ans);
    }

    // Function 1
    bool empty()
    {
        if(cnt==0)
            return true;
        else
            return false;
    }

    // Function 2
    ll size()
    {
        return cnt;
    }

    // Function 3
    bool contains(T1 x)
    {
        bool f = false;
        search(root,x,f);
        return f;
    }

    // Function 4
    bool insert(T1 x, T2 y)
    {
        bool f = false;
        root = insertNode(root,x,y,f);
        if(f)
            cnt++;
        return f;
    }

    // Function 5
    bool erase(T1 x)
    {
        if(!contains(x))
            return false;
        else
        {
            Node<T1,T2>* node = search2(root,x);
            // bool f = false;
            root = deleteNode(root,node->key,node->val);
            // if(f)
            //     cnt--;
            // return f;
            cnt--;
            return true;
        }
    }

    // Function 6
    T2 &operator[](T1 x)
    {
        Node<T1,T2>* node = search2(root,x);
        return node->val;
    }

    // Function 7
    vector<T1> keys()
    {
        vector<T1> ans;
        inorder(root,ans);
        return ans;
    }

    // Function 8
    void clear()
    {
        vector<T1> vec = keys();
        for(auto v: vec)
        erase(v);
        cnt=0;
    }

    // Function 9
    pair<bool,T1> lower_bound(T1 x)
    {
        Node<T1,T2>* lb = NULL;
        Node<T1,T2>* node = root;
        while(node!=NULL)
        {
            if(node->key >= x)
            {
                lb = node;
                node = node->left;
            }
            else
                node = node->right;
        }
        if(lb==NULL)
            return {false, T1()};
        else
            return {true, lb->key};
    }

    // Function 10
    pair<bool,T1> upper_bound(T1 x)
    {
        Node<T1,T2>* ub = NULL;
        Node<T1,T2>* node= root;
        while(node!=NULL)
        {
            if(node->key > x)
            {
                ub = node;
                node = node->left;
            }
            else
                node = node->right;
        }
        if(ub==NULL)
            return {false, T1()};
        else
            return {true, ub->key};
    }
};

int main()
{
Map<int,string> mp;
while(1)
{
    int ch;
    cin>>ch;

    switch (ch)
    {
        case 0:
            return 0;
        case 1:
            cout<<boolalpha<<mp.empty()<<"\n";
            break;
        case 2:
            cout<<mp.size()<<"\n";
            break;
        case 3:
        {
            int key;
            cin>>key;
            cout<<boolalpha<<mp.contains(key)<<"\n";
            break;
        }
        case 4:
        {
            int key;
            string val;
            cin>>key>>val;
            cout<<boolalpha<<mp.insert(key,val)<<"\n";
            break;
        }
        case 5:
        {
            int key;
            cin>>key;
            cout<<boolalpha<<mp.erase(key)<<"\n";
            break;
        }

        case 6:
        {
            int key;
            cin>>key;
            cout<<mp[key]<<"\n";
            break;
        }
        case 7:
            mp.clear();
            break;
        case 8:
        {
            vector<int> vec = mp.keys();
            for(ll i=0;i<vec.size();i++)
            cout<<vec[i]<<" ";
            cout<<"\n";
            break;
        }
        case 9:
        {
            int key;
            cin>>key;
            pair<bool,int> p = mp.lower_bound(key);
            if(p.first)
                cout<<boolalpha<<p.first<<"\n"<<p.second<<"\n";
            else
                cout<<boolalpha<<p.first<<"\n";
            break;
        }
        case 10:
        {
            int key;
            cin>>key;
            pair<bool,int> p = mp.upper_bound(key);
            if(p.first)
                cout<<boolalpha<<p.first<<"\n"<<p.second<<"\n";
            else
                cout<<boolalpha<<p.first<<"\n";
            break;
        }
        default:
            return 0;
        }
    }
    return 0;
}