#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define MAZE_SIZE 30
char maze[MAZE_SIZE][MAZE_SIZE];

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

int bfs(int startX, int startY, int endX, int endY) {
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

    int pathFound = 0;

    #pragma omp parallel shared(queue, front, rear, pathFound) num_threads(4)
    {
        while (front < rear && !pathFound) {
            struct Node *current;

            #pragma omp critical
            {
                if (front < rear) {
                    current = queue[front++];
                }
            }

            if (current) {
                int x = current->x;
                int y = current->y;

                if (x == endX && y == endY) {
                    #pragma omp critical
                    {
                        pathFound = 1;
                        struct Node *tmp = current;
                        while (tmp != NULL) {
                            maze[tmp->x][tmp->y] = '>';
                            tmp = tmp->parent;
                        }
                    }
                }

                if (!visited[x][y]) {
                    visited[x][y] = 1;
                    for (int i = 0; i < 4; i++) {
                        int newX = x + dx[i];
                        int newY = y + dy[i];
                        if (isValid(newX, newY) && maze[newX][newY] != '#' && !visited[newX][newY]) {
                            struct Node *newNode = createNode(newX, newY, current);
                            #pragma omp critical
                            {
                                queue[rear++] = newNode;
                            }
                        }
                    }
                }
            }
        }
    }

    return pathFound;
}
int main() {
    double start, end;
    for (int num_threads = 1; num_threads <= 16; num_threads *= 2) {
        omp_set_num_threads(num_threads);
        createMaze(); // Cria o labirinto
        start = omp_get_wtime();
        int pathFound = bfs(0, 0, MAZE_SIZE - 1, MAZE_SIZE - 1); // Busca o caminho
        end = omp_get_wtime();

        printf("Threads: %d, Tempo: %f segundos\n", num_threads, end - start);
    }
    return 0;
}
