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


const char* TEX_NAME_FILES = "fileTeX.tex";
const char* TREE_FILES = "../resources/save.txt";
const char* TREE_FILES1 = "../resources/save1.txt";
const long int LI = 1000000000;
typedef char* TYPE_TREE;


#include "../resources/tree.h"

#include "../resources/read.h"


enum Type_Tree {
    T_symbol = 1,
    T_value = 2,
    T_operator = 3,
    T_const = 4
};



enum paramTeX {
    TeX_begin = 1,
    TeX_print = 2,
    TeX_end = 3
};



enum DiffMark {
    diff = 1,
    nodiff = 2,
    enddiff = 3
};



enum NumberTextTeX {
    BeginDiffTeX = 1,
    EndDiffTeX = 2,
    RNDDiffTeX = 3,
    SpeakDiffTeX = 4,
    ShortDiffTeX = 5,
    PresentDiffTeX = 6
};


Cell_t* Diffunction (Tree_t* Tree, Cell_t* cell);



Cell_t* TreeTypeRecurs (Tree_t* Tree, Cell_t* cell);



Cell_t* New_dCell (Tree_t* dTree, int type, char* val, Cell_t* dcell_l, Cell_t* dcell_r);



int TreeShort (Tree_t* Tree, Cell_t* cell, int next);



Cell_t* TreeShorten (Tree_t* Tree, Cell_t* cell, int* mark, int next);



int CellDel (Tree_t* Tree, Cell_t* cell);



double StoD (char* str);



char* DtoS (double var);



Cell_t*  CellRegLeft (Tree_t* Tree, Cell_t* cell, int next);



Cell_t*  CellRegRight (Tree_t* Tree, Cell_t* cell, int next);



Cell_t* ShortADD(Tree_t* Tree, Cell_t* cell, int* mark, int next);//'+'



Cell_t* ShortSUB (Tree_t* Tree, Cell_t* cell, int* mark, int next);//'-'



Cell_t* ShortMUL (Tree_t* Tree, Cell_t* cell, int* mark, int next);//'*'



Cell_t* ShortDIV (Tree_t* Tree, Cell_t* cell, int* mark, int next);//'/'



int PrintTeX (Tree_t* Tree, Cell_t* cell, int param, int mark);



Cell_t* PrintTexRecurs (Tree_t* Tree, Cell_t* cell, FILE* file_TeX, int mark, int* recurs);



int TextTeX (int number, char * str, int mark);







int main() {
    
    char str0 [] = "";
    
    Tree_t* Tree = TreeConstruct(str0);
    Tree_t* dTree = TreeConstruct(str0);
    
    long int number_of_char = 0;
    char* my_buffer = ReadFiles (TREE_FILES , &number_of_char);
    
    Tree->cell->nextl = GetG0(Tree, my_buffer);
    Tree->cell->nextl->prev = Tree->cell;
    TreeGoRound(Tree, Tree->cell->nextl, TreeTypeRecurs, FROM_BELOW);
    
    PrintTeX(NULL, NULL, TeX_begin, NULL);
    
    
    TextTeX (BeginDiffTeX, NULL, NULL);
    TextTeX (RNDDiffTeX, NULL, NULL);
    dTree->cell->nextl = Diffunction(dTree, Tree->cell->nextl);
    assert(dTree->cell->nextl);
    dTree->cell->nextl->prev = dTree->cell;
    
    TextTeX (PresentDiffTeX, NULL, NULL);
    PrintTeX(Tree, Tree->cell->nextl, TeX_print, diff);
    PrintTeX(dTree, dTree->cell->nextl, TeX_print, enddiff);
    
    TextTeX (ShortDiffTeX, NULL, NULL);
    PrintTeX(Tree, Tree->cell->nextl, TeX_print, diff);
    TreeShort(dTree, dTree->cell->nextl, LEFT_cell);
    PrintTeX(dTree, dTree->cell->nextl, TeX_print, enddiff);
    
    
    
    TextTeX (EndDiffTeX, NULL, NULL);
    
    TreeDump(dTree, dTree->cell->nextl);
    
    PrintTeX(NULL, NULL, TeX_end, NULL);
    
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
        assert(dC);
        memcpy(dC, "0", 2);
        dcell = New_dCell (dTree, T_value, dC, NULL, NULL);
        assert(dcell);
    }
    
    if (cell->type == T_symbol) {
        char* dx = new char;
        assert(dx);
        memcpy(dx, "1", 2);
        dcell = New_dCell (dTree, T_value, dx, NULL, NULL);
        assert(dcell);
    }
    
    if (cell->type == T_operator) {
#define DIFF_( NAME, TYPE, DECLARATION )\
if (strcmp(#NAME, cell->data) == 0) {\
dcell = (DECLARATION);\
assert(dcell);\
TextTeX (RNDDiffTeX, NULL, 2);\
PrintTeX(dTree, cell, TeX_print, diff);\
PrintTeX(dTree, dcell, TeX_print, enddiff);\
}
        
#include "../resources/diff.h"
        
#undef DIFF_
    }
    //printf("%s\n", dcell->data);
    return dcell;
}



Cell_t* New_dCell (Tree_t* dTree, int type, char* val, Cell_t* dcell_l, Cell_t* dcell_r) {
    Cell_t* dcell_new = CellNew(dTree);
    assert(dcell_new);
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



Cell_t* TreeShorten (Tree_t* Tree, Cell_t* cell, int* mark, int next) {
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
                    cell = ShortDIV (Tree, cell, mark, next);
                    break;
                    
                default:
                    break;
            }
        }
    
    if (cell != NULL) {
        if (cell->nextl != NULL)
            cell = TreeShorten (Tree, cell->nextl, mark, LEFT_cell);
        
        if (cell->nextr != NULL)
            cell = TreeShorten (Tree, cell->nextr, mark, RIGHT_cell);
    }
    if (cell->prev != 0)
        return cell->prev;
    else
        return cell;
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
    assert(str);
    
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
        if (strcmp("0", cell->nextl->data) == 0) {
            cell = CellRegRight (Tree, cell, next);
            ++*mark;
        } else
            if (strcmp("0", cell->nextr->data) == 0) {
                cell = CellRegLeft (Tree, cell, next);
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
        if (strcmp("0", cell->nextr->data) == 0) {
            cell = CellRegLeft (Tree, cell, next);
            ++*mark;
        } else
            if (((cell->nextl->type == T_symbol) && (cell->nextr->type == T_symbol)) ||
                ((cell->nextl->type == T_const) && (cell->nextr->type == T_const))) {
                if (strcmp(cell->nextl->data, cell->nextr->data) == 0) {
                    char* str = new char [CELL_SIZE_DATA];
                    assert(str);
                    memcpy(str, "0", 2);
                    cell->data = str;
                    cell->type = T_value;
                    CellDel (Tree, cell);
                    ++*mark;
                }
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
        if ((strcmp("0", cell->nextl->data) == 0) || (strcmp("0", cell->nextr->data) == 0)) {
            char* str = new char [CELL_SIZE_DATA];
            assert(str);
            memcpy(str, "0", 2);
            cell->data = str;
            cell->type = T_value;
            CellDel (Tree, cell);
            ++*mark;
        } else
            if (strcmp("1", cell->nextl->data) == 0) {
                cell = CellRegRight (Tree, cell, next);
                ++*mark;
            } else
                if (strcmp("1", cell->nextr->data) == 0) {
                    cell = CellRegLeft (Tree, cell, next);
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
            assert(str);
            memcpy(str, "0", 2);
            cell->data = str;
            cell->type = T_value;
            CellDel (Tree, cell);
            ++*mark;
        } else
            if (strcmp("1", cell->nextr->data) == 0) {
                cell = CellRegLeft (Tree, cell, next);
                ++*mark;
            } else
                if (((cell->nextl->type == T_symbol) && (cell->nextr->type == T_symbol)) ||
                    ((cell->nextl->type == T_const) && (cell->nextr->type == T_const))) {
                    if (strcmp(cell->nextl->data, cell->nextr->data) == 0) {
                        char* str = new char [CELL_SIZE_DATA];
                        assert(str);
                        memcpy(str, "1", 2);
                        cell->data = str;
                        cell->type = T_value;
                        CellDel (Tree, cell);
                        ++*mark;
                    }
                }
    
    return cell;
}



int TreeShort (Tree_t* Tree, Cell_t* cell, int next) {
    assert(Tree);
    assert(cell);
    int mark = 0;
    
    do {
        mark = 0;
        
        PrintTeX(Tree, Tree->cell->nextl, TeX_print, nodiff);
        cell = TreeShorten(Tree, cell, &mark, next);
    } while (mark != 0);
    
    return 0;
}



Cell_t*  CellRegLeft (Tree_t* Tree, Cell_t* cell, int next) {
    
    cell->nextl->prev = cell->prev;
    
    if (next == LEFT_cell)
        cell->prev->nextl = cell->nextl;
    else
        if (next == RIGHT_cell)
            cell->prev->nextr = cell->nextl;
    
    
    
    return cell->nextl;
}



Cell_t*  CellRegRight (Tree_t* Tree, Cell_t* cell, int next) {
    
    cell->nextr->prev = cell->prev;
    
    if (next == LEFT_cell)
        cell->prev->nextl = cell->nextr;
    else
        if (next == RIGHT_cell)
            cell->prev->nextr = cell->nextr;
    
    return cell->nextr;
}



int PrintTeX (Tree_t* Tree, Cell_t* cell, int param, int mark) {
    switch (param) {
        case TeX_begin:
        {
            FILE *file_TeX = fopen(TEX_NAME_FILES,"wt");
            if (file_TeX == NULL)
                return ERROR_DUMP;
            fprintf(file_TeX, "\\documentclass[a4paper,12pt]{article}\n");
            fprintf(file_TeX, "\\usepackage[T2A]{fontenc}\n\\usepackage[utf8]{inputenc}\n\\usepackage[english,russian]{babel}\n");
            fprintf(file_TeX, "\\usepackage{amsmath,amsfonts,amssymb,amsthm,mathtools}\n");
            fprintf(file_TeX, "\\author{By Khromov Alexey} \n\\title{Differentiator \\LaTeX{}} \n\\date{\\today}");
            fprintf(file_TeX, "\\begin{document}\n\\maketitle\n\\newpage");
            fclose(file_TeX);
        }
            break;
        case TeX_end:
        {
            FILE *file_TeX = fopen(TEX_NAME_FILES,"at");
            if (file_TeX == NULL)
                return ERROR_DUMP;
            fprintf(file_TeX, "\\end{document}\n");
            fclose(file_TeX);
            system("open -a /Applications/texmaker.app '/Users/macbook/Documents/GitHub/Differentiator/Differentiator/fileTeX.tex'");
            //system("latex /Users/macbook/Documents/GitHub/Differentiator/Differentiator/fileTeX.tex");
            //system("open  /Users/macbook/fileTeX.dvi");
        }
            break;
        case TeX_print:
        {
            assert(Tree);
            assert(cell);
            int recurs = 0;
            FILE *file_TeX = fopen(TEX_NAME_FILES,"at");
            fprintf(file_TeX, "\\begin{equation}\n");
            PrintTexRecurs (Tree, cell, file_TeX, mark, &recurs);
            if (mark != enddiff)
                fprintf(file_TeX, "=");
            fprintf(file_TeX, "\n\\end{equation}\n");
            fclose(file_TeX);
        }
            break;
            
        default:
            break;
    }
    return 0;
}



Cell_t* PrintTexRecurs  (Tree_t* Tree, Cell_t* cell, FILE* file_TeX, int mark, int* recurs) {
    assert(Tree);
    assert(cell);
    ++*recurs;
    
    if (mark == diff)
        fprintf(file_TeX, "\\left( ");
    if (cell->data [0] == '/')
        fprintf(file_TeX, "\\frac{");
    if (strcmp("log", cell->data) == 0)
        fprintf(file_TeX, "\\log_");
    if ((cell->data [0] == '+') || (cell->data [0] == '-'))
        if (cell->prev != 0) {
            if (strcmp("sqrt", cell->prev->data) != 0)
                fprintf(file_TeX, "\\left( ");
        } else
            fprintf(file_TeX, "\\left( ");
    
    if (cell->nextl != NULL) {
        if (strcmp("sqrt", cell->data) == 0)
            fprintf(file_TeX, "\\%s {", cell->data);
        if ((cell->nextr == NULL) && (strcmp("sqrt", cell->data) != 0))
            fprintf(file_TeX, "%s \\left( ", cell->data);
        
        
        fprintf(file_TeX, "{");
        PrintTexRecurs (Tree, cell->nextl, file_TeX, nodiff, recurs);
        fprintf(file_TeX, "}");
        
        if (cell->nextr != NULL) {
            if ((cell->data [0] != '/') && (strcmp("log", cell->data) != 0))
                fprintf(file_TeX, "%s ", cell->data);
        } else
            if (strcmp("sqrt", cell->data) != 0)
                fprintf(file_TeX, "\\right) ");
            else
                fprintf(file_TeX, "} ");
    }
    
    if (cell->data [0] == '/')
        fprintf(file_TeX, "}{");
    
    
    if (cell->nextr != NULL) {
        if (strcmp("log", cell->data) == 0)
            fprintf(file_TeX, "\\left( ");
        
        fprintf(file_TeX, "{");
        PrintTexRecurs (Tree, cell->nextr, file_TeX, nodiff, recurs);
        fprintf(file_TeX, "}");
        
        if (strcmp("log", cell->data) == 0)
            fprintf(file_TeX, "\\right) ");
    }
    
    
    if ((cell->nextl == NULL) && (cell->nextr == NULL)) {
        fprintf(file_TeX, "%s ", cell->data);
    }
    
    if (cell->data [0] == '/')
        fprintf(file_TeX, "}");
    if ((cell->data [0] == '+') || (cell->data [0] == '-'))
        if (cell->prev != 0) {
            if (strcmp("sqrt", cell->prev->data) != 0)
                fprintf(file_TeX, "\\right) ");
        } else
            fprintf(file_TeX, "\\right) ");
    
    if (mark == diff)
        fprintf(file_TeX, "\\right)' ");
    
    return cell;
}



int TextTeX (int number, char * str, int mark) {
    FILE *file_TeX = fopen(TEX_NAME_FILES,"at");
    if (file_TeX == NULL)
        return ERROR_DUMP;
    switch (number) {
        case BeginDiffTeX:
            if (mark == NULL)
                fprintf(file_TeX, "\nПроизводная функции находится очевидным и нетривиальным способом:\n");
            else {
                fprintf(file_TeX, "\nПроизводная ");
                fprintf(file_TeX, "%i ", mark);
                fprintf(file_TeX, "порядка равна:\n");
            }
            break;
        case EndDiffTeX:
            fprintf(file_TeX, "\nВ общем, смотри, катай и изучай :)\n");
            break;
        case RNDDiffTeX:
            if (mark == NULL)
                fprintf(file_TeX, "\nДалее будем рассматривать призводные функции по частям, дабы облегчить себе задачу.\n");
            else
                switch (mark) {
                    case 1:
                        fprintf(file_TeX, "\nЭта легкая функция, справится с ней даже школьник.\n");
                        break;
                    case 2:
                        fprintf(file_TeX, "\nДавайте рассмотрим подробней эту фунцию.\n");
                        break;
                    case 3:
                        fprintf(file_TeX, "\nТут мы воспользуемся формулами и найдем производную.\n");
                        break;
                        
                    default:
                        break;
                }
                
            break;
        case SpeakDiffTeX:
            fprintf(file_TeX, "\n%s\n", str);
            break;
        case ShortDiffTeX:
            fprintf(file_TeX, "\nТут слегка упростим наше выражение\n");
            break;
        case PresentDiffTeX:
            fprintf(file_TeX, "\nПредставим ответ в полном виде:\n");
            break;
            
        default:
            break;
    }
    fclose(file_TeX);
    return 0;
}
