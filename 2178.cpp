#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

#define MAX_EXPLORE 101*101 + 1

//Function declaration
int main(void);
void get_input(int *N, int * M);
int ** create_maze(int N, int M);
void init_maze(int **maze, int N, int M);
void init_visited(int ** visited, int N, int M);
int explore(int src_i, int src_j, int dest_i, int dest_j, int N, int M, int ** maze, int ** visited);
void visit_neighbor(int i, int j, int N, int M, int **maze, int **visited);
void free_maze(int **maze, int N, int M);
void print_maze(int **maze, int N, int M);

//End of Function declaration


void get_input(int *N, int * M) 
{
    cin >> *N >> *M;
    return;
}

int ** create_maze(int N, int M) {
    int ** maze = new int * [N];
    for (int i = 0 ; i < N ; i++) {
        maze[i] = new int[M];
    }

    return maze;
}

void init_maze(int **maze, int N, int M) {
    string mazeLine;
    for(int i = 0 ; i < N ; i++) {
        //get line input
        cin >> mazeLine;
        //parse input and store it into the maze array 
        for (int j = 0 ; j < M ; j ++) {
            maze[i][j] = stoi(mazeLine.substr(j, 1));
        }
    }
}

void init_visited(int ** visited, int N, int M) {
    for(int i = 0 ; i < N ; i ++) {
        for (int j = 0 ; j < M ; j ++) {
            visited[i][j] = 0;
        }
    }
    return;
}


int main(void)
{
    int N, M;
    get_input(&N, &M);


    //allocate array for storing maze 
    int **maze = create_maze(N, M);
    //get maze input
    init_maze(maze, N, M);


    //create visited_array that tracks if node is visited
    int ** visited = create_maze(N, M);
    //init visited
    init_visited(visited, N, M);



    //explore the maze 
    int src_i = 0;
    int src_j = 0;
    int dest_i = N-1;
    int dest_j = M-1;

    visited[src_i][src_j] = 1;

    int min_moves = explore(src_i, src_j, dest_i, dest_j, N, M, maze, visited);

    cout << min_moves;


    //free maze 
    free_maze(maze, N, M);

    //free visited
    free_maze(visited, N, M);

    return 0;
}

//src에서 dest까지의 최단 경로를 반환한다.
int explore(int src_i, int src_j, int dest_i, int dest_j, int N, int M, int ** maze, int ** visited) {

    if(visited[dest_i][dest_j] == 1) {
        //reached to destination.
        return 1;
    }

    //from visited_node, mark neighbor nodes as visited.
    for(int i = 0 ; i < N ; i ++) {
        for (int j = 0 ; j < M ; j ++) {
            if(visited[i][j] == 1) {
                visit_neighbor(i, j, N, M, maze, visited);
            }
        }
    }

    //change all visited nodes that are marked as 2 to 1
    for(int i = 0 ; i < N ; i ++) {
        for (int j = 0 ; j < M ; j ++) {
            if(visited[i][j] == 2) {
                visited[i][j] = 1;
            }
        }
    }

    return 1 + explore(src_i, src_j, dest_i, dest_j, N, M, maze, visited);

}

//mark (i,j)'s neighbor nodes as visited(mark as 2. to distinguish from previous visit and new visit)
void visit_neighbor(int i, int j, int N, int M, int **maze, int **visited) {
    //i-1, j
    if(i-1 >= 0 && maze[i-1][j] == 1 && visited[i-1][j] == 0) {
        visited[i-1][j] = 2;
    }
    //i+1, j
    if(i+1 < N && maze[i+1][j] == 1 && visited[i+1][j] == 0) {
        visited[i+1][j] = 2;
    }
    //i, j-1
    if(j-1 >= 0 && maze[i][j-1] == 1 && visited[i][j-1] == 0) {
        visited[i][j-1] = 2;
    }
    //i, j+1
    if(j+1 < M && maze[i][j+1] == 1 && visited[i][j+1] == 0) {
        visited[i][j+1] = 2;
    }

}

void free_maze(int **maze, int N, int M) {
    for (int i = 0 ; i < N ; i ++) {
        delete[] maze[i];
    }
    delete[] maze;
} 

void print_maze(int **maze, int N, int M) {
    for (int i = 0 ; i < N ; i ++) {
        for (int j = 0 ; j < M ; j ++) {
            cout << maze[i][j] << " ";

        }
        cout << endl;
    }
}
