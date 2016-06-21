#pragma once

#include <Data.h>
#include <Tree.h>

class Builder{
public:
    // Setter
    void setData(Data* x){data = x;}

    // Building
    void build(Tree*);

private:
    Data* data;
};
