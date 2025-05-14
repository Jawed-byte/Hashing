#include <iostream>
#include <sstream>
#define ll long long
using namespace std;

template<typename T>
class vector
{
private:
    T* arr;
    ll cap;
    ll curr;
public:
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
	double dlf = 1;

	// Multiplicative hashing
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
	unorderedmap()
	{
		cap = 5;
		vec = vector<Node*>(cap);
	}

	// function 1
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