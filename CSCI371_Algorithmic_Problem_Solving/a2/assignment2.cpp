#include<iostream>
#include<vector>
#include<map>
#include <iomanip>
#include <fstream>
#include<string>
#include<set>

using namespace std;
#define ll long long
bool slidingWindow(vector<int>& ans, int k, int t) {

	//edge cases
	if(k <= 0 || t <0) return false;
	set<int> c(ans.begin(), ans.end());
	if(t == 0 && ans.size() == c.size()) return false;

	int len = ans.size();
	vector<pair<int, int> > occ;


    for (int i = 0; i < ans.size(); i++) {
        occ.push_back(make_pair(ans[i], i));
    }


    sort(occ.begin(), occ.end());


    for (int i = 0; i < ans.size(); i++) {
	    int j = i + 1;
	    while(occ[j].first-occ[i].first <= t) {

	    	if(j >= len) break;
	    	int sum = abs(occ[j].second-occ[i].second);
	        if(sum <= k) return true;
	       	j++;

	        }
    }
    
    return false;


}

int main() {
	for(char c = '1'; c <= '2'; c++) {
		// input array
			ifstream inFile;
			string s = "case";
			inFile.open(s + c +".txt");
			vector<int> ans;
			int v;
			while(inFile>>v) {
				ans.push_back(v);
			}

		// solution
			if(c == '1') cout<<(slidingWindow(ans, 3, 3) == false ? "false" : "true")<<endl;
			if(c == '2') cout<<(slidingWindow(ans, 2, 4) == false ? "false" : "true")<<endl;

			inFile.close();
		}
		return 0;
}

