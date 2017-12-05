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
const long int LI = 1000000000;
typedef char* TYPE_TREE;


#include "../resources/tree.h"


enum Type_Tree {
    T_symbol = 1,
    T_value = 2,
    T_operator = 3,
    T_const = 4
};


Cell_t* Diffunction (Tree_t* Tree, Cell_t* cell);



Cell_t* TreeTypeRecurs (Tree_t* Tree, Cell_t* cell);



Cell_t* New_dCell (Tree_t* dTree, int type, char* val, Cell_t* dcell_l, Cell_t* dcell_r);



int TreeShort (Tree_t* Tree, Cell_t* cell);



int TreeShorten (Tree_t* Tree, Cell_t* cell, int* mark, int next);



int CellDel (Tree_t* Tree, Cell_t* cell);



double StoD (char* str);



char* DtoS (double var);



int CellRegLeft (Tree_t* Tree, Cell_t* cell, int next);



int CellRegRight (Tree_t* Tree, Cell_t* cell, int next);



Cell_t* ShortADD(Tree_t* Tree, Cell_t* cell, int* mark, int next);//'+'



Cell_t* ShortSUB (Tree_t* Tree, Cell_t* cell, int* mark, int next);//'-'



Cell_t* ShortMUL (Tree_t* Tree, Cell_t* cell, int* mark, int next);//'*'



Cell_t* ShortDIV (Tree_t* Tree, Cell_t* cell, int* mark, int next);//'/'





int main() {
    
    char str0 [] = "";
    
    Tree_t* Tree = TreeConstruct(str0);
    TreeReadFiles(TREE_FILES, Tree, Tree->cell, LEFT_cell);
    
    TreeGoRound(Tree, Tree->cell->nextl, TreeTypeRecurs, FROM_BELOW);
    
    Tree_t* dTree = TreeConstruct(str0);
    
    dTree->cell->nextl = Diffunction(dTree, Tree->cell->nextl);
    assert(dTree->cell->nextl);
    dTree->cell->nextl->prev = dTree->cell;
    
    TreeShort(dTree, dTree->cell->nextl);
    
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
            if ((strcmp("pi", cell->data) == 0) ||
                (strcmp("e", cell->data) == 0) ||
                (strcmp("π", cell->data) == 0)) {
                cell->type = T_const;
            } else
            cell->type = T_symbol;
    }
    
    return cell->prev;
}



Cell_t* Diffunction (Tree_t* dTree, Cell_t* cell) {
    assert(dTree);
    assert(cell);
    
    
    Cell_t* dcell = NULL;// = CellNew(dTree);
    
    if ((cell->type == T_value) || (cell->type == T_const)) {
        char* dC = new char;
        dC = "0";
        dcell = New_dCell (dTree, T_value, dC, NULL, NULL);
        assert(dcell);
    }
    
    if (cell->type == T_symbol) {
        char* dx = new char;
        dx = "1";
        dcell = New_dCell (dTree, T_value, dx, NULL, NULL);
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
        if (dcell_l !=NULL)
            dcell_new->nextl->prev = dcell_new; //->nextl
        if (dcell_r !=NULL)
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



int TreeShorten (Tree_t* Tree, Cell_t* cell, int* mark, int next) {
    
    if ((cell->type == T_operator) && (cell->nextl != NULL) && (cell->nextr != NULL))
    if (((cell->nextl->nextl == NULL) && (cell->nextl->nextr == NULL)) ||
        ((cell->nextr->nextl == NULL) && (cell->nextr->nextr == NULL))) {
        
        switch (cell->data [0]) {
            case '+':
                cell = ShortADD (Tree, cell, mark, next);
                break;
               
            case '-':
                cell = ShortSUB (Tree, cell, mark, next);
                break;
                
            case '*':
                cell = ShortMUL (Tree, cell, mark, next);
                break;
                
            case '/':
                cell = ShortSUB (Tree, cell, mark, next);
                break;
                
            default:
                break;
        }
    }
    
    if (cell->nextl != NULL)
        TreeShorten (Tree, cell->nextl, mark, LEFT_cell);
        
    if (cell->nextr != NULL)
        TreeShorten (Tree, cell->nextr, mark, RIGHT_cell);
    
    return 0;
}



double StoD (char* str) {
    double pov = 0;
    double div = 0;
    bool mark = false;
    int i = 0;
    
    if (str [i] == '-') {
        mark = true;
        ++i;
    }
        
    while ((str [i] != '.') && (str [i] != '\0')) {
        pov = pov * 10 + str[i] - '0';
        ++i;
    }
    
    if (str [i] == '.') {
        ++i;
        int j = 1;
        
        while ((str [i] != '\0')) {
            div = div * 10 + str[i] - '0';
            ++i;
            j = j * 10;;
        }
        
        if (j > 0) {
            div = div / j;
            pov = pov + div;
        }
        
    }
    
    if (mark)
        pov = (-1) * pov;
    
    return pov;
}



char* DtoS (double var) {
    
    int i = 0;
    char* str = new char [CELL_SIZE_DATA];
    
    if (var < 0) {
        var = (-1) * var;
        str [i] = '-';
        ++i;
    }
    
    long int maxd = 1;
    long int maxp = 1;
    long int j = 0;
    long int pov = var;
    long int div = var * LI - pov * LI;
    long int longdiv = LI;
    
    
    
    while((j == 0) && (div > 0))
    {
        div = div / 10;
        j = div % 10;
        longdiv = longdiv / 10;
    }
    
    longdiv = longdiv / 10;
    
    while (maxp <= pov) maxp = maxp * 10;
    maxp = maxp / 10;
    
    while (maxd <= div) maxd = maxd * 10;
    maxd = maxd / 10;
    
    while (maxp > 0) {
        str [i] = pov / maxp + '0';
        if (pov > 0)
            pov = pov - (pov / maxp) * maxp;
        maxp = maxp / 10;
        ++i;
    }
    if (maxd > 0) {
        str [i] = '.';
        ++i;
        
        while (longdiv != maxd) {
            str [i] = '0';
            ++i;
            longdiv = longdiv / 10;
        }
        
        while (div > 0) {
            str [i] = div / maxd + '0';
            div = div - (div / maxd) * maxd;
            maxd = maxd / 10;
            ++i;
        }
    }
    if (i == 0) {
        str [i] = '0';
        ++i;
    }
    str [i] = '\0';
    
    return str;
    
}



int CellDel (Tree_t* Tree, Cell_t* cell) {
    
    TreeCellDelete(Tree, cell->nextr);
    TreeCellDelete(Tree, cell->nextl);
    cell->nextl = NULL;
    cell->nextr = NULL;
    
    return 0;
}



Cell_t* ShortADD (Tree_t* Tree, Cell_t* cell, int* mark, int next) {
    
    if ((cell->nextl->type == T_value) && (cell->nextr->type == T_value)) {
        cell->data = DtoS(StoD(cell->nextl->data) + StoD(cell->nextr->data));
        cell->type = T_value;
        CellDel (Tree, cell);
        ++*mark;
    }  else
        if (cell->nextl->data [0] == '0') {
            CellRegRight (Tree, cell, next);
            ++*mark;
        } else
            if (cell->nextr->data [0] == '0') {
                CellRegLeft (Tree, cell, next);
                ++*mark;
            }
    
    return cell;
}



Cell_t* ShortSUB (Tree_t* Tree, Cell_t* cell, int* mark, int next) {
    
    if ((cell->nextl->type == T_value) && (cell->nextr->type == T_value)) {
        cell->data = DtoS(StoD(cell->nextl->data) - StoD(cell->nextr->data));
        cell->type = T_value;
        CellDel (Tree, cell);
        ++*mark;
    } else
        if (cell->nextr->data [0] == '0') {
            CellRegLeft (Tree, cell, next);
            ++*mark;
        }
    
    return cell;
}



Cell_t* ShortMUL (Tree_t* Tree, Cell_t* cell, int* mark, int next) {
    if ((cell->nextl->type == T_value) && (cell->nextr->type == T_value)) {
        cell->data = DtoS(StoD(cell->nextl->data) * StoD(cell->nextr->data));
        cell->type = T_value;
        CellDel (Tree, cell);
        ++*mark;
    } else
        if ((cell->nextl->data [0] == '0') || (cell->nextr->data [0] == '0')) {
            char* str = new char [CELL_SIZE_DATA];
            str = "0";
            cell->data = str;
            cell->type = T_value;
            CellDel (Tree, cell);
            ++*mark;
        } else
            if (cell->nextl->data [0] == '1') {
                CellRegRight (Tree, cell, next);
                ++*mark;
            } else
                if (cell->nextr->data [0] == '1') {
                    CellRegLeft (Tree, cell, next);
                    ++*mark;
                }
    return cell;
}



Cell_t* ShortDIV (Tree_t* Tree, Cell_t* cell, int* mark, int next) {
    
    if ((cell->nextl->type == T_value) && (cell->nextr->type == T_value)) {
        
        cell->data = DtoS(StoD(cell->nextl->data) / StoD(cell->nextr->data));
        cell->type = T_value;
        CellDel (Tree, cell);
        ++*mark;
    } else
        if (cell->nextl->data [0] == '0') {
            char* str = new char [CELL_SIZE_DATA];
            str = "0";
            cell->data = str;
            cell->type = T_value;
            CellDel (Tree, cell);
            ++*mark;
        } else
            if (cell->nextl->data [0] == '1') {
                CellRegRight (Tree, cell, next);
                ++*mark;
            } else
                if (cell->nextr->data [0] == '1') {
                    CellRegLeft (Tree, cell, next);
                    ++*mark;
                }
    
    return cell;
}



int TreeShort (Tree_t* Tree, Cell_t* cell) {
    
    int mark = 0;
    
    do {
        mark = 0;
        TreeShorten(Tree, cell, &mark, NULL);
    } while (mark != 0);
    
    return 0;
}



int CellRegLeft (Tree_t* Tree, Cell_t* cell, int next) {
    
    cell->nextl->prev = cell->prev;
    
    if (next == LEFT_cell)
        cell->prev->nextl = cell->nextl;
    else
        if (next == RIGHT_cell)
            cell->prev->nextr = cell->nextl;
    
    
    
    return 0;
}



int CellRegRight (Tree_t* Tree, Cell_t* cell, int next) {
    
    cell->nextr->prev = cell->prev;
    
    if (next == LEFT_cell)
        cell->prev->nextl = cell->nextr;
    else
        if (next == RIGHT_cell)
            cell->prev->nextr = cell->nextr;
    
    return 0;
}
