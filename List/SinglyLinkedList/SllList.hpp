class List {
    public:
    virtual void print() = 0;
    virtual void addHead(int) = 0;
    virtual void addTail(int) = 0;
    virtual int getPosition(int) = 0;
    virtual int remove(int) = 0;
};