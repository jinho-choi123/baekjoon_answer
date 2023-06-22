#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>

using namespace std;

#define MAX_EXPLORE 101*101 + 1

//Function declaration
int main(void);
void get_input(int *N);
int ** create_map(int N, int M);
void init_map(int **map, int N);
void init_visited(int ** visited, int N);
int explore(int N, int ** map, int ** visited);
void explore2(int N, int **map, int **visited, int **group_sizes, int group_id);
void grouping(int seed_i, int seed_j, int N, int **map, int **visited);
void grouping2(int seed_i, int seed_j, int N, int **map, int **visited, int * group_size);
//End of Function declaration


void get_input(int *N) 
{
    cin >> *N;
    return;
}

int ** create_map(int N) {
    int ** map = new int * [N];
    for (int i = 0 ; i < N ; i++) {
        map[i] = new int[N];
    }

    return map;
}

void init_map(int **map, int N) {
    string mapLine;
    for(int i = 0 ; i < N ; i++) {
        //get line input
        cin >> mapLine;
        //parse input and store it into the maze array 
        for (int j = 0 ; j < N ; j ++) {
            map[i][j] = stoi(mapLine.substr(j, 1));
        }
    }
}

void init_visited(int ** visited, int N) {
    for(int i = 0 ; i < N ; i ++) {
        for (int j = 0 ; j < N ; j ++) {
            visited[i][j] = 0;
        }
    }
    return;
}

//return home group number
int explore(int N, int ** map, int ** visited) {
    int seed_i = -1;
    int seed_j = -1;
    //check if there are any home that are not visited 
    //if all houses are visited, then return
    for (int i = 0 ; i < N ; i ++) {
        for (int j = 0 ; j < N ; j ++) {

            //house (i,j) is not visited
            if(map[i][j] == 1 && visited[i][j] == 0) {
                seed_i = i;
                seed_j = j;
            }
        }
    }

    if(seed_i == -1 && seed_j == -1) {
        //all houses are visited
        return 0;
    }

    //house (seed_i, seed_j) is not grouped
    grouping(seed_i, seed_j, N, map, visited);

    return 1 + explore(N, map, visited);

}

void explore2(int N, int **map, int **visited, int *group_sizes, int group_id) 
{   
    int seed_i = -1;
    int seed_j = -1;
    //check if there are any home that are not visited 
    //if all houses are visited, then return
    for (int i = 0 ; i < N ; i ++) {
        for (int j = 0 ; j < N ; j ++) {

            //house (i,j) is not visited
            if(map[i][j] == 1 && visited[i][j] == 0) {
                seed_i = i;
                seed_j = j;
            }
        }
    }
    if(seed_i == -1 && seed_j == -1) {
        //all houses are visited
        return;
    }

    int group_size = 0;
    //do grouping and get group size
    grouping2(seed_i, seed_j, N, map, visited, &group_size);

    //set group_sizes
    group_sizes[group_id] = group_size;


    return explore2(N, map, visited, group_sizes, group_id + 1);
}

//group houses of src (seed_i, seed_j)
void grouping(int seed_i, int seed_j, int N, int **map, int **visited) {

    //invalid seed_i or seed_j
    if (seed_i < 0 || seed_j< 0 || seed_i >= N || seed_j >= N) {
        return;
    }

    //if there is a house, then 
    if (map[seed_i][seed_j] == 1 && visited[seed_i][seed_j] == 0) {
        //mark as visited
        visited[seed_i][seed_j] = 1;

        //propagate to neighbor
        grouping(seed_i+1, seed_j, N, map, visited);
        grouping(seed_i-1, seed_j, N, map, visited);
        grouping(seed_i, seed_j+1, N, map, visited);
        grouping(seed_i, seed_j-1, N, map, visited);
    }

    return;
}

//do grouping and return group size of it
void grouping2(int seed_i, int seed_j, int N, int **map, int **visited, int * group_size)
{
    //invalid seed_i or seed_j
    if (seed_i < 0 || seed_j< 0 || seed_i >= N || seed_j >= N) {
        return;
    }

    //if there is a house, then 
    if (map[seed_i][seed_j] == 1 && visited[seed_i][seed_j] == 0) {
        //mark as visited
        visited[seed_i][seed_j] = 1;

        //increase group_size 1
        *group_size = *group_size + 1;

        //propagate to neighbor
        grouping2(seed_i+1, seed_j, N, map, visited, group_size);
        grouping2(seed_i-1, seed_j, N, map, visited, group_size);
        grouping2(seed_i, seed_j+1, N, map, visited, group_size);
        grouping2(seed_i, seed_j-1, N, map, visited, group_size);
    }

    return;

}


int main(void)
{
    int N;
    get_input(&N);

    //create map
    int ** map = create_map(N);
    //init map
    init_map(map, N);
    
    //create visited
    int ** visited = create_map(N);
    //init visited
    init_visited(visited, N);

    //get group_num and create group_sizes array
    int group_num = explore(N, map, visited);
    int *group_sizes = new int [group_num];


    //reset visited 
    init_visited(visited, N);

    //recalculate group_sizes 
    explore2(N, map, visited, group_sizes, 0);

    //sort group_sizes array
    std::sort(group_sizes, group_sizes + group_num);

    cout << group_num << endl;

    //print group_sizes array
    for(int i = 0 ; i < group_num ; i ++) {
        cout << group_sizes[i] << endl;
    }


    return 0;
}
