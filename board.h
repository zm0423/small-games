#ifndef BOARD_H_
#define BOARD_H_

#include<vector>

namespace board
{

tamplate<typename T1, typename T2>
struct my_pair
{
    T1 first;
    T2 second;
};

class point_loc
{
 public:
    point_loc(int x, int y):data((x << 4) | y){}
    int x(){return data >> 4;}
    int y(){return data & 0x0F;}
 private:
    uc data;
};

typedef my_pair<point_loc, point_loc> p_pair;

typedef unsigned char uc;


/*
   from left
   345 line number when block
   6   0 player1 1 player 2
   78  type;
*/
class point
{

 public:
    enum{P_EMPTY = 0, P_LINE, P_POINT, P_HEADS};

    p_pair pre_change(int type, int player);

    void change_type(int type, int player, line * l = 0);

    void add(){if(type() == P_LINE)status += 0x08;}
    
    void lose(){if(type() == P_LINE)status -= 0x08;}

    int type(){return status & 0x03;}

    bool zero(){return status & 0x38;}

    int player(){return status & 0x04;}

    point():status(0), d_l(0){}

 private:
    uc status;
    line *d_l;
    void c_type(int type){status = ((status & 0xFC) | type);}
    void c_player(int player){status = ((status & 0xFB) | player);};
};

class line
{
 public:
    line(int x1, int y1, int x2, int y2);
    ~line(){circle(0, 0);}
    static board *s;
 private:
    void circle(int type, int person);
    p_pair p;
};

class board
{
    friend class line;
 public:
    board(){}
    void start();
 private:
    int make_line(point_loc p1, point_loc p2, int player);
    point_loc choose_point(int point);
    bool point_validity(point_loc p);
    std::vector<point_loc> temp;
    
    point_loc bd[10][10];
};

void print()



} //namespace board



#endif
