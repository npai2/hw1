using namespace std;
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <sstream>

struct Item {
  Item(int v, Item* n) { val = v; next = n; }
  int val;
  Item* next;
};

Item* concatenate(Item* head1, Item* head2);  // returns head pointer to new list
void removeEvens(Item*& head);	// removes even numbers
double findAverage(Item* head); // finds average of all numbers 
int _findAverageHelper(Item* head, int &x, int &y);
void readLists(ifstream& ifile, Item*& head1, Item*& head2);
void printList(ostream& ofile, Item* head);



void printList(ostream& ofile, Item* head)
{
  if(head == NULL)
    ofile << std::endl;
  else {
    ofile << head->val << " ";
    printList(ofile, head->next);    
  }
}

void readLists(ifstream& ifile, Item*& head1, Item*& head2)
{
	string str1, str2;
	getline(ifile, str1);
	getline(ifile, str2);
	stringstream ss;
	ss << str1;
	if(!str1.empty())
	{
		Item *newItem;
		int a;
		ss >> a;
		head1 = new Item(a, NULL);
		Item *dummy = head1;
		int x;
		ss >> x;
		while(ss){
			newItem = new Item(x, NULL);
			dummy->next = newItem;
			dummy = newItem;
			ss >> x;
		}
	}
	stringstream ss2;
	ss2 << str2;
	if(!str2.empty())
	{
		Item *newItem2;
		int b;
		ss2 >> b;
		head2 = new Item(b, NULL);
		Item *dummy2 = head2;
		int y;
		ss2 >> y;
		while(ss2){
			newItem2 = new Item(y, NULL);
			dummy2->next = newItem2;
			dummy2 = newItem2;
			ss2 >> y;
		}
	}
	return;


	}

Item* concatenate(Item* head1, Item* head2)
{
	if(!head1 && !head2)
	{
		return NULL;
	}
	else if(!head1)
	{
		return head2;
	}
	else if(!head2)
		return head1;
	else if(head1->next)
		concatenate(head1->next, head2);
	else
	{
		head1->next = head2;
	}
	return head1;
}



void removeEvens(Item*& head)
{
	if(!head)
	{
		return;
	}
	else if(!head->next)
	{
		if(head->val%2 == 0)
		{	
			head = NULL;
			return;
		}
	}
	else if(head->val%2 == 0)
	{	
		head = head->next;
		removeEvens(head);
	}
	else
	{
		removeEvens(head->next);
	}

	return;

}


double findAverage(Item* head)
{
	if(head==NULL)
		{
			return 0.0;
		}
	int x = 0;
	int y = 0;
	_findAverageHelper(head, x, y);
	double avg = static_cast<double>(x)/y;
	return avg;
}

int _findAverageHelper(Item* head, int &x, int &y)
{
	x = x + head->val;
	y++;
	if(head->next)
	{
		_findAverageHelper(head->next, x, y);
	}
	return x;
}



int main(int argc, char* argv [])
{
	Item *head1, *head2, *head3;
	head1 = NULL;
	head2 = NULL;
	head3 = NULL;
	ifstream myFile;
	myFile.open(argv[1]);
	if(myFile.fail()) {
		cerr << "File didn't open" << endl;
	}
	readLists(myFile, head1, head2);

	ofstream oFile;
	oFile.open(argv[2]);
	
	printList(oFile, head1);
	printList(oFile, head2);

	
	head3 = concatenate(head1, head2);

	printList(oFile, head3);
	
	removeEvens(head3);
	printList(oFile, head3);
	cout << findAverage(head3) << endl;
	oFile.close();
	myFile.close();
	//cout << "compile" << endl;
	
	/*while(head1)
	{
		Item *iterator = head1;
		head1 = head1->next;
		delete iterator;
	}
	while(head2)
	{
		Item *iterator = head2;
		head2 = head2->next;
		delete iterator;
	}

	while(head3)
	{
		Item *iterator = head3;
		head3 = head3->next;
		delete iterator;
	}*/


	return 0;

}