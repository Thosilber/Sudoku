#pragma once

#include "model.hxx"

//Initializes the size of each individual square/cell
static int const size_of_cell = 60;
static ge211::geometry::Posn<int> easy_game{120,300};
static ge211::geometry::Posn<int> hard_game{370,300};
static ge211::geometry::Posn<int> restart_game{120, 300};

class View
{
public:
    /// Dimensions will use `int` coordinates.
    using Dimensions = ge211::Dims<int>;

    /// Positions will use `int` coordinates.
    using Position = ge211::Posn<int>;

    ///Defines the View class
    explicit View(Model const& model);

    ///Returns initial board dimensions
    Dimensions window_dimensions() const;

    ///Defines draw function which will add sprites to screen
    void draw(ge211::Sprite_set& set, Position pos);

    ///Allows you to convert pixel locations (mouse position) to what grid on
    /// the board it is so it's easier to understand
    Position screen_to_board(Position screen_pos) const;


private:
    Model const& model_;

    //stores the number of times the game has been succesfully played
    int number_of_games;

    ///Defines sprites for draw
    ge211::Rectangle_sprite const grid_sprite;
    ge211::Text_sprite number_sprite_[9][9];
    ge211::Font sans30_{"sans.ttf", 30};
    ge211::Text_sprite game_over;
    ge211::Text_sprite easy_message;
    ge211::Text_sprite hard_message;
    ge211::Text_sprite move_message;
    ge211::Text_sprite restart_message;
    ge211::Text_sprite points_message;
    ge211::Text_sprite score_message;
    ge211::Text_sprite score_rating_message;
    ge211::Rectangle_sprite big_block;
    ge211::Rectangle_sprite blue_sprite;
    ge211::Rectangle_sprite red_sprite;
    ge211::Rectangle_sprite invalid_block;
};