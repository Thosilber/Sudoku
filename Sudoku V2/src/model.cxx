#include "model.hxx"
Model::Model()
        : end_(false),
        valid_(true),
        latest_move_(Position{100,100}),
        stage_(1),
        clicks_count_(0)
{
    //This sets every square in the board to be empty initially
    for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < grid_size; j++) {
            squares_[i][j] = ' ';
            fixedsquares_[i][j] = ' ';
        }
    }
}

void Model::play(int x, int y, char number) {

    //Update the latest invalid move
    set_latest_move(x,y);


    //Check if the move was valid or not:
    check_move(number, latest_move_.x, latest_move_.y);


    //changes the value at the given position in the array to the input number
    squares_[x][y] = number;


    //Check if the game ended:
    check_end();


}
char Model::square_at(int i, int j) const {
    return squares_[i][j];
}

char Model::square_at_start(int i, int j) const {
    return fixedsquares_[i][j];
}

void Model::set_square_empty(int i, int j) {
    squares_[i][j] = ' ';
    valid_=true;
}

void Model::check_end()
{

    for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < grid_size; j++) {
            if(squares_[i][j] == ' '){
                return;
            }
        }
    }

    end_ = true;
}

bool Model::get_end() const
{
    return end_;
}

void Model::check_move(char number, int x, int y)
{

    //Checks row for an invalid move
    for (int i = 0; i < grid_size; i++) {
            if (squares_[x][i]!= ' ' and squares_[x][i] == number){
                valid_= false;
                return;
        }
    }

    //Checks column for an invalid move
    for (int j = 0; j < grid_size; j++) {
            if (squares_[j][y]!= ' ' and squares_[j][y] == number){
                valid_= false;
                return;
        }
    }

    //Checks the respective box for an invalid move

    int row_check = x - x % 3;
    int col_check  = y - y % 3;

    for (int i=0; i < box_size; i ++){
        for (int j = 0; j < box_size; j++){
            if(squares_[i+row_check][j+col_check]!= ' ' and squares_[i+row_check][j+col_check] ==
            number){
                valid_ = false;
                return;
            }
        }
    }

    valid_= true;

}

bool Model::get_move() const{
   return valid_;
}

void Model::set_latest_move(int x, int y)
{
    latest_move_ = {x,y};
}

Model::Position Model::get_latest_move() const
{
    return latest_move_;
}

void Model::increment_count()
{
    clicks_count_ = clicks_count_ + 1;
}

int Model::return_clicks_count() const
{
    return clicks_count_;
}

int Model::check_game_stage() const
{
    return stage_;
}

void Model::set_game_stage_1()
{
    stage_ = 1;
    end_ = false;
    valid_ = true;
    latest_move_ = Position{100,100};
    clicks_count_ = 0;

    //This sets every square in the board to be empty initially
    for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < grid_size; j++) {
            squares_[i][j] = ' ';
            fixedsquares_[i][j] = ' ';
        }
    }
}

void Model::set_game_stage_2()
{
    // setting the game stage to 2 (easy board)
    stage_ = 2;


    // setting the numbers for the easy board
    fixedsquares_[0][4] = '2';
    fixedsquares_[0][5] = '7';
    fixedsquares_[0][7] = '3';
    fixedsquares_[0][8] = '8';
    fixedsquares_[1][2] = '7';
    fixedsquares_[1][4] = '9';
    fixedsquares_[1][5] = '8';
    fixedsquares_[1][7] = '2';
    fixedsquares_[2][0] = '8';
    fixedsquares_[2][3] = '5';
    fixedsquares_[2][5] = '6';
    fixedsquares_[2][8] = '4';
    fixedsquares_[3][3] = '9';
    fixedsquares_[3][4] = '4';
    fixedsquares_[3][5] = '3';
    fixedsquares_[4][0] = '2';
    fixedsquares_[4][1] = '5';
    fixedsquares_[4][3] = '6';
    fixedsquares_[4][4] = '7';
    fixedsquares_[4][5] = '1';
    fixedsquares_[4][7] = '4';
    fixedsquares_[5][1] = '7';
    fixedsquares_[5][2] = '4';
    fixedsquares_[5][6] = '6';
    fixedsquares_[6][2] = '3';
    fixedsquares_[6][4] = '6';
    fixedsquares_[6][8] = '2';
    fixedsquares_[7][1] = '2';
    fixedsquares_[7][4] = '5';
    fixedsquares_[7][5] = '4';
    fixedsquares_[7][6] = '3';
    fixedsquares_[8][1] = '9';
    fixedsquares_[8][2] = '6';
    fixedsquares_[8][4] = '1';
    fixedsquares_[8][5] = '2';
    fixedsquares_[8][8] = '5';

    for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < grid_size; j++) {
            squares_[i][j] = fixedsquares_[i][j];
        }
    }


}

void Model::set_game_stage_3()
{
    // setting the game stage to 3 (hard board)
    stage_ = 3;


    // setting the numbers for the hard board
    fixedsquares_[0][8] = '9';
    fixedsquares_[1][0] = '6';
    fixedsquares_[1][1] = '8';
    fixedsquares_[1][4] = '5';
    fixedsquares_[2][0] = '5';
    fixedsquares_[2][3] = '6';
    fixedsquares_[2][7] = '2';
    fixedsquares_[3][0] = '2';
    fixedsquares_[3][4] = '6';
    fixedsquares_[3][7] = '4';
    fixedsquares_[4][2] = '6';
    fixedsquares_[4][3] = '3';
    fixedsquares_[4][5] = '7';
    fixedsquares_[5][0] = '9';
    fixedsquares_[5][4] = '4';
    fixedsquares_[5][6] = '7';
    fixedsquares_[5][7] = '5';
    fixedsquares_[6][0] = '3';
    fixedsquares_[6][5] = '4';
    fixedsquares_[6][7] = '9';
    fixedsquares_[7][4] = '8';
    fixedsquares_[7][8] = '3';
    fixedsquares_[8][1] = '1';


    for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < grid_size; j++) {
            squares_[i][j] = fixedsquares_[i][j];
        }
    }

}







