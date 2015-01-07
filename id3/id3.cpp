#include <stdio.h>
#include <iostream>
#include <memory.h>
#include <math.h>
#include <queue>
#include <vector>

using namespace std;

#define dataNum 12

bool exist[dataNum];
bool used[3];
int data[dataNum][3];
int dataRet[dataNum];

double cal(double tt) {
	return - tt * log10(tt) / log10(2);
}

double entropy(double t1, double t2) {
	return cal(t1) + cal(t2);
}

double QS(int x) {
	double sum = 0;
	double ans = 0;
	int cnt[3][2];
	memset(cnt, 0, sizeof(cnt));
	for(int i = 0;i < dataNum;i ++) {
		if(true == exist[i])
			continue;
		sum += 1;
		cnt[data[i][x]][dataRet[i]] ++;
	}
	for(int i = 0 ;i < 3;i++) {
		double tt = cnt[i][0] + cnt[i][1];
		ans += tt / sum * entropy(cnt[i][0] / tt, cnt[i][1] / tt);
	}
	return ans;
}

class Node {
	public:
	Node * next[3];
	bool isResult;
	int Result;
	int cnt[2], feature;

	void init() {
		for(int i = 0 ;i < 3;i ++)
			next[i] = NULL;
		cnt[0] = cnt[1] = 0;
		feature = 0;
	}

	void Build() {
		init();

		for(int i = 0 ;i < dataNum; i++)
			if(false == exist[i])
				cnt[dataRet[i]] ++;

		for(int i = 0 ;i < 3;i ++)
			if(false == used[i])
				feature ++;

		if(0 == cnt[0]) {
			isResult = true;
			Result = 1;
			return ;
		}
		if(0 == cnt[1]) {
			isResult = true;
			Result = 0;
			return ;
		}
		
		if(0 == feature) {
			isResult = true;
			if(cnt[0] > cnt[1])
				Result = 0;
			else
				Result = 1;
			return ;
		}

		Result = findBest();
		cout << "quxiao" << Result << endl;

		isResult = false;
		used[Result] = true;
	//	cout << "xinjian fenzhi" << endl;
		for(int i = 0 ;i < 3;i ++) {
			next[i] = new Node();
			vector<int> tem;
			for(int f = 0; f < dataNum; f++)
				if(false == exist[f] && data[f][Result] != i) 
					tem.push_back(f);

			for(int f = 0;f < tem.size() ;f++)
				exist[tem[f]] = true;
	//		cout << "goto " << i << endl;
			next[i]->Build();
			for(int f = 0;f < tem.size() ;f++)
				exist[tem[f]] = false;
		}
		used[Result] = false;
	}

	int findBest() {
		int E[3];
		E[0] = E[1] = E[2] = 2;
		for(int i = 0;i < 3;i ++) {
			if(true == used[i])
				continue;
			E[i] = QS(i);
		}
		double minn = min(min(E[0], E[1]), E[2]);
		for(int i = 0 ;i < 3;i ++)
			if(minn == E[i])
				return i;
	}
};

void read() {
	for(int i = 0;i < dataNum;i ++) {
		for(int f = 0;f < 3 ;f++) {
			cin >> data[i][f];
			data[i][f] --;
		}
		cin >> dataRet[i];
	}

	memset(exist, false, sizeof(exist));
	memset(used, false, sizeof(used));
}

int getAns(int id, Node* Root) {
	if(Root->isResult == true)
		return Root->Result;
	return getAns(id, Root->next[data[id][Root->Result]]);
}

void test(Node * Root) {
	int sum = 0;
	for(int i = 0;i < dataNum; i++) {
		cout << i << " " << getAns(i, Root) << endl;
		if(getAns(i, Root) == dataRet[i])
			sum ++;
	}
	cout << "success " << sum << endl;
}

int main() {
	freopen("data", "r", stdin);
	read();
	Node * Root = new Node();
	Root->Build();
	test(Root);
	return 0;
}
