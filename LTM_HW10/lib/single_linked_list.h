// cap nhat con tro prev neu cur != root
void update()
{
    node *tmp = root;
    while (tmp != NULL && cur != NULL && tmp->next != cur)
    {
        tmp = tmp->next;
    }
    pre = tmp;
}

node *makeNewNode(AccountList new_e)
{

    node *new;
    new = (node *)malloc(sizeof(node));
    new->element = new_e;
    new->next = NULL;
    return new;
}

// them vao dau danh sach
void insertAtHead(node *r, AccountList new_e)
{
    node *new = makeNewNode(new_e);
    if (r == NULL)
    {
        r = new;
        pre = NULL;
        cur = r;
    }
    new->next = r;
    r = new;
    cur = r;
    pre = NULL;
}

// them vao sau con tro cur
void insertAfterCur(node *r, AccountList new_e)
{
    if (cur == NULL)
    {
        printf("Loi con tro current!\n");
        return;
    }
    node *new = makeNewNode(new_e);
    if (r == NULL)
    {
        r = new;
        cur = r;
        pre = NULL;
        return;
    }
    else
    {
        new->next = cur->next;
        cur->next = new;
        pre = cur;
        cur = cur->next;
    }
}

// them vao truoc con tro cur
void insertBeforeCur(node *r, AccountList new_e)
{
    node *new = makeNewNode(new_e);
    if (r == NULL)
    {
        r = new;
        cur = r;
        pre = NULL;
    }
    else
    {
        new->next = cur;
        if (cur == r)
        {
            r = new;
        }
        else
        {
            pre->next = new;
        }
        cur = new;
    }
}

// tim vi tri prev
void findPrev(node *r)
{
    node *tmp;
    tmp = r;
    while (tmp != NULL && tmp->next != cur && cur != NULL)
    {
        tmp = tmp->next;
    }
    pre = tmp;
}

// xoa node dau
void deleteNodeFirst(node *r)
{
    node *del = r;
    if (del == NULL)
    {
        return;
    }
    r = del->next;
    free(del);
    cur = r;
    pre = NULL;
}

// xoa node o vi tri con tro hien tai
void deleteNodeCur(node *r)
{
    node *del = r;
    if (del == NULL)
        return;
    if (cur != r)
    {
        update();
    }
    pre->next = cur->next;
    cur = NULL;
    free(cur);
    cur = pre->next;
}

// dao list
void reverseList(node *r)
{
    node *new = r;
    node *tsugi, *pre;
    tsugi = pre = NULL;
    while (new != NULL)
    {
        tsugi = new->next;
        new->next = pre;
        pre = new;
        new = tsugi;
    }
    r = pre;
    cur = r;
    pre = NULL;
}

// xoa List
void freeList(node *r)
{
    node *to_free = r;
    // to_free = (node*)malloc(sizeof(node));
    while (to_free != NULL)
    {
        r = r->next;
        free(to_free);
        to_free = r;
    }
}

// in node
void displayNode(node *x)
{
    if (x == NULL)
    {
        // printf("Khong du bo nho cap phat!");
        return;
    }
    // int p = x->data;
    printf("%-10s%-10s%-5d\n\n", x->element.username, x->element.password, x->element.status);
}

// in list
void printList(node *r)
{
    if (r == NULL)
    {
        printf("Loi con tro NULL\n");
        return;
    }
    node *tmp;
    tmp = r;

    while (tmp != NULL)
    {
        displayNode(tmp);
        tmp = tmp->next;
    }
    printf("\n");
}

// them node vao vi tri x
void InsertAtPos(node *r, AccountList new_e, int x)
{
    if (r == NULL)
    {
        root = (node *)malloc(sizeof(node));
        root->element = new_e;
        return;
    }
    node *iter = r;
    /*for(; iter->next != NULL; iter = iter->next)
        ;*/
    while ((--x) && iter->next != NULL)
    {
        iter = iter->next;
    }
    node *new = iter->next;

    iter->next = (node *)malloc(sizeof(node));
    // iter->next = new;
    iter = iter->next;
    iter->next = new;
    iter->element = new_e;
}

// xoa node tai vi tri x
void deletaAtPos(node *r, int x)
{
    if (r == NULL)
    {
        return;
    }
    else
    {
        node *del = r;
        if (x == 0)
            deleteNodeFirst(root);
        else
        {
            while ((--x) && del->next != NULL)
            {
                pre = del;
                del = del->next;
            }
            pre->next = del->next;
            free(del);
        }
    }
}

//
node *split(node *r, int fi, int num)
{

    node *res = NULL;
    if (r == NULL)
        return NULL;
    else
    {
        node *tmp = r;
        int i;
        for (i = 0; i < fi; ++i)
        {
            tmp = tmp->next;
        }
        cur = tmp;
        update();
        // danh dau vi tri ket thuc
        node *mark = cur;
        for (i = 0; i < num - 1; ++i)
        {
            mark = mark->next;
        }
        // neu n1 + 1 + n2 = n
        if (mark->next == NULL)
        {
            res = cur;
            pre->next = NULL;
            return res;
        }
        else
        {
            res = cur;
            pre->next = mark->next;
            mark->next = NULL;
            return res;
        }
    }
}

// Check username
int checkUsername(char enterUsername[20], node *r)
{
    if (r == NULL)
    {
        printf("Loi con tro NULL\n");
        return 1;
    }
    node *tmp;
    tmp = r;

    while (tmp != NULL)
    {
        if (strcmp(enterUsername, tmp->element.username) == 0)
        {
            cur = tmp;
            return 0;
        }
        tmp = tmp->next;
    }
    return 1;
}

// Check username
int checkPassword(char enterPassword[20])
{
    if (cur == NULL)
    {
        printf("Loi con tro cur == NULL\n");
        return 1;
    }
    if (strcmp(enterPassword, cur->element.password) == 0)
        return 0;
    return 1;
}

// kich hoat acc
int activateAccount(char username[20])
{
    checkUsername(username, root);
    cur->element.status = 1;
    return 0;
}
// khoa acc
int lockAcc(char username[20])
{
    checkUsername(username, root);
    cur->element.status = 0;
    return 0;
}