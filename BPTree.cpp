#include"BPTree.h"

Node::Node(){
    size=0;
}

void Node::sterlizeNode(){
    for(int i =this->size;i<MAX_SIZE;i++){
        this->key[i]=0;
        this->ptr[i+1] = nullptr;
    }
}


BPTree::BPTree(){
    root = nullptr;
}

Node* BPTree::findLeafNode(int x){
    if (root == nullptr){
        return nullptr;
    }
    else{
        Node* currentNode = root;
        while(currentNode->isLeaf ==false){
            for (int i =0;i<currentNode->size;i++){
                if (x < currentNode->key[i]){
                    currentNode = currentNode->ptr[i];
                    break;
                }
                if (i == currentNode->size-1){
                    currentNode = currentNode->ptr[i+1];
                    break;
                }
            }
        }
        return currentNode;
    }
}


void BPTree::search(int x){
    Node* reqNode = findLeafNode(x);
    if (reqNode == nullptr){
        std::cout<<"NO"<<std::endl;
        return;
    }
    for (int i=0;i<reqNode->size;i++){
            if(x==reqNode->key[i]){
                std::cout<<"YES"<<std::endl;
                return;
            }
        }
    std::cout<<"NO"<<std::endl;
}

void BPTree::insert(int x){
    Node* candidateNode = findLeafNode(x);
    if (candidateNode == nullptr) {
        root = new Node;
        root->key[0]=x;
        root->parent= nullptr;
        root->isLeaf = true;
        root->size = 1;
    }
    else
    {
//Leaf Node Has Space to accomodate the inserted key
        if (candidateNode->size < MAX_SIZE){
            int i = 0;
            while (x >=candidateNode->key[i] && i<candidateNode->size)
            {
                i++;
            }
            for(int j = candidateNode->size ; j>i;j--)
            {
                candidateNode->key[j]=candidateNode->key[j-1];
            }
            candidateNode->key[i] = x;
            candidateNode->size++;
            candidateNode->ptr[candidateNode->size]=candidateNode->ptr[candidateNode->size-1];
            candidateNode->ptr[candidateNode->size-1]=nullptr;
        }
//Leaf Node Overflows
        else{
            Node* newLeaf = new Node;
            newLeaf->isLeaf=true;
            int virtualNode[MAX_SIZE+1];
            for(int i=0;i<candidateNode->size;i++)
                virtualNode[i] = candidateNode->key[i];
            int i =0;
            while (x >=virtualNode[i] && i<candidateNode->size)
            {
                i++;
            }
            for(int j = candidateNode->size ; j>i;j--)
            {
                virtualNode[j]=virtualNode[j-1];
            } 
            virtualNode[i]=x;
            int splitPos = (MAX_SIZE+1)/2;
            candidateNode->size = splitPos;
            newLeaf->size = (MAX_SIZE+1)-splitPos;
            candidateNode->ptr[candidateNode->size]=newLeaf;
            newLeaf->ptr[newLeaf->size] = candidateNode->ptr[MAX_SIZE];
            candidateNode->ptr[MAX_SIZE]=nullptr;
            for (i = 0; i < splitPos; i++) { 
                candidateNode->key[i]  = virtualNode[i]; 
            }
            for (int i = 0, j = splitPos;i < newLeaf->size; i++, j++) { 
                newLeaf->key[i] = virtualNode[j]; 
            }
            candidateNode->sterlizeNode();
            if (candidateNode->parent == nullptr){
                Node* newRoot = new Node;  
                newRoot->key[0] = newLeaf->key[0]; 
                newRoot->ptr[0] = candidateNode; 
                newRoot->size = 1; 
                newRoot->ptr[newRoot->size] = newLeaf; 
                newRoot->isLeaf = false; 
                root = newRoot; 
                newLeaf->parent=candidateNode->parent=root;
            }
            else{
                insertParent(newLeaf->key[0],newLeaf,candidateNode->parent);
                // newLeaf->parent=candidateNode->parent;
            }
        }
    }
}

void BPTree::insertParent(int x, Node* newChild,Node* currentNode)
{
    if (currentNode->size<MAX_SIZE){
        int i =0;
        while(x>=currentNode->key[i] && i<currentNode->size){
            i++;
        }
        for(int j = currentNode->size;j>i;j--){
            currentNode->key[j]=currentNode->key[j-1];
            currentNode->ptr[j+1] = currentNode->ptr[j];
        }
        currentNode->key[i]=x;
        currentNode->ptr[i+1]=newChild;
        newChild->parent = currentNode;
        currentNode->size++;
    }
    else{
        Node* newInternal = new Node;
        newInternal->isLeaf=false;
        int virtualKey[MAX_SIZE+1];
        Node* virtualPtr[MAX_SIZE+2];
        for(int i=0;i<MAX_SIZE;i++)
            virtualKey[i] = currentNode->key[i];
        for(int i=0;i<MAX_SIZE+1;i++)
            virtualPtr[i] = currentNode->ptr[i]; 
        int i=0;
        while(x>=virtualKey[i] && i<MAX_SIZE){
            i++;
        }
        for(int j = MAX_SIZE;j>i;j--){
            virtualKey[j]=virtualKey[j-1];
            virtualPtr[j+1] = virtualPtr[j];
        }
        virtualKey[i]=x;
        virtualPtr[i+1]=newChild;
        int splitPos = (MAX_SIZE+1)/2;
        currentNode->size = splitPos;
        newInternal->size = MAX_SIZE-splitPos;
        for (i = 0; i < splitPos; i++) { 
            currentNode->key[i]  = virtualKey[i]; 
            currentNode->ptr[i] = virtualPtr[i];
            currentNode->ptr[i]->parent = currentNode;
            
        }
        currentNode->ptr[splitPos]=virtualPtr[splitPos];
        currentNode->ptr[splitPos]->parent = currentNode;
        currentNode->sterlizeNode();

        for (int i = 0, j = splitPos+1;i < newInternal->size; i++, j++) { 
            newInternal->key[i] = virtualKey[j];
            newInternal->ptr[i] = virtualPtr[j]; 
            newInternal->ptr[i]->parent = newInternal;
        }
        newInternal->ptr[newInternal->size]=virtualPtr[MAX_SIZE+1];
        newInternal->ptr[newInternal->size]->parent = newInternal;

    
        if (currentNode->parent == nullptr){
            Node* newRoot = new Node;  
            newRoot->key[0] = virtualKey[splitPos]; 
            newRoot->ptr[0] = currentNode; 
            newRoot->size = 1; 
            newRoot->ptr[newRoot->size] = newInternal; 
            newRoot->isLeaf = false; 
            root = newRoot; 
            newInternal->parent=currentNode->parent=root;
        }
        else{
            insertParent(virtualKey[splitPos],newInternal,currentNode->parent);
            // newLeaf->parent=candidateNode->parent;
        }

    }
}


// to help with duplicate values ask for a node from findLeafNode with (x-1) 

void BPTree::range(int x, int y){
    Node* reqNode = findLeafNode(x-1);
    int count = 0;
    bool rangeExceedFlag = false;
    while(reqNode != nullptr){
        for (int i=0;i<reqNode->size;i++){
            if(x<=reqNode->key[i] && reqNode->key[i]<=y){
                count++;
            }
            if(reqNode->key[i]>y){
                rangeExceedFlag = true;
                break;
            }
        }
        if(rangeExceedFlag == false){
            reqNode = reqNode->ptr[reqNode->size];
        }  
        else{
            reqNode = nullptr;
        }
    }

    std::cout<<count<<std::endl;
    
}
void BPTree::count(int x){
    range(x,x);
}