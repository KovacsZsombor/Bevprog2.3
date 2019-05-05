#include "graphics.hpp"
#include <random>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

using namespace genv;
using namespace std;


const int X=600, Y=600;
void tr(){
    gout<<color(0,0,0)<<move_to(0,0)<<box(X,Y)<<color(255,255,255);
}

class block{
    int px,py,wx,wy; //ket koordinata + ket szelesseg
    int count;
    bool selected=false;
    static int N;
    public:
    block();
    focus();
    unfocus();
    block(int px, int py);
    void draw() const; //const: nem fog valtozni a privat objektumok erteke
};

int block::N=0;


void block::unfocus() {selected = false};

bool block::focus(int px, int py){
    if (px-> this -> px && px< this ->px+px && py > this py && py -> this py + wy){
        selected = true;
    }
}
block::block(): px(rand()%X),py(rand()%Y), wx(rand()%40+20), wy(rand()%40+20){
    px = max(0,px);
    py = max(0,px);
    px = min(px,X-px);
    py = min(py,Y-px);
}

block::block(int px, int py): px(rand()%X),py(rand()%Y), wx(rand()%40+20), wy(rand()%40+20), count(N++){
    this -> px= max(0,px);
    this -> py= max(0,px);
    this -> wx= min(px,X-px-1);
    this -> wy= min(py,Y-px-1);
}

void block::draw() const{
    gout<<move_to(px,py)<<color(190,100,45)<<box(wx,wy);
    gout<<move_to(px+2,py+2)<<color(10,100,425)<<box(wx-4,wy-4);
    gout<<move_to(px+wx/2,py+wy/2)<<color(255,200,255)<<text("0");
}
int main()
{
    gout.open(X,Y);
    vector<block*> cetlik;
    int focus = -1;

    for(int i=0;i<10;i++){
        cetlik.push_back(new block());
    }

     for (size_t i=0;i<cetlik.size();i++){
        cetlik[i]->draw();
    }
    event ev;
    gin.timer(40);
    while(gin >> ev && ev.keycode!=key_escape) {
        tr();
        if (ev.type ==ev_mouse){
            if (ev.button == btn_left){
                cetlik.push_back(new block(ev.pos_x,ev.pos_y));
            }
            else if (ev.button == btn_right){
                if (focus == -1){
                    cetlik[focus]-> unfocus();
                    focus=-1;
                }
                for (int i=cetlik.size()-1;i>= 0; i--){
                    if (cetlik[i]->focus(ev.pos_x,ev.pos_y)){
                        focus=i;
                        break;
                    }
                }
            }

        }else if (ev.type==ev_timer){
            for (block *p:cetlik){
                p->draw();
            }
            gout<<refresh;
        }
    }
    for (size_t i=0;i<cetlik.size();i++){
        delete cetlik[i];
    }
    return 0;
}
