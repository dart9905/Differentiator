
#define dT_symbol 1
#define dT_value 2
#define dT_operator 3



#define dl                               Diffunction(dTree, cell->nextl)
#define dr                               Diffunction(dTree, cell->nextr)

#define l                                TreeCopyRecurs(dTree, dcell, cell->nextl, LEFT_cell)
#define r                                TreeCopyRecurs(dTree, dcell, cell->nextl, LEFT_cell)



#define ADD(  left , right )              New_dCell(dTree, dT_operator, "+",   left, right)
#define MUL(  left , right )              New_dCell(dTree, dT_operator, "*",   left, right)
#define DIV(  left , right )              New_dCell(dTree, dT_operator, "/",   left, right)
#define SUB(  left , right )              New_dCell(dTree, dT_operator, "-",   left, right)
#define POV(  left , right )              New_dCell(dTree, dT_operator, "^",   left, right)
#define SIN(  left , right )              New_dCell(dTree, dT_operator, "sin", left, right)
#define COS(  left , right )              New_dCell(dTree, dT_operator, "cos", left, right)
#define TG(   left , right )              New_dCell(dTree, dT_operator, "tg",  left, right)
#define CTG(  left , right )              New_dCell(dTree, dT_operator, "ctg", left, right)



DIFF_( +  , dT_operator, ADD( dl, dr) )
DIFF_( -  , dT_operator, SUB( dl, dr) )
DIFF_( /  , dT_operator, DIV(SUB(MUL(dl, r), MUL(l, dr)), MUL(r , r)) )
DIFF_( *  , dT_operator, ADD(MUL (dl, r), MUL(l, dr)) )
DIFF_( sin, dT_operator, MUL(  dl , SIN( l, NULL )) )
DIFF_( cos, dT_operator, MUL(  dl , COS( l, NULL )) )
DIFF_( tg , dT_operator, MUL(  dl , TG( l, NULL )) )
DIFF_( ctg, dT_operator, MUL(  dl , CTG( l, NULL )) )
DIFF_( ^  , dT_operator, MUL(  dl , POV( dl, dr)) )

#undef dT_symbol
#undef dT_value
#undef dT_operator
#undef PLUS
#undef MUL
#undef DIV
#undef SUB
#undef POV
#undef SIN
#undef COS
#undef TG
#undef CTG
#undef dl
#undef dr
#undef l
#undef r
