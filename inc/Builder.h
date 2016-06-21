#pragma once

#include <Data.h>
#include <Tree.h>

class Builder{
public:
    //Constructors & Destructors
    Builder(Data*);

    // Getter
    unsigned int getTypeSignal(){return typeSignal;}

    // Setter
    void setData(Data* x){data = x;}
    void setTypeSignal(unsigned int x){typeSignal = x;}

    // Building
    void build(Tree*);

    // Node splitting
    void split(Tree*, Node*);
    inline float separationGain(float purity){return purity*(1.0-purity);}

private:
    Data* data;
    unsigned int typeSignal;
};
