
const char* DUMP_DOT_NAME_FILES = "dump_tree.gv";

const int CELL_SIZE_DATA = 20;

/*!
 \brief Cell Tree
 */
struct Cell_t  {
    TYPE_TREE data = 0;            ///<value element cell
    Cell_t* nextl;                 ///<pointer on previous element cell, if his on that it is empty (left)
    Cell_t* nextr;                 ///<pointer on previous element cell, if his on that it is empty (right)
    Cell_t* prev;                  ///<pointer on next element cell, if his on that it is empty
    int number;                    ///<cell number from the list
    int type;                      ///<type cell
    //int mark;
};


/*!
 \brief type Tree
 */
struct Tree_t {
    Cell_t* cell;                  ///<pointer on dynamic massif cells
    int size = 0;                  ///<size array cells
    Cell_t* position_first_cell;   ///<pointer to the first cell of the tree
    
        int position_number;           ///<number to a tree item
        Cell_t* position_cell;         ///<pointer to a tree item
    
    int format;                    ///<indent format
    bool param;                    ///<bool parameter
    char* str_param;                ///<string parameter
    
};


enum ERROR {
    ERROR_NEW_CELL = 1,            ///<error creating a new tree cell
    ERROR_DUMP = 2,                ///<dump error
    ERROR_DEL_CELL = 3             ///<error removing the cell tree
};


enum PLUS_CELL {
    LEFT_cell = 1,                 ///<left direction
    RIGHT_cell = 2                 ///<right direction
};


enum DIRECTION_REC {
    FROM_BELOW = 1,                 ///<recursion from below
    FROM_ABOVE = 2                  ///<recursion from above
};


/*!
 \brief TreeConstruct sheet constructor type TYPE_Tree
 \param element the first default item in the Tree
 \return pointer to TYPE_Tree type list
 */
Tree_t* TreeConstruct (TYPE_TREE element);


/*!
 \brief TreeDestructor sheet constructor type TYPE_Tree
 \param Tree pointer to TYPE type Tree
 \return int
 */
int TreeDestructor (Tree_t* Tree);


/*!
 \brief CellDelete an auxiliary function for removing tree cells, this function is used only in the TreeGoRound and in the TreeRecurs
 \param Tree pointer to TYPE type Tree
 \param cell pointer to a cell to delete
 \return Cell_t pointer to the previous branch in the tree
 */
Cell_t* TreeCellDelete(Tree_t* Tree, Cell_t* cell);


/*!
 \brief TreeAdd adding a new item
 \param Tree pointer to TYPE type Tree
 \param cell a pointer to the cell of the array
 \param next branch: LEFT_cell or RIGHT_cell
 \param element insertion element
 \return int
 */
int TreeAdd (Tree_t* Tree, Cell_t* cell, const int next, TYPE_TREE element);


/*!
 \brief TreeAddLeft adding a new element on the left branch
 \param Tree pointer to TYPE type Tree
 \param cell a pointer to the cell of the array
 \param element insertion element
 \return int
 */
int TreeAddLeft(Tree_t* Tree, Cell_t* cell, TYPE_TREE element);


/*!
 \brief TreeAddRight adding a new element on the right branch
 \param Tree pointer to TYPE type Tree
 \param cell a pointer to the cell of the array
 \param element insertion element
 \return int
 */
int TreeAddRight(Tree_t* Tree, Cell_t* cell, TYPE_TREE element);


/*!
 \brief TreeConstruct sheet constructor type TYPE_TREE
 \param Tree pointer to TYPE type Tree
 \param cell a pointer to the cell of the array
 \return int
 */
int TreeDelete (Tree_t* Tree, Cell_t* cell);


/*!
 \brief TreeDump dump on a sheet
 \param Tree pointer to TYPE type Tree
 \param cell print pointer to a dump cell
 \return int
 */
int TreeDump (Tree_t* Tree, Cell_t* cell);


/*!
 \brief TreePrintNode1 (full format) recursive printing of cells into a dump, this function is used only in the TreeGoRound and in the TreeRecurs
 \param Tree pointer to TYPE type Tree
 \param cell print pointer to a dump cell
 \return Cell_t pointer to the previous branch in the tree
 */
Cell_t* TreePrintNode1 (Tree_t* Tree, Cell_t* cell);


/*!
 \brief TreePrintNode2 (full format) recursive printing of cells into a dump, this function is used only in the TreeGoRound and in the TreeRecurs
 \param Tree pointer to TYPE type Tree
 \param cell print pointer to a dump cell
 \return Cell_t pointer to the previous branch in the tree
 */
Cell_t* TreePrintNode2 (Tree_t* Tree, Cell_t* cell);


/*!
 \brief TreePrintNodeUSE1 (compressed format) recursive printing of cells into a dump, this function is used only in the TreeGoRound and in the TreeRecurs
 \param Tree pointer to TYPE type Tree
 \param cell print pointer to a dump cell
 \return Cell_t pointer to the previous branch in the tree
 */
Cell_t* TreePrintNodeUSE1 (Tree_t* Tree, Cell_t* cell);


/*!
 \brief TreePrintNodeUSE2 (compressed format) recursive printing of cells into a dump, this function is used only in the TreeGoRound and in the TreeRecurs
 \param Tree pointer to TYPE type Tree
 \param cell print pointer to a dump cell
 \return Cell_t pointer to the previous branch in the tree
 */
Cell_t* TreePrintNodeUSE2 (Tree_t* Tree, Cell_t* cell);


/*!
 \brief PositionCell_data  ПОТОМ ХУЯКНУ СУДЫ ОПРЕДЕЛЕНИЕ
 \param Tree pointer to TYPE type Tree
 \param cell print pointer to a dump cell
 \return Cell_t* pointer to the branch
 */
Cell_t* TreePositionCell_data (Tree_t* Tree, Cell_t* cell);


/*!
 \brief TreePosRecurs_data ПОТОМ ХУЯКНУ СУДЫ ОПРЕДЕЛЕНИЕ, this function is used only in the TreeGoRound and in the TreeRecurs
 \param Tree pointer to TYPE type Tree
 \param cell print pointer to a dump cell
 \return Cell_t pointer to the previous branch in the tree
 */
Cell_t* TreePosRecurs_data (Tree_t* Tree, Cell_t* cell);


/*!
 \brief PositionCell search for a branch with a number in cell_number in the Tree
 \param Tree pointer to TYPE type Tree
 \param cell_number number of the desired branch
 \return Cell_t* pointer to the branch
 */
Cell_t* TreePositionCell (Tree_t* Tree, int cell_number);


/*!
 \brief TreePosRecurs recursively searches for a cell with a number, this function is used only in the TreeGoRound and in the TreeRecurs
 \param Tree pointer to TYPE type Tree
 \param cell print pointer to a dump cell
 \return Cell_t pointer to the previous branch in the tree
 */
Cell_t* TreePosRecurs (Tree_t* Tree, Cell_t* cell);


/*
 \brief error_prog searching for errors in the use of a tree
 \param number error number
 \return int
*/
int TreeErrorProg (int number);


/*!
 \brief TreeGoRound function of wood crocheting and processing
 \param Tree pointer to TYPE type Tree
 \param cell print pointer to a dump cell
 \param function This is an auxiliary function that will handle the final element of the tree branch, be sure to watch the ad
 \return int
 */
int TreeGoRound (Tree_t* Tree, Cell_t* cell, Cell_t* (*function)(Tree_t*, Cell_t*), const int direction);


/*!
 \brief TreeRecurs recursively traverses the entire tree by stopping on each finite branch
 \param pos_cell a pointer to the cell of the array
 \param function This is an auxiliary function that will handle the final element of the tree branch, be sure to watch the ad
 \param direction recursion direction
 \return int returns a pointer to the previous branch element for recursive traversal (WARNING)!!!
 */
Cell_t* TreeRecurs (Tree_t* Tree, Cell_t* pos_cell, Cell_t* (*function)(Tree_t*, Cell_t*), const int direction);


/*!
 \brief TreeReadFiles function that creates a new tree to the branch, read from a file
 \param name_files name of the file to read
 \param Tree pointer to TYPE type Tree
 \param cell pointer to a tree branch
 \return int
 */
int TreeReadFiles (const char* name_files, Tree_t* Tree, Cell_t* cell);


/*!
 \brief TreeReadFilesRecurs function to recursively read a file from the buffer and create new branches
 \param my_buffer buffer with the contents of the file
 \param number_of_char buffer size in characters
 \param Tree pointer to TYPE type Tree
 \param cell pointer to a tree branch
 \param next branch: LEFT_cell or RIGHT_cell
 \return pointer to a new buffer
 */
char* TreeReadFilesRecurs (char* my_buffer, long int number_of_char, Tree_t* Tree, Cell_t* cell, int next);


/*!
 \brief ReadFiles file reading function
 \param name_files name of the file to read
 \param number_of_char buffer size in characters
 \return pointer to a new buffer
 */
char* ReadFiles (const char* name_files, long int *number_of_char);


/*!
 \brief TreePrintFile print a tree to a file, this function is used only in the TreeGoRound and in the TreeRecurs
 \param Tree pointer to TYPE type Tree
 \param cell print pointer to a dump cell
 \return Cell_t pointer to the previous branch in the tree
 */
int TreePrintFile (Tree_t* Tree,  Cell_t* cell);


/*!
 \brief TreePrintFileRecurs print a tree to a file, this function is used only in the TreeGoRound and in the TreeRecurs
 \param Tree pointer to TYPE type Tree
 \param cell print pointer to a dump cell
 \return Cell_t pointer to the previous branch in the tree
 */
Cell_t* TreePrintFileRecurs (Tree_t* Tree, Cell_t* cell);


/*!
 \brief Cell_new creates a tree cell
 \param Tree pointer to TYPE type Tree
 \return Cell_new returns a pointer to a new tree element
 */
Cell_t* CellNew(Tree_t* Tree);



/*
 \brief TreeCopyRecurs copies the entire tree from the "cell" branch (inclusive) to the "cell_copy" sub-branch of the "TreeC" tree, the left or right sub-branch of the "next" sub-branch, given by the constant.
 \param TreeC wood for a copy
 \param cell_copy branch for inserting a copy
 \param cell pointer to the beginning of the copied part of the tree, branches
 \param next branch sub-branch
 \return Cell_t Specifies the copied tree, the initial branch of the tree
*/
Cell_t* TreeCopyRecurs (Tree_t* TreeC, Cell_t* cell_copy, Cell_t* cell, const int next);






/*
 |===================|
 |                   |
 |     function      |
 |                   |
 |===================|
*/



Tree_t*  TreeConstruct (TYPE_TREE element)
{
    Tree_t* Tree = new Tree_t;
    
    Cell_t* cell = new Cell_t;
    cell->data = element;
    cell->number = 0;
    cell->prev = NULL;
    cell->nextl = NULL;
    cell->nextr = NULL;
    //cell->mark = 0;
    
    Tree->cell = cell;
    
        Tree->position_number = 0;
        Tree->position_cell = NULL;
    
    Tree->format = 0;
    Tree->param = true;
    Tree->str_param = NULL;
    
    Tree->position_first_cell = Tree->cell;
    Tree->size = 1;
    return Tree;
}



int TreeDestructor (Tree_t* Tree) {
    assert(Tree);
    TreeGoRound (Tree, Tree->position_first_cell, TreeCellDelete, FROM_BELOW);
    delete Tree;
    return 0;
}



Cell_t* TreeCellDelete(Tree_t* Tree, Cell_t* cell) {
    assert(cell);
    Cell_t* pos_cell_prev = cell->prev;
    
    delete cell;
    
    return pos_cell_prev;
}


//после
int TreeAdd(Tree_t* Tree, Cell_t* cell, int next, TYPE_TREE element) {
    assert(cell);
    assert(Tree);
    Cell_t* new_cell = new Cell_t;
    if (new_cell == NULL)
        return ERROR_NEW_CELL;
    new_cell->data = element;
    new_cell->number = Tree->size;
    new_cell->prev = cell;
    new_cell->nextl = NULL;
    new_cell->nextr = NULL;
    
    if (next == LEFT_cell)
        cell->nextl = new_cell;
    else
        if (next == RIGHT_cell)
            cell->nextr = new_cell;
    //вывод ошибки!!!!!!!!!!!!!!!!!!!!!!!!!!!
    
    ++Tree->size;
    return 0;
}



int TreeAddLeft(Tree_t* Tree, Cell_t* cell, TYPE_TREE element) {
    assert(cell);
    assert(Tree);
    TreeAdd(Tree, cell, LEFT_cell, element);
    return 0;
}



int TreeAddRight(Tree_t* Tree, Cell_t* cell, TYPE_TREE element) {
    assert(cell);
    assert(Tree);
    TreeAdd(Tree, cell, RIGHT_cell, element);
    return 0;
}



//удаление
int TreeDelete (Tree_t* Tree, Cell_t* cell) {
    assert(cell);
    assert(Tree);
    
    if ((cell->nextl == NULL) && (cell->nextr == NULL)) {
        delete cell;
        --Tree->size;
        return 0;
    }
    return ERROR_DEL_CELL;
}




int TreeDump (Tree_t* Tree, Cell_t* cell) {
    assert(Tree);
    
    FILE *file_dump = fopen(DUMP_DOT_NAME_FILES,"wt");
    if (file_dump == NULL)
        return ERROR_DUMP;
    fprintf(file_dump, "digraph list {\n\tnode [shape = record,height=.1];\n");
    fclose(file_dump);
    
    TreeGoRound (Tree, cell, TreePrintNodeUSE1, FROM_BELOW); // TreePrintNode1 or TreePrintNodeUSE1
    TreeGoRound (Tree, cell, TreePrintNodeUSE2, FROM_BELOW); // TreePrintNode2 or TreePrintNodeUSE2
    
    file_dump = fopen(DUMP_DOT_NAME_FILES,"at");
    if (file_dump == NULL)
        return ERROR_DUMP;
    fprintf(file_dump, "}");
    fclose(file_dump);
    
    system("open -a /Applications/Graphviz.app '/Users/macbook/Documents/GitHub/Differentiator/Differentiator/dump_tree.gv'");
    
    return 0;
}

Cell_t* TreePrintNodeUSE1 (Tree_t* Tree, Cell_t* cell) {
    FILE *file_dump = fopen(DUMP_DOT_NAME_FILES,"at");
    
    fprintf(file_dump, "\t\"node%i\" [label = \"<f0>%s\" ] ;\n", cell->number, cell->data);
    
    fclose(file_dump);
    return cell->prev;
}



Cell_t* TreePrintNodeUSE2 (Tree_t* Tree, Cell_t* cell) {
    FILE *file_dump = fopen(DUMP_DOT_NAME_FILES,"at");
    
    if (cell->nextl != NULL)
        fprintf(file_dump, "\t\"node%i\":f0 -> \"node%i\":f0 [color=""red""];\n", cell->number, (cell->nextl)->number);
    if (cell->nextr != NULL)
        fprintf(file_dump, "\t\"node%i\":f0 -> \"node%i\":f0  [color=""green""];\n", cell->number, (cell->nextr)->number);
    
    fclose(file_dump);
    return cell->prev;
}

Cell_t* TreePrintNode1 (Tree_t* Tree, Cell_t* cell) {
    FILE *file_dump = fopen(DUMP_DOT_NAME_FILES,"at");
    
    fprintf(file_dump, "\t\"node%i\" [label = \"<f0>data = %s |<f1>nextl = %p |<f2>nextr = %p |<f3>pos = %p |<f4>prev = %p | <f5>type = %i \" ] ;\n", cell->number, cell->data, cell->nextl, cell->nextr, cell, cell->prev, cell->type);
    
    fclose(file_dump);
    return cell->prev;
}



Cell_t* TreePrintNode2 (Tree_t* Tree, Cell_t* cell) {
    FILE *file_dump = fopen(DUMP_DOT_NAME_FILES,"at");
    
    if (cell->nextl != NULL)
        fprintf(file_dump, "\t\"node%i\":f1 -> \"node%i\":f3 [color=""red""];\n", cell->number, (cell->nextl)->number);
    if (cell->nextr != NULL)
        fprintf(file_dump, "\t\"node%i\":f2 -> \"node%i\":f3 [color=""green""];\n", cell->number, (cell->nextr)->number);
    if (cell->prev != NULL)
        fprintf(file_dump, "\t\"node%i\":f4 -> \"node%i\":f3;\n", cell->number, (cell->prev)->number);
    
    fclose(file_dump);
    return cell->prev;
}



Cell_t* TreePositionCell_data (Tree_t* Tree, Cell_t* cell) {
    assert(Tree);
    
    Tree->cell = Tree->position_first_cell;
    Tree->position_cell = NULL;
    
    TreeGoRound (Tree, Tree->position_first_cell, TreePosRecurs_data, FROM_BELOW);
    
    if (Tree->position_cell == NULL)
        return NULL;
    
    return Tree->position_cell;
}



Cell_t* TreePosRecurs_data (Tree_t* Tree, Cell_t* cell) {
    if (strcmp(Tree->str_param, cell->data) == 0) {
        Tree->position_cell = cell;
    }
    return cell->prev;
}



Cell_t* TreePositionCell (Tree_t* Tree, int cell_number) {
    assert(Tree);
    Tree->position_cell = NULL;
    Tree->cell = Tree->position_first_cell;
    Tree->position_number = cell_number;
    TreeGoRound (Tree, Tree->position_first_cell, TreePosRecurs, FROM_BELOW);
    
    return Tree->position_cell;
}



Cell_t* TreePosRecurs (Tree_t* Tree, Cell_t* cell) {
    if (Tree->position_number == cell->number) {
        Tree->position_cell = cell;
    }
    return cell->prev;
}



int TreeGoRound (Tree_t* Tree, Cell_t* cell, Cell_t* (*function)(Tree_t*, Cell_t*), const int direction) {
    assert(function);
    assert(Tree);
    
    Tree->cell = Tree->position_first_cell;
    TreeRecurs (Tree, cell, function, direction);
    return 0;
}



Cell_t* TreeRecurs  (Tree_t* Tree, Cell_t* pos_cell, Cell_t* (*function)(Tree_t*, Cell_t*), const int direction) {
    assert(function);
    assert(Tree);
    assert(pos_cell);
    
    if (direction == FROM_ABOVE) {
        Tree->param = true;
        function (Tree, pos_cell); // функция обязательна должна возвращать pos_prev указатель на предыдующую ветку дерева!!!!!!!!
    }
    
    if (pos_cell->nextl != NULL) {
        pos_cell = pos_cell->nextl;
        pos_cell = TreeRecurs (Tree, pos_cell, function, direction);
    }
    if (pos_cell->nextr != NULL) {
        pos_cell = pos_cell->nextr;
        pos_cell = TreeRecurs (Tree, pos_cell, function, direction);
    }
    
    if (direction == FROM_ABOVE)
        Tree->param = false;
    
    pos_cell = function (Tree, pos_cell); // функция обязательна должна возвращать pos_prev указатель на предыдующую ветку дерева!!!!!!!!
    
    return pos_cell;
}



int TreeReadFiles (const char* name_files, Tree_t* Tree, Cell_t* cell, const int next) {
    assert(Tree);
    assert(cell);
    long int number_of_char = 0;
    
    char* my_buffer = ReadFiles (name_files, &number_of_char);
    
    TreeReadFilesRecurs(my_buffer, number_of_char, Tree, cell, next);
    
    return 0;
}



char* TreeReadFilesRecurs (char* my_buffer, long int number_of_char, Tree_t* Tree, Cell_t* cell, int next) {
    assert(my_buffer);
    assert(Tree);
    assert(cell);
    
    //craft
    char* str = new char [CELL_SIZE_DATA];
    
    for (int i = 0; ((i < number_of_char) && (my_buffer [0] != '\'')); ++i, ++my_buffer) {}
    ++my_buffer;
    for (int i = 0; my_buffer [i] != '\''; ++i) {
        str [i] = my_buffer [i];
        str [i+1] = '\0';
    }
    for (int i = 0; ((i < number_of_char) && (my_buffer [0] != '\'')); ++i, ++my_buffer) {}
    ++my_buffer;
    
    for (int i = 0; ((i < number_of_char) && (my_buffer [0] != '(') && (my_buffer [0] != ')')); ++i, ++my_buffer) {}
    
    Cell_t* cell_new = new Cell_t;
    cell_new->data = str;
    cell_new->number = Tree->size;
    cell_new->prev = cell;
    cell_new->nextl = NULL;
    cell_new->nextr = NULL;
    ++Tree->size;
    
    if (next == LEFT_cell)
        cell->nextl = cell_new;
    else
        if (next == RIGHT_cell)
            cell->nextr = cell_new;
    
    
    if (my_buffer [0] == '(') {
        my_buffer = TreeReadFilesRecurs (my_buffer, number_of_char, Tree, cell_new, LEFT_cell);
        
        ++my_buffer;
        for (int i = 0; ((i < number_of_char) && (my_buffer [0] != '(') && (my_buffer [0] != ')')); ++i, ++my_buffer) {}
        
        if (my_buffer [0] == ')') {
            return my_buffer;
        }
        
        my_buffer = TreeReadFilesRecurs (my_buffer, number_of_char, Tree, cell_new, RIGHT_cell);
        
        ++my_buffer;
        for (int i = 0; ((i < number_of_char) && (my_buffer [0] != '(') && (my_buffer [0] != ')')); ++i, ++my_buffer) {}
        if (my_buffer [0] == ')') {
            return my_buffer;
        }
        
    }
    
    return my_buffer;
}



char* ReadFiles (const char* name_files, long int *number_of_char) {
    
    
    FILE *files = fopen (name_files, "rt");
    
    
    if (files == NULL)
    {
        assert(files != NULL);
    }
    
    fseek (files, 0, SEEK_END);
    *number_of_char = ftell(files);
    
    char* file_validation = new char [++*number_of_char];
    
    
    fseek (files, 0, SEEK_SET);
    fread (file_validation, sizeof (char), *number_of_char, files);
    fclose (files);
    file_validation [*number_of_char - 1] = '\0';
    return file_validation;
}



int TreePrintFile (Tree_t* Tree,  Cell_t* cell) {
    assert(Tree);
    assert(cell);
    Tree->format = 0;
    Tree->param = true;
    
    FILE *files = fopen (TREE_FILES1, "wt");
    fclose(files);
    TreeGoRound(Tree, cell, TreePrintFileRecurs, FROM_ABOVE);
    
    return 0;
}



Cell_t* TreePrintFileRecurs (Tree_t* Tree, Cell_t* cell) {
    
    FILE *files = fopen (TREE_FILES1, "at");
    
    
    if (Tree->param) {
        for (int i = 0; i < Tree->format; ++i)
            fprintf(files,"      ");
        
        fprintf(files,"('%s'\n",cell->data);
        ++Tree->format;
        
    } else {
        --Tree->format;
        
        for (int i = 0; i < Tree->format; ++i)
            fprintf(files,"      ");
        
        fprintf(files,")\n");
    }
    
    fclose(files);
    return cell->prev;
}



Cell_t* CellNew(Tree_t* Tree) {
    Cell_t* cell_new = new Cell_t;
    cell_new->number = Tree->size;
    cell_new->prev = NULL;
    cell_new->nextl = NULL;
    cell_new->nextr = NULL;
    ++Tree->size;
    return cell_new;
}



Cell_t* TreeCopyRecurs (Tree_t* TreeC, Cell_t* cellC, Cell_t* cell, const int next) {
    assert(TreeC);
    assert(cell);
    
    Cell_t* cell_copy = CellNew(TreeC);
    cell_copy->data = cell->data;
    cell_copy->type = cell->type;
    //cell_copy->mark = cell->mark;
    
    cell_copy->prev = cellC;
    
    if (cellC != NULL) {
        if (next == LEFT_cell)
            cellC->nextl = cell_copy;
        else
            if (next == RIGHT_cell)
                cellC->nextr = cell_copy;
    } else
        printf("WARNING:\n  In TreeCopyRecurs() parameter cellC = %p\n",cellC);
    
    if (cell->nextl != NULL) {
        cell_copy->nextl = TreeCopyRecurs (TreeC, cell_copy, cell->nextl, LEFT_cell);
        
    }
    if (cell->nextr != NULL) {
        cell_copy->nextr = TreeCopyRecurs (TreeC, cell_copy, cell->nextr, RIGHT_cell);
    }
    
    // функция обязательна должна возвращать pos_prev указатель на предыдующую ветку дерева!!!!!!!!
    
    return cell_copy;
}



int TreeErrorProg (int number) {
    switch (number) {
        case ERROR_DUMP:
            printf("\ndump error in .dot\n");
            assert(0);
            break;
            
        case ERROR_NEW_CELL:
            printf("\nerror of writing a new cell to the list\n");
            assert(0);
            break;
            
        case ERROR_DEL_CELL:
            printf("\nerror on deleting the desired item\n");
            assert(0);
            break;
            
        case 0:
            return 0;
            break;
            
        default:
            printf("\nunknown error %i\n", number);
            assert(0);
            break;
    }
    return 0;
}


