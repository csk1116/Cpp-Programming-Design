class MyVector
{    
protected:    //can be access by itself and its successors(child classes)
    int dimension;
    double* vectorPtr;
public:
    MyVector(); 
    MyVector(int dim, double elements[]);
    MyVector(const MyVector& vec);
    ~MyVector();  
    //automatically defined in the child class
    void printVector() const;      
    bool operator==(const MyVector& vec) const; 
    bool operator<(const MyVector& vec) const;
    bool operator!=(const MyVector& vec) const;
    double operator[](int index) const;
    double& operator[](int index);
    void operator=(const MyVector& vec);
};

class MyVector2D : public MyVector
{
public:
    MyVector2D();
    MyVector2D(double elements[]);
    void printVector() const; //overridding
    void setValue(double e1, double e2);
};

//grand child class
class NNVector2D : public MyVector2D
{
public:
    NNVector2D();
    NNVector2D(double elements[]);
    NNVector2D(const NNVector2D& vec);
    void setValue(double e1, double e2);
};