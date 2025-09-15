#include <iostream>
#include <string>
using namespace std; 

class Hanoi  {
public:
	Hanoi();
	void StartToDest(string s, string A1, string A2, string A3, string d, int n);
	void StartToA3(string s, string A1, string A2, string A3, int n);
	void twoHops(string A1, string A2, string A3, int n);
	void oneHop(string A1, string A2, string A3, int n);
	void A1ToDest(string A1, string A2, string A3, string d, int n);
	int count;
	void move(string from, string to, int disk);
};

int main() {
	int disks = 0;
	cout << "Enter number of disks: ";
	cin >> disks;
	Hanoi obj;
	obj.StartToDest("Start", "A1", "A2", "A3", "Dest", disks);
	cin.ignore();
	cin.get();
	return 0;
}

Hanoi::Hanoi() {count = 0;}

void Hanoi::StartToDest(string s, string A1, string A2, string A3, string d, int n) { //move from start to dest using start
	if (n == 1){ //move n to dest 
		move(s, A1, n);
		move(A1, A2, n);
		move(A2, A3, n);
		move(A3, d, n);
	} else if (n >= 2) {
		StartToA3(s, A1, A2, A3, n - 1); //move n-1 to A3 using start, ignore dest
		move(s, A1, n);
		move(A1, A2, n); //move n to A2
		oneHop(A3, A1, A2, n - 1); //move n-1 to A1, ignore start and dest
		move(A2, A3, n); //move n to dest
		move(A3, d, n);
		A1ToDest(A1, A2, A3, d, n - 1); //move n-1 from A1 to dest, ignore start
	}
}

void Hanoi::StartToA3(string s, string A1, string A2, string A3, int n) {
	if (n == 1) {
		move(s, A1, 1);
		move(A1, A2, 1);
		move(A2, A3, 1);
	} else if (n >= 2) {
		StartToA3(s, A1, A2, A3, n - 1); //send n-1 to A3
		move(s, A1, n); //move bottom n to A2
		move(A1, A2, n);
		oneHop(A3, A1, A2, n - 1); //move n-1 to A1, ignore start and dest
		move(A2, A3, n);
		twoHops(A1, A2, A3, n - 1); //move n-1 from A1 to A3, ignore start and dest
	}
}

void Hanoi::twoHops(string A1, string A2, string A3, int n) { //moves n-1 to A1, ignoring start and dest
	if (n == 1) {
		move(A1, A2, n);
		move(A2, A3, n);
	} else if (n >= 2) {
		twoHops(A1, A2, A3, n - 1);//move n-1 to A2
		move(A1, A2, n);
		oneHop(A3, A1, A2, n - 1);//move n-1 from A3 to A1
		move(A2, A3, n);
		twoHops(A1, A2, A3, n - 1);//move n-1 from A1 to A3
	}	
}

void Hanoi::A1ToDest(string A1, string A2, string A3, string d, int n) { //moves n-1 from A1 to dest, ignoring start
	if (n == 1) {
		move(A1, A2, n);
		move(A2, A3, n);
		move(A3, d, n);
	} else if (n >= 2) {
		twoHops(A1, A2, A3, n - 1); //move n-1 from A1 to A3
		move(A1, A2, n); //move n to A2
		oneHop(A3, A1, A2, n - 1); //move n-1 from A3 to A1
		move(A2, A3, n); //move n to d
		move(A3, d, n);
		A1ToDest(A1, A2, A3, d, n - 1); //move n-1 from A1 to Dest
	}
}

void Hanoi::oneHop(string A1, string A2, string A3, int n) {
	if (n == 1) { move(A1, A2, 1);
    }
	else if (n >= 2)
	{
		twoHops(A1, A2, A3, n - 1);//move n-1 to A3
		move(A1, A2, n);
		twoHops(A3, A1, A2, n - 1);//move n-1 to A2
	}
}


/*void Hanoi::move(string from, string to, int disk)
{
	count++;
	cout <<count<<": "<< "Move disk" << disk << "from " << from << " to " << to << endl;
} */
void Hanoi::move(string from, string to, int disk)
{
    count++;
    cout << count << ": Move disk " << disk << " from " << from << " to " << to << endl;
}


