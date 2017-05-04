#include "pokitto.h"
#include "sprites.h"
Pokitto::Core game;
bool checkcheck(short x, short y,short w, short h){
    short t =((short)(-y+w)/16)*8 +(short)((short)((-x+h)/16)/2);
    if(((short)((-x+h)/16))%2 ==1){
        if(level[t+3]>>4 == 15) return 0;
    }
    else{
       if(((uint8_t)(level[t+2]<<4))>>4 == 15)  return 0;
    }
    return 1;
}
bool collcheck(short x, short y){
    if(checkcheck(-x,-y,55,59)){
        return 0;
    }
    if(checkcheck(-x,-y,55,49)){
        return 0;
    }
    if(checkcheck(-x,-y,39,59)){
        return 0;
    }
    if(checkcheck(-x,-y,39,49)){
        return 0;
    }
    if(checkcheck(-x,-y,33,59)){
        return 0;
    }
    if(checkcheck(-x,-y,33,49)){
        return 0;
    }
    return 1;
}
void DrawLevel(short x, short y){
   game.display.drawRectangle((short)((-x+59)/16)*16+x,((short)(-y+55)/16)*16+y,16,16);
   game.display.drawRectangle((short)((-x+49)/16)*16+x,((short)(-y+55)/16)*16+y,16,16);
   game.display.drawRectangle((short)((-x+59)/16)*16+x,((short)(-y+39)/16)*16+y,16,16);
   game.display.drawRectangle((short)((-x+49)/16)*16+x,((short)(-y+39)/16)*16+y,16,16);
   game.display.drawRectangle((short)((-x+59)/16)*16+x,((short)(-y+33)/16)*16+y,16,16);
   game.display.drawRectangle((short)((-x+49)/16)*16+x,((short)(-y+33)/16)*16+y,16,16);
    Uint8 width = level[0];
    Uint8 w2 = width/2;
    Uint8 tileSize = 16;
    Uint8 ts2 = tileSize*2;
    for(int i = 0; i < width*(level[1]/2); i++){
        if ((level[i+2]>>4) <2){
            game.display.drawBitmap(((i%w2)*ts2)-tileSize+x,(((int)i/w2)*tileSize)+y,rock[(level[i+2]>>4)]);
        }
        if (((uint8_t)(level[i+2]<<4))>>4 <2){
            game.display.drawBitmap(((i%w2)*ts2)+x,(((int)i/w2)*tileSize)+y,rock[((uint8_t)(level[i+2]<<4))>>4]);
        }
    }
}

int main () {
game.begin();
game.display.bgcolor=11;
short x = 50;
short y = 184;
float vy = 0;
char frame = 0;
bool derection = false;
game.display.load565Palette(pallet);
while (game.isRunning()) {

     if (game.buttons.pressed(BTN_A)){
            vy=30;
        }

    if (game.update()) {

        if(vy > 0){
            if (collcheck(x,y-(vy/10))==1){
                y-=vy/9;
                vy-=2;
            }else vy=0;
        }
        else if(y < 184){

            if (collcheck(x,y+1)==1){
                y++;
            }
        }

         if (game.buttons.repeat(BTN_LEFT,0)){
            if (collcheck(x-2,y)==1) x-=2;
            derection = false;
            if(x%2==0){
            frame++;
            frame=frame%6;
            }
        }
        else if (game.buttons.repeat(BTN_RIGHT,0)){
            if (collcheck(x+2,y)==1) x+=2;
            derection = true;
            if(x%2==0){
            frame++;
            frame=frame%6;
            }
        } else frame = 0;


        DrawLevel(-x,-y);
        game.display.setInvisibleColor(14);
        game.display.drawBitmap(55-7,44-13,sprite[frame],0,derection);
    }

}

return 1;
}
