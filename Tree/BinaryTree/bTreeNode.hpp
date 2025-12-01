struct node {
    int elem;
    node* parent;
    node* left;
    node* right;

    node(int elem, node* parent, node* left, node* right){
        this->elem = elem;
        this->parent = parent;
        this->left = left;
        this->right = right;
    }

    node(int elem, node* parent) : node(elem, parent, nullptr, nullptr){}

    node(int elem) : node(elem, nullptr, nullptr, nullptr){}
};