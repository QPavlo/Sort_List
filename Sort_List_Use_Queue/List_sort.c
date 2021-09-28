#include <stdio.h>
#include <stdlib.h>

typedef struct list
{
    int key;
    struct list* next;
} list_t;

typedef struct node_of_list
{
    list_t ptr;
} node_l;

typedef struct
{
    int size;
    node_l* head;
    node_l* tail;
} queue_t;

void queue_init(queue_t*);
int queue_push(queue_t*, list_t);
void queue_pop(queue_t*);
list_t queue_front(queue_t*);
int queue_empty(queue_t*);
void queue_print(queue_t*);
void clear_queue(queue_t*);
void getData(list_t**, int*);
list_t* insert(list_t*, int);
void printList(list_t*);
queue_t sort_q(list_t*, int);
list_t* deletelem(list_t*, list_t*);
list_t* deletehead(list_t*);

int main()
{
    int _count = 0;
    list_t* li = NULL;
    queue_t q;
    getData(&li, &_count);
    printList(li);
    q = sort_q(li, _count);
    queue_print(&q);
    clear_queue(&q);
    printf("\n\n\n\n");
    system("pause");
    return 0;
}

list_t* insert(list_t* node, int data)
{
    list_t* tmp = (list_t*)malloc(sizeof(list_t));
    if (tmp != NULL)
    {
        tmp->key = data;
        tmp->next = NULL;
    }
    return tmp;
}

void getData(list_t** adr_root, int* count)
{
    int tmp;
    printf(" Input elemens (input char to stop input data) : ");
    while (scanf_s("%d", &tmp) != 0)
    {
        *adr_root = insert(*adr_root, tmp);
        adr_root = &(*adr_root)->next;
        *count += 1;
    }
}

queue_t sort_q(list_t* root, int count)
{
    queue_t q;
    queue_init(&q);
    list_t* min = root, * temp = root;
    int j = 0;

    for (int i = 0; i < count; i++)
    {
        for (j = 0, temp = root; (j < count - i && temp != NULL); j++, temp = temp->next)
        {
            if (temp->key <= min->key)
            {
                min = temp;
            }
        }
        if (min != NULL)
        {
            queue_push(&q, *min);
            if (min->key == root->key)
            {
                root = deletehead(root);
            }
            else
            {
                deletelem(min, root);
            }
            min = root;
        }
    }
    return q;
}

void printList(list_t* node)
{
    printf("\n inputed list\n");
    for (list_t* temp = node; temp != NULL; temp = temp->next)
    {
        printf(" %d ", temp->key);
    }
    printf("\n");
}

list_t* deletelem(list_t* lst, list_t* root)
{
    list_t* temp = root;
    while (temp->next != lst)
    {
        temp = temp->next;
    }
    temp->next = lst->next;
    free(lst);
    return(temp);
}

list_t* deletehead(list_t* root)
{
    list_t* temp;
    temp = root->next;
    free(root);
    return(temp);
}

void queue_init(queue_t* q)
{
    q->head = q->tail = NULL;
    q->size = 0;
}

int queue_empty(queue_t* q)
{
    return (q->head == NULL);
}

list_t queue_front(queue_t* q)
{
    if (q->head != NULL)
    {
        return q->head->ptr;
    }
}

int queue_push(queue_t* q, list_t ptr)
{
    node_l* p = (node_l*)malloc(sizeof(node_l));
    if (p != NULL)
    {
        p->ptr = ptr;
        p->ptr.next = NULL;
        if (q->head == NULL)
        {
            q->head = q->tail = p;
            q->size = 1;
        }
        else
        {
            q->tail->ptr.next = p;
            q->tail = p;
            q->size++;
        }
    }
    return (p != NULL);
}

void queue_pop(queue_t* q)
{
    node_l* t;
    if (q->head != NULL)
    {
        t = q->head;
        q->head = q->head->ptr.next;
        free(t);
        if (q->head == NULL)
        {
            q->tail = NULL;
        }
        q->size--;
    }
}

void queue_print(queue_t* q)
{
    printf("\n sorted list \n");
    for (int i = 0, q_size = q->size; i < q_size; i++)
    {
        printf(" %d ", queue_front(q).key);
        queue_push(q, queue_front(q));
        queue_pop(q);
    }
}

void clear_queue(queue_t* q)
{
    while (!queue_empty(q))
    {
        queue_pop(q);
    }
}