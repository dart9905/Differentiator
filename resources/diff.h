
#define dT_symbol 1
#define dT_value 2
#define dT_operator 3
#define DT_const 4



#define dl                               Diffunction(dTree, cell->nextl)
#define dr                               Diffunction(dTree, cell->nextr)

#define l                                TreeCopyRecurs(dTree, dcell, cell->nextl, LEFT_cell)
#define r                                TreeCopyRecurs(dTree, dcell, cell->nextr, LEFT_cell)



#define ADD(  left , right )              New_dCell(dTree, dT_operator, "+",   left, right)
#define MUL(  left , right )              New_dCell(dTree, dT_operator, "*",   left, right)
#define DIV(  left , right )              New_dCell(dTree, dT_operator, "/",   left, right)
#define SUB(  left , right )              New_dCell(dTree, dT_operator, "-",   left, right)
#define POV(  left , right )              New_dCell(dTree, dT_operator, "^",   left, right)
#define SIN(  left , right )              New_dCell(dTree, dT_operator, "sin", left, right)
#define COS(  left , right )              New_dCell(dTree, dT_operator, "cos", left, right)
#define TG(   left , right )              New_dCell(dTree, dT_operator, "tg",  left, right)
#define CTG(  left , right )              New_dCell(dTree, dT_operator, "ctg", left, right)
#define LN(   left , right )              New_dCell(dTree, dT_operator, "ln", left, right)
#define MN1(  left , right )              New_dCell(dTree, dT_value, "-1", left, right)
#define AD1(  left , right )              New_dCell(dTree, dT_value, "1", left, right)
#define SQRT( left , right )              New_dCell(dTree, dT_operator, "sqrt", left, right)


DIFF_( +     , dT_operator, ADD( dl, dr) )
DIFF_( -     , dT_operator, SUB( dl, dr) )
DIFF_( /     , dT_operator, DIV( SUB( MUL( dl, r), MUL( l, dr)), MUL( r, r)) )
DIFF_( *     , dT_operator, ADD( MUL( dl, r), MUL( l, dr)) )
DIFF_( sin   , dT_operator, MUL( dl, COS( l, NULL)) )
DIFF_( cos   , dT_operator, MUL( MN1( NULL, NULL), MUL( dl, SIN( l, NULL))) )
DIFF_( tg    , dT_operator, DIV( dl, MUL( COS(l, NULL), COS(l, NULL))) )
DIFF_( ctg   , dT_operator, DIV( MUL( dl, MN1( NULL, NULL)), MUL( SIN(l, NULL), SIN(l, NULL))) )
DIFF_( ^     , dT_operator, MUL( POV( l, r), ADD( MUL( LN( l, NULL), dr), DIV( r, l))) )
DIFF_( ln    , dT_operator, DIV( dl, l) )
DIFF_( log   , dT_operator, DIV( dr, MUL( r, LN( l, NULL))) )
DIFF_( arcsin, dT_operator, DIV( dl, SQRT( SUB( AD1( NULL, NULL), MUL( l, l)), NULL)) )
DIFF_( arccos, dT_operator, DIV( dl, MUL( MN1( NULL, NULL), SQRT( SUB( AD1( NULL, NULL), MUL( l, l)), NULL))) )
DIFF_( arctg , dT_operator, DIV( dl, ADD( AD1( NULL, NULL), MUL( l, l))) )
DIFF_( arcctg, dT_operator, DIV( dl, MUL( MN1( NULL, NULL), ADD( AD1( NULL, NULL), MUL( l, l)))) )



#undef dT_symbol
#undef dT_value
#undef dT_operator
#undef DT_const
#undef PLUS
#undef MUL
#undef DIV
#undef SUB
#undef POV
#undef SIN
#undef COS
#undef TG
#undef CTG
#undef LN
#undef MN1
#undef SQRT
#undef dl
#undef dr
#undef l
#undef r
