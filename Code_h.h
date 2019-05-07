# include <iostream>
# include <fstream>
const double MAXAGE = 0.95;
const double MINAGE = 0;

struct Node
{
	int nodecode;
	double age;
	Node * next;

};

class list
{
public:
	Node * head;
	list()
	{
		head = new Node;
		head->next = NULL;
	}
	~list();
	void insert(int z);
	int neinumber(void);
	int check(int z);
	int cutoff(int z);
};

list::~list()
{
	Node *p = head->next, *q;
	while (p != NULL)
	{
		q = p->next;
		delete p;
		p = q;
	}
	delete head;
	head = NULL;
}

void list::insert(int z)
{
	Node *s, *q = head;
	s = new Node;
	s->nodecode = z;
	s->age = (double)rand() / RAND_MAX * MAXAGE;
	s->next = q->next;
	q->next = s;
}

int list::neinumber(void)
{
	int number = 0;
	Node *q = head;
	q = head->next;
	while (q != NULL)
	{
		number++;
		q = q->next;
	}
	return number;
}

int list::check(int z)
{
	Node *q = head;
	while (q != NULL)
	{
		if (q->nodecode == z)
		{
			return 1;
		}
		q = q->next;
	}
	return 0;
}

int list::cutoff(int z)
{
	Node *s, *q = head;
	s = q->next;
	while (s != NULL)
	{
		if (s->nodecode == z)
		{
			q->next = s->next;
			delete s;
			return 1;
			break;
		}
		q = s;
		s = s->next;
	}
	return 0;
}
