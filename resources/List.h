//typedef int TYPE_LIST;

/*!
 \brief Cell list
 */
struct List_Cell_t  {
    TYPE_LIST data = 0;   ///<value element cell
    List_Cell_t* next;    ///<pointer on previous element cell, if his on that it is empty
    List_Cell_t* prev;    ///<pointer on next element cell, if his on that it is empty
    int number;           ///<cell number from the list
};


/*!
 \brief type list
 */
struct List_t {
    List_Cell_t* cell;                  ///<pointer on dynamic massif cells
    int size = 0;                       ///<size array cells
    List_Cell_t* position_cell;         ///<pointer to a list item
    List_Cell_t* position_first_cell;   ///<pointer to the first cell of the list
};


enum List_ERROR {
    List_ERROR_NEW_CELL = 1,
    List_ERROR_DUMP = 2
};


/*!
 \brief ListConstruct sheet constructor type TYPE_LIST
 \param element the first default item in the list
 \return pointer to TYPE_LIST type list
 */
List_t* ListConstruct (TYPE_LIST element);

/*!
 \brief ListDestructor sheet constructor type TYPE_LIST
 \param List pointer to TYPE type list
 \return int
 */
int ListDestructor (List_t* List);

/*!
 \brief ListConstruct sheet constructor type TYPE_LIST
 \param List pointer to TYPE type list
 \param cell a pointer to the cell of the array
 \param element insertion element
 \return int
 */
int ListAddBefore (List_t* List, List_Cell_t* cell, TYPE_LIST element);


int ListAddBeforeUSR (List_t* List, int number, TYPE_LIST element);


/*!
 \brief ListConstruct sheet constructor type TYPE_LIST
 \param List pointer to TYPE type list
 \param cell a pointer to the cell of the array
 \param element insertion element
 \return int
 */
int ListAddAfter (List_t* List, List_Cell_t* cell, TYPE_LIST element);


int ListAddAfterUSR (List_t* List, int number, TYPE_LIST element);


/*!
 \brief ListConstruct sheet constructor type TYPE_LIST
 \param List pointer to TYPE type list
 \param cell a pointer to the cell of the array
 \return int
 */
int ListDelete (List_t* List, List_Cell_t* cell);


/*!
 \brief ListDump dump on a sheet
 \param List pointer to TYPE type list
 \return int
 */
int ListDump (List_t* List);


List_Cell_t* PositionCell (List_t* List, int cell_number);


int ListComparison (const void* pcell1, const void* pcell2);


int printlist (List_t* List) {
    List->cell = List->position_first_cell;
    printf("\n=========\n");
    for (int i = 0; i < List->size; ++i) {
        printf("\ncell[%i]\n    data = %s;\n    pcell = %p;\n    next = %p;\n    prev = %p;\n", (List->cell)->number, (List->cell)->data, List->cell, (List->cell)->next, (List->cell)->prev);
        List->cell = (List->cell)->next;
        
    }
    return 0;
}


int error_prog (int number);





/*
 |===================|
 |                   |
 |     function      |
 |                   |
 |===================|
*/



List_t*  ListConstruct (TYPE_LIST element)
{
    List_t* List = new List_t;
    
    List_Cell_t* cell = new List_Cell_t;
    cell->data = element;
    cell->number = 0;
    cell->prev = NULL;
    cell->next = NULL;
    
    List->cell = cell;
    List->position_cell = NULL;
    List->position_first_cell = List->cell;
    List->size = 1;
    return List;
}



int ListDestructor (List_t* List) {
    assert(List);
    List->cell = List->position_first_cell;
    for (int i = 1; i < List->size; ++i) {
        List->position_cell = List->cell;
        List->cell = (List->cell)->next;
        delete [] List->cell->data;
        delete List->position_cell;
    }
    delete List;
    return 0;
}


//после
int ListAddBefore (List_t* List, List_Cell_t* cell, TYPE_LIST element) {
    assert(cell);
    assert(List);
    List_Cell_t* new_cell = new List_Cell_t;
    if (new_cell == NULL)
        return List_ERROR_NEW_CELL;
    new_cell->data = element;
    new_cell->number = List->size;
    new_cell->prev = cell;
    new_cell->next = cell->next;
    
    (new_cell->prev)->next = new_cell;
    if (new_cell->next != NULL)
        (new_cell->next)->prev = new_cell;
    
    ++List->size;
    return 0;
}



int ListAddBeforeUSR (List_t* List, int number, TYPE_LIST element) {
    int error = ListAddAfter (List, PositionCell (List, number), element);
    error_prog (error);
    return 0;
}


//перед
int ListAddAfter (List_t* List, List_Cell_t* cell, TYPE_LIST element) {
    assert(cell);
    assert(List);
    List_Cell_t* new_cell = new List_Cell_t;
    if (new_cell == NULL)
        return List_ERROR_NEW_CELL;
    new_cell->data = element;
    new_cell->number = List->size;
    new_cell->prev = cell->prev;
    new_cell->next = cell;
    
    if (new_cell->prev != NULL)
        (new_cell->prev)->next = new_cell;
    else
        List->position_first_cell = new_cell;
    cell->prev = new_cell;
    
    ++List->size;
    
    return 0;
}



int ListAddAfterUSR (List_t* List, int number, TYPE_LIST element) {
    int error = ListAddBefore (List, PositionCell (List, number), element);
    error_prog (error);
    return 0;
}


//удаление
int ListDelete (List_t* List, List_Cell_t* cell) {
    assert(cell);
    assert(List);
    if (cell->next != NULL)
        (cell->next)->prev = cell->prev;
    if (cell->prev != NULL)
        (cell->prev)->next = cell->next;
    else
        List->position_first_cell = cell->next;
    
    delete cell;
    --List->size;
    return 0;
}



int ListDump (List_t* List) {
    assert(List);
    
    FILE *file_dump = fopen("dump.gv","wt");
    if (file_dump == NULL)
        return List_ERROR_DUMP;
    
    fprintf(file_dump, "digraph list {\n\tnode [shape = record,height=.1];\n");
    
    List->cell = List->position_first_cell;
    
    for (long int i = 0; i < List->size; ++i) {
        fprintf(file_dump, "\t\"node%i\" [label = \"<f0>data = %s |<f1>next = %p |<f2>pos = %p |<f3>prev = %p\" ] ;\n", (List->cell)->number, (List->cell)->data, (List->cell)->next, List->cell, (List->cell)->prev);
        List->cell = (List->cell)->next;
        
    }
    
    List->cell = List->position_first_cell;
    
    for (long int i = 0; i < List->size; ++i) {
        if ((List->cell)->next != NULL)
            fprintf(file_dump, "\t\"node%i\":f1 -> \"node%i\":f2;\n", (List->cell)->number, ((List->cell)->next)->number);
        if ((List->cell)->prev != NULL)
            fprintf(file_dump, "\t\"node%i\":f3 -> \"node%i\":f2;\n", (List->cell)->number, ((List->cell)->prev)->number);
        
        List->cell = (List->cell)->next;
    }
    
    fprintf(file_dump, "}");
    
    fclose(file_dump);
    system("open -a /Applications/Graphviz.app '/Users/macbook/Documents/GitHub/List/Lists/dump.gv'");
    
    return 0;
}



List_Cell_t* PositionCell (List_t* List, int cell_number) {
    assert(List);
    List->cell = List->position_first_cell;
    
    for (int i = 0; i < List->size; ++i) {
        if ((List->cell)->number == cell_number) {
            return List->cell;
        }
        List->cell = (List->cell)->next;
    }
    return NULL;
}



int error_prog (int number) {
    switch (number) {
        case List_ERROR_DUMP:
            printf("\ndump error in .dot\n");
            assert(0);
            break;
            
        case List_ERROR_NEW_CELL:
            printf("\nerror of writing a new cell to the list\n");
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
