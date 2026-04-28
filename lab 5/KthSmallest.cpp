// K-th Smallest: Finds k-th smallest element using selection strategy. Time Complexity: O(n) average with quickselect.
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> vertices;

int getDistance(vector<int> &a, vector<int> &b, vector<int> &c) {
    return (a[0]*(b[1]-c[1])) - (b[0]*(a[1]-c[1])) + (c[0]*(a[1]-b[1]));
}

vector<vector<int>> getLeftList(vector<int> &p1, vector<int> &p2, vector<vector<int>> &points) {
    vector<vector<int>> temp;

    for (auto &pt : points) {
        if (getDistance(p1, p2, pt) > 0) temp.push_back(pt);
    }

    return temp;
}

vector<int> getFarthest(vector<vector<int>> &points, vector<int> &p1, vector<int> &p2) {
    vector<int> far;
    int dist = 0;

    for (auto &pt : points) {
        int d = getDistance(p1, p2, pt);
        if (d > dist) {
            dist = d;
            far = pt;
        }
    }

    return far;
}

void solveRec(vector<int> &p1, vector<int> &p2, vector<vector<int>> &points) {
    if (points.empty()) return;

    vector<int> far = getFarthest(points, p1, p2);
    vertices.push_back(far);

    vector<vector<int>> left1 = getLeftList(p1, far, points);
    vector<vector<int>> left2 = getLeftList(far, p2, points);

    solveRec(p1, far, left1);
    solveRec(far, p2, left2);
}

vector<vector<int>> solve(vector<vector<int>> &points) {
    vertices.clear();

    vector<int> minX = points[0], maxX = points[0];

    for (auto &pt : points) {
        if (pt[0] < minX[0]) minX = pt;
        if (pt[0] > maxX[0]) maxX = pt;
    }

    vertices.push_back(minX);
    vertices.push_back(maxX);

    vector<vector<int>> left = getLeftList(minX, maxX, points);
    vector<vector<int>> right = getLeftList(maxX, minX, points);

    solveRec(minX, maxX, left);
    solveRec(maxX, minX, right);

    return vertices;
}

int main() {
    vector<vector<int>> points = {
        {1,1},{1,3},{-1,2},{3,1},{0,0},{-21,21}
    };

    vector<vector<int>> hull = solve(points);

    for (auto &p : hull) {
        cout << "(" << p[0] << "," << p[1] << ") ";
    }

    return 0;
}
