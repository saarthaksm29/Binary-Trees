#include <bits/stdc++.h>
using namespace std;

class node
{
public:
    int data;
    node *left;
    node *right;

    node(int d)
    {
        data = d;
        left = NULL;
        right = NULL;
    }
};

node *buildtree()
{
    int n;
    cin >> n;

    if (n == -1)
    {
        return NULL;
    }
    node *root = new node(n);
    root->left = buildtree();
    root->right = buildtree();
    return root;
}

void printpreorder(node *root)
{
    if (root == NULL)
    {
        return;
    }
    cout << root->data << " ";
    printpreorder(root->left);
    printpreorder(root->right);
}

void printinorder(node *root)
{
    if (root == NULL)
    {
        return;
    }
    printinorder(root->left);
    cout << root->data << " ";
    printinorder(root->right);
}

void printpostorder(node *root)
{
    if (root == NULL)
    {
        return;
    }

    printpostorder(root->left);
    printpostorder(root->right);
    cout << root->data << " ";
}

void levelorderbuild(node *root)
{
    int d;
    cin >> d;

    root = new node(d);
    queue<node *> qu;
    qu.push(root);

    while (!qu.empty())
    {
        node *f = qu.front();
        qu.pop();

        int d1, d2;
        cin >> d1 >> d2;

        if (d1 != -1)
        {
            f->left = new node(d1);
            qu.push(f->left);
        }
        if (d2 != -1)
        {
            f->right = new node(d2);
            qu.push(f->right);
        }
    }
}

int height(node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    int ls = height(root->left);
    int rs = height(root->right);
    return max(ls, rs) + 1;
}

void printkthlevel(node *root, int k)
{
    if (root == NULL)
    {
        return;
    }
    if (k == 1)
    {
        cout << root->data << " ";
        return;
    }
    printkthlevel(root->left, k - 1);
    printkthlevel(root->right, k - 1);
    return;
}

void printallevels(node *root)
{
    int h = height(root);
    for (int i = 1; i <= h; i++)
    {
        printkthlevel(root, i);
        cout << endl;
    }
    return;
}

void bfs(node *root)
{
    // storing the address of the node in the queue so that while adding its children
    // we know which node needs to be accessed and popped
    queue<node *> q;
    q.push(root);
    q.push(NULL);
    while (!q.empty())
    {
        node *f = q.front();
        if (f == NULL)
        {
            cout << endl;
            q.pop();
            if (!q.empty())
            {
                q.push(NULL);
            }
        }
        else
        {
            cout << f->data << " ";
            q.pop();

            if (f->left)
            {
                q.push(f->left);
            }
            if (f->right)
            {
                q.push(f->right);
            }
        }
    }
}

int count(node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    return 1 + count(root->left) + count(root->right);
}

int sum(node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    int ans = root->data;
    int left = sum(root->left);
    int right = sum(root->right);
    return ans + left + right;
}

int diameter(node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    int h1 = height(root->left);
    int h2 = height(root->right);

    int op1 = h1 + h2;
    int op2 = diameter(root->left);
    int op3 = diameter(root->right);

    return max({op1, op2, op3});
}

class pairr
{
public:
    int height;
    int diameter;
};

pairr fastdiameter(node *root)
{
    pairr p;
    if (root == NULL)
    {
        p.height = p.diameter = 0;
        return p;
    }
    pairr left = fastdiameter(root->left);
    pairr right = fastdiameter(root->right);

    p.height = max(left.height, right.height) + 1;
    p.diameter = max({left.height + right.height, left.diameter, right.diameter});
    return p;
}

int replacesum(node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    if (root->left == NULL and root->right == NULL)
    {
        return root->data;
    }
    int leftsum = replacesum(root->left);
    int rightsum = replacesum(root->right);
    int temp = root->data;
    root->data = leftsum + rightsum;
    return temp + root->data;
}

bool isBalanced(node *root)
{
    if (root == NULL)
    {
        return true;
    }
    if (isBalanced(root->left) == false)
    {
        return false;
    }
    if (isBalanced(root->right) == false)
    {
        return false;
    }
    int leftheight = height(root->left);
    int rightheight = height(root->right);

    if (abs(leftheight - rightheight) <= 1)
    {
        return true;
    }
    return false;
}

class hbpair
{
public:
    int height;
    bool balance;
};

hbpair isbalancedtree(node *root)
{
    hbpair p;
    if (root == NULL)
    {
        p.height = 0;
        p.balance = true;
        return p;
    }
    hbpair left = isbalancedtree(root->left);
    hbpair right = isbalancedtree(root->right);

    p.height = max(left.height, right.height) + 1;
    if (abs(left.height - right.height) <= 1 and left.balance and right.balance)
    {
        p.balance = true;
    }
    else
    {
        p.balance = false;
    }
    return p;
}

//method to build balanced binary tree
node *buildtreefromarray(int *a, int s, int e)
{
    if (s > e)
    {
        return NULL;
    }
    int mid = (s + e) / 2;
    node *root = new node(a[mid]);
    root->left = buildtreefromarray(a, s, mid - 1);
    root->right = buildtreefromarray(a, mid + 1, e);
    return root;
}

node *createtreefromtraversal(int *in, int *pre, int s, int e)
{
    static int i = 0;
    if (s > e)
    {
        return NULL;
    }
    node *root = new node(pre[i]);
    int index = -1;
    for (int j = s; s <= e; j++)
    {
        if (in[j] == pre[i])
        {
            index = j;
            break;
        }
    }

    i++;
    root->left = createtreefromtraversal(in, pre, s, index - 1);
    root->right = createtreefromtraversal(in, pre, index + 1, e);
    return root;
}

void printrightview(node *root, int level, int &maxlevel)
{
    if (root == NULL)
    {
        return;
    }
    if (maxlevel < level)
    {
        cout << root->data << " ";
        maxlevel = level;
    }
    printrightview(root->right, level + 1, maxlevel);
    printrightview(root->left, level + 1, maxlevel);
}

void printrightviewaman(node *root) //better approach for right view
{
    if (root == NULL)
    {
        return;
    }
    queue<node *> qu;
    qu.push(root);
    while (!qu.empty())
    {
        int n = qu.size();
        for (int i = 0; i < n; i++)
        {
            node *f = qu.front();
            qu.pop();
            if (i == n - 1)
            {
                cout << f->data << " ";
            }
            if (f->left != NULL)
            {
                qu.push(f->left);
            }
            else
            {
                qu.push(f->right);
            }
        }
    }
}

istream &operator>>(istream &is, node *&root)
{
    levelorderbuild(root);
    return is;
}

// k distance from the root node
void printatlevelk(node *root, int k)
{
    if (root == NULL)
    {
        return;
    }
    if (k == 0)
    {
        cout << root->data << " ";
        return;
    }

    printatlevelk(root->left, k - 1);
    printatlevelk(root->right, k - 1);
}

int printatdistancek(node *root, node *target, int k)
{
    if (root == NULL)
    {
        return -1;
    }
    if (root == target)
    {
        printatlevelk(target, k);
        return 0;
    }
    int dl = printatdistancek(root->left, target, k);
    if (dl != -1)
    {
        if (dl + 1 == k)
        {
            cout << root->data << " ";
        }
        else
        {
            printatlevelk(root->right, k - 2 - dl);
        }
        return 1 + dl;
    }

    int dr = printatdistancek(root->right, target, k);
    if (dr != -1)
    {
        if (dr + 1 == k)
        {
            cout << root->data << " ";
        }
        else
        {
            printatlevelk(root->left, k - 2 - dr);
        }
        return 1 + dr;
    }
    return -1;
}

node *lca(node *root, int a, int b)
{
    if (root == NULL)
    {
        return NULL;
    }
    if (root->data == a or root->data == b)
    {
        return root;
    }
    node *leftans = lca(root->left, a, b);
    node *rightans = lca(root->right, a, b);

    if (leftans and rightans)
    {
        return root;
    }

    if (leftans)
    {
        return leftans;
    }
    return rightans;
}

class Pair
{
public:
    int branchsum;
    int maxsum;

    Pair()
    {
        branchsum = 0;
        maxsum = 0;
    }
};

Pair maxsumpath(node *root)
{
    Pair p;
    if (root == NULL)
    {
        return p;
    }

    Pair left = maxsumpath(root->left);
    Pair right = maxsumpath(root->right);

    int op1 = root->data;
    int op2 = root->data + left.branchsum + right.branchsum;
    int op3 = root->data + left.branchsum;
    int op4 = root->data + right.branchsum;

    int current_ans_through_root = max({op1, op2, op3, op4});

    p.branchsum = max({left.branchsum, right.branchsum, 0}) + root->data;
    p.maxsum = max({left.branchsum, right.branchsum, current_ans_through_root});
    return p;
}

//finding the level of a given node from root/any given node
int search(node *root, int key, int level)
{
    if (root == NULL)
    {
        return -1;
    }
    if (root->data == key)
    {
        return level;
    }
    int left = search(root->left, key, level + 1);
    if (left != -1)
    {
        return left;
    }
    return search(root->right, key, level + 1);
}
//function to find distance b/w 2 nodes
int finddistance(node *root, int a, int b)
{
    node *lca_node = lca(root, a, b);

    int l1 = search(lca_node, a, 0);
    int l2 = search(lca_node, b, 0);
    return l1 + l2;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    // node *root = buildtree();

    // printpreorder(root);
    // cout << endl;
    // printinorder(root);
    // cout << endl;
    // printpostorder(root);
    // cout << endl;

    // int length = height(root);
    // cout << length << endl;
    // printkthlevel(root, 3);
    // printallevels(root);
    // bfs(root);
    // cout << count(root) << endl;

    // pairr p;
    // p = fastdiameter(root);
    // cout << p.height << endl;
    // cout << p.diameter << endl;

    // bfs(root);
    // cout << endl;
    // replacesum(root);
    // bfs(root);

    // hbpair p;
    // if (isbalancedtree(root).balance)
    // {
    //     cout << "Yes balanced" << endl;
    // }
    // else
    // {
    //     cout << "Not balanced" << endl;
    // }

    // int a[] = {1, 2, 3, 4, 5, 6, 7};
    // int n = sizeof(a) / sizeof(int);
    // node *root = buildtreefromarray(a, 0, n - 1);
    // bfs(root);

    // int in[] = {3, 2, 8, 4, 1, 6, 7, 5};
    // int pre[] = {1, 2, 3, 4, 8, 5, 6, 7};
    // int n = sizeof(in) / sizeof(int);
    // node *root = createtreefromtraversal(in, pre, 0, n - 1);
    // bfs(root);
    node *root = NULL;
    cin >> root;
    int a = 7, b = 9;

    cout << lca(root, 4, 7)->data;
    return 0;
}