struct Node
{
    ElmType data;
    int count;
    struct Node *next;
};

typedef struct Node node;

// l - tree/ list/ root, cur - con tr? hi?n t?i, prev - con tr? tru?c cur
node *l, *cur, *prev, *search;
// FILE *f, *f1;

// tao node
node *create_note(ElmType x)
{
    node *tmp = (node *)malloc(sizeof(node));
    tmp->next = NULL;
    tmp->data = x;
    return tmp;
}

// Insert dau
void insert_at_head(ElmType x)
{
    // node *tmp = create_note(x);
    node *tmp = (node *)malloc(sizeof(node));
    tmp->data = x;
    tmp->next = l;
    l = tmp;
    cur = l;
    // prev = NULL;
}

// Insert cuoi
void insert_at_tail(ElmType x)
{
    node *tmp = create_note(x);
    node *tail = l;
    if (tail == NULL && tail->next == NULL)
        return;
    while (tail->next != NULL)
    {
        tail = tail->next;
    }
    tail->next = tmp;
}

// Insert sau cur
void insert_after_cur(ElmType x)
{
    node *tmp = create_note(x);
    if (l == NULL)
    {
        l = tmp;
        cur = l;
        prev = NULL;
    }
    else
    {
        if (cur == NULL)
            return;

        tmp->next = cur->next;
        cur->next = tmp;
        prev = cur;
        cur = cur->next;
    }
}

// Insert truoc cur
void insert_before_cur(ElmType x)
{
    node *tmp = create_note(x);
    if (l == NULL)
    {
        l = tmp;
        cur = l;
        prev = NULL;
    }
    else
    {
        tmp->next = cur;
        prev->next = tmp;
        prev = tmp;
    }
}

// cap nhat con tro prev neu cur != l
void update()
{
    if (cur == l)
    {
        prev = NULL;
    }
    else
    {
        node *tmp = l;
        while (tmp != NULL && cur != NULL && tmp->next != cur)
        {
            tmp = tmp->next;
        }
        prev = tmp;
    }
}

// delete head
void delete_head()
{
    node *del = l;
    if (del == NULL)
        return;
    l = del->next;
    free(del);
    cur = l;
    prev = NULL;
}

// delete current
void delete_middle()
{
    node *del = l;
    if (del == NULL)
        return;
    if (cur != l)
    {
        // Update prev pointer
        update();
    }
    prev->next = cur->next;
    cur = NULL;
    free(cur);
    cur = prev->next;
}

// xoa duoi
void delete_tail()
{
    node *del = l;
    if (del == NULL && del->next == NULL)
        return;
    while (del->next->next != NULL)
    {
        del = del->next;
    }
    del->next = NULL;
    free(del->next);
}

// dao list
void reverse_list()
{
    node *p = l;
    node *tsugi, *pre;
    tsugi = pre = NULL;
    while (p != NULL)
    {
        tsugi = p->next;
        p->next = pre;
        pre = p;
        p = tsugi;
    }
    l = pre;
    cur = l;
    prev = NULL;
}

// Input
/*void ReadNode(et *a)
{
    printf("\nEnter name: ");
    fflush(stdin); gets(a->name);
    printf("\nEnter telephone: ");
    fflush(stdin); gets(a->telephone);
    printf("\nEnter email: ");
    fflush(stdin); gets(a->email);
} */

// Output
void display_node(node *x)
{
    if (x == NULL)
    {
        printf("\nCon tro loi - NULL!\n");
        return;
    }
    ElmType tmp = x->data;
    // printf("\n%-15s%-20s%-20s%-15s\n", "Model", "Memory Space(GB)", "Screen Size (inches)", "Price");
    //  printf("%-20s%-25.2f%-25.2f%-20.2f\n", tmp.model, tmp.ms, tmp.ss, tmp.price);
}

void free_list()
{
    node *p = l;
    while (p != NULL)
    {
        l = l->next;
        free(p);
        p = l;
    }
}

void print_list()
{
    node *p = l;
    // int i = 1;
    if (p == NULL)
    {
        printf("\nCon tro NULL!\n");
        return;
    }
    while (p != NULL)
    {
        // for(i = 0; i < num; ++i)
        display_node(p);
        // printf("%-20s%-25.2f%-25.2f%-20.2f\n", a[i].model, a[i].ms, a[i].ss, a[i].price);
        p = p->next;
        // i++;
    }
    // printf("\n");
}

// Phan bai tap tuan 8
node *insert_at_position(node *t, ElmType ad, int n)
{
    node *tmp = create_note(ad);
    if (t == NULL)
    {
        t = tmp;
        cur = t;
        prev = NULL;
    }
    else
    {
        node *root = t;
        int i;
        for (i = 0; i < n - 1; ++i)
        {
            root = root->next;
        }
        cur = root;
        // cap nhat con tro prev
        update();
        tmp->next = cur->next;
        cur->next = tmp;
        prev = cur;
        cur = tmp;
        return t;
    }
}

node *delete_at_position(node *t, int n)
{
    if (t == NULL)
        return NULL;
    else
    {
        node *root = t;
        int i;
        for (i = 0; i < n - 1; ++i)
        {
            root = root->next;
        }
        node *tmp = root->next;
        root->next = tmp->next;
        free(tmp);
        cur = root;
        update();
        return t;
    }
}

node *split(node *t, int n1, int n2)
{
    node *res = NULL;
    if (t == NULL)
        return NULL;
    else
    {
        node *tmp = t;
        int i;
        if (n1 > 0)
        {
            for (i = 0; i < n1; ++i)
                tmp = tmp->next;
            cur = tmp;
            if (cur != t)
                update();
            // danh dau vi tri ket thuc
            node *mark = cur;
            for (i = 0; i < n2 - 1; ++i)
                mark = mark->next;
            // neu n1 + 1 + n2 = n
            if (mark->next == NULL)
            {
                res = cur;
                prev->next = NULL;
                return res;
            }
            else
            {
                res = cur;
                prev->next = mark->next;
                mark->next = NULL;
                return res;
            }
        }
        else
        {
            res = t;
            node *mark = res;
            for (i = 0; i < n2 - 1; ++i)
                mark = mark->next;
            l = mark->next;
            cur = l;
            prev = NULL;
            mark->next = NULL;
            return res;
        }
    }
}
