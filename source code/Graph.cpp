#include"headers/Graph.h"
#include<vector>
#include<algorithm>
#include<set>
#include<queue>


// funtion to read all lines from a text file.
void load_lines(vector <string> &lines) {
    string line;
    ifstream myfile("data/example.txt");
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            string s="";
            for(int i=0;i<line.length();i++){
                   if(line[i]=='/')
                    break;
                    s+=line[i];
            }
            lines.push_back(s);
        }
        myfile.close();
        return;
    }
    else cout  << " Unable to open file";
}


//function to make hash map of stations with their line.
void hashes(map<pairstr, int> &result,vector<string>& station_name) {
    ifstream myfile("data/stations.txt");
    if (myfile.is_open())
    {
        string full;
        while (getline(myfile, full))
        {
            string word = "";
            int j = 0;
            pairstr x;
            int val=0;
            for (int i = 0; i < full.length(); i++) {
                if (full[i] == ' ' && full[i + 2] == 'n'){
                    if(j==0){ 
                        x.first=word;
                        station_name.push_back(word);
                    }
                    if (j == 1) {
                        x.second = word;
                        int a = max((int)full[full.length() - 1]-48,0);
                        int b = max((int)full[full.length() - 2]-48,0);
                        val = b * 10 + a;
                        break;
                    }
                    j++;
                    i = i + 3;
                    word = "";
                }
                else {
                    word=word+full[i];
                }
            }
            result[x]=val;
        }
        myfile.close();
        return;
    }
    else cout << "Unable to open file";
}


//funtion to check the line name of a station.
string line_name(vector < string > &l, map< pairstr, int > &m , string name ){

    for(int i=0;i<l.size();i++){

        if(m.find ( {name, l[i]} ) != m.end() ){
            return l[i];
        }
    }
    return "invalid station name";
}


// funtion to make hash map of station on more than one line.
void intersecting_stations_funtion(map< pairstr ,set< string >>& intersecting_stations,vector<string >& line,map< pairstr, int > &m,vector<string >& station_name){
    for(int i=0;i<line.size();i++){
            for(int j=0;j<line.size();j++){
                    if(line[i]==line[j])continue;
                    if(intersecting_stations.find({line[j],line[i]}) == intersecting_stations.end()){
                        for(auto k:station_name){
                            if(m.find({k,line[i]})!=m.end() && m.find({k,line[j]})!=m.end()){
                                intersecting_stations[{line[i],line[j]}].insert(k);
                            }
                        }
                    }
                    else{
                        intersecting_stations[{line[i],line[j]}]=intersecting_stations[{line[j],line[i]}];
                    }
            }
    }
}


// funtion to make line_hash.
void line_hash_function(map<int,string>&line_num ,vector<string>&line){
    for(int i=0;i<line.size();i++){
        line_num[i]=line[i];
    }
} 


//Function to make adcancy matrix for the graph 
void graph_function(vector <vector<int>> &graph) {
    string l;
    ifstream myfile("data/matrix.txt");
    if (myfile.is_open())
    {  
        int i=0;
        while (getline(myfile, l))
        {
            for(int j=0;j<l.size();j++){
                if(l[i]=='/')break;
                if(l[j]=='1'){
                    graph[i].push_back(j);
                }
            }
            i++;
        }
        myfile.close();
        return;
    }
    else cout  << " Unable to open file";
}


//function for respected line number
int line_num_function(map<int,string>&line_num,string& line){
    for(int i=0;i<line_num.size();i++){
        if(line_num[i]==line)return i;
    }
    return -1;
} 


//for checking the visited node.
bool vistied(int& node,vector<int >& path){
    for(auto i:path){
        if(i==node)return false;
    }
    return true;
}


//for finding the path from source to destination.
vector<vector<int>> path_function(vector<vector<int>>& graph,int& src,int& des){
    vector<vector<int >>ans;
    queue<vector<int >>que;
    vector<int >curr_path;
    curr_path.push_back(src);
    que.push(curr_path);
    while(!que.empty()){
        curr_path=que.front();
        que.pop();
        int n=curr_path.size();
        int last=curr_path[n-1];
        if(last==des && n<=4){   //we can change depth by changing the condition(here 4 is depth).
            ans.push_back(curr_path);
            continue;
        }
        for(auto i:graph[last]){
            if(vistied(i,curr_path)){
                vector<int >new_path(curr_path);
                new_path.push_back(i);
                que.push(new_path);
            }
        }
    }
    
    return ans;
}


//function for finding the path with all stations.
vector<node>path_with_station(vector<vector<int>>& dfs_paths , map< pairstr ,set< string >>& intersecting_stations, map< pairstr, int > &m,map<int , string>& line_num , string& start, string& end){
    vector<node>ans;
    
    for(auto i:dfs_paths){
        if(i.size()>1){  // here we can add contions for number of changes.

            vector<node>curr;
            for(auto k:intersecting_stations[{line_num[i[0]],line_num[i[1]]}]){
                struct node temp;
                string line=line_num[i[0]];
                temp.val=abs(m[{k,line}]-m[{start,line}]);
                temp.route.push_back(start);
                if(start!=k)
                    temp.route.push_back(k);
                curr.push_back(temp);
                
            }
            
            for(int j=1;j<i.size()-1;j++){
                vector<node>new_curr;
                bool flag=false;
                for(auto k:intersecting_stations[ {line_num[i[j]],line_num[i[j+1]]} ]){
                    for(auto l:curr){
                        flag=true;
                        struct node temp=l;
                        int n=temp.route.size();
                        string prev=temp.route[n-1];
                        temp.val+=abs(m[{k,line_num[i[j]]}] - m[{prev,line_num[i[j]]}] );
                        if(prev!=k)
                            temp.route.push_back(k);
                        new_curr.push_back(temp);
                    }
                }
                if(flag)
                    curr=new_curr;

            }

            for(auto j:curr){
                string last_line=line_num[i[i.size()-1]];
                int n=j.route.size();
                string prev=j.route[n-1];
                j.val+=abs(m[{end,last_line}] - m[{prev,last_line}]);
                if(end!=prev)
                    j.route.push_back(end);
                ans.push_back(j);
            }

        }
    }
    return ans;
}


// function for sorting the paths
bool compare(node temp1,node temp2){
    if(temp1.val==temp2.val){
        if(temp1.route.size()<temp2.route.size())return true;
        else return false;
    }
    else if(temp1.val<temp2.val)
        return true;
    else 
        return false;

}
void sorting(vector<node>& routes){
    sort(routes.begin(),routes.end(),compare);
}