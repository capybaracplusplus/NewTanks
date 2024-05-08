#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <map>
#include <windows.h>


struct Position {
    int x;
    int y;
};

enum rotation {
    up,
    down,
    right,
    left,
};

struct Player {
    Position position;
    rotation rotation;
};


enum tile {
    ground = 0, // ничего
    wall, // разрушаемая стена
    unbreakable_wall, // нерушимая стена
    bush, // куст
    river, // река
    base, // база игрока
    left_caterpillar,
    right_caterpillar,
    double_up,
    tower,
    lower_stroke,
    double_equally,
    hight_stroke,
};

std::map<tile, std::string> map_tile = {
        {tile::ground, "::"},
        {tile::wall, "▓▓"},
        {tile::unbreakable_wall, "██"},
        {tile::bush, "░░"},
        {tile::river, "~~"},
        {tile::base, "<>"},

        {tile::left_caterpillar, "[ "},
        {tile::right_caterpillar, " ]"},
        {tile::double_up, "||"},
        {tile::tower, "()"},
        {tile::lower_stroke, "__"},
        {tile::double_equally, "=="},
        {tile::hight_stroke, "--"},
};

tile tank_up[3][3] = {
    {tile::left_caterpillar, tile::double_up, tile::right_caterpillar},
    {tile::left_caterpillar, tile::tower, tile::right_caterpillar},
    {tile::left_caterpillar, tile::lower_stroke, tile::right_caterpillar}
};

void rendering(std::vector<std::vector<tile>> render) {
    for (int i = 0; i < 60; ++i) {
        for (int j = 0; j < 60; j++) {
            std::cout << map_tile[render[i][j]];
        }
            std::cout << std::endl;
    }
}

void tank_render(Player Player, std::vector<std::vector<tile>> & render) {
    for (int y = Player.position.y; y < Player.position.y + 3; y++) {
        for (int x = Player.position.x; x < Player.position.x + 3; x++) {
            render[y][x] = tank_up[y - Player.position.y][x - Player.position.x];
        }
    }
}


int main() {


    Player player_1 = {};
    player_1.position = {};
    player_1.position.x = 10;
    player_1.position.y = 5;


    std::vector<std::vector<tile>> render(60, std::vector<tile> (60));

    for (int i = 0; i < 60; i++) {
         render.push_back({});
         for (int j = 0; j < 60; j++) {
             render[i].push_back(tile::ground);
         }
     }
    bool game{ true };
    while (game) {
        Sleep(500);
        system("cls");
        tank_render(player_1, render);
        rendering(render);
    }






     /*

     = "[ ";    left_caterpillar
     = " ]";    right_caterpillar
     = "||";    double_up
     = "()";    tower
     = "__";    lower_stroke
     = "==";    double_equally
     = "--";    hight_stroke


      [ || ]
      [ () ]
      [ __ ]

      [ -- ]
      [ () ]
      [ || ]

      ------
      ||()==
      ------

      ------
      ==()||
      ------

    */

    return 0;
}

