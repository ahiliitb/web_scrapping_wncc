#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t; cin>>t;
    while (t--)
    {
      int n; cin>>n;
      unordered_map<int, int> mymap;
      for(int i=0; i<n; i++)
      {
        int m; cin>>m;
        int s; cin>>s;
        mymap[m] = s;
      }
      unordered_map<int, int> :: iterator iter = mymap.begin();
      vector<vector<int>> matrix;
      for (int i = 0; i < 4; i++)
      {
        vector<int> v;
        matrix.push_back(v);
      }
      
      while (iter != mymap.end())
      {
        if(iter->second == 00)matrix[0].push_back(iter->first);
        else if(iter->second == 01)matrix[1].push_back(iter->first);
        else if(iter->second == 10)matrix[2].push_back(iter->first);
        else if(iter->second == 11) matrix[3].push_back(iter->first);
        iter++;
      }
      for(int i=1; i<4; i++)
      {
        if(matrix[i].size() == 0)continue;
        sort(matrix[i].begin(), matrix[i].end());
      }
      int ans;
      if((matrix[1].size() == 0 || matrix[2].size() == 0) && matrix[3].size() == 0)ans = -1;
      else
      {
        if(matrix[1].size() == 0 || matrix[2].size() == 0)ans=matrix[3][0];
        else if(matrix[3].size() == 0)ans = matrix[1][0]+matrix[2][0];
        else
        {
          ans = min((matrix[1][0]+matrix[2][0]), matrix[3][0]);
        }
      }
      cout<<ans<<endl;
    }
    

    return 0;
}

