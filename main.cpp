#include <iostream>
using namespace std;

template <typename Key, typename Info>
class dictionary{
private:
    struct Node {
        Key key;
        Info info;
        int h;//height
        Node *rlink, *llink;
    };
    Node *root;
public:
    //-------------------- Constructor --------------------
    dictionary<Key, Info>(){
        root = NULL;
    }
    //--------------------- greater ------------------
    Key max(const Key &a, const Key &b){
        return (a > b)? a : b;
    }
    //--------------------- Height ------------------
    int height(Node *&roota){
        if (roota == NULL)
            return 0;
        return roota->h;
    }
    //--------------------- insert ------------------
    void insert(const Key &ke,const Info &in);
    //--------------------- insertAVL ------------------
    void insertAVL(Node *&roota, Node *&newnode);
    //--------------------- deleteNode ------------------
    bool del(Node *&roota,const Key &key);
    //--------------------- del ------------------
    bool deleteNode(const Key &key);
    //--------------------- balance ------------------
    void balance(Node *&roota,const Key &key);
    //--------------------- get balance ------------------
    int getBalance(Node *&roota){
        if (roota == NULL)
            return 0;
        return height(roota->llink)-height(roota->rlink);
    }
    //-------------------- smallestInorder --------------------
    Node* smallestInorder(Node *&rootb){
        Node * curr = rootb;
    //cout<<"SMALLEST IN ORDER: "<<curr->key<<endl;
    while (curr->llink != NULL)
        curr = curr->llink;
    return curr;
    //cout<<"SMALLEST IN ORDER: "<<curr->key<<endl
    }
    //-------------------- print --------------------
    void print();

    //-------------------- printinorder --------------------
    void printinorder(Node *&roota) const;
    //-------------------- printpreorder --------------------
    void printpreorder(Node *&roota) const;
    //-------------------- printpostorder --------------------
    void printpostorder(Node *&roota) const;
    //--------------------- leftrotation ------------------
    Node* leftRotation(Node *&roota){
            struct Node *y = roota->rlink;
    struct Node *T2 = y->llink;
    y->llink = roota;
    roota->rlink = T2;
    roota->h = max(height(roota->llink), height(roota->rlink))+1;
    y->h = max(height(y->llink), height(y->rlink))+1;
    return y;
    }
    //--------------------- rightrotation ------------------
    Node* rightRotation(Node *roota){
        struct Node *x = roota->llink;
    struct Node *T2 = x->rlink;
    x->rlink = roota;
    roota->llink = T2;
    roota->h = max(height(roota->llink), height(roota->rlink))+1;
    x->h = max(height(x->llink), height(x->rlink))+1;
    return x;
    }
};

/// -|-|-|-|-|-|-|-|-|-| main() -|-|-|-|-|-|-|-|-|-|
int main()
{
    dictionary<int,int> tree;
    cout << "Creating new tree" << endl;
    tree.insert(40,1);
    tree.insert(30,1);
    tree.insert(20,1);
    tree.insert(60,1);
    tree.insert(50,1);
    tree.insert(80,1);
    tree.insert(15,1);
    tree.insert(28,1);
    tree.insert(25,1);
    tree.print();
    tree.deleteNode(50);
    tree.print();

}
//--------------------- smallestInorder ------------------
/*template <typename Key, typename Info>
void dictionary<Key, Info>::smallestInorder(Node *&rootb){
    Node * curr = rootb;
    //cout<<"SMALLEST IN ORDER: "<<curr->key<<endl;
    while (curr->llink != NULL)
        curr = curr->llink;
    rootb = curr;
    //cout<<"SMALLEST IN ORDER: "<<curr->key<<endl;
}*/
//--------------------- deleteNode ------------------
template <typename Key, typename Info>
bool dictionary<Key,Info>::deleteNode(const Key &_key){
    if (root == NULL)//Condition for recursive algorithm
        return false;
    else
        del(root,_key);
    return true;
}
//--------------------- del ------------------
template <typename Key, typename Info>
bool dictionary<Key,Info>::del(Node*& roota,const Key &_key){
    //Check in which sub-tree is the key allocated
    cout<<"DELETING node"<<roota->key<<"KEY "<<_key<<endl;
    if (_key<roota->key)
        del(roota->llink,_key);
    else if(_key>roota->key)
        del(roota->rlink,_key);
    else{
    //current node is going to be deleted, one or no child
        if((roota->llink == NULL)||(roota->rlink==NULL)){
            //only one child
            //Node *t = roota->llink;
            //cout<<"CONTROL node"<<roota->key<<"KEY "<<_key<<endl;
            if (roota->llink == NULL&&roota->rlink == NULL){
            //cout<<"CONTROL node nullnull"<<roota->key<<"KEY "<<_key<<endl;
                //it will get either NULL(leaf) or the value of the right (and only)child
                roota=NULL;

            }
            else if (roota->llink != NULL)// only one
                roota=roota->llink;//In case the only child is on the left
            else if (roota->rlink != NULL)
                roota=roota->rlink;
        }
        else{
        //Two children
            //Node *temp = roota;
            Node *temp = smallestInorder(roota->rlink);
            //cout<<"temp: "<<temp->key<<endl;
            //cout<<"temp right: "<<temp->rlink->key<<endl;
            //cout<<"OLD NODE: "<<roota->key<<endl;
            //cout<<"TEMP: "<<temp->key<<endl;
            //smallestInorder(temp->rlink);
            //cout<<"temp: "<<temp->key<<endl;
            //cout<<"temp right: "<<temp->rlink->key<<endl;
            //roota->key = temp->rlink->key;
            //roota->info = temp->rlink->info;
            roota->key = temp->key;
            roota->info = temp->info;
            //cout<<"NEW NODE: "<<roota->key<<endl;
            //cout<<"NEW NODE rlink: "<<roota->rlink->key<<endl;
            //cout<<"TEMP KEY "<<temp->key<<endl;
            del(roota->rlink,temp->key);
        }
    }
    if (roota == NULL){
        return true;
    }
   roota ->h = 1 + max(height(roota->llink),height(roota->rlink));
   //cout << "node: "<<roota->key<<"-h: "<<roota->h<<" Balance: "<<getBalance(roota)<<endl;

   //BALANCE

   int tempbalance=getBalance(roota);
   if(tempbalance>1 && getBalance(roota->llink)>=0)
        roota=rightRotation(roota);
   else if(tempbalance>1&&getBalance(roota->llink)<0){
        roota->llink=leftRotation(roota->llink);
        roota=rightRotation(roota);
   }
   else if (tempbalance < -1 && getBalance(roota->rlink)<=0){
        roota=leftRotation(roota);
   }
   else if (tempbalance < -1 && getBalance(roota->rlink)>0){
        roota->rlink = rightRotation(roota->rlink);
        roota=leftRotation(roota);
   }

    return true;
}
//--------------------- insert ------------------
template <typename Key, typename Info>
void dictionary<Key,Info>::insert(const Key &_key,const Info &_inf){
    cout << "-----" << endl;
    Node *newNode;
    newNode = new Node;
    newNode -> key = _key;
    newNode -> info = _inf;
    newNode -> rlink = NULL;
    newNode -> llink = NULL;

    insertAVL(root,newNode);
}

//--------------------- insertAVL ------------------
template <typename Key, typename Info>
void dictionary<Key,Info>::insertAVL(Node *& roota, Node *& newNode){
    if (roota == NULL){
        roota = newNode;
    }
    else if (roota -> key == newNode ->key)
        cerr << "No duplicates are allowed"<<endl;
    else if (roota ->key > newNode->key){
    //left subtree
        insertAVL(roota->llink, newNode);
    }
    else{
    //right subtree
        insertAVL(roota->rlink,newNode);
    }
    roota ->h = 1 + max(height(roota->llink),height(roota->rlink));
    cout << "INSERTED: "<<roota->key<<"-h: "<<roota->h<<" Balance: "<<getBalance(roota)<<endl;
    balance(roota,newNode->key);
}
//--------------------- balance ------------------
template <typename Key, typename Info>
void dictionary<Key, Info>::balance(Node *&roota,const Key &key){
    int tempbalance = getBalance(roota);//Check and balance the nodes if necesary

    if (tempbalance > 1 && key<roota->llink->key)
        roota=rightRotation(roota);
    if (tempbalance < -1 && key > roota->rlink->key)
        roota=leftRotation(roota);
    if (tempbalance > 1 && key > roota->llink->key){
        roota->llink = leftRotation(roota->llink);
        roota=rightRotation(roota);
    }
    if (tempbalance < -1 && key < roota->rlink->key){
        roota->rlink = rightRotation(roota->rlink);
        roota=leftRotation(roota);
    }
}

//--------------------- leftrotation ------------------
/*template <typename Key, typename Info>
dictionary::Node* dictionary::leftRotation(Node *&roota){
    struct Node *y = roota->rlink;
    struct Node *T2 = y->llink;

    // Perform rotation
    y->llink = roota;
    roota->rlink = T2;

    //  Update heights
    roota->h = max(height(roota->llink), height(roota->rlink))+1;
    y->h = max(height(y->llink), height(y->rlink))+1;

    // Return new root
    return y;
}
//--------------------- rightrotation ------------------
template <typename Key, typename Info>
void dictionary<Key, Info>::rightRotation(Node *roota){
    struct Node *x = roota->llink;
    struct Node *T2 = x->rlink;

    // Perform rotation
    x->rlink = roota;
    roota->llink = T2;

    // Update heights
    roota->h = max(height(roota->llink), height(roota->rlink))+1;
    x->h = max(height(x->llink), height(x->rlink))+1;

    // Return new root
    return x;
}

*/
//--------------------- print ------------------
template <typename Key, typename Info>
void dictionary<Key, Info>::print()
{
    Node *currin, *currpre, *currpos;
    currin = currpre = currpos = root;
    cout << "PRINTING"<<endl;
    if (root != NULL)
    {
        cout << "printing in order" << endl;
        printinorder(currin);
        cout << "\nprinting preorder" << endl;
        printpreorder(currpre);
        cout << "\nprinting postorder" << endl;
        printpostorder(currpos);
    }
    else
        cerr << "Error: No tree" << endl;
}
//--------------------- printinorder ------------------
template <typename Key, typename Info>
void dictionary<Key, Info>::printinorder(Node *&roota) const
{
    if (roota != NULL)
    {
        printinorder(roota->llink);
        cout << roota->key << " ";
        printinorder(roota->rlink);
    }
}
//--------------------- printpreorder ------------------
template <typename Key, typename Info>
void dictionary<Key, Info>::printpreorder(Node *&roota) const
{
    if (roota != NULL)
    {
        cout << roota->key << " ";
        printpreorder(roota->llink);
        printpreorder(roota->rlink);
    }
}
//--------------------- printpostorder ------------------
template <typename Key, typename Info>
void dictionary<Key, Info>::printpostorder(Node *&roota) const
{
    if (roota != NULL)
    {
        printpostorder(roota->llink);
        printpostorder(roota->rlink);
        cout << roota->key << " ";
    }
}
