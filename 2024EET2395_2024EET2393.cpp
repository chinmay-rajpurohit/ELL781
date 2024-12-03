#include <iostream>
#include <unordered_map> //for demo and consolidate
#include <queue> //for printing tree
#include<fstream> //for taking input for file

using namespace std;


//node structure
class HeapNode
{
public:
    int key, degree;
    HeapNode *parent, *left, *right, *child;
    bool marked;

    HeapNode(int data)
    {
        parent = NULL;
        left = this;
        right = this;
        child = NULL;
        key = data;
        degree = 0;
        marked = false;
    }
    ~HeapNode(){

        parent = NULL;
        left = this;
        right = this;
        child = NULL;
        key = 0;
        degree = 0;
        marked = false;
    }
};



class FibHeap
{

private:

    HeapNode *min; //pointer to min Element
    int keys; // number of keys

    void addRightToMin(HeapNode *node)
    {
        node->parent = NULL;
        if (min->right == min->left && min->right == min)
        {

            min->left = node;
            min->right = node;
            node->left = min;
            node->right = min;
        }
        else
        {
            node->left = min;
            node->right = min->right;
            min->right = node;
        }
    }

    void cutNode(HeapNode *node)
    {
        if (node->parent != NULL)
        {
            node->marked = false;
            if (node->left == node->right)
            {
                if (node->right == node)
                {
                    node->parent->child = NULL;
                    addRightToMin(node);
                }
                else
                {
                    node->right->left = node->right;
                    node->right->right = node->right;
                    node->parent->child = node->right;
                    addRightToMin(node);
                }
            }
            else
            {
                node->left->right = node->right;
                node->right->left = node->left;
                node->parent->child = node->right;
                addRightToMin(node);
            }
        }
    }
public:

    FibHeap()
    {
        min = NULL;
        keys = 0;
    }

    HeapNode *insert(int key)
    {
        // add node to right of min in the rootlist

        HeapNode *newNode = new HeapNode(key);

        if (min == NULL)
        {
            min = newNode;
        }
        else
        {
            addRightToMin(newNode);
            if (newNode->key < min->key)
            {
                min = newNode;
            }
        }

        keys += 1;
        return newNode;
    }

    int extractMin()
    {
        if (keys == 0)
        {
            cout << "Empty Tree, So Cannot Do extractMin" << endl;
            return INT_MIN;
        }

        // extract the minimum element
        int retVal = min->key;
        if (keys == 1)
        {
            keys = 0;
            delete(min);
            min = NULL;
            return retVal;
        }

        // join the child elements of minimum element to rootList
        HeapNode *child = min->child;
        keys -= 1;
        if (child != NULL){
            min->left->right = child->right;
            min->right->left = child;

            child->right->left = min->left;
            child->right = min->right;
            delete(min);
            min = child;
            child->parent = NULL;
        }
        // if no child then remove min and connect left and right
        else
        {

            min->left->right = min->right;
            min->right->left = min->left;
            HeapNode *right = min->right;
            delete(min);
            min = right;
        }
        
        //consolidate
        unordered_map<int, HeapNode *> degreeMap;
        HeapNode *temp = min;
        do
        {
            HeapNode *next = temp->right;
            temp->left = temp;
            temp->right = temp;

            while (true)
            {

                if (degreeMap.find(temp->degree) == degreeMap.end())
                {
                    degreeMap[temp->degree] = temp;

                    break;
                }
                else
                {

                    if (degreeMap[temp->degree] == NULL)
                    {
                        degreeMap[temp->degree] = temp;
                        break;
                    }
                    else
                    {
                        HeapNode *temp1 = degreeMap[temp->degree];
                        if (temp1->key > temp->key)
                        {
                            HeapNode *tempx = temp1;
                            temp1 = temp;
                            temp = tempx;
                        }
                        if (temp1->child != NULL)
                        {

                            temp->parent = temp1;

                            if (temp1->child->left == temp1->child->right && temp1->child->right == temp1->child)
                            {
                                temp1->child->left = temp;
                                temp1->child->right = temp;
                                temp->right = temp1->child;
                                temp->left = temp1->child;
                            }
                            else
                            {

                                temp->right = temp1->child->right;
                                temp->left = temp1->child;
                                temp1->child->right->left = temp;
                                temp1->child->right = temp;
                            }
                        }
                        else
                        {
                            temp1->child = temp;
                            temp->parent = temp1;
                        }
                        degreeMap[temp->degree] = NULL;
                        temp1->degree += 1;
                        temp = temp1;
                    }
                }
            }
            temp = next;
        } while (temp != min);

        min = NULL;
        for (auto i = degreeMap.begin(); i != degreeMap.end(); i++)
        {
            if (i->second != NULL)
            {
                if (min == NULL)
                {
                    min = i->second;
                }
                else
                {
                    addRightToMin(i->second);
                }
            }
        }

        // assign min
        HeapNode *it = min->right;
        temp = min;
        while (it != min)
        {
            if (it->key < temp->key)
            {
                temp = it;
            }
            it = it->right;
        }

        min = temp;
        return retVal;
    }

    void decreaseKey(HeapNode *keyAddress,int val)
    {
        if (keyAddress != NULL)
        {
            if (keyAddress->key>=val){

                keyAddress->key = val;
            }
            else{
                // error if node value lesser then value to decrease
                cout << "ERR : Value greater than value of the key!"<<endl;
                return;
            }
            
            if (keyAddress->parent == NULL)
            {
                // update Min
                if (min->key > keyAddress->key)
                {
                    min = keyAddress;
                }
            }
            else
            {
                // cut and cascading cut
                if (keyAddress->key >= keyAddress->parent->key)
                {
                    return;
                }
                else
                {
                    if (!keyAddress->parent->marked)
                    {
                        keyAddress->parent->marked = true;
                        keyAddress->parent->degree--;
                        cutNode(keyAddress);

                        if (keyAddress->key < min->key)
                        {
                            min = keyAddress;
                        }
                    }
                    else
                    {
                        HeapNode *parent = keyAddress->parent;
                        parent->degree--;
                        cutNode(keyAddress);
                        // so that min is updated as extracted min would remove previous min
                        if (keyAddress->key<min->key){
                            min = keyAddress;
                        }
                        // cascading cut
                        keyAddress = parent;
                        while(keyAddress->marked && keyAddress->parent!=NULL){
                            parent = keyAddress->parent;
                            parent->degree--;
                            cutNode(keyAddress);
                            keyAddress = parent;
                        }
                            keyAddress->marked = true;
                        
                     
                    }
                }
            }
        }
    }

    void printLevelOrder()
    {
        if (keys >= 1)
        {

            queue<HeapNode *> q;

            HeapNode *temp;
            q.push(min);
            while (!q.empty())
            {
                temp = q.front();
                cout << " ( ";
                if (temp->parent != NULL)
                {

                    cout << temp->parent->key << "  --->  ";
                }
                else
                {
                    cout << "NULL --->  ";
                }
                do
                {
                    cout << temp->key << " ";
                    if (temp->child != NULL)
                    {
                        q.push(temp->child);
                    }
                    temp = temp->right;
                } while (temp != q.front());
                cout << ")"<<endl;
                q.pop();
            }
            cout << endl;
        }
        else
        {
            cout << "Empty Tree";
        }
    }
    int getMin(){
        if (min!=NULL){
            return min->key;
        }
        return INT_MIN;
    }
    void deleteNode( HeapNode* node){
        if (node!=NULL){
            decreaseKey(node,min->key-1);
            extractMin();
        }
    }
    int getNumberofKeys(){
        return keys;
    }

};

int main()
{
    ifstream inputFile("input.txt");

    FibHeap heap = FibHeap();
    unordered_map<int,HeapNode*> nodes;
    

    if (!inputFile.is_open()){

        cout<<"Error in opening Input File"<<endl;
        return 1;
    }
    
    string line;
    int index = 0;

    HeapNode *node;
    while(getline(inputFile,line)){
        if (index == 0){
            line+=" ";
            string s = "";
            for(int i=0;i<line.size();i+=1){
                if (line[i] != ' '){
                    s+=line[i];
                }
                else{
                    if (s!=""){
                        int x = stoi(s);
                        node = heap.insert(x);
                        nodes[x] = node;

                    }

                    s= "";
                }
            }
            index+=1;
        }
    }
    int x;
    int y;
    
    while(true){
        cout<<endl;
        cout<<"1. Insert Node"<<endl;
        cout<<"2. Get Min"<<endl;
        cout<<"3. Exctract min"<<endl;
        cout<<"4. Decrease key"<<endl;
        cout<<"5. Delete Node"<<endl;
        cout<<"6. Print Tree"<<endl;
        cout<<"Any other number to exit"<<endl;
        cout<<endl;
        int input;

        cin>>input;
        switch (input)
        {
        case 1:
            cout<<"Enter a value for node to add"<<endl;
            cin>>x;
            nodes[x]= heap.insert(x);
            cout<<"node inserted"<<endl;
            break;
        case 2:
            cout<<"Current minimum element: "<<heap.getMin()<<endl;
            break;
        case 3:
            x = heap.extractMin();
            cout<<"extracted min = "<< x<<endl;
            break;

        case 4:
            cout<<"enter value on which you have to apply decrease key: "<<endl;
            cin>>x;
            cout<<"Enter value to which you have to decrease"<<endl;
            cin>>y;
            heap.decreaseKey(nodes[x],y);
            break;

        case 5:
            cout<<"Enter Node to Delete: "<<endl;
            cin>>x;
            heap.deleteNode(nodes[x]);
            break;

        case 6:
            cout<<endl;
            heap.printLevelOrder();
            break;
        default:
            cout<<"Program exitted"<<endl;
            return 0;
            break;
        }
        cout<<endl<<"------------------------------ "<<endl;
    }
    
    return 0;
}