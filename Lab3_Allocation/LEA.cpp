#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class l {
public:
	int n;		//編號
	int start;	//開始時間
	int end;	//結束時間
	int reg;	//register
};

int main(void) {
	fstream file;
	int n, i, start, end;
	
	//讀檔 
	file.open("test.txt", ios::in);
	file >> n;  //數量
	vector<l> L(n);
	for(i = 0; i < n; ++i) {
		file >> start >> end;
		L[i].n = i + 1;
		L[i].start = start;
		L[i].end = end;
		L[i].reg = -1;
	}
	file.close();
	
	//以start time由小排到大
	l temp;
	for(i = 0; i < n-1; ++i) {
		for(int j = i+1; j < n; ++j) {
			if((L[i].start>L[j].start) || ((L[i].start==L[j].start)&&(L[i].n > L[j].n))) {
				temp = L[i];
				L[i] = L[j];
				L[j] = temp;
			}
		}
	}
	
	//Left-Edge Algorithm
	vector<int> MAP(n);
	int reg_index = 0;
	int last;
	while(L.size()) {
		++reg_index;
		last = 0;
		for(i = 0; i < L.size(); ++i) {
			if(L[i].start >= last) {
				MAP[L[i].n-1] = reg_index;
				last = L[i].end;
				L.erase(L.begin()+i);
			}
		}
	}
	
	//print
	int s = MAP.size();
	for(int reg = 1; reg <= reg_index; ++reg) {
		cout << "r" << reg << ": ";
		for(i = 0; i < s; ++i) {
			if(MAP[i] == reg) {
				cout << i + 1 << " ";
			}
		}
		cout << endl;
	}
	
	return 0;
}

