#include"../headers/Graph.h"
#include"Graph.cpp"
using namespace std;
#include<map>
int main() {

	map< pairstr, int > m;
    vector< string >station_name;
	vector<string> line;
    map< pairstr ,set< string >> intersecting_stations;
    map<int ,string>line_num;
	load_lines(line);
    vector<vector< int >> graph(line.size());
	hashes(m,station_name);
    line_hash_function(line_num,line);
    intersecting_stations_funtion(intersecting_stations,line,m,station_name);
    graph_function(graph);




    //for output of station names.
    // for(auto i:station_name){
    //     cout<< i <<endl;
    // }


    //for output of lines stored.
    //for(auto i: line )cout<<i<<endl;;


    //for output of line_hash.
    // for(auto i:line_num){
    //     cout<<i.first<<" "<<i.second<<endl;
    // }

	//for output of hash map of stations
    // for (auto hash : m) {
    //     if(hash.first.second=="violet" || hash.first.second=="yellow" )
	// 	cout << hash.first.first << " " << hash.first.second << " " << hash.second<<endl;
    // }
  

    //for output of intersecting stations.
    // int cnt=0;
    // for(auto i: line){
        
    //     for(auto j:line){
    //         if(i==j)continue;
    //         //cout<<"common stations between line "<<i<<" and "<<j<<" line " <<" are :"<<endl;
    //         if(intersecting_stations.find({i,j}) != intersecting_stations.end()){
    //             cout<<"common stations between line "<<i<<" and "<<j<<" line " <<" are :"<<endl;
    //             for(auto k:intersecting_stations[{i,j}] ){
    //                 cout<<k<<endl;
    //                 cnt++;
    //             }
    //         }
    //        //else{
    //           //  cout<<"sorry!. NO station :("<<endl;
    //         //}
    //         //cout<<endl;
    //     }
    //     cout<<cnt<<endl;
    // }

    //for checking the graph
    // for(auto i:graph){
    //    //cout<<i.size()<<endl;
    //    for(auto j:i)cout<<j<<" ";
    //    cout<<endl;
    // }



    cout<<endl<<endl<<endl;;
    cout<<"     Hey !  Welcome To METRO ASSISTANT  :)"<<endl<<endl<<endl;
    //cout<<"      We will help you inn your journey  :) "<<endl<<endl;
    cout<<"     Please enter the staions accordingly  :"<<endl<<endl;

    // taking input from user.
    string station1,station2;
    cout<<"     enter the source/staring station  :- ";
    getline(cin ,station1);
    cout<<"     enter the destination/ending station :- ";
    getline(cin,station2);
    cout<<endl;
    //for checking the input station lines.
    string line1=line_name(line,m,station1);
    string line2=line_name(line,m,station2);
    // cout<<line1<<" "<<line2<<endl;

    //for lines to their line number.
    int line_num1=line_num_function(line_num,line1);
    int line_num2=line_num_function(line_num,line2);
    //cout<<line_num1<<" "<<line_num2<<endl;

    if(line_num1==-1 || line_num2==-1){
        cout<<"     sorry! you entered wrong station name . Please Try again."<<endl;
    }
    else{
        if(line_num1==line_num2){
            int num=abs( m[{station1,line1}]-m[{station2,line1}]);
            cout<<"     Both these stations are on same line "<<line1<<" so we donot need to change any line"<<endl;
            
            cout<<"     Start from station "<<station1<<" to station "<<station2<<" via line "<<line1<<endl;
            cout<<"     Total number of station u have to cover are :"<<num<<endl;
            cout<<"     Thank You  and Have a safe journey  "<<endl;
        }
        else{

            // for finding the paths with a limit or interchanging stations.
            vector<vector<int >>dfs_paths;
            dfs_paths=path_function(graph,line_num1,line_num2);


            //for otuput of paths according to the line number.
            // cout<<"total number of paths are : "<<endl;
            // cout<<dfs_paths.size()<<endl;
            // for(auto i:dfs_paths){
            //      //cout<<i.size()<<endl;
            //     for(auto j:i){
            //         cout<<j<<" ";
            //     }
            //     cout<<endl;
            // }


            //finding path with station's name .
            vector<node>routes;
            routes=path_with_station(dfs_paths, intersecting_stations,m,line_num,station1,station2);
            
            //for sorting the path on the basis of their station numbers.
            sorting(routes);

            
           // for printing all the routes.
            // cout<<routes.size()<<endl;
            // for(auto i:routes){
            //     cout<<i.val<<endl;
            //     for(auto j:i.route){
            //         cout<<j<<" ";
            //     }
            //     cout<<endl;
            // }

            // for printing the output
            int path_number=0;
            int n=routes.size();
            for(auto i: routes){

                
                if(path_number==0){

                    path_number++;
                    cout<<"     The sortest path from station "<<station1<<"  to station  "<<station2<<" is :"<<endl;
                    cout<<"     ";
                    bool flag=true;
                    for(auto j:i.route){
                        if(flag){
                            cout<<j;
                            flag =false;
                        }
                        else{
                            cout<<"  -->  "<<j;
                        }
                    }
                    cout<<endl;
                    cout<<"     total number of stations u travelled during this shortest route are : "<<i.val<<endl;
                    cout<<endl;
                }
                else if(path_number<n && path_number<3){
                    path_number++;
                    if(path_number==2)
                        cout<<"     "<<path_number<<"nd shortest  path from station "<<station1<<"  to station  "<<station2<<" is :"<<endl;
                    if(path_number==3)
                        cout<<"     "<<path_number<<"rd shortest  path from station "<<station1<<"  to station  "<<station2<<" is :"<<endl;

                    cout<<"     ";
                    bool flag=true;
                    for(auto j:i.route){
                        if(flag){
                            cout<<j;
                            flag =false;
                        }
                        else{
                            cout<<"  -->  "<<j;
                        }
                    }
                    cout<<endl;
                    cout<<"     total number of stations u travelled during this shortest route are : "<<i.val<<endl;
                    cout<<endl;

                }
                else if(path_number<n && path_number>2){
                    path_number++;
                    char c;
                    cout<<"     DO you want one  more path. Enter y/n : ";
                    cin>>c;
                    if(c=='y'){
                        cout<<endl;
                        cout<<"     "<<path_number<<"th shortest  path from station "<<station1<<"  to station  "<<station2<<" is :"<<endl;
                        cout<<"     ";
                        bool flag=true;
                        for(auto j:i.route){
                            if(flag){
                                cout<<j;
                                flag =false;
                            }
                            else{
                                cout<<"  -->  "<<j;
                            }
                        
                        }
                        cout<<endl;
                        cout<<"     total number of stations u travelled during this shortest route are : "<<i.val<<endl;
                        cout<<endl;

                    }
                    else{
                        cout<<"     Thank You  and Have a safe journey  "<<endl<<endl;
                        break;
                    }

                }
                if(path_number==n){
                    cout<<"     Thank You and Have a safe journey  "<<endl<<endl;
                    break;
                }
                
            }

        }

    }

    
}