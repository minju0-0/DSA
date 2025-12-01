struct node {
    int elem;
    node* parent;
    node* left;
    node* right;

    int height() {
        return 1 + max(left? left->height() : -1, right? right->height() : -1);
    }

    int depth() {
        node* curr = this;
        int d = 0;
        while (curr->parent) {
            d++;
            curr = curr->parent;
        }
        return d;
    }
};

