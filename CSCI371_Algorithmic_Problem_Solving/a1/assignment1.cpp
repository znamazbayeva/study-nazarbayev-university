#include<iostream>
#include<vector>
#include<map>
#include <iomanip>
#include <fstream>
#include<string>
using namespace std;
#define ll long long
int main() {
	int v;
	for(char c = '1'; c <= '3'; c++) {
		ifstream inFile;
		string s = "case";
		inFile.open(s + c +".txt");
		vector<int> ans;
		map<int,int> occ;
		int l =1;
		
		while(inFile>>v) {
			occ[v] = l++;
			ans.push_back(v);
		}
		int cnt = 0;
		for(int i = 0; i < ans.size(); i++) {
			for(int j = i+1; j < ans.size(); j++) {
				int sum = (ans[i] + ans[j])*-1;
				if(occ[sum]&& i!=j && i != occ[sum]-1 && j != occ[sum]-1) cnt++;
			}	
		}
		cout<<cnt/3<<endl;
		inFile.close();
	}
	return 0;
}

