#include<stdio.h>
#include<stdlib.h>

typedef int data_t;

typedef struct singleLinked_list
{
	data_t data;
	struct singleLinked_list* next;
}linkedlist_node;


void sort_list();
void delete_given_node();
void delete_startNode();
void delete_endNode();
int search_node(data_t);
void insert_at_start();
void display_list(linkedlist_node*);
void insert_at_end();
linkedlist_node* create_node(data_t data);
void accept_node_data(data_t* ptr);


linkedlist_node* head = NULL;
int main()
{
	int ch = -1;
	while (ch != 0)
	{
		printf("\n 0. Exit\n");
		printf("1. Display List\n");
		printf("2. Insert at End\n");
		printf("3. Insert at Start\n");
		printf("4. Delete start node\n");
		printf("5. Delete End node\n");
		printf("6. Delete Node\n");
		printf("7. Sort the List\n");
		printf("Enter your choice : ");
		scanf_s("%d", &ch);


		switch (ch)
		{
		case 1:
			display_list(head);
			break;
		case 2:
			insert_at_end();
			break;
		case 3:
			insert_at_start();
			break;
		case 4:
			delete_startNode();
			break;
		case 5:
			delete_endNode();
			break;
		case 6:
			delete_given_node();
			break;
		case 7:
			sort_list();
			break;
		}
	}
}
	void sort_list()
	{
		data_t temp;
		linkedlist_node* trav, *trav_back;

		for (trav = head; trav->next != NULL; trav = trav->next)
		{
			for (trav_back = trav->next; trav_back != NULL; trav_back = trav_back->next)
			{
				if (trav->data > trav_back->data)
				{
					temp = trav->data;
					trav->data = trav_back->data;
					trav_back->data = temp;
				}
			}
		}
	}


	void delete_given_node()
	{
		data_t element;

		linkedlist_node *trav, *trav_back;
		printf("Enter node to be deleted: ");
		scanf_s("%d", &element);

		trav = head;
		trav_back = trav;

		if (trav->data == element)
		{
			delete_startNode();
		}
		else
		{
			while (trav != NULL)
			{
				if (trav->data == element)
				{
					trav_back->next = trav->next;
					free(trav);
					trav = NULL;
					break;
				}
				else
				{
					trav_back = trav;
					trav = trav->next;
				}
			}
		}
	}

	void delete_endNode()
	{
		linkedlist_node* trav, *trav_back = NULL;

		trav = head;
		if (trav == NULL)
		{
			printf("List is already empty\n");
			exit(0);
		}

		while (trav->next != NULL)
		{
			trav_back = trav;
			trav = trav->next;
		}
		if (head == trav)
		{
			head = NULL;
		}
		else
		{
			trav_back->next = NULL;
		}

		free(trav);
		trav = NULL;
	}

	void delete_starNode()
	{
		linkedlist_node* trav;
		trav = head;


		if (trav == NULL)
		{
			printf("List is empty \n");
			exit(0);
		}
		if (head->next == NULL)
		{
			head = NULL;
		}
		else
		{
			head = head->next;
		}
		free(trav);
		trav = NULL;
	}

	void insert_at_start()
	{
		linkedlist_node* trav, *new_node;
		data_t data;


		accept_node_data(&data);

		new_node = create_node(data);

		if (head == NULL)
		{
			head = new_node;
		}
		else
		{
			new_node->next = head;
			head = new_node;
		}
		trav = NULL;
	}


	void display_list(linkedlist_node* head)
	{
		linkedlist_node* trav = head;
		printf("\n ==================================\n");
		while (trav != NULL)
		{
			printf("%d\n", trav->data);
			trav = trav->next;
		}
		printf("END \n"); 
		printf("\n===================================\n");

	}
	void insert_at_end()
	{
		data_t num;
		linkedlist_node* trav;
		linkedlist_node* new_node = NULL;

		accept_node_data(&num);

		new_node = create_node(num);

		printf("\n new node -> data = %d\n", new_node->data);

		if (head == NULL)
			head = new_node;

		else
		{
			trav = head;

			while (trav->next != NULL)
			{
				trav = trav->next;
			}
			trav->next = new_node;
		}
	}


	linkedlist_node* create_node(data_t data)
	{
		linkedlist_node* new_node;

		new_node = (linkedlist_node*)malloc(sizeof(linkedlist_node));

		if (new_node == NULL)
		{
			printf("Memory allocation error, exiting.....\n");
			exit(0);
		}

		new_node->data = data;
		new_node->next = NULL;
		return(new_node);
	}


	void accept_node_data(data_t* ptr)
	{
		printf("Enter the node data : ");
		scanf_s("%d", ptr);

	}

	void delete_startNode()
	{
		linkedlist_node* trav;
		trav = head;

		if (trav == head)
		{
			printf("List is Empty ............\n");
			exit(0);
		}
		if (head->next == NULL)
		{
			head = NULL;
		}
		else
		{
			head = head->next;
		}

		free(trav);
		trav = NULL;
	}