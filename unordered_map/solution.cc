#include <iostream>
#include <sstream>
#define ll long long
using namespace std;

template<typename T>
class vector
{
private:
    T* arr;  // Pointer to the dynamic array.
    ll cap;     // Capacity of the array.
    ll curr;    // Current number of elements.
public:
    /*
    Constructors:
    Default: Initializes empty vector.
    Parametrized: Initializes with a fixed capacity.
    */
    vector()
    {
        cap = 0;
        curr = 0;
        arr = new T[0];
    }
    vector(ll num)
    {
        cap = num;
        curr = num;
        arr = new T[num];
    }

    /*
    push_back:
    If capacity is 0, allocate 1.
    If array is full, doubles capacity and copies elements.
    */
    void push_back(T num)
    {
        if(cap==0)
        {
            cap = 1;
            T *newarr = new T[cap];
            arr = newarr;
            newarr = NULL;

        }
        else if(cap==curr)
        {
            cap *= 2;
            T *newarr = new T[cap];
            for(ll i=0;i<cap;i++)
            newarr[i] = arr[i];
            delete[] arr;
            arr = newarr;
            newarr = NULL;
        }
        arr[curr] = num;
        curr++;
    }

    // pop_back: Removes last element (decreases curr)
    void pop_back()
    {
        if(curr != 0)
            curr--;
    }

    ll size()
    {
        return curr;
    }
    ll capacity()
    {
        return cap;
    }
    T &operator[](ll i)
    {
        return arr[i];
    }
    ll back()
    {
        return arr[curr-1];
    }   
};


template< class T1, class T2>
class unorderedmap 
{
public:
	class Node 
	{
	public:
		T1 key;
		T2 val;
		Node* next;

		Node()
		{
			key = 0;
			val = 0;
			next = NULL;
		}
		Node(T1 x, T2 y) 
		{
			key = x;
			val = y;
			next = NULL;
		}
	};
	
	ll cnt=0;
	ll cap;
	double dlf = 1; // dlf -> load factor threshold

	// Multiplicative hashing

    /*
    - Converts the key to a string using a string stream.
    - This allows the hash function to operate on the string representation of any key type T1.
    - l is the length of the string s.
    - ha is initialized with the length. It will accumulate the hash value.
    - The shifting and XOR operations spread entropy, helping reduce collisions.
    - It follows a variation of the Mixing Hash technique: it blends the current hash with new information (character + shifted version).
    - This final step ensures the hash value is within bounds [0, m-1], which is required to index into the array of buckets (of size m).
    */
	ll hash(T1 key, ll m) 
	{
		ostringstream input;
        input<<key;
        string s=input.str();
        ll l = s.size();
        ll ha = l;
        for(ll i=0; i<l; i++)
        {
            ha <<= 7;
            ha ^= (ha >> 25);
            ha ^= s[i];
        }
        return ha % m;
	}
public:
	vector<Node*> vec;
    /*
    - Initializes the hash table with 5 empty buckets (each a nullptr).
    - Sets up the basic structure for storing key-value pairs using separate chaining (where collisions are handled by linked lists).
    */
	unorderedmap()
	{
		cap = 5;
		vec = vector<Node*>(cap);
	}

	// function 1
    /*
    - It returns true if the key was successfully inserted.
    - It returns false if the key already exists (duplicate key).
    - Computes the hash of key and reduces it modulo cap (number of buckets).
    - This gives the index (pos) in the vec array where this key should be inserted.
    - Traverse the linked list at vec[pos].
    - If a node with the same key is found, return false — no duplicate keys allowed.
    - Creates a new node with the given key and value.
    - Inserts it at the head of the linked list at vec[pos] (common technique in separate chaining).
    - Updates the bucket's head to point to the new node.
    - Increments cnt, the count of stored key-value pairs.
    - Computes the load factor = number of elements / number of buckets.
    - If it exceeds the threshold dlf (default load factor = 1), it triggers rehashing:
      - Doubles the capacity.
      - Re-distributes all existing elements into the new buckets.
    */
	bool insert(T1 key, T2 val) 
	{
		ll pos = hash(key,cap);
		Node* head = vec[pos];
		while(head!=NULL) 
		{
			if(head->key == key) 
			{
				// head->val = val;
				// return true;
				return false;
			}
			head = head->next;
		}
		Node* nnode = new Node(key, val);
		head = vec[pos];
		nnode->next = head;
		vec[pos] = nnode;
		cnt++;
		double lf = (1.0*cnt)/cap;
		if(lf > dlf) 
			rehash();
		return true;
    }

    /*
    - This function doubles the capacity of the hash table and re-inserts all existing key-value pairs into the newly sized hash table.
    - Copies the current vector of buckets (vec) into a temporary vector temp.
    - We'll use this to access all existing elements before we rebuild the hash table.
    - cap *= 2: Doubles the number of buckets.
    - Creates a new vector vec of size cap, with all entries initialized to NULL.
    - Resets cnt = 0 since we will re-insert all nodes and count them again.
    - Loops over every old bucket in the temp hash table.
    - For each node in each linked list:
        - Extract the key and value.
        - Call insert(key, val) to re-insert it into the new (larger) table using the updated hash. 
    */

    void rehash() 
	{
		vector<Node*> temp = vec;
		cap *= 2;
		vec=vector<Node*>(cap);
		for(ll i=0; i<cap; i++) 
		vec[i] = NULL;
	    cnt = 0;
        for(ll i=0; i<temp.size(); i++) 
		{
			Node* head = temp[i];
		    while (head != NULL) 
			{
				T1 key = head->key;
				T2 val = head->val;
				insert(key, val);
				head = head->next;
		    }
	    }
	}

	// function 2
    /*
    - Uses the hash function to find the bucket index for key x in the hash table.
    - If the bucket is empty (NULL), the key does not exist → return false.
    - check if there's a chain (more than one node)
    - delete the matched index
    - If only one node in the bucket and its key matches x, delete it.
    */
	bool erase(T1 x)
    {
        ll pos = hash(x,cap);
        if(vec[pos]!=NULL)
        {
            Node* p = vec[pos];
            if(p->next!=NULL)
            {
                Node* q;
                while(p!=NULL)
                {
                    if(p->key == x)
                    {
                        q->next = p->next;
                        free(p);
                        cnt--;
                        return true;
                    }
                }
            }
            else
            {
                if(p->key == x)
                {
                    vec[pos] = NULL;
                    free(p);
                    cnt--;
                    return true;
                }
            }
        }
        else
        {
            return false;
        }
    }

	// function 3
    /*
    - The function uses a custom hash function to compute the index (pos) where the key x would be located in the hash table (vec), 
      which is a vector<Node*>.
    - If the bucket at index pos is empty, the key is definitely not present → return false.
    - Start with the head node (p) of the linked list at the given bucket.
    - Traverse the list node by node.
    - If a node's key matches x, return true.
    - If the traversal completes without finding x, return false.
    */
	bool contains(T1 x)
    {
        ll pos = hash(x,cap);
        if(vec[pos]!=NULL)
        {
            Node* p = vec[pos];
            while(p!=NULL)
            {
                if(p->key == x)
                    return true;
                p = p->next;
            }
            return false;
        }
        else
            return false;
    }

	// function 4
    /*
    - Check: If the key x already exists in the map (using the contains method).
    - Find and Return: Traverse the linked list at the hashed bucket to find the matching key 
      and return a reference to its value (p->val).
    - Create New Node: If the key is not present, insert a new node with:
        - key = x
        - value = T2() → default constructor of the value type
    - Store it: Place the new node at index pos in the hash table.
    - Return: A reference to the default-initialized value.
    */

	T2 &operator[](T1 x)
    {
		if(contains(x))
		{
			ll pos = hash(x,cap);
			Node* p = vec[pos];
			Node* q;
			while(p!=NULL)
			{
				if(p->key == x)
					return p->val;
				p = p->next;
			}
		}
        else
		{
			ll pos = hash(x, cap);
			Node* newNode = new Node(x, T2());  
			vec[pos] = newNode;
			return newNode->val;
		}
    }

	// function 5
	void clear()
	{
		cap = 0;
		vec = vector<Node*>(cap);
		cnt = 0;	
	}

	// function 6
	ll size()
    {
        return cnt;
    }

	// function 7
	bool empty()
    {
        if(cnt==0)
            return true;
        else
            return false;
    }

	// function 8
    /*
    - Returns: A vector<T1> containing all the keys present in the hash table.
    - T1 is the key type.
    - Loop over each bucket in the hash table (vec).
    - Traverse the linked list in each bucket (to handle collisions via chaining).
    */
   
	vector<T1> keys()
	{
		vector<T1> ans;
		ll pos = 0;
		while(pos < cap)
		{
			Node* p = vec[pos];
			Node* q;
			while(p!=NULL)
			{
				ans.push_back(p->val);
				p = p->next;
			}
			pos++;
		}
		return ans;
	}
	
};

int main()
{
    int q;
    cin>>q;
    unorderedmap<int,int> mp;

    while(q--)
    {
        int ch;
		cin>>ch;
        if(ch==1)
        {
			// insert
			int key, val;
			cin>>key>>val;
			cout<<boolalpha<<mp.insert(key,val)<<"\n";
        }
        else if(ch==2)
        {
            // erase
			int key;
			cin>>key;
			cout<<boolalpha<<mp.erase(key)<<"\n";
        }
        else if(ch==3)
        {
            // Contains
			int key;
			cin>>key;
			cout<<boolalpha<<mp.contains(key)<<"\n";
        }
        else if(ch==4)
        {
            // map
            int key;
			cin>>key;
			cout<<mp[key]<<"\n";
        }
        else if(ch==5)
        {
            // Clear
            mp.clear();
        }
        else if(ch==6)
        {
            // Size
            cout<<mp.size()<<"\n";
        }
        else if(ch==7)
        {
			// empty
            cout<<boolalpha<<mp.empty()<<"\n";
        }
        else if(ch==8)
        {
            // Keys
			vector<int> vec;
			vec = mp.keys();
            for(int i=0;i<vec.size();i++)
			cout<<vec[i]<<" ";
			cout<<"\n";
        }
    }
    return 0;
}