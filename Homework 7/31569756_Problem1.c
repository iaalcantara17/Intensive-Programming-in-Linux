#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 4
#define NxN (N*N)
#define TRUE 1
#define FALSE 0

struct node 
{
	int tiles[N][N];
	int f, g, h;
	short zero_row, zero_column;	/* location (row and colum) of blank tile 0 */
	struct node *next;
	struct node *parent;			/* used to trace back the solution */
};

int goal_rows[NxN];
int goal_columns[NxN];
struct node *start,*goal;
struct node *open = NULL, *closed = NULL;
struct node *succ_nodes[4];

void print_a_node (struct node *pnode) 
{
	int i, j;
	for (i = 0; i < N; i++) 
	{
		for (j = 0; j < N; j++) 
			printf("%2d ", pnode->tiles[i][j]);
		printf("\n");
	}
	printf("\n");
}

struct node *initialize (char **argv)
{
	int i, j, k, index, tile;
	struct node *pnode;

	pnode = (struct node *)malloc(sizeof(struct node));
	index = 1;
	for (j = 0; j < N; j++)
		for (k = 0; k < N; k++) 
		{
			tile = atoi(argv[index++]);
			pnode->tiles[j][k] = tile;
			if (tile == 0) 
			{
				pnode->zero_row = j;
				pnode->zero_column = k;
			}
		}

	pnode->f = 0;
	pnode->g = 0;
	pnode->h = 0;
	pnode->next = NULL;
	pnode->parent = NULL;
	start = pnode;
	printf("initial state\n");
	print_a_node(start);

	pnode = (struct node *)malloc(sizeof(struct node));
	goal_rows[0] = 3;
	goal_columns[0] = 3;

	for(index = 1; index < NxN; index++)
	{
		j = (index - 1) / N;
		k = (index - 1) % N;
		goal_rows[index] = j;
		goal_columns[index] = k;
		pnode->tiles[j][k] = index;
	}
	pnode->tiles[N - 1][N - 1] = 0;	      /* empty tile=0 */
	pnode->f = 0;
	pnode->g = 0;
	pnode->h = 0;
	pnode->next = NULL;
	goal = pnode; 
	printf("goal state\n");
	print_a_node(goal);

	return start;
}

/* merge the remaining nodes pointed by succ_nodes[] into open list. 
 * Insert nodes based on their f values --- keep f values sorted. */
void merge_to_open () 
{
	struct node *prev;
	struct node *curr;
	struct node *pnode;
	int flag = 0;
	for (int i = 0; i < 4; i++)
	{
		prev = NULL;
		curr = open;
		flag = 0;
		pnode = succ_nodes[i];
		if (pnode == NULL)
		{
			continue;
		}
		if (curr == NULL)
		{
			open = pnode;
			pnode->next = NULL;
		}
		else if (pnode->f < curr->f)
		{
			pnode->next = curr;
			open = pnode;
		}
		else
		{
			prev = curr;
			curr = curr->next;
			while (curr != NULL)
			{
				if (pnode->f < curr->f)
				{
					pnode->next = curr;
					prev->next = pnode;
					flag = 1;
					break;
				}
				prev = curr;
				curr = curr->next;
			}
			if (!flag)
			{
				prev->next = pnode;
				pnode->next = NULL;
			}

		}

	}
	
}

/*swap two tiles in a node*/
void swap (int row1, int column1, int row2, int column2, struct node * pnode)
{
	int temp = pnode->tiles[row1][column1];
	pnode -> tiles[row1][column1] = pnode -> tiles[row2][column2];
	pnode -> tiles[row2][column2] = temp;
}

/*update the f,g,h function values for a node */
void update_fgh (int i) 
{
	struct node *pnode = succ_nodes[i];
	if (pnode == NULL)
	{
		return;
	}
	pnode -> g++;
	int manTotal = 0;
	for (int x = 0; x < N; x++)
	{
		for (int y = 0; y < N; y++)
		{
			if (pnode -> tiles[x][y] == 0)
			{
				continue;
			}
			
			manTotal += abs(x-goal_rows[pnode->tiles[x][y]]) + abs(y-goal_columns[pnode->tiles[x][y]]);
		}
	}

	pnode -> h = manTotal;
	pnode -> f = pnode -> g + manTotal;
}

/* 0 goes down by a row */
void move_down (struct node * pnode)
{
	if (pnode -> zero_row + 1 > 3)
	{
		return;
	}
	else
	{

		swap (pnode -> zero_row, pnode -> zero_column, pnode -> zero_row+1, pnode -> zero_column, pnode);
		pnode->zero_row++;
	}
}

/* 0 goes right by a column */
void move_right (struct node * pnode)
{
	if (pnode -> zero_column + 1 > 3)
	{
		return;
	}
	else
	{
		swap (pnode -> zero_row, pnode -> zero_column, pnode -> zero_row, pnode -> zero_column + 1, pnode);
		pnode->zero_column++;
	}
}

/* 0 goes up by a row */
void move_up (struct node * pnode)
{
	if (pnode -> zero_row - 1 < 0)
	{
		return;
	}
	else
	{
		swap (pnode -> zero_row, pnode -> zero_column, pnode -> zero_row - 1, pnode -> zero_column, pnode);
		pnode->zero_row--;
	}
}

/* 0 goes left by a column */
void move_left (struct node * pnode)
{
	if (pnode -> zero_column - 1 < 0)
	{
		return;
	}
	else
	{
		swap (pnode -> zero_row, pnode -> zero_column, pnode -> zero_row, pnode -> zero_column - 1, pnode);
		pnode->zero_column--;
	}
}


int nodes_same (struct node *a,struct node *b) 
{
	int flg = FALSE;
	if (memcmp(a->tiles, b->tiles, sizeof(int)*NxN) == 0)
		flg = TRUE;
	return flg;
}

/* expand a node, get its children nodes, and organize the children nodes using
 * array succ_nodes.
 */
void expand (struct node *selected) 
{
	for (int i = 0; i < 4; i++)
	{
		struct node *succ = (struct node *)malloc(sizeof(struct node));
		*succ = *selected;
		if (i == 0)
		{
			move_down(succ);
		}

		else if (i == 1)
		{
			move_left(succ);
		}

		else if (i == 2)
		{
			move_up(succ);
		}

		else if (i == 3)
		{
			move_right(succ);
		}

		if (nodes_same(succ, selected))
		{
			succ_nodes[i] = NULL;
		}
		else
		{
			succ_nodes[i] = succ;
		}
		if (succ_nodes[i] != NULL)
		{
			succ_nodes[i]->parent=selected;
		}
	}
}


/* Filtering. Some states in the nodes pointed by succ_nodes may already be included in 
 * either open or closed list. There is no need to check these states. Release the 
 * corresponding nodes and set the corresponding pointers in succ_nodes to NULL. This is 
 * important to reduce execution time.
 * This function checks the (i)th node pointed by succ_nodes array. You must call this
 * function in a loop to check all the nodes in succ_nodes. Free the successor node and 
 * set the corresponding pointer to NULL in succ_node[] if a matching node is found in 
 * the list.
 */ 
void filter (int i, struct node *pnode_list)
{ 
	struct node *pnode = succ_nodes[i];

	struct node *curr = pnode_list;
	while (curr != NULL)
	{
		if (pnode == NULL)
		{
			break;
		}
		else if (nodes_same(curr, pnode))
		{
			free(pnode);
			succ_nodes[i] = NULL;
		}
		else
		{
			curr = curr->next;
		}
	}
}

int main (int argc,char **argv) 
{
	if (argc != 17)
	{
		fprintf(stderr,
				"Usage: %s index0 index1 ... index 15\n"
				"    (exactly 16 tile values 0-15)\n",
				argv[0]);
		return EXIT_FAILURE;
	}
	int iter;
	struct node *copen, *solution_path;
	int i, pathlen = 0;
	int found = 0;

	solution_path = NULL;
	start = initialize(argv);	/* init initial and goal states */
	open = start; 

	iter = 0; 
	while (open != NULL) 
	{	/* Termination cond with a solution is tested in expand. */
		copen = open;
		open = open->next;  /* get the first node from open to expand */
		
		/* DEBUG: print the node (layout) in *copen 
		 * Fix segmentation faults first. If the program cannot produce correct results,
		 * select an initial layout close to the goal layout, and debug the program with it.
		 * gdb is recommended. You may also print data on the screen. But this is not as
		 * convenient as using gdb.
		 * */

		if (nodes_same(copen,goal))
		{ /* goal is found */
			do
			{ /* trace back and add the nodes on the path to a list */
				copen->next = solution_path;
				solution_path = copen;
				copen = copen->parent;
				pathlen++;
			} 
			while (copen != NULL);
			printf("Path (length=%d):\n", pathlen); 
			copen = solution_path;
			found = 1;

			/* print out the nodes on the list */

			while (copen != NULL)
			{
				print_a_node(copen);
				copen = copen->next;
			}
			break;
		}
		expand(copen);       /* Find new successors */

		/* DEBUG: print the layouts/nodes organized by succ_nodes[] */

		for(i = 0; i < 4; i++)
		{

			filter(i,open);
			filter(i,closed);
			update_fgh(i);
		}

		/* DEBUG: print the layouts/modes remaining in succ_nodes[] */

		merge_to_open(); /* New open list */

		/* DEBUG: print the layouts/nodes on the open list */

		copen->next = closed;
		closed = copen;		/* New closed */
		/* print out something so that you know your 
		 * program is still making progress 
		 */
		iter++;
		if (iter % 1000 == 0)
			printf("iter %d\n", iter);
	}
	if (!found)
	{
		printf("no solution\n");
	}
	return 0;
} /* end of main */
