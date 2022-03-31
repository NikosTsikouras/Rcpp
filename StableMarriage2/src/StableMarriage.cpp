#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>

#include <Rcpp.h>
using namespace Rcpp;

std::unordered_map<std::string,std::string> task_1(std::unordered_map<std::string,std::vector<std::string>> p1, std::unordered_map<std::string,std::vector<std::string>> p2)
{
  int k = 0;
  
  List male;
  List female;
  
  
  for(const auto& p : p1)
  {
    male.push_back(p.first);
  }
  
  for(const auto& p : p2)
  {
    female.push_back(p.first);
  }
  
  int n = p1[male[1]].size();
  
  for(int j = 0; j<=n-1; j++)
  {
    p2[female[j]].push_back("O");
  }
  
  
  std::unordered_map<std::string, std::string> matching;
  
  for(int i = 0; i<=n-1; i++)
  {
    matching[female[i]] = "O";
  }
  
  for(int k = 0; k<n;)
  {
    std::string X = male[k];
    for(;X!="O";)
    {
      auto x_curr = p1[X][0];
      auto pre_ind1 = find(p2[x_curr].begin(),p2[x_curr].end(),X);
      int ind1 = std::distance(p2[x_curr].begin(),pre_ind1);
      
      auto pre_ind2 = find(p2[x_curr].begin(),p2[x_curr].end(),matching[x_curr]);
      int ind2 = std::distance(p2[x_curr].begin(),pre_ind2);
      
      if (ind1 < ind2)
      {
        std::string X_old = X;
        std::string X_new = matching[x_curr];
        matching[x_curr] = X;
        X = X_new;
      }
      if (X!= "O")
      {
        p1[X].erase(p1[X].begin());
      }
    }
    k = k + 1;
    
  }
  
  //We reverse the matching so that the resulting matching corresponds to the book format. Note that this step can be skipped.
  std::unordered_map <std::string, std::string> reversed_matching;
  for (const auto& p : matching)
  {
    reversed_matching[p.second] = p.first;
  }
  return reversed_matching;
}
// [[Rcpp::export]]

//keys1,values1 and keys2, values2 are used to give the preferences of the males and females.
//keys1 and keys2 give the order of males and females and values1, values2 give the preferences of these ordered males and females.
std::unordered_map<std::string,std::string> pairing_algorithm(std::vector<std::string> keys1,std::vector<std::vector<std::string>> values1, std::vector<std::string> keys2, std::vector<std::vector<std::string>> values2)
{
  int n = keys1.size();
  
  //key_values1 is combining keys1, values1 to create the first map of either males or females
  std::unordered_map<std::string,std::vector<std::string>> key_values1;
  
  for(int i = 0; i <= n-1; i++)
  {
    key_values1[keys1[i]] = values1[i];
  }
  
  //key_values2 is combining keys2, values2 to create the remaining map
  
  std::unordered_map<std::string,std::vector<std::string>> key_values2;
  for(int i = 0; i <= n-1; i++)
  {
    key_values2[keys2[i]] = values2[i];
  }
  
  std::unordered_map<std::string,std::string> result = task_1(key_values1,key_values2);
  
  return result;
}



 