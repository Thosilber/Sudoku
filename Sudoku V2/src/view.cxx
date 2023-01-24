#include "view.hxx"



//Initializes colors to be used by sprites
static ge211::Color const brown_color {222,184,135};
static ge211::Color const green_color {0,255,0};
static ge211::Color const blue_color {0,0,255};
static ge211::Color const red_color {255,0,0};

View::View(Model const& model)
        : model_(model),
          number_of_games(1),
          grid_sprite({size_of_cell -5, size_of_cell -5},
                      brown_color),
          game_over(),
          easy_message(),
          hard_message(),
          move_message(),
          restart_message(),
          big_block(window_dimensions(), green_color),
          blue_sprite({size_of_cell-5,size_of_cell-5}, blue_color),
          red_sprite({size_of_cell-5,size_of_cell-5}, red_color),
          invalid_block({window_dimensions().width,
                         window_dimensions().height-50}, brown_color)
{ }

View::Dimensions
View::window_dimensions() const
{
    return {size_of_cell * model_.grid_size, size_of_cell * model_
            .grid_size + 60};
}

void
View::draw(ge211::Sprite_set& set, Position pos)
{


    ///Creates screen when the game is in stage 1, the selection screen

    //places two boxes for selection, the easy game or hard game
    if(model_.check_game_stage() == 1){
        set.add_sprite(blue_sprite,easy_game, 1*number_of_games);
        set.add_sprite(blue_sprite,hard_game,1*number_of_games);

        //Places titles above the two boxes
        ge211::Text_sprite::Builder name_builder(sans30_);
        name_builder << "Easy Game";
        easy_message.reconfigure(name_builder);
        set.add_sprite(easy_message,{easy_game.x - 40,easy_game.y-50},1*number_of_games);
        ge211::Text_sprite::Builder name_builder2(sans30_);
        name_builder2 << "Hard Game";
        hard_message.reconfigure(name_builder2);
        set.add_sprite(hard_message,{hard_game.x - 40,hard_game.y-50},1*number_of_games);

    }

        ///Creates screen when the game enters stage 2, the easy board
    else if (model_.check_game_stage() == 2) {

        ///The following section sets up the grid. It is a bit complicated
        /// because the spacing between rows and columns needs to increase when
        /// outside of a 9x9 square. That is why spacing_i and spacing_j are used
        int spacing_j = 0;
        int spacing_i = 0;

        for (int i = 0; i < model_.grid_size; i++) {
            //need to re-initialize spacing to 0 every time
            spacing_j = 0;
            if (i == 3 or i == 6) {
                spacing_i += 5;
            }
            for (int j = 0; j < model_.grid_size; j++) {
                //This block of code fills the number_sprite with the values that
                // we want to print at each square
                ge211::Text_sprite::Builder letter_builder(sans30_);
                letter_builder << model_.square_at(i, j);
                number_sprite_[i][j].reconfigure(letter_builder);

                if (model_.get_move()) {

                    //The following set of statements print the grid and value at
                    // each grid on the board with correct spacing
                    if (j < 2) {
                        set.add_sprite(grid_sprite,
                                       {i * size_of_cell + spacing_i, j *
                                                                      size_of_cell +
                                                                      spacing_j}, 1*number_of_games);

                        set.add_sprite(number_sprite_[i][j], {i * size_of_cell
                                                              + spacing_i,
                                                              j * size_of_cell +
                                                              spacing_j},
                                       3*number_of_games);



                    } else if (j == 3) {
                        spacing_j += 5;
                        set.add_sprite(grid_sprite,
                                       {i * size_of_cell + spacing_i, j *
                                                                      size_of_cell +
                                                                      spacing_j},1*number_of_games);

                        set.add_sprite(number_sprite_[i][j], {i * size_of_cell
                                                              + spacing_i,
                                                              j * size_of_cell +
                                                              spacing_j},
                                       3*number_of_games);

                    } else if (j > 3 and j < 6) {
                        set.add_sprite(grid_sprite,
                                       {i * size_of_cell + spacing_i, j *
                                                                      size_of_cell +
                                                                      spacing_j},1*number_of_games);

                        set.add_sprite(number_sprite_[i][j], {i * size_of_cell
                                                              + spacing_i,
                                                              j * size_of_cell +
                                                              spacing_j},
                                       3*number_of_games);

                    } else if (j == 6) {
                        spacing_j += 5;
                        set.add_sprite(grid_sprite,
                                       {i * size_of_cell + spacing_i, j *
                                                                      size_of_cell +
                                                                      spacing_j},1*number_of_games);

                        set.add_sprite(number_sprite_[i][j], {i * size_of_cell
                                                              + spacing_i,
                                                              j * size_of_cell +
                                                              spacing_j},
                                       3*number_of_games);

                    } else {
                        set.add_sprite(grid_sprite,
                                       {i * size_of_cell + spacing_i, j *
                                                                      size_of_cell +
                                                                      spacing_j},1*number_of_games);

                        set.add_sprite(number_sprite_[i][j], {i * size_of_cell
                                                              + spacing_i,
                                                              j * size_of_cell +
                                                              spacing_j},
                                       3*number_of_games);
                    }

                    if (model_.get_move() and i == model_.get_latest_move().x
                        and model_.get_latest_move().y == j) {
                        ///Says good job if most recent move was valid
                        ge211::Text_sprite::Builder name_builder(sans30_);
                        name_builder << "Good Job!";
                        move_message.reconfigure(name_builder);
                        // Prints Good job text:
                        set.add_sprite(move_message,
                                       {size_of_cell * 4, window_dimensions()
                                                                  .width - 2},
                                       3*number_of_games);
                    }

                    ///Places sprite over the box the user is at (only for
                    /// boxes that user can edit)
                    if (model_.square_at_start(screen_to_board(pos).x,
                                               screen_to_board(pos).y) == ' '){
                        if (screen_to_board(pos).x == i and
                            screen_to_board(pos).y == j) {
                            set.add_sprite(blue_sprite,
                                           {i * size_of_cell + spacing_i,
                                            j * size_of_cell + spacing_j},
                                           2*number_of_games);
                        }
                    }
                }

                if (!model_.get_move() and i == model_.get_latest_move().x
                    and model_.get_latest_move().y == j) {



                    ///Places try again message on bottom
                    ge211::Text_sprite::Builder name_builder(sans30_);
                    name_builder << "Try Again! Delete move to continue";
                    move_message.reconfigure(name_builder);
                    // Prints Good job text:
                    set.add_sprite(move_message,
                                   {2,
                                    window_dimensions().width
                                    - 2}, 3*number_of_games);

                    ///Covers the rest of the grid to stop gameplay until move is
                    /// corrected
                    set.add_sprite(invalid_block, {0, 0}, 3*number_of_games);
                    ///Places red sprite if it was an invalid move and places the
                    /// value on top of everything else so user can see the value
                    set.add_sprite(red_sprite,
                                   {i * size_of_cell + spacing_i, j *
                                                                  size_of_cell +
                                                                  spacing_j},
                                   4*number_of_games);
                    set.add_sprite(number_sprite_[i][j], {i * size_of_cell
                                                          + spacing_i,
                                                          j * size_of_cell +
                                                          spacing_j}, 5*number_of_games);

                }
            }
        }

        ///Deals with end of game:
        if (model_.get_end()){

            ge211::Text_sprite::Builder name_builder(sans30_);
            name_builder << "You Won!";
            game_over.reconfigure(name_builder);
            // Prints Winning text:
            set.add_sprite(game_over, {size_of_cell*3,
                                       30},5*number_of_games);
            set.add_sprite(big_block, {0, 0},4*number_of_games);

            // restart button
            set.add_sprite(blue_sprite,restart_game,5*number_of_games);
            // restart text
            ge211::Text_sprite::Builder name_builder2(sans30_);
            name_builder2 << "Start Over?";
            restart_message.reconfigure(name_builder2);
            set.add_sprite(restart_message,{restart_game.x - 40,
                                            restart_game.y-50}, 5*number_of_games);

            // prints the score - number of clicks
            ge211::Text_sprite::Builder name_builder3(sans30_);
            name_builder3 << model_.return_clicks_count();
            points_message.reconfigure(name_builder3);
            set.add_sprite(points_message, {size_of_cell*2,
                                            size_of_cell*2},5*number_of_games);
            // prints text placed on top of the score
            ge211::Text_sprite::Builder name_builder4(sans30_);
            name_builder4 << "Score (number of clicks):";
            score_message.reconfigure(name_builder4);
            set.add_sprite(score_message, {size_of_cell*2 - 40,
                                            size_of_cell*2-50},
                           5*number_of_games);

            // prints the rating of the score (excellent, good, okay)
            ge211::Text_sprite::Builder name_builder5(sans30_);
            if(model_.return_clicks_count() <= 50){
                name_builder5 << "EXCELLENT!";
            }
            if(model_.return_clicks_count() > 50 and model_
            .return_clicks_count() <= 65){
                name_builder5 << "GOOD!";
            }
            if(model_.return_clicks_count() > 65){
                name_builder5 << "OKAY...";
            }
            score_rating_message.reconfigure(name_builder5);
            set.add_sprite(score_rating_message, {size_of_cell*2 + 40,
                                           size_of_cell*2+50},
                           5*number_of_games);

            number_of_games += 1;
            // when game ends, increment, meaning that
            // one extra game was played -> used so sprites are on top of one
            // another when starting new game

        }
    }

    else if (model_.check_game_stage() == 3) {


        ///The following section sets up the grid. It is a bit complicated
        /// because the spacing between rows and columns needs to increase when
        /// outside of a 9x9 square. That is why spacing_i and spacing_j are used
        int spacing_j = 0;
        int spacing_i = 0;

        for (int i = 0; i < model_.grid_size; i++) {
            //need to re-initialize spacing to 0 every time
            spacing_j = 0;
            if (i == 3 or i == 6) {
                spacing_i += 5;
            }
            for (int j = 0; j < model_.grid_size; j++) {
                //This block of code fills the number_sprite with the values that
                // we want to print at each square
                ge211::Text_sprite::Builder letter_builder(sans30_);
                letter_builder << model_.square_at(i, j);
                number_sprite_[i][j].reconfigure(letter_builder);

                if (model_.get_move()) {

                    //The following set of statements print the grid and value at
                    // each grid on the board with correct spacing
                    if (j < 2) {
                        set.add_sprite(grid_sprite,
                                       {i * size_of_cell + spacing_i, j *
                                       size_of_cell + spacing_j},
                                       1*number_of_games);

                        set.add_sprite(number_sprite_[i][j], {i * size_of_cell
                                                              + spacing_i,
                                                              j * size_of_cell +
                                                              spacing_j},
                                       3*number_of_games);



                    } else if (j == 3) {
                        spacing_j += 5;
                        set.add_sprite(grid_sprite,
                                       {i * size_of_cell + spacing_i, j *
                                                                      size_of_cell +
                                                                      spacing_j},1*number_of_games);

                        set.add_sprite(number_sprite_[i][j], {i * size_of_cell
                                                              + spacing_i,
                                                              j * size_of_cell +
                                                              spacing_j},
                                       3*number_of_games);

                    } else if (j > 3 and j < 6) {
                        set.add_sprite(grid_sprite,
                                       {i * size_of_cell + spacing_i, j *
                                                                      size_of_cell +
                                                                      spacing_j},1*number_of_games);

                        set.add_sprite(number_sprite_[i][j], {i * size_of_cell
                                                              + spacing_i,
                                                              j * size_of_cell +
                                                              spacing_j},
                                       3*number_of_games);

                    } else if (j == 6) {
                        spacing_j += 5;
                        set.add_sprite(grid_sprite,
                                       {i * size_of_cell + spacing_i, j *
                                                                      size_of_cell +
                                                                      spacing_j},1*number_of_games);

                        set.add_sprite(number_sprite_[i][j], {i * size_of_cell
                                                              + spacing_i,
                                                              j * size_of_cell +
                                                              spacing_j},
                                       3*number_of_games);

                    } else {
                        set.add_sprite(grid_sprite,
                                       {i * size_of_cell + spacing_i, j *
                                                                      size_of_cell +
                                                                      spacing_j},1*number_of_games);

                        set.add_sprite(number_sprite_[i][j], {i * size_of_cell
                                                              + spacing_i,
                                                              j * size_of_cell +
                                                              spacing_j},
                                       3*number_of_games);
                    }

                    if (model_.get_move() and i == model_.get_latest_move().x
                        and model_.get_latest_move().y == j) {
                        ///Says good job if most recent move was valid
                        ge211::Text_sprite::Builder name_builder(sans30_);
                        name_builder << "Good Job!";
                        move_message.reconfigure(name_builder);
                        // Prints Good job text:
                        set.add_sprite(move_message,
                                       {size_of_cell * 4, window_dimensions()
                                                                  .width - 2},
                                       3*number_of_games);
                    }

                    ///Places sprite over the box the user is at (only for
                    /// boxes that user can edit)
                    if (model_.square_at_start(screen_to_board(pos).x,
                                               screen_to_board(pos).y) == ' '){
                        if (screen_to_board(pos).x == i and
                            screen_to_board(pos).y == j) {
                            set.add_sprite(blue_sprite,
                                           {i * size_of_cell + spacing_i,
                                            j * size_of_cell + spacing_j},
                                           2*number_of_games);
                        }
                    }
                }

                if (!model_.get_move() and i == model_.get_latest_move().x
                    and model_.get_latest_move().y == j) {



                    ///Places try again message on bottom
                    ge211::Text_sprite::Builder name_builder(sans30_);
                    name_builder << "Try Again! Delete move to continue";
                    move_message.reconfigure(name_builder);
                    // Prints Good job text:
                    set.add_sprite(move_message,
                                   {2,
                                    window_dimensions().width
                                    - 2}, 3*number_of_games);

                    ///Covers the rest of the grid to stop gameplay until move is
                    /// corrected
                    set.add_sprite(invalid_block, {0, 0}, 3*number_of_games);
                    ///Places red sprite if it was an invalid move and places the
                    /// value on top of everything else so user can see the value
                    set.add_sprite(red_sprite,
                                   {i * size_of_cell + spacing_i, j *
                                                                  size_of_cell +
                                                                  spacing_j},
                                   4*number_of_games);
                    set.add_sprite(number_sprite_[i][j], {i * size_of_cell
                                                          + spacing_i,
                                                          j * size_of_cell +
                                                          spacing_j}, 5*number_of_games);

                }
            }
        }

        ///Deals with end of game:
        if (model_.get_end()){

            ge211::Text_sprite::Builder name_builder(sans30_);
            name_builder << "You Won!";
            game_over.reconfigure(name_builder);
            // Prints Winning text:
            set.add_sprite(game_over, {size_of_cell*3,
                                       30},5*number_of_games);
            set.add_sprite(big_block, {0, 0},4*number_of_games);

            // restart button
            set.add_sprite(blue_sprite,restart_game,5*number_of_games);
            // restart text
            ge211::Text_sprite::Builder name_builder2(sans30_);
            name_builder2 << "Start Over?";
            restart_message.reconfigure(name_builder2);
            set.add_sprite(restart_message,{restart_game.x - 40,
                                            restart_game.y-50}, 5*number_of_games);

            // prints the score - number of clicks
            ge211::Text_sprite::Builder name_builder3(sans30_);
            name_builder3 << model_.return_clicks_count();
            points_message.reconfigure(name_builder3);
            set.add_sprite(points_message, {size_of_cell*2,
                                            size_of_cell*2},5*number_of_games);
            // prints text placed on top of the score
            ge211::Text_sprite::Builder name_builder4(sans30_);
            name_builder4 << "Score (number of clicks):";
            score_message.reconfigure(name_builder4);
            set.add_sprite(score_message, {size_of_cell*2 - 40,
                                           size_of_cell*2-50},
                           5*number_of_games);

            // prints the rating of the score (excellent, good, okay)
            ge211::Text_sprite::Builder name_builder5(sans30_);
            if(model_.return_clicks_count() <= 60){
                name_builder5 << "EXCELLENT!";
            }
            if(model_.return_clicks_count() > 60 and model_.return_clicks_count() <= 75){
                name_builder5 << "GOOD!";
            }
            if(model_.return_clicks_count() > 75){
                name_builder5 << "OKAY...";
            }
            score_rating_message.reconfigure(name_builder5);
            set.add_sprite(score_rating_message, {size_of_cell*2 + 40,
                                                  size_of_cell*2+50},
                           5*number_of_games);

            number_of_games += 1;
            // when game ends, increment, meaning that
            // one extra game was played -> used so sprites are on top of one
            // another when starting new game
        }
    }


}

// Transforms a screen position into a board position
View::Position
View::screen_to_board(View::Position pos) const
{
    return {pos.x /size_of_cell , pos.y /size_of_cell};
}