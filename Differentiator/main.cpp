//
//  main.cpp
//  Differentiator
//
//  Created by macbook on 25.11.2017.
//  Copyright © 2017 macbook. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <cassert>
#include <string.h>
#include <math.h>
//#include "../resources/diff.h"


const char* TREE_FILES = "../resources/save.txt";
const char* TREE_FILES1 = "../resources/save1.txt";
typedef char* TYPE_TREE;

#include "../resources/tree.h"


int main() {
    //char STR [] = "(*(-(4)(2))(5))";
    Tree_t* Tree = TreeConstruct("Привет");
    TreeReadFiles(TREE_FILES, Tree, Tree->cell, LEFT_cell);
    
    TreeDump(Tree, Tree->cell->nextl);
    TreePrintFile(Tree, Tree->cell->nextl);
    TreeDestructor(Tree);
    
    return 0;
}
