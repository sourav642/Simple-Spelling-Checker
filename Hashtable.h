//Simple code for a spell Checker
//@author-Sourav
#include<bits/stdc++.h>
using namespace std;
#define SIZE 100

template <class Items>
class HashTable
{
public:
	HashTable(int hashSze = SIZE);
	bool isEmpty(int key);

	bool  isFull();

	int keygen(Items newItem);

	void insert(Items newItem);

	void append(int key, Items newItem);

	bool remove(Items deleteItem, int key = -1);

	int table_size();

	int total_elements();

	int bsize(int key);

	int search_table(Items searchItem);

	void clear();

	~HashTable();

	class Iterator;


	Iterator begin(int key)
	{
	    return(!isEmpty(key)) ? head[key]:NULL;
	}


	Iterator end(int key=0)
	{
	    return NULL;
    }

private:
	struct list_node
	{
		Items currentItem;
		list_node* next;
	};
	list_node** head; // array of linked list
	int hashSize;
	int totElems;
	int* bucket_size;
};

template<class Items>
HashTable<Items>::HashTable(int hashSze)
{
	hashSize = hashSze;
	head = new list_node*[hashSize];
	bucket_size = new int[hashSize];
	for(int x=0; x < hashSize; ++x)
	{
		head[x] = NULL;
		bucket_size[x] = 0;
	}
	totElems = 0;
}

template<class Items>
bool HashTable<Items>::isEmpty(int key)
{
	if(key >=0 && key < hashSize)
	{
		return head[key] == NULL;
	}
	return true;
}

template<class Items>
bool HashTable<Items>::isFull()
{
	try
	{
		list_node* location = new list_node;
		delete location;
		return false;
	}
	catch(bad_alloc&)
	{
		return true;
	}
}

template<class Items>
int HashTable<Items>::keygen(Items newItem)
{
	long h = 19937;//prime number
	stringstream convert;

	/* convert the parameter to a string using "stringstream" for hashing
        with various datatypes*/

	convert << newItem;
	string temp = convert.str();

	for(unsigned x=0; x < temp.length(); ++x)
	{
		h = (h << 6) ^ (h >> 26) ^ temp[x];//simple hash function generating key h
	}
	return abs(h % hashSize);
}

template<class Items>
void HashTable<Items>::insert(Items newItem)
{
	if(isFull())
	{
        cout<<"\nnError:TABLE FULL\n";
	}
	else
	{
		int key = keygen(newItem);
		append(key,newItem);
	}
}

template<class Items>
void HashTable<Items>::append(int key, Items newItem)
{
	if(isFull())
	{
        cout<<"\nERROR:TABLE FULL\n";
	}
	else
	{
		list_node* newNode = new list_node;  // adding a new list_node
		newNode-> currentItem = newItem;
		newNode-> next = NULL;

		if(isEmpty(key))
		{
			head[key] = newNode;
		}
		else
		{
			list_node* tempPtr = head[key];
			while(tempPtr-> next != NULL)
			{
				tempPtr = tempPtr-> next;
			}
			tempPtr-> next = newNode;
		}
		++bucket_size[key];
		++totElems;
	}
}

template<class Items>
bool HashTable<Items>::remove(Items deleteItem, int key)
{
	bool isFound = false;
	list_node* tempPtr;
	if(key == -1)
	{
		key = keygen(deleteItem);
	}

    if(isEmpty(key))
    {
        cout<<"\nnERROR:TABLE EMPTY\n";
    }
    else if(head[key]->currentItem == deleteItem)
    {
        tempPtr = head[key];
        head[key] = head[key]-> next;
        delete tempPtr;
        --totElems;
        --bucket_size[key];
        isFound = true;
    }
    else
    {
        for(tempPtr = head[key];tempPtr->next!=NULL;tempPtr=tempPtr->next)
        {
            if(tempPtr->next->currentItem == deleteItem)
            {
                list_node* deleteNode = tempPtr->next;
                tempPtr-> next = tempPtr-> next-> next;
                delete deleteNode;
                isFound = true;
                --totElems;
                --bucket_size[key];
                break;
            }
        }
    }
	return isFound;
}
template<class Items>
int HashTable<Items>::table_size()
{
    return hashSize;
}
template<class Items>
int HashTable<Items>::total_elements()
{
    return totElems;
}

template<class Items>
int HashTable<Items>::bsize(int key)
{
	return(!isEmpty(key)) ? bucket_size[key]:0;
}

template<class Items>
int HashTable<Items>::search_table(Items searchItem)
{
	int key = keygen(searchItem);
	int find = 0;

        for(list_node* tempPtr = head[key];tempPtr!=NULL;tempPtr=tempPtr->next)
        {
            if(tempPtr->currentItem == searchItem)
            {
                ++find;
            }
        }
    return find;
}

template<class Items>
void HashTable<Items>::clear()
{
    totElems = 0;
    for(int x=0; x < hashSize; ++x)
    {
        if(!isEmpty(x))
        {

            while(!isEmpty(x))
            {
                list_node* temp = head[x];

                head[x] = head[x]-> next;
                delete temp;
            }
        }
        bucket_size[x] = 0;
    }
}

template<class Items>
HashTable<Items>::~HashTable()
{
	clear();
	delete[] head;
	delete[] bucket_size;
}


template <class Items>
class HashTable<Items>::Iterator :
		public iterator<forward_iterator_tag,Items>,
		public HashTable<Items>
	{
public:

	Iterator(list_node* otherIter = NULL)
	{
		itHead = otherIter;
	}
	~Iterator() {}

	Iterator& operator=(const Iterator& other)
	{
		itHead = other.itHead;
		return(*this);
	}
	bool operator==(const Iterator& other)const
	{
		return itHead == other.itHead;
	}
	bool operator!=(const Iterator& other)const
	{
		return itHead != other.itHead;
	}
	bool operator<(const Iterator& other)const
	{
		return itHead < other.itHead;
	}
	bool operator>(const Iterator& other)const
	{
		return other.itHead < itHead;
	}
	bool operator<=(const Iterator& other)const
	{
		return (!(other.itHead < itHead));
	}
	bool operator>=(const Iterator& other)const
	{
		return (!(itHead < other.itHead));
	}

	Iterator operator+(int incr)
	{
		list_node* temp = itHead;
		for(int x=0; x < incr && temp!= NULL; ++x)
		{
			temp = temp->next;
		}
		return temp;
	}
	Iterator operator+=(int incr)
	{
		for(int x=0; x < incr && itHead!= NULL; ++x)
		{
			itHead = itHead->next;
		}
		return itHead;
	}
	Iterator& operator++()
	{
		if(itHead != NULL)
		{
			itHead = itHead->next;
		}
		return(*this);
	}
	Iterator operator++(int)
	{
		list_node* temp = itHead;
		this->operator++();
		return temp;
	}
	Items& operator[](int incr)
	{

		if(itHead == NULL || (*this + incr) == NULL)
		{
			return junk;
		}
		return(*(*this + incr));
	}

	Items& operator*()
	{

		if(itHead == NULL)
		{
			return junk;
		}
		return itHead->currentItem;
	}
	Items* operator->()
	{
		return(&**this);
	}
private:
	list_node* itHead;
	Items junk;
};
