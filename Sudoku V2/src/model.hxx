#pragma once

#include <ge211.hxx>

class Model
{
public:
    Model();

    /// Positions will use `int` coordinates.
    using Position = ge211::Posn<int>;

    const int grid_size = 9;
    const int box_size = 3;

    // returns the number at a specific square
    char square_at(int i, int j) const;
    char square_at_start(int i, int j) const;
    void set_square_empty(int i, int j);


    //Allows user to play at a square
    void play(int x, int y, char number);

    void check_end();
    bool get_end() const;

    void check_move(char value, int x, int y);
    bool get_move() const;

    //Returns the location of the latest move
    void set_latest_move(int x, int y);
    Position get_latest_move() const;

    //Returns the state of the game
    int check_game_stage() const;
    void set_game_stage_1();
    void set_game_stage_2();
    void set_game_stage_3();

    // counts the clicks
    void increment_count();
    int return_clicks_count() const;


private:
    //end_ stores whether the board has been successfully completed or not
    bool end_;

    //squares_ is an array which will hold the actual values on the board so
    // far
    char squares_[9][9];

    // fixedsquares_ is an array which will hold the initial values on the board
    char fixedsquares_[9][9];

    //Stores whether most recent move is valid or not
    bool valid_;

    //Stores latest move
    Position latest_move_;

    //Stores the stage of the game
    int stage_;

    // stores the amount of clicks a player had
    int clicks_count_;

};
