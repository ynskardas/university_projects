#include <iostream>
#include <fstream>
#include <vector>

#include <queue>
#include <algorithm>

using namespace std;

int globalN;
int globalM;

vector<vector<int>> visited1;
vector<vector<int>> diff;

struct Compare{

public:

    bool operator()(pair<pair<int, int>, int> a, pair<pair<int, int>, int > b)  {

        return a.second > b.second;

    }

};

vector<pair<int, int>> adjVector(pair<int, int> poss){

    vector<pair<int, int>> adj;
    int x = poss.first;
    int y = poss.second;

    if(x - 1 >= 0){

        pair<int, int> p01 = make_pair(x-1, y);
        if(visited1[x-1][y] == 0){
            adj.push_back(p01);
        }

    }

    if(x + 1 <= globalN - 1){

        pair<int, int> p02 = make_pair(x+1, y);
        if(visited1[x+1][y] == 0) {
            adj.push_back(p02);
        }
    }

    if(y - 1 >= 0){

        pair<int, int> p03 = make_pair(x, y-1);
        if(visited1[x][y-1] == 0) {
            adj.push_back(p03);
        }
    }

    if(y + 1 <= globalM - 1){

        pair<int, int> p04 = make_pair(x, y+1);
        if(visited1[x][y+1] == 0) {
            adj.push_back(p04);
        }
    }

    return adj;
}
vector<vector<int>> height;
priority_queue<pair<pair<int, int>, int>, vector<pair<pair<int, int>, int>>, Compare> bfsQ;

int main(int argc,char* argv[]) {

    string input,output;
    input=argv[1];
    output=argv[2];
    ifstream inp(input);

    //ifstream inp("/home/student/ClionProjects/GridLand/large.txt");

    int n;
    int m;

    inp >> n >> m;

    globalN = n;
    globalM = m;

    height.resize(n);

    visited1.resize(n);
    diff.resize(n);

    int h;

    for(int i = 0; i < n ; i++){

        height[i].resize(m);

        visited1[i].resize(m, 0);
        diff[i].resize(m, -1);

        for(int j = 0; j < m; j++){

            inp >> h;
            height[i][j] = h;
        }
    }

    int repeat;

    inp >> repeat;

    int x1, y1, x2, y2;

    ofstream out;
    out.open(output);

    //for(int k = 0; k < repeat; k++){

        inp >> x1 >> y1 >> x2 >> y2;
        x1 = x1 - 1;
        x2 = x2 - 1;
        y1 = y1 - 1;
        y2 = y2 - 1;

        diff[x1][y1] = 0;

        pair<int, int> p0 = make_pair(x1, y1);
        pair<pair<int, int>, int> p1 = make_pair(p0, diff[x1][y1]);
        bfsQ.push(p1);

        while(bfsQ.size()){

            pair<pair<int, int>, int> pairs = bfsQ.top();
            bfsQ.pop();

            pair<int, int> poss = pairs.first;
            int x = poss.first;
            int y = poss.second;

            if(x == x2 && y == y2){

                out << diff[x2][y2] << endl;
                break;
            }
            else{

                if(visited1[x][y] == 0){

                    visited1[x][y] = 1;

                    vector<pair<int, int>> adj;
                    adj = adjVector(poss);

                    for(int i = 0; i < adj.size(); i++){

                        int x0 = adj[i].first;
                        int y0 = adj[i].second;

                        int dif = abs(height[x][y] - height[x0][y0]);

                        if(diff[x0][y0] == -1){

                            diff[x0][y0] = max(diff[x][y], dif);
                        }
                        else{

                            diff[x0][y0] = min(diff[x0][y0], max(diff[x][y], dif));
                        }

                        int d0 = diff[x0][y0];

                        pair<int, int> p20 = make_pair(x0,y0);
                        pair<pair<int, int>, int> p21 = make_pair(p20, d0);

                        bfsQ.push(p21);


                    }

                }
            }
        }
    //}
}