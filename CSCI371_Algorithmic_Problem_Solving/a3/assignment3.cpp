#include<iostream>
#include<vector>
#include <utility>
using namespace std;
#define ll long long
void answer(vector<int> ans, int x, int z) {

	if((z-ans[x])%(ans[x]+1)==0) {
		int sum = (z-ans[x])/(ans[x+1]);
		if (sum >= ans[0] && sum <= ans[ans.size()-1]) cout<<ans[x]<<" "<<sum<<endl;
	}

}
int main() {
	vector<int> ans;
	int l = -1000;

	//create array
	for(int i = 0; i < 2001; i++) {
		ans.push_back(l);
		l++;
	}

	int y = 0;
	int z = 1024;
	int x = ans.size()-1;
	while(y < x) {
		if(y != ans.size()/2-1) answer(ans, y, z);
		if(x != ans.size()/2+1) answer(ans, x, z);
		y++;
		x--;
	}
	
	return 0;
}

