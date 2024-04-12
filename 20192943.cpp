#include <iostream>
#include <cmath>

using namespace std;

struct point {
    int x;
    int y;
    int idx;
};

bool compareP(const point p1, const point p2) {
    return p1.x == p2.x && p1.y == p2.y;
}

void printPoint(const point p) {
    cout << "(" << p.x << "," << p.y << ") ";
} 

bool isClosedCurve(const point p1, const point p2) {
    return abs(p1.x - p2.x) <= 1 && abs(p1.y - p2.y) <= 1;
}

double exDistance(const point p1, const point p2, const point middle) {
    return abs(middle.x * (p1.y - p2.y) - middle.y * (p1.x - p2.x) + (p2.y * p1.x) - (p1.y * p2.x)) / sqrt(pow(p1.y - p2.y, 2) + pow((p1.x - p2.x), 2));
}

void polygonApprox(const int m, const point C[], const int startIdx, const int endIdx, const double TH) {
    int pEndIdx, breakPointIdx;
    double distance = 0;
    bool isClosed = false;

    if(endIdx - startIdx + 1 == m) {
        printPoint(C[startIdx]);
    }

    if (isClosedCurve(C[startIdx], C[endIdx])) {
        pEndIdx = (startIdx + endIdx)/2;
        isClosed = true;
    }
    else{
        pEndIdx = endIdx;
    }

    for (int i = startIdx; i < pEndIdx + 1; i++) {
        double exDis = exDistance(C[startIdx], C[pEndIdx], C[i]);
        if (distance < exDis) {
            distance = exDis;
            breakPointIdx = i;
        }
    }

    if (distance > TH) {
        polygonApprox(m, C, startIdx, breakPointIdx, TH);
        printPoint(C[breakPointIdx]);
        polygonApprox(m, C, breakPointIdx, pEndIdx, TH);
    }

    if (isClosed) {
        printPoint(C[pEndIdx]);
        polygonApprox(m, C, pEndIdx, endIdx, TH);
    }
    else if (endIdx - startIdx + 1 == m) {
        printPoint(C[endIdx]);
    }

    return;
}

int main(void) {
    int m, x, y;
    point *C;
    double TH;

    cout << "점의 갯수 입력 : ";
    cin >> m;
    C = (point *)malloc(sizeof(point) *m);
    cout << "점 입력 : ";
    for (int i = 0; i < m; i++){
        cin >> C[i].x; 
        cin >> C[i].y;
        C[i].idx = i;
    }
    cout << "임계값 입력 : ";
    cin >> TH;

    polygonApprox(m, C, 0, m - 1, TH);
    delete[] C;
    return 0;
}
