#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include<set>
#include<map>
#include <utility>
using namespace std;
struct node{
    int val=0;
    vector<string> route;
};
typedef pair<string,string> pairstr;
void load_lines(vector <string> &);
void hashes(map< pairstr, int > &,vector<string>&);
void line_hash_function(map<int,string>&,vector<string>&);
void intersecting_stations_funtion(map< pairstr ,set< string >>&,vector<string >& ,map< pairstr, int > &,vector<string >&);
string line_name(vector < string > &, map< pairstr, int > & , string );
void graph_function(vector<vector<int >> &);
int line_num_function(map<int,string>&,string&);
bool vistied(int& ,vector<int >&);
vector<vector<int>> path_function(vector<vector<int>>& ,int& src,int&);
vector<node>path_with_station(vector<vector<int>>& ,map< pairstr ,set< string >>& ,map< pairstr, int > &,map<int ,string>&, string& ,string& );
void sorting(vector<node>&);