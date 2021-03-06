#pragma once

#include <Data.h>
#include <Tree.h>

class Builder{
public:
    //Constructors & Destructors
    Builder(Data*);

    // Getter
    unsigned int getTypeSignal(){return typeSignal;}
    unsigned int getTypeBackground(){return typeBackground;}

    // Setter
    void setData(Data* x){data = x;}
    void setTypeSignal(unsigned int x){typeSignal = x;}
    void setTypeBackground(unsigned int x){typeSignal = x;}

    // Building
    void build(Tree*);

    // Node splitting
    void split(Tree*, Node*);

private:
    Data* data;
    unsigned int typeSignal;
    unsigned int typeBackground;
};
