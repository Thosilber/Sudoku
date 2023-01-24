#include "controller.hxx"

Controller::Controller()
        : view_(model_),
        number_typed(' '),
        mouse_{0,0}
{ }

void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set, mouse_);
}

View::Dimensions
Controller::initial_window_dimensions() const
{
    return view_.window_dimensions();
}

void
Controller::on_key(ge211::Key key)
{
    if (key == ge211::Key::code('1')) {
        number_typed = '1';
    }
    if (key == ge211::Key::code('2')) {
        number_typed = '2';
    }
    if (key == ge211::Key::code('3')) {
        number_typed = '3';
    }
    if (key == ge211::Key::code('4')) {
        number_typed = '4';
    }
    if (key == ge211::Key::code('5')) {
        number_typed = '5';
    }
    if (key == ge211::Key::code('6')) {
        number_typed = '6';
    }
    if (key == ge211::Key::code('7')) {
        number_typed = '7';
    }
    if (key == ge211::Key::code('8')) {
        number_typed = '8';
    }
    if (key == ge211::Key::code('9')) {
        number_typed = '9';
    }
    if (key == ge211::Key::shift()) {
        number_typed = ' ';
    }
    if (key == ge211::Key::code('q')) {
        quit();
    }
}

void
Controller::on_mouse_down(ge211::Mouse_button m, ge211::Posn<int> position)
{
    //Now if you use board_pos it relates to a specific square
    View::Position board_pos = view_.screen_to_board(position);


    // on the main menu -- selecting the easy or hard game
    if (model_.check_game_stage() == 1) {

        if (board_pos == view_.screen_to_board(easy_game)) {
            model_.set_game_stage_2();
        } else if (board_pos == view_.screen_to_board(hard_game)) {
            model_.set_game_stage_3();
        }
    }

        // when game is finished: if user clicks restart button, go back to menu
    else if (model_.get_end()) {
        if (board_pos == view_.screen_to_board(restart_game)) {
            model_.set_game_stage_1(); // going back to menu
        }
        return;
    }

        // inside each board - making so that you can only select the squares
        // that are valid - the ones that weren't in the board before
    else if(model_.check_game_stage() == 2 or model_.check_game_stage() == 3) {
        if (model_.square_at_start(board_pos.x, board_pos.y) == ' ') {
            if (model_.get_move()) {
                model_.play(board_pos.x, board_pos.y, number_typed);
            }
            if (number_typed == ' ' and model_.get_latest_move() == board_pos) {
                model_.set_square_empty(board_pos.x, board_pos.y);
            }
        }

        // count the number of clicks
        // if mouse is pressed, increment 1 to int click_count
        model_.increment_count();
    }
}

void
Controller::on_mouse_move(ge211::Posn<int> pos)
{

    mouse_ = pos;
}