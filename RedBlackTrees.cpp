/*The Red Black trees are termed as Self balancing trees... They have many unique properties that are listed here... 
The Root Node is always black in color... The Children of a Red parent are always Black... Every External 
Node ( Null Nodes ) is black... All External Nodes ( Null Nodes ) have the same black depth...*/
#include <iostream>
using namespace std;
class Node              // Node class for creating attributes of a Node of Red Black tree
{
    public:        // Data Members
    int data;
    Node* left;
    Node* right;
    string color;
    Node* parent;
    bool empty;
    Node(int val)        // Parametrized Constructor
    {
        data = val;
        left = NULL;
        right = NULL;
        color = "Red";    // Default Color set to Black
        parent = NULL;
        empty = true;
    }
};
Node *newNode(int val)      // Node to create and specify parent pointer dynamically
{
    Node *node = new Node(val);
    node -> data = val;
    node -> left = node -> right = node -> parent = NULL;   // Left, Right and Parent are specified to Null
    node -> color = "Red";      // Default Color set to Black
    return node;
}
class RedBlackTree 
{
    private:
    Node* root;
    public:
    Node* InsertNodeInTree(Node* root,int val)
    {
        if(root == NULL) 
        {
            Node* n = new Node(val);
            n -> color = "Red";          // All other Nodes are colored red by default
            return n;
        }
        if(val <= root -> data)
        {
            root -> left = InsertNodeInTree(root -> left, val);
            root -> left -> parent = root;
        }
        else
        {
            root -> right = InsertNodeInTree(root -> right, val);
            root -> right -> parent = root;
        }
        return root;
    }
    public:
    void DisplayTree(Node* root)
    {
        if(root == NULL)
            return;
        DisplayTree(root -> left);
        cout << "Node : " << endl;
        if(root -> left != NULL)
            cout << "\t" << root -> data << " ---> " << root -> left -> data << "\t Left (Occupied)" << endl;
        if(root -> left == NULL)
            cout << "\t" << root -> data << " ---> Null " << "\t Left (Empty)" << endl;
        if(root -> right != NULL)
            cout << "\t" << root -> data << " ---> " << root -> right -> data << "\t Right (Occupied)" << endl;
        if(root -> right == NULL)
            cout << "\t" << root -> data << " ---> Null " << "\t Right (Empty)" << endl;
        cout << "\t" << root -> color << "\t\t (Node Color)" << endl;
        DisplayTree(root -> right);
    }
    public:
    void ChildNodesAreBlack(Node* root)
    {
        if(root == NULL)
            return;
        if(root -> color == "Red")
        {
            if(root -> left)
                root -> left -> color = "Black";
            if(root -> right)
                root -> right -> color = "Black";
        }
        ChildNodesAreBlack(root -> left);
        ChildNodesAreBlack(root -> right);
        return;
    }
    public:
    Node* GetSibling(Node* temp)
    {
        Node* t = temp;
        if(temp -> parent == NULL)
            return NULL;
        if(temp -> parent -> parent == NULL)
            return temp -> parent;
        if(temp -> parent -> parent -> left == temp -> parent)
            t = temp -> parent -> parent -> right;
        if(temp -> parent -> parent -> right == temp -> parent)
            t = temp -> parent -> parent -> left;
        return t;
    }
    public:
    void CheckRotatingCondition(Node* temp)
    {
        if(root -> parent == NULL)
            return;
        Node* t = GetSibling(temp);
        if(temp -> parent -> color == "Red" && temp -> color == "Red")
        {
            t -> color = "Black";
            temp -> parent -> color = "Black";
        }
        return;
    }
    void FixTree(Node* node)
    {
        while(node -> parent -> color == "Red" && node != root)
        {
            if(node -> parent == node -> parent -> parent -> left)
            {
                Node* uncle = node -> parent -> parent -> right;
                if(uncle -> color == "Red")
                {
                    node -> parent -> color = "Black";
                    node -> parent -> parent -> color = "Red";
                    uncle -> color = "Black";
                    node = node -> parent -> parent;
                }
                else
                {
                    if(node == node -> parent -> right)
                    {
                        node = node -> parent;
                        LeftRotate(node);
                    }
                    node -> parent -> color = "Black";
                    node -> parent -> parent -> color = "Red";
                    RightRotate(node -> parent -> parent);
                }
            }
            else
            {
                Node* uncle = node -> parent -> parent -> left;
                if(uncle -> color == "Red")
                {
                    node -> parent -> color = "Black";
                    uncle -> color = "Red";
                    node -> parent -> parent -> color = "Red";
                    node = node -> parent -> parent;
                }
                else
                {
                    if(node == node -> parent -> left)
                    {
                        node = node -> parent;
                        RightRotate(node);
                    }
                    node -> parent -> color = "Black";
                    node -> parent -> parent -> color = "Red";
                    LeftRotate(node -> parent -> parent);
                }
            }
            root -> color = "Black";
        }
    }
    void LeftRotate(Node* node)
    {
        Node* sibling = node -> right;
        node -> right = sibling -> left;
        if(sibling -> left != NULL)
        {
            sibling -> left -> parent = node;
        }
        sibling -> parent = node -> parent;
        if(node -> parent == NULL)
            root = node;
        else 
        {
            if(node == node -> parent -> left)
                node -> parent -> left = sibling;
            else
                node -> parent -> right = sibling;
        }
        sibling -> left = node;
        node -> parent = sibling;
    }
    void RightRotate(Node* node)
    {
        Node* sibling = node -> left;
        node -> left = sibling -> right;
        if(sibling -> right != NULL)
        {
            sibling -> right -> parent = node;
        }
        sibling -> parent = node -> parent;
        if(node -> parent == NULL)
            root = node;
        else 
        {
            if(node == node -> parent -> right)
                node -> parent -> right = sibling;
            else
                node -> parent -> left = sibling;
        }
        sibling -> right = node;
        node -> parent = sibling;
    }
};
int main()
{
    Node* root = NULL;
    RedBlackTree redblacktree;
    int s, x;
    cout << "Insert value of Root Node for the Red Black Tree : ";
    cin >> x;
    root = redblacktree.InsertNodeInTree(root, x);
    root -> color = "Black";
    cout << "Enter the Number of Operations to be performed : ";
    cin >> s;
    for(int loop = 1; loop <= s; loop++)
    {
        cout << "Enter the value of the new Node : ";
        cin >> x;
        root = redblacktree.InsertNodeInTree(root, x);
        cout << loop << " th Operation !!" << endl;
        redblacktree.FixTree(root);
        cout << " ==================================================================" << endl;
        redblacktree.DisplayTree(root);
        cout << " ==================================================================" << endl;
        cout << endl;
    }
    return 0;
}