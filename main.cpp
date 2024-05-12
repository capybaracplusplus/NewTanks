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
    left_caterpillar, // левая гусеница
    right_caterpillar, // правая гусеница
    double_up, // часть такнка
    tower, // башня танка
    lower_stroke, // часть такнка
    double_equally, // часть такнка
    hight_stroke, // часть такнка
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

// tank in position - tower looking up
tile tank_up[3][3] = {
    {tile::left_caterpillar, tile::double_up, tile::right_caterpillar},
    {tile::left_caterpillar, tile::tower, tile::right_caterpillar},
    {tile::left_caterpillar, tile::lower_stroke, tile::right_caterpillar}
};

tile tank_down[3][3] = {
        {tile::left_caterpillar, tile::hight_stroke, tile::right_caterpillar},
        {tile::left_caterpillar, tile::tower, tile::right_caterpillar},
        {tile::left_caterpillar, tile::double_up, tile::right_caterpillar}
};

tile tank_left[3][3] = {
        {tile::hight_stroke, tile::hight_stroke, tile::hight_stroke},
        {tile::double_equally, tile::tower, tile::double_up},
        {tile::hight_stroke, tile::hight_stroke, tile::hight_stroke}
};

tile tank_right[3][3] = {
        {tile::hight_stroke, tile::hight_stroke, tile::hight_stroke},
        {tile::double_up, tile::tower, tile::double_equally},
        {tile::hight_stroke, tile::hight_stroke, tile::hight_stroke}
};

tile true_ground[3][3] = {
        {tile::ground, tile::ground, tile::ground},
        {tile::ground, tile::ground, tile::ground},
        {tile::ground, tile::ground, tile::ground}
};


void gotoxy(int xpos, int ypos) {
    COORD scrn;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    scrn.X = xpos; scrn.Y = ypos;
    SetConsoleCursorPosition(hOuput, scrn);
};


void rendering(std::vector<std::vector<tile>> render) {
    for (int i = 0; i < 63; ++i) {
        for (int j = 0; j < 63; j++) {
            std::cout << map_tile[render[i][j]];
        }
            std::cout << std::endl;
    }
};

// displaying the tank on the screen in a certain position (up)
void tank_render_up(Player Player, std::vector<std::vector<tile>> & render) {
    for (int y = Player.position.y; y < Player.position.y + 3; y++) {
        for (int x = Player.position.x; x < Player.position.x + 3; x++) {
            render[y][x] = tank_up[y - Player.position.y][x - Player.position.x];
        }
    }
};

void tank_render_down(Player Player, std::vector<std::vector<tile>> & render) {
    for (int y = Player.position.y; y < Player.position.y + 3; y++) {
        for (int x = Player.position.x; x < Player.position.x + 3; x++) {
            render[y][x] = tank_down[y - Player.position.y][x - Player.position.x];
        }
    }
};

void tank_render_left(Player Player, std::vector<std::vector<tile>> & render) {
    for (int y = Player.position.y; y < Player.position.y + 3; y++) {
        for (int x = Player.position.x; x < Player.position.x + 3; x++) {
            render[y][x] = tank_left[y - Player.position.y][x - Player.position.x];
        }
    }
};

void tank_render_right(Player Player, std::vector<std::vector<tile>> & render) {
    for (int y = Player.position.y; y < Player.position.y + 3; y++) {
        for (int x = Player.position.x; x < Player.position.x + 3; x++) {
            render[y][x] = tank_right[y - Player.position.y][x - Player.position.x];
        }
    }
};

void delete_tank(Player Player, std::vector<std::vector<tile>> & render) {
    for (int y = Player.position.y; y < Player.position.y + 3; y++) {
        for (int x = Player.position.x; x < Player.position.x + 3; x++) {
            render[y][x] = true_ground[y - Player.position.y][x - Player.position.x];
        }
    }
};

/*
 void move_up ();
 void move_down ();
 void move_left ();
 void move_right ();
 */

/*
 void move_up (Player Player, std::vector<std::vector<tile>> & render) {
     if (Player.position.y > 2) {
         // поле 39 на 39 клетки 3 на 3 тогда итог 13 на 13
        // проверить на то нет ли сверху препятствий
        if (render[Player.position.x][Player.position.y + 1] == tile::ground ||
            render[Player.position.x][Player.position.y + 1] == tile::bush) {
            // добавить стирание страго места танка
            Player.position.y += 3;
        }
     }
 }
 */


int main() {

    Player player_1 = {};
    player_1.position = {};
    player_1.position.x = 10;
    player_1.position.y = 5;

    // размер поля 21 на 21 клеток 3 на 3
    std::vector<std::vector<tile>> render(63, std::vector<tile> (63));

    std::vector<std::vector<tile>> map_test(63, std::vector<tile> (63));

    std::vector<std::vector<tile>> map_main(63, std::vector<tile> (63));

    // заполение map_main из map_test либо любой другой
    // map_main для опред грунт или курс

    int menu;
    std::cout << "1. play" << "\n" << "2. rules" << "\n" << "3. exit" << "\n" << "\n" << "select: ";
    std::cin >> menu;
    std::cout << "\n";

    switch (menu) {
        case (1): {
            gotoxy(0,0);
            for (int i = 0; i < 63; i++) {
                render.push_back({});
                for (int j = 0; j < 63; j++) {
                    render[i].push_back(tile::ground);
                }
            }
            bool game{true};
            while (game) {
                Sleep(500);
                system("cls");
                gotoxy(0,0);
                tank_render_up(player_1, render);
                rendering(render);
                // delete_tank(player_1, render);
            }
            break;
        }
        case (2): {
            system("color 5" );
            std::cout << " In a two-player game, the first player holds the center and left flank, while the second \n"
                         " player holds the right flank. When playing alone, you will either have to actively rush \n"
                         " around the map or take a defensive position near the headquarters.";
            break;
        }
        case (3):
            break;
        default: {
            system("color 4" );
            std::cout << "error, please select an option from the list";
            break;
        }
    }

    return 0;
}

