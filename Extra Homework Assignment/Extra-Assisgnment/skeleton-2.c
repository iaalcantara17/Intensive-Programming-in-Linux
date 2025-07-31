include <stdio.h>
include <stdlib.h>
include <string.h>

define N 4

typedef struct node {
    int tiles[N][N];
    short zero_row, zero_column;
    struct node *next;    // for queue/stack linkage or solution path
    struct node *parent;  // to reconstruct path
} Node;

/* Global states */
Node *start = NULL;
Node *goal = NULL;
Node *succ_nodes[4]; // to hold up to 4 successors

/* Function prototypes */
Node* initialize(char **argv);
void print_node(const Node *p);
int nodes_same(const Node *a, const Node *b);
Node* clone_node(const Node *src);
void swap_tiles(int r1, int c1, int r2, int c2, Node *p);
void move_up(Node *p);
void move_down(Node *p);
void move_left(Node *p);
void move_right(Node *p);
void expand(Node *sel);
void filter(int i, Node *list);   // for DFS duplicate removal
void reconstruct_and_print(Node *goal_node);

/* BFS queue structures */
typedef struct qnode {
    Node *state;
    struct qnode *next;
} QNode;
QNode *q_front = NULL, *q_rear = NULL;

/* BFS queue operations */
void enqueue(Node *p);
Node* dequeue(void);

/* DFS stack structure: use Node *stack_open as head of linked list */
Node *stack_open = NULL;

int main(int argc, char **argv) {
    if (argc != 18) {
        fprintf(stderr, "Usage: %s [bfs|dfs] idx0 ... idx15\n", argv[0]);
        return 1;
    }
    int use_bfs = strcmp(argv[1], "bfs") == 0;
    int use_dfs = strcmp(argv[1], "dfs") == 0;
    if (!use_bfs && !use_dfs) {
        fprintf(stderr, "First argument must be 'bfs' or 'dfs'\n");
        return 1;
    }

    /* Initialize start and goal states from argv[2..17] */
    start = initialize(argv + 1);

    if (use_bfs) {
        /* Implement BFS loop using enqueue, dequeue, expand, print, free */
    } else {
        /* Implement DFS loop with CLOSED list, using expand, filter, push/pop, print */
    }

    return 0;
}

/* initialize: parse command line into start state and create goal state */
Node* initialize(char **argv) {
    /* Allocate and fill start and goal nodes; print them */
    return NULL;  // placeholder
}

/* print_node: display 4x4 puzzle state */
void print_node(const Node *p) {
    /* Print the tiles in a 4x4 grid */
}

/* nodes_same: compare two states for equality */
int nodes_same(const Node *a, const Node *b) {
    /* Return 1 if identical, 0 otherwise */
    return 0;
}

/* clone_node: deep copy a node (except next/parent pointers) */
Node* clone_node(const Node *src) {
    /* Allocate and copy tiles and zero position; set parent */
    return NULL;
}

/* swap_tiles: swap two positions in a state's tiles array */
void swap_tiles(int r1, int c1, int r2, int c2, Node *p) {
    /* Swap tile values */
}

/* move_*: slide blank tile in one direction */
void move_up(Node *p)    { /* TODO */ }
void move_down(Node *p)  { /* TODO */ }
void move_left(Node *p)  { /* TODO */ }
void move_right(Node *p) { /* TODO */ }

/* expand: generate up to 4 successors into succ_nodes[] */
void expand(Node *sel) {
    /* For each valid direction, clone sel, apply move_*, set parent, store in succ_nodes */
}

/* filter: remove succ_nodes[i] if duplicate in given list (for DFS) */
void filter(int i, Node *list) {
    /* If succ_nodes[i] matches any node in list, free and null it */
}

/* BFS queue operations */
void enqueue(Node *p) {
    /* Add p to q_rear */
}
Node* dequeue(void) {
    /* Remove and return from q_front */
    return NULL;
}

/* reconstruct_and_print: follow parent links and print solution path */
void reconstruct_and_print(Node *gnode) {
    /* Build path from start to goal and print each state */
}
