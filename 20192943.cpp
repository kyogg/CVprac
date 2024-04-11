#include <iostream>
#include <stack>
#include <utility>
#include <cmath>

using namespace std;

void polygon(pair<int, int> p1, pair<int, int> p2, stack<pair<int, int>> pStack, stack<pair<int, int>>* bStack, double limit, bool close = false) {
	double exDis;
	double distance = limit;
	int x1 = p1.first;
	int x2 = p2.first;
	int y1 = p1.second;
	int y2 = p2.second;
	int count = 0;
	stack <pair<int, int>> newPStack = pStack;
	while (!(newPStack.top() == p1)) {
		newPStack.pop();
	}
	while (!(newPStack.top() == p2)) {
		exDis = (newPStack.top().first * (y1 - y2) - newPStack.top().second * (x1 - x2) + (y2 * x1) - (y1 * x2)) / sqrt(pow(y1 - y2, 2) + pow((x1 - x2), 2));

		if (exDis < 0)
			exDis *= (-1);
		if (exDis > distance) {
			distance = exDis;
			for (int i = 0; i < count; i++) {
				bStack->pop();
			}
			count = 0;
			bStack->push(newPStack.top());
			count++;
		}
		else if (exDis == distance) {
			bStack->push(newPStack.top());
			count++;
		}
		newPStack.pop();
	}

	if (distance == limit) {

		//exDis == limit
		for (int j = 0; j < count; j++) {
			bStack->pop();
		}
		bStack->pop();
		cout << "(" << p2.first << "," << p2.second << ") ";
		if (bStack->empty()) {
			if (close == false)
				cout << "(" << p1.first << "," << p1.second << ") ";
		}
		else {
			polygon(bStack->top(), p1, pStack, bStack, limit, close);
		}
	}
	else {
		polygon(bStack->top(), p2, pStack, bStack, limit, close);
	}
}

int main(void) {
	int size;
	int n, m, x1, y1, x2, y2, limit, fx, fy; //x1~y2 = 첫 중단점 좌표, fx,fy = 닫힌모양인지 판별
	stack<pair<int, int>> pStack;
	stack<pair<int, int>> bStack;
	
	cout << "점의 갯수 : ";
	cin >> size;
	cout << "점 입력 : "; //시작점부터 이어지게 입력
	for (int i = 0; i < size; i++) {
		cin >> n >> m;
		if (i == 0) {
			fx = n;
			fy = m;
		}
		pStack.push(make_pair(n, m));
	}
	cout << "중단점 입력 : "; //하나는 시작점
	cin >> x1 >> y1 >> x2 >> y2;
	pair<int, int> p1(x1, y1);
	pair<int, int> p2(x2, y2);
	bStack.push(p2);
	cout << "임계값 입력 : ";
	cin >> limit;

	if ((fx - pStack.top().first) >= -1 && (fx - pStack.top().first) <= 1) {
		if ((fy - pStack.top().second) >= -1 && (fy - pStack.top().second) <= 1) {
			pStack.push(make_pair(fx, fy));
			polygon(p2, p1, pStack, &bStack, limit, true);
			bStack.push(p1);
			polygon(p1, p2, pStack, &bStack, limit, true);
		}
		else
			polygon(p2, p1, pStack, &bStack, limit);
	}
	else
		polygon(p2,p1, pStack, &bStack, limit);
	
	cout << endl;
	return 0;
}