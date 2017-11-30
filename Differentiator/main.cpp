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


enum Type_Tree {
    T_symbol = 1,
    T_value = 2,
    T_operator = 3
};


Cell_t* Diffunction (Tree_t* Tree, Cell_t* cell);

Cell_t* TreeTypeRecurs (Tree_t* Tree, Cell_t* cell);


Cell_t* New_dCell (Tree_t* dTree, int type, char* val, Cell_t* dcell_l, Cell_t* dcell_r);



int main() {
    
    char str0 [] = "";
    
    Tree_t* Tree = TreeConstruct(str0);
    TreeReadFiles(TREE_FILES, Tree, Tree->cell, LEFT_cell);
    
    TreeGoRound(Tree, Tree->cell->nextl, TreeTypeRecurs, FROM_BELOW);
    
    Tree_t* dTree = TreeConstruct(str0);
    
    dTree->cell->nextl = Diffunction(dTree, Tree->cell->nextl);
    
    TreeDump(Tree, Tree->cell->nextl);
    TreePrintFile(Tree, Tree->cell->nextl);
    TreeDestructor(Tree);
    
    return 0;
}


//case не получился так как счет был от первого символа в аски и многие буквы совпали cos & ctg
Cell_t* TreeTypeRecurs (Tree_t* Tree, Cell_t* cell) {
    assert(Tree);
    assert(cell);
    
    bool var = true;
    #define DIFF_( NAME, TYPE, DECLARATION )\
        if (strcmp(#NAME, cell->data) == 0) {\
            cell->type = TYPE;\
            var = false;\
        }
    
    #include "../resources/diff.h"
    
    #undef DIFF_
    
    if (var) {
        if ('0' <= (cell->data [0]) && (cell->data [0]) <= '9') {
            cell->type = T_value;
        } else
            cell->type = T_symbol;
    }
    
    return cell->prev;
}



Cell_t* Diffunction (Tree_t* dTree, Cell_t* cell) {
    assert(dTree);
    assert(cell);
    
    char dx [] = "1";
    char dC [] = "0";
    
    Cell_t* dcell = CellNew(dTree);
    
    if (cell->type == T_value)
        return New_dCell (dTree, T_value, dC, NULL, NULL);
    
    if (cell->type == T_symbol)
        return New_dCell (dTree, T_symbol, dx, NULL, NULL);
    
    if (cell->type == T_operator) {
        Cell_t* pCell = NULL;
        #define DIFF_( NAME, TYPE, DECLARATION )\
            if (strcmp(#NAME, cell->data) == 0) {\
                pCell = (DECLARATION);\
            }
        
        //#include "../resources/diff.h"
        
        #undef DIFF_
        return pCell;
    }
    
    return NULL;
}



Cell_t* New_dCell (Tree_t* dTree, int type, char* val, Cell_t* dcell_l, Cell_t* dcell_r) {
    Cell_t* dcell_new = CellNew(dTree);
    
    if (type == T_operator) {
        
        dcell_new->nextl = dcell_l;
        dcell_new->nextr = dcell_r;
        if (dcell_new->nextl != 0)
            dcell_new->nextl->prev = dcell_new; //->nextl
        if (dcell_new->nextr != 0)
            dcell_new->nextr->prev = dcell_new; //->nextr
        
        dcell_new->type = T_operator;
        dcell_new->data = val;
        
    } else if ((type == T_value) || (type == T_symbol)) {
        
        dcell_new->nextl = NULL;
        dcell_new->nextr = NULL;
        dcell_new->type = type;
        dcell_new->data = val;
        
    }
    
    return dcell_new;
    
}



