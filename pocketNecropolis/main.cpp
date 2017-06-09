#include "Pokitto.h"
#include <vector>
#include "sprites.h"
Pokitto::Core game;


uint8_t dungeon[20][20]={
    {1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1},
    {1,2,2,2,2, 2,2,2,2,2, 1,2,2,2,2, 2,2,2,2,1},
    {1,0,0,0,0, 0,0,0,0,0, 1,0,0,0,0, 0,0,0,0,1},
    {1,0,0,0,0, 0,0,0,0,0, 1,0,0,0,0, 0,0,0,0,1},
    {1,0,0,0,0, 0,0,0,0,0, 1,1,1,0,1, 1,1,1,1,1},
    {1,0,0,0,0, 0,0,0,0,0, 1,2,2,0,2, 2,2,2,2,1},
    {1,0,0,0,0, 0,0,0,0,0, 1,0,0,0,0, 0,0,0,0,1},
    {1,1,1,1,1, 0,1,1,1,1, 1,0,0,0,0, 0,0,0,0,1},
    {1,2,2,2,2, 0,2,2,2,2, 1,0,0,0,0, 0,0,0,0,1},
    {1,0,0,0,0, 0,0,0,0,0, 1,0,0,0,0, 0,0,0,0,1},
    {1,0,0,0,0, 0,0,0,0,0, 2,0,0,0,0, 0,0,0,0,1},
    {1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1},
    {1,0,0,0,0, 0,0,0,0,0, 1,0,0,0,0, 0,0,0,0,1},
    {1,0,0,0,0, 0,0,0,0,0, 1,0,0,0,0, 0,0,0,0,1},
    {1,0,0,0,0, 0,0,0,0,0, 1,0,0,0,0, 0,0,0,0,1},
    {1,0,0,0,0, 0,0,0,0,0, 1,0,0,0,0, 0,0,0,0,1},
    {1,0,0,0,0, 0,0,0,0,0, 1,0,0,0,0, 0,0,0,0,1},
    {1,0,0,0,0, 0,0,0,0,0, 1,0,0,0,0, 0,0,0,0,1},
    {1,0,0,0,0, 0,0,0,0,0, 1,0,0,0,0, 0,0,0,0,1},
    {1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1},
};
struct entity{
    uint8_t x;
    uint8_t y;
    int8_t hp;
    uint8_t id;
};

#define ID_SKELETON_MAGE     9
#define ID_SKELETON_ARCHER   10
#define ID_SKELETON_WARIOR   11
#define ID_BLOOD_SKELETON    12
#define ID_BLOOD             13
#define ID_RAT               14
#define ID_SCROLL            15
#define ID_CHEST             16
#define ID_CHEST_OPEN        17
#define ID_MIMIC             18
#define ID_COIN              19
#define ID_COINS             20
#define ID_BAG               21

int entities_size = 2;
std::vector<entity> entities(entities_size);


void entitiesLogic(int playerX, int playerY){
    for(int i=0; i<entities.size(); ++i){

        switch(entities[i].id){
        case ID_CHEST:


            break;
        case ID_CHEST_OPEN:


            break;
        case ID_MIMIC:
            if(entities[i].x > playerX) entities[i].x-=1;
            if(entities[i].x < playerX) entities[i].x+=1;
            if(entities[i].y > playerY) entities[i].y-=1;
            if(entities[i].y < playerY) entities[i].y+=1;
            break;
        default:
            printf("unknown entety %i\n", entities[i].id);
            break;
        }
    }
}
void mapgen(uint8_t depth, uint8_t x,uint8_t y,uint8_t w,uint8_t h){
    //needs better rng limits
    uint8_t rx = random(y,h);
    for(uint8_t i = x; i < w; i++){
        dungeon[i][rx] = 1;
    }
    uint8_t ry = random(x,w);
    for(uint8_t i = y; i < h; i++){
        dungeon[ry][i] = 1;
    }

    //doorways
    dungeon[random(x,ry)][rx] = 0;
    dungeon[ry][random(y,rx)] = 0;
    dungeon[random(ry,w)][rx] = 0;
    dungeon[ry][random(rx,h)] = 0;

    if (depth < 3) {
        mapgen(depth+1,x,y,ry,rx);
        mapgen(depth+1,ry,rx,w,h);
        mapgen(depth+1,ry,y,w,rx);
        mapgen(depth+1,x,rx,ry,h);
    }
}
void drawHP(int hp){
    //gui
        game.display.drawBitmap(212,0,UI1);
        game.display.drawFastVLine(219,3,158);
        game.display.drawFastVLine(211,3,158);
        game.display.drawBitmap(212,162,UI2);
        int UI_hp = hp * 0.78;

        if(hp >= 0){
            for(int i = 0; i < UI_hp; i++){
                game.display.drawBitmap(213,159-(i*2),UI4);
            }
            game.display.drawBitmap(213,160-((UI_hp+1)*2),UI3);
            game.display.drawBitmap(213,161,UI5);
        }
}
int main () {

game.begin();
//mapgen(0,0,0,20,20);
game.display.loadRGBPalette(paletteCGA);
//game.display.setFont(fontAdventurer);
//game.display.persistence = true;
game.display.setInvisibleColor(0);
int playerX = 2;
int playerY = 2;
int playerHP = 100;

entities[0].id = ID_CHEST;
entities[0].x = 5;
entities[0].y = 3;
entities[1].id = ID_MIMIC;
entities[1].x = 15;
entities[1].y = 15;


while (game.isRunning()) {

    if (game.update()) {
        if (game.buttons.repeat(BTN_UP,4)){
            if (!dungeon[playerY-1][playerX]){
                playerY --;
                entitiesLogic( playerX, playerY);
            }
        }
        if (game.buttons.repeat(BTN_DOWN,4)){
            if (!dungeon[playerY+1][playerX]){
                playerY ++;
                entitiesLogic( playerX, playerY);
            }
        }
        if (game.buttons.repeat(BTN_LEFT,4)){
            if (!dungeon[playerY][playerX-1]){
                playerX --;
                entitiesLogic( playerX, playerY);
            }
        }
        if (game.buttons.repeat(BTN_RIGHT,4)){
            if (!dungeon[playerY][playerX+1]){
                playerX ++;
                entitiesLogic( playerX, playerY);
            }
        }
        for(int x =playerX-7; x<playerX+8; x++){ //7
            for(int y =playerY-6; y<playerY+6; y++){
                if(x >= 0 && y >= 0 && x <20 && y < 20){
                    game.display.drawBitmap(14*(x-playerX+7),14*(y-playerY+6),background[dungeon[y][x]]);
                }
            }
        }

        game.display.setCursor(0,168);
        game.display.color = 1;
        game.display.print("OMG! this font just fits on the screen");
        game.display.drawBitmap(14*(7),14*(6),sprites[3]);


        drawHP(playerHP);

        for(int i=0; i<entities.size(); ++i){
            game.display.color = 0; //remove before release
            game.display.fillRect(14*(entities[i].x-playerX+7),14*(entities[i].y-playerY+6),14,14);//remove and fix before release
            game.display.drawBitmap(14*(entities[i].x-playerX+7),14*(entities[i].y-playerY+6),sprites[entities[i].id]);
        }
    }

}

return 1;
}
