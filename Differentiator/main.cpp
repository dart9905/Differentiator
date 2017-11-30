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
    assert(dTree->cell->nextl);
    dTree->cell->nextl->prev = dTree->cell;
    
    TreeDump(dTree, dTree->cell->nextl);
    TreePrintFile(Tree, Tree->cell->nextl);
    TreeDestructor(Tree);
    TreeDestructor(dTree);
    
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
    
    
    Cell_t* dcell = NULL;// = CellNew(dTree);
    
    if (cell->type == T_value) {
        char* dC = new char;
        dC = "0";
        dcell = New_dCell (dTree, T_value, dC, NULL, NULL);
        assert(dcell);
    }
    
    if (cell->type == T_symbol) {
        char* dx = new char;
        dx = "1";
        dcell = New_dCell (dTree, T_symbol, dx, NULL, NULL);
        assert(dcell);
    }
    
    if (cell->type == T_operator) {
        #define DIFF_( NAME, TYPE, DECLARATION )\
            if (strcmp(#NAME, cell->data) == 0) {\
                dcell = (DECLARATION);\
                assert(dcell);\
            }
        
        #include "../resources/diff.h"
        
        #undef DIFF_
        
    }
    return dcell;
}



Cell_t* New_dCell (Tree_t* dTree, int type, char* val, Cell_t* dcell_l, Cell_t* dcell_r) {
    Cell_t* dcell_new = CellNew(dTree);
    
    if (type == T_operator) {
        
        dcell_new->nextl = dcell_l;
        dcell_new->nextr = dcell_r;
        dcell_new->nextl->prev = dcell_new; //->nextl
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



