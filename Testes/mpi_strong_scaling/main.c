#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

#define MAZE_SIZE 500
char maze[MAZE_SIZE][MAZE_SIZE];

struct Node {
    int x, y;
    struct Node *parent;
};

struct Node *createNode(int x, int y, struct Node *parent) {
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    node->x = x;
    node->y = y;
    node->parent = parent;
    return node;
}

int isValid(int x, int y) {
    return (x >= 0 && y >= 0 && x < MAZE_SIZE && y < MAZE_SIZE);
}


void printMaze() {
    for (int i = 0; i < MAZE_SIZE; i++) {
        for (int j = 0; j < MAZE_SIZE; j++) {
            printf("%c ", maze[i][j]);
        }
        printf("\n");
    }
}

void createMaze() {
    for (int i = 0; i < MAZE_SIZE; i++) {
        for (int j = 0; j < MAZE_SIZE; j++) {
            maze[i][j] = '#';
        }
    }

    maze[0][0] = 'E';
    maze[0][1] = ' ';
    maze[MAZE_SIZE - 1][MAZE_SIZE - 1] = 'S';
    maze[MAZE_SIZE - 1][MAZE_SIZE - 2] = ' ';

    int x = 1;
    int y = 0;
    while (x < MAZE_SIZE - 1 || y < MAZE_SIZE - 2) {
        maze[x][y] = ' ';
        if (x < MAZE_SIZE - 1 && rand() % 2 == 0) {
            x++;
        } else if (y < MAZE_SIZE - 2) {
            y++;
        }
    }

    for (int i = 1; i < MAZE_SIZE - 1; i += 2) {
        for (int j = 1; j < MAZE_SIZE - 2; j++) {
            if (rand() % 2 == 0) {
                maze[i][j] = ' ';
            }
        }
    }

    for (int i = 2; i < MAZE_SIZE - 1; i += 2) {
        for (int j = 2; j < MAZE_SIZE - 2; j++) {
            if (rand() % 2 == 0) {
                maze[i][j] = ' ';
            }
        }
    }
}

int bfs(int startX, int startY, int endX, int endY, int rank, int size) {
    int visited[MAZE_SIZE][MAZE_SIZE];
    for (int i = 0; i < MAZE_SIZE; i++) {
        for (int j = 0; j < MAZE_SIZE; j++) {
            visited[i][j] = 0;
        }
    }

    struct Node *queue[MAZE_SIZE * MAZE_SIZE];
    int front = 0, rear = 0;
    struct Node *startNode = createNode(startX, startY, NULL);
    queue[rear++] = startNode;

    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};

    while (front < rear) {
        struct Node *current = queue[front++];
        int x = current->x;
        int y = current->y;

        if (x == endX && y == endY) {
            while (current != NULL) {
                maze[current->x][current->y] = '>';
                current = current->parent;
            }
            return 1;
        }

        visited[x][y] = 1;

        for (int i = 0; i < 4; i++) {
            int newX = x + dx[i];
            int newY = y + dy[i];

            if (isValid(newX, newY) && maze[newX][newY] != '#' && !visited[newX][newY]) {
                struct Node *newNode = createNode(newX, newY, current);
                queue[rear++] = newNode;
                visited[newX][newY] = 1;
            }
        }
    }

    return 0;
}
int main(int argc, char **argv) {
    int rank, size;
    double start, end;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    for (int num_procs = 1; num_procs <= 16; num_procs *= 2) {
        if (rank == 0) {
            createMaze(); // Cria o labirinto no processo raiz
        }
        MPI_Barrier(MPI_COMM_WORLD); // Sincroniza os processos
        start = MPI_Wtime();
        int pathFound = bfs(0, 0, MAZE_SIZE - 1, MAZE_SIZE - 1, rank, size);
        end = MPI_Wtime();

        if (rank == 0) {
            printf("Processos: %d | Tempo: %f segundos\n", num_procs, end - start);
        }
    }

    MPI_Finalize();
    return 0;
}
