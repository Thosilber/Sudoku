#include "model.hxx"
#include <catch.hxx>

TEST_CASE("play a move")
{
    Model m;

    //Checks initially in empty board every square has blank space
    for (int i = 0; i < m.grid_size; i++) {
        for (int j = 0; j < m.grid_size; j++) {
            CHECK(m.square_at(i,j) == ' ');
        }
    }

    //Check you can play a move at a square
    m.play(1,1,'8');
    CHECK(m.square_at(1,1) == '8');

    //Check that you can play a move at a square that's already been played in
    m.play(1,1,'7');
    CHECK(m.square_at(1,1) == '7');

    //Check that you can erase a square that you played in before
    m.set_square_empty(1,1);
    CHECK(m.square_at(1,1) == ' ');


}

TEST_CASE("Check whether move is valid or not")
///If a move is valid, model.get_move returns true, otherwise it returns false
{
    Model m;

    //Check that initially placing a 1 at any square is a valid move
    for (int i = 0; i < m.grid_size; i++) {
        for (int j = 0; j < m.grid_size; j++) {
            m.check_move(i,j,1);
            CHECK(m.get_move() == true);
        }
    }

    //play a move at square (0,0)
    m.play(0,0,'1');

    //check that playing the same move at (0,1) is an invalid move since a 1
    // is already present in row 0
    m.check_move('1',0,1);
    CHECK(m.get_move() == false);

    //check that playing the same move at (1,0) is an invalid mode since a 1
    // is already present in column 0
    m.check_move('1',1,0);
    CHECK(m.get_move() == false);

    //check that playing the same move at (2,2) is an invalid mode since a 1
    // is already present in its bounding box (the top left 3x3 box of the
    // board)
    m.check_move('1',2,2);
    CHECK(m.get_move() == false);

    //check that playing the same move at (3,3) would be a valid move since
    // no 1 is present in its row, column, or bounding box
    m.check_move('1',3,3);
    CHECK(m.get_move() == true);
}

TEST_CASE("Test_full_game")
{
    ///Going to fill a completed, valid board from scratch to see that the
    /// game is playing every move and then testing end of game case

    Model m;
    m.play(0,0,'1');

    //Initially end should be false since board only has one entry
    m.check_end();
    CHECK(m.get_end() == false);



    char board[9][9] = { {'7','3','5','6','1','4','8','9','2'},
                         {'8','4','2','9','7','3','5','6','2'},
                         {'9','6','1','2','8','5','3','7','4'},
                         {'2','8','6','3','4','9','1','5','7'},
                         {'4','1','3','8','5','7','9','2','6'},
                         {'5','7','9','1','2','6','4','3','8'},
                         {'1','5','7','4','9','2','6','8','3'},
                         {'6','9','4','7','3','8','2','1','5'},
                         {'3','2','8','5','6','1','7','4','9'} };



    for (int i = 0; i < m.grid_size; i++) {
        for (int j = 0; j < m.grid_size; j++) {
            m.play(i,j,board[i][j]);
        }
    }

    //Now the entire board should be completed and we should have reached end
    // of game. This also proves to us that m.play is correctly calling
    // check_end and changing the value of our end_ bool since model will now
    // know it reached the end without directly calling check_end in this
    // test
    CHECK(m.get_end() == true);

}

TEST_CASE("Check correct latest move")
{
    Model m;

    //Checks the initial position initialized in model constructor
    CHECK(m.get_latest_move() == Model::Position{100,100});

    //Play move at (0,0)
    m.play(0,0,'1');
    //Check the latest move is now position (0,0)
    CHECK(m.get_latest_move() == Model::Position{0,0});

    //manually set latest move
    m.set_latest_move(3,3);
    CHECK(m.get_latest_move() == Model::Position{3,3});

}

TEST_CASE("Checks stage and board setting works fine")
{
    Model m;

    // game initializes at game stage 1
    CHECK(m.check_game_stage() == 1);


    // set game stage 2 -> easy board
    m.set_game_stage_2();
    CHECK(m.check_game_stage() == 2);
    // checking squares that belong to easy board (ones that appear when
    // initializing it)
    CHECK(m.square_at(0,4) == '2');
    CHECK(m.square_at(6,4) == '6');
    CHECK(m.square_at(7,1) == '2');
    CHECK(m.square_at(8,4) == '1');
    CHECK(m.square_at(6,3) == ' '); // supposed to be blank -> user can input
    // number here


    // set game stage 3 -> hard board
    m.set_game_stage_1();
    m.set_game_stage_3();
    CHECK(m.check_game_stage() == 3);
    // checking squares that belong to hard board (ones that appear when
    // initializing it)
    CHECK(m.square_at(0,8) == '9');
    CHECK(m.square_at(4,2) == '6');
    CHECK(m.square_at(7,4) == '8');
    CHECK(m.square_at(8,1) == '1');
    CHECK(m.square_at(8,2) == ' ');


    // set game stage 3 -> to return to menu page and restart game
    m.set_game_stage_1();
    CHECK(m.check_game_stage() == 1);
    CHECK_FALSE(m.get_end());
    CHECK(m.return_clicks_count() == 0);
    CHECK(m.get_latest_move() == Model::Position{100, 100});
    CHECK(m.get_move());
    // check if all elements of board are ' ' when restarted
    for (int i = 0; i < m.grid_size; i++) {
        for (int j = 0; j < m.grid_size; j++) {
            CHECK(m.square_at(i,j) == ' ');
        }
    }

}

TEST_CASE("Checks set_square_empty works just fine")
{
    Model m;

    m.play(0,0,'1');

    CHECK(m.square_at(0,0) == '1');
    m.set_square_empty(0,0);
    CHECK(m.square_at(0,0) == ' ');
    CHECK(m.get_move());

}

TEST_CASE("Checks if clicks count is working")
{
    Model m;

    CHECK(m.return_clicks_count() == 0);
    m.increment_count();
    CHECK(m.return_clicks_count() == 1);
    m.increment_count();
    CHECK(m.return_clicks_count() == 2);

    // when game is restarted, count goes to 0
    m.set_game_stage_1();
    CHECK(m.return_clicks_count() == 0);
}