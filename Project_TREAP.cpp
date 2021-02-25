#include <iostream>
using namespace std;


typedef class ctreenode *ctree;
/*
 * Tree Node Declaration
 */
class ctreenode
{

public :

    int key, fix, priority;
    ctree left, right;
};
ctree nullnode, root;

/*
 * Treap Class Declaration
 */
class CTree
{

public:

    void initialize()
    {
        nullnode = new ctreenode;
        nullnode->left = nullnode->right = nullnode;
        root = nullnode;
    }

    /*
     * Left Rotation
     */
    void sigrotl(ctree &k1)
    {
        ctree k2;
        k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1 = k2;
    }

    /*
     * Right Rotation
     */
    void sigrotr(ctree &k1)
    {
        ctree k2;
        k2 = k1->left;
        k1->left = k2->right;
        k2->right = k1;
        k1 = k2;
    }
    /*
     * Insert Element into Treap
     */
    void insert(ctree &t, int x)
    {
        if (t == nullnode)
            {
                t = new ctreenode;
                t->left = t->right = nullnode;
                t->key = x;
                t->fix = rand();
            }
        else
            {
                if (t->key == x)
                    {
                        return;
                    }
                else
                    {
                        if (x < t->key)
                            {
                                insert(t->left, x);
                                if (t->left->fix > t->fix)
                                    sigrotr(t);
                            }
                        else
                            {
                                insert(t->right, x);
                                if (t->right->fix > t->fix)
                                    sigrotl(t);
                            }
                    }
            }
    }

    /*
     * Remove Element from Treap
     */
    void remove(ctree &t, int x)
    {
        if (t == nullnode)
            return;
        if (x > t->key)
            remove(t->right, x);
        else if (x < t->key)
            remove(t->left, x);
        else
            {
                if (t->left == nullnode && t->right == nullnode)
                    {
                        delete t;
                        t = nullnode;
                    }
                else if (t->left == nullnode)
                    {
                        ctree tmp = t;
                        t = t->right;
                        delete tmp;
                    }
                else if (t->right == nullnode)
                    {
                        ctree tmp = t;
                        t = t->left;
                        delete tmp;
                    }
                else
                    {
                        if (t->left->fix < t->right->fix)
                            {
                                sigrotl(t);
                                remove(t->left, x);
                            }
                        else
                            {
                                sigrotr(t);
                                remove(t->right, x);
                            }
                    }
            }
    }
    /*
     * Search an element in Treap
     */
    bool find(ctree t,int x)
    {
        if(t == nullnode)
            return false;
        if(t->key == x)
            return true;
        else
            {
                if (x < t->key)
                    return find(t->left, x);
                else
                    return find(t->right, x);
            }
    }

    /*
     * Display elements of Treap
     */
    void display(ctree ptr, int level)
    {
        int i;
        if(ptr == nullnode)
            return;
        if(ptr != NULL)
            {
                display(ptr->right, level + 1);
                cout<<endl;
                if(ptr == root)
                    cout<<"Root->:  ";
                else
                    {
                        for (i = 0; i < level; i++)
                            cout<<"       ";
                    }
                cout<<ptr->key;
                display(ptr->left, level + 1);
            }
    }
        /*
         * minTOmax Travesal of Treap
         */
        void inorder(ctree ptr)
        {
            if (ptr == nullnode)
                return;
            if (ptr != NULL)
                {
                    inorder(ptr->left);
                    cout<<ptr->key<<"->";
                    inorder(ptr->right);
                }
        }
        /*
         * maxTOmin Travesal of Treap
         */
        void maximumtomin(ctree ptr1)
        {
            if (ptr1 == nullnode)
                return;
            if (ptr1 != NULL)
                {
                    maximumtomin(ptr1->right);
                    cout<<ptr1->key<<"->";
                    maximumtomin(ptr1->left);
                }
        }
        /*
        

    int main()
    {
        CTree ct;
        int choice, num;
        bool flag = false;
        ct.initialize();

        while (1)
            {
                cout<<endl<<"----------------------------"<<endl;
                cout<<endl<<"Operations on Treap"<<endl;
                cout<<endl<<"----------------------------"<<endl;
                cout<<"1.Insert Element in Treap : "<<endl;
                cout<<"2.Delete Element from Treap :"<<endl;
                cout<<"3.Minimum to Maximum Traversal"<<endl;
                cout<<"4.Maximum to Minimum Traversal"<<endl;
                cout<<"5.Search Element from Treap : "<<endl;
                
                cout<<"6.Display Treap : "<<endl;
                cout<<"7.Quit"<<endl;
                cout<<"Enter your choice : ";
                cin>>choice;


                switch(choice)
                    {

                    case 1:
                        cout<<"Enter the number to be inserted : ";
                        cin>>num;
                        ct.insert(root, num);
                        break;

                    case 2:
                        if (root == nullnode)
                            {
                                cout<<"Tree is empty, nothing to delete"<<endl;
                                continue;
                            }
                        cout<<"Enter the number to be deleted : ";
                        cin>>num;
                        if  (ct.find(root, num))
                            {
                                cout<<"Element found"<<endl;
                                flag = true;
                            }

                        else
                            cout<<"Element not found"<<endl;
                        ct.remove(root, num);
                        if (!ct.find(root, num) && flag)
                            cout<<"Element Deleted"<<endl;
                        break;
                    case 3:
                        if (root == nullnode)
                            {
                                cout<<"Tree is empty, insert element first"<<endl;
                                continue;
                            }
                        cout<<"Minimum to Maximum Traversal :"<<endl;
                        ct.inorder(root);
                        cout<<endl;
                        break;
                    case 4:
                        if (root == nullnode)
                            {
                                cout<<"Tree is empty, insert element first"<<endl;
                                continue;
                            }
                        cout<<"Maximum to Minimum Traversal"<<endl;
                        ct.maximumtomin(root);
                        cout<<endl;
                        break;
                    case 5:
                        if (root == nullnode)
                            {
                                cout<<"Tree is empty, nothing to delete"<<endl;
                                continue;
                            }
                        cout<<"Enter the number you want to Search : ";
                        cin>>num;
                        if  (ct.find(root, num))
                            {
                                cout<<"Element found"<<endl;
                                flag = true;
                            }

                        else
                            cout<<"Element not found"<<endl;
                        break;
                   
                    case 6:
                        if (root == nullnode)
                            {
                                cout<<"Tree is empty"<<endl;
                                continue;
                            }
                        cout<<"Display Treap:"<<endl;
                        ct.display(root, 1);
                        cout<<endl;
                        break;
                    case 7:
                        exit(1);
                        break;
                    default:
                        cout<<"Wrong choice"<<endl;
                    }
            }
    }
