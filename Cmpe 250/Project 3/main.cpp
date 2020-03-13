#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;


vector<vector <int>> mainVec;
vector<vector <int>> mainTrans;
vector<vector<int>> sccStore;
vector<vector <int>> sccVec;
vector<vector <int>> sccTrans;
vector<int> visited;
vector<int> visited2;
stack<int> Stack;
stack<int> CrackScc;
vector<int> store;

int place;

void dfs(int node){

    visited2[node] = 1;

    sccStore[place].push_back(node);

    for(int i = 0; i < mainTrans[node].size(); i++){

        int next = mainTrans[node][i];

        if(visited2[next] == 0){

            dfs(next);

        }

    }

}

void fullyStack(int node){

    visited[node] = 1;

    for(int i = 0; i < mainVec[node].size(); i++){

        int next = mainVec[node][i];
        if(visited[next] == 0){

            fullyStack(next);
        }
    }

    Stack.push(node);

}

int main(int argc,char* argv[]) {

    string input,output;
    input=argv[1];
    output=argv[2];
    ifstream inp(input);


    int n;

    inp >> n;

    mainVec.resize(n);
    mainTrans.resize(n);
    visited.resize(n,0);
    visited2.resize(n,0);
    sccStore.resize(n);

    store.resize(n);

    for(int i = 0; i < n; i++){

        int numOfKey;

        inp >> numOfKey;

        for(int j = 0; j < numOfKey; j++){

            int key;

            inp >> key;

            if(i != key - 1){

                mainVec[i].push_back(key-1);
                mainTrans[key-1].push_back(i);
            }

        }

    }

    for(int i = 0; i < n; i++){

        if(visited[i] == 0){

            fullyStack(i);
        }

    }

    int check = 0;

    while(Stack.size()){

        place = check;

        int a = Stack.top();

        Stack.pop();

        if(visited2[a] == 0){

            dfs(a);
            check++;
        }

    }

    sccStore.resize(check);
    sccTrans.resize(check);
    sccVec.resize(check);

    for(int i = 0; i < sccStore.size(); i++){

        for(int j = 0; j < sccStore[i].size(); j++){

            int temp = sccStore[i][j];

            store[temp] = i;

        }
    }

    for(int i = 0; i < sccStore.size(); i++){

        for(int j = 0; j < sccStore[i].size(); j++){

            int temp = sccStore[i][j];

            for(int k = 0; k < mainVec[temp].size(); k++){

                int x = mainVec[temp][k];
                int y = store[x];

                if(y != i){

                    sccVec[i].push_back(y);
                    sccTrans[y].push_back(i);

                }
            }
        }
    }

    int count = 0;
    bool control = false;

    for(int i = 0; i < sccTrans.size(); i++){
        if(sccTrans[i].size() != 0){
            control = true;
            break;
        }

    }

    if(control){

        for(int i = 0; i < sccTrans.size(); i++){

            if(sccTrans[i].size() == 0){

                CrackScc.push(i);
                count++;
            }
        }
    }
    else{

        for(int i = 0; i < sccStore.size(); i++){

            if(sccStore[i].size() > 0){

                CrackScc.push(i);
                count++;
            }
        }
    }

    ofstream out;
    out.open(output);
    out << count << " ";
    while(CrackScc.size()){

        int crack = CrackScc.top();

        CrackScc.pop();

        out << sccStore[crack][0] + 1 << " ";
    }
    out << endl;

    return 0;

}