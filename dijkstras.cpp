// dijsktras.cpp
//Ty Anderson
//CS302: Proj4
//Given a nxn grid of tiles with values of leaving the tiles, find the shortest path between 2 points using Dijkstras algorithm.

#include <iostream>
#include <vector>
#include <map>
using namespace std;

class Dijks{

    public:
        vector<char> board;
        vector<int> distances;
        vector<int> backlink;
        vector<int> visited;
        map<char, int> tile_costs;
        vector<int> answer;

        map<int, vector<int> >adj;
        map<int, vector<int > >::iterator it;

        multimap<int, int> frontier;
        int num_cols;
        int num_rows;
        void build_adjmap();
        void find_path(int i, int j);
        int get_weight(int t);
        bool in_map(int x);
        void fill_vecs();
        int get_cost(int i, int j);
        void build_out(int s_row, int s_col, int e_row, int e_col);

};

    
//Returns the weight at a board index given an index
int Dijks::get_weight(int t){
    char tile = board[t];
    map<char, int>::iterator it1;
    for(it1 = tile_costs.begin(); it1 != tile_costs.end(); ++it1){
        if(it1->first == tile) return it1->second;
    }
	return -1;
}

//Checks if a value is already in the map and if it is delete the element
bool Dijks::in_map(int x){
    multimap<int, int>::iterator it2;
    for(it2 = frontier.begin(); it2 != frontier.end(); ++it2){
        if(x == it2->second){
            frontier.erase(it2->first);
            return true;
        } 
    }
    return false;
}


void Dijks::find_path(int i, int j){
    int ind = 0;
    int d = 0;
    int start = i*num_cols + j;				//turn to 1D representation
    frontier.insert(make_pair(0,start));	//start the frontier
    
    while(frontier.empty() != true){

        ind = frontier.begin()->second;
        visited[ind] = 1;

        if(ind == start){
            d = get_weight(start);		//if we are just starting we have to track the cost of leaving the first element
            distances[ind] = d;
        }

        frontier.erase(frontier.begin());	//delete front of frontier

        vector<int>::iterator iter;
		//Loop through all adjacent nodes
        for(iter = adj[ind].begin(); iter != adj[ind].end(); ++iter){   //Iter = index of neighboring nodes 
            if(visited[*iter] == -1){
                d = distances[ind] + get_weight(*iter);
                if(distances[*iter] == -1 || d < distances[*iter]){		//if it's not visited or has a shorter path, add it to frontier
                    
                    in_map(*iter);			//see if already in map, if so delete
                    distances[*iter] = d;	//set distance
                    backlink[*iter] = ind;	//set backlink
                    frontier.insert(make_pair(d,*iter));
                }             
            }
        }
        
    }

}

//Initialize all vecs
void Dijks::fill_vecs(){
    visited.resize(num_cols*num_rows);
    distances.resize(num_cols*num_rows);
    backlink.resize(num_cols*num_rows);
    for(int i = 0; i < (num_cols*num_rows); i++){
        backlink[i] = -1;
        distances[i] = -1;
        visited[i] = -1;
    }
}

//Check up, right, left, down for adjacent nodes and add them to the vector given the key of the parent index
void Dijks::build_adjmap(){

    for(int i = 0; i < num_rows; i++){
        for(int j = 0; j < num_cols; j++){

            if(j != (num_cols - 1)){
                adj[i*num_cols+j].push_back((i*num_cols+(j+1)));
                if( j > 0){ //Look left
                    adj[i*num_cols+j].push_back((i*num_cols+(j-1)));
                }
            }
            else{
                adj[i*num_cols+j].push_back((i*num_cols+(j-1)));	//still look left if can't look right
            }


            if(i != (num_rows - 1)){
                adj[i*num_cols+j].push_back((i+1)*num_cols+ j);
                if(i > 0){ //Look right 
                    adj[i*num_cols+j].push_back((i-1)*num_cols+ j);	
                }
            }
            else{
                adj[i*num_cols+j].push_back((i-1)*num_cols+ j);
            }
        }
    }

}

//Returns total cost from distance vector given i and j
int Dijks::get_cost(int i, int j){
    return distances[(i*num_cols+j)] - get_weight((i*num_cols+j));

}

void Dijks::build_out(int s_row, int s_col, int e_row, int e_col){
    int ind = (e_row*num_cols + e_col); //begin backlink check from the end
    int x = 0;
    int r, c = 0;
	answer.push_back(ind);
    while(ind != (s_row*num_cols + s_col)){		//keep going till we reach the beginning
        ind = backlink[ind];		//iterate through respective backlinks
        answer.push_back(ind);
    }
	//Print in correct format turning 1D index representation into 2d (row,col)
    for(int i = answer.size()-1; i >= 0; i--){
        x = answer[i];
        r = x / num_cols;
        c = x % num_cols;
        cout << r << " " << c << endl;

    }
}

int main(){
    int tile_type = 0;
    char t;
    int val = 0;
    int map_rows = 0;
    int map_cols = 0;
    int start_row, start_col = 0;
    int end_row, end_col = 0;
    char el;

	//Read in input data
    while(cin >> tile_type){
        Dijks d;
		//store tile costs in list to be accessed later 
        for(int i = 0; i < tile_type; i++){
            cin >> t >> val;
            d.tile_costs.insert(make_pair(t, val));
        }

        cin >> map_rows >> map_cols;
        d.num_cols = map_cols;
        d.num_rows = map_rows;
        d.fill_vecs();	//initialize vectors to -1 to start

        for(int i = 0; i < (map_rows*map_cols); i++){
            cin >> el;
            d.board.push_back(el);
        }

        cin >> start_row >> start_col;
        cin >> end_row >> end_col;

        d.build_adjmap();						//makes adj map out of input board
        d.find_path(start_row, start_col);		//Runs Dijkstras
        cout << d.get_cost(end_row, end_col);	//Gets the cost of our destination

        cout << endl;

        d.build_out(start_row, start_col, end_row, end_col);	//prints the moves based on the backlinks
        

    }

}
