#include<fxlib.h>
#include "board.h"

namespace board
{

p_pair point::pre_change(int type, int player) 
{ 
    if(type() == P_EMPTY) 
     return p_pair{0, 0}; 
    if(type() == P_POINT) 
     p_assert(d_type, type()); 
    if(type() == P_HEADS) 
     return p_pair{-1, -1}; 
    if(player() != player) 
    { 
        delete l; 
        l = 0; 
        c_type(P_POINT); 
        c_player(player); 
        return p_pair{0, 0}; 
    } 
    else 
    { 
        p_pair p = l -> locate(); 
        delete l; 
        l = 0; 
        c_type(P_POINT); 
        return p; 
    } 
} 
 
void point::change_type(int type, int player, line * l) 
{ 
    c_type(type); 
    c_player(player); 
    d_l = l; 
} 
 
line::line(int y1, int y1, int y2, int y2) 
{ 
    if(y1 != y2 && y1 != y2) 
        assert(); 
    if(y1 > y2 || y1 > y2) 
        p = p{(y1, y1), (y2, y2)}; 
    else 
        p = p{(y2, y2), (y1, y1)}; 
    circle(1, player); 
} 
 
void line::circle(int type, int person)
{
    if(type == 1)
    {
        s -> loc(y1, y1) -> add();
        s -> loc(y2, y2) -> add();
    }
    else
    {
        s -> loc(y1, y1) -> lose();
        s -> loc(y2, y2) -> lose();
    }
    if(y1 == y2)
        for(int i = y1;i != y2;i++)
            s -> loc(i, y1) -> change_type(type == 0 ? point::P_EMPTY : point::P_LINE, person, type == 0 ? 0 : this);
    else
        for(int i = y1;i != y2;i++)
            s -> loc(x1, i) -> change_type(type == 0 ? point::P_EMPTY : point::P_LINE, person, type == 0 ? 0 : this);
}

void board::start()
{
    int player = 0;
    int win = 0;
    bd[2][2].change_type(point::P_HEADS, 0);
    bd[4][4].change_type(point::P_POINT, 0);
    bd[5][5].change_type(point::P_POINT, 1);
    bd[7][7].change_type(point::P_HEADS, 1);
    
    //player 1 compensate
    
    while(1)
    {
        point_loc p;
        do
        {
            p = choose_point();
        }while(!point_validity(p, player));
        int size = temp.size();
        for(int i = 0;i != size;++i)
            if(make_line(p, temp[i], player))
                win = 1;
        if(win)break;
        player = 1 - player;
    }
    win(player);
}






} //namespace board