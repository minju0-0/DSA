class Graph{
    public:
    virtual void insertVertex(char) = 0;
    virtual void insertEdge(char, char, int) = 0;
    virtual int numVertices() = 0;
    virtual char* vertices() = 0;
    virtual int numEdges() = 0;
    virtual int* edges() = 0;
    virtual int getEdge(char, char) = 0;
    virtual char* endVertices(int) = 0;
    virtual char opposite(char, int) = 0;
    virtual int outDegree(char) = 0;
    virtual int inDegree(char) = 0;
    virtual int* outgoingEdges(char) = 0;
    virtual int* incomingEdges(char) = 0;
    virtual int removeVertex(char) = 0;
    // virtual bool removeEdge(int) = 0;
    virtual void print() = 0;

};