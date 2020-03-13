#include <cstdio>
#include <iostream>
#include <set>
#include <vector>
#include <cstring>
#define MOD 1000000007
using namespace std;
int dp[1010];
char word[1010];
char text[1010];
int textLen;
set <int> hashSet;

int hashValue(char str[]) {
    long long hash = 0;
    int n = strlen(str);
    for(int i = 0; i < n; i++) {
        hash = hash * 131 + str[i];
        hash %= MOD;
    }
    return hash;
}

int solve(int k) {
    if(k == textLen) return 1;
    if(dp[k] != -1) return dp[k];
    dp[k] = 0;

    long long currentHash = 0;

    for(int i = k; i < textLen; i++) {
        currentHash = currentHash * 131 + text[i];
        currentHash %= MOD;
        if(hashSet.find(currentHash) != hashSet.end()) {
            dp[k] += solve(i+1);
            dp[k] %= MOD;
        }
    }

    return dp[k];
}

int main(int argc, char* argv[]) {
    freopen(argv[1], "r", stdin);
    freopen(argv[2], "w", stdout);

    int m;
    scanf(" %s", text);
    scanf(" %d",&m);
    textLen = strlen(text);
    while(m--) {
        int hash;
        scanf(" %s", word);
        hash = hashValue(word);
        hashSet.insert(hash);
    }

    for(int i = 0; i <= 1000; i++) {
        dp[i] = -1;
    }

    cout << solve(0) << endl;
    return 0;
}