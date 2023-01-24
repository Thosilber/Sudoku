#pragma once

#include "model.hxx"
#include "view.hxx"

#include <ge211.hxx>

class Controller : public ge211::Abstract_game
{
public:
    Controller();

protected:
    void draw(ge211::Sprite_set& set) override;

    ///Defines window dimensions
    View::Dimensions initial_window_dimensions() const override;

    /// Defines how the game responds to mouse clicks (which is by
    /// telling the model to launch the ball).
    void on_mouse_down(ge211::Mouse_button m, ge211::Posn<int> position)
    override;

    ///Gives you the position of the mouse
    void on_mouse_move(ge211::Posn<int> pos) override;

    /// Defines how the game responds to key events.
    void on_key(ge211::Key) override;

private:
    Model model_;
    View view_;
    char number_typed;
    ge211::Posn<int> mouse_;
};
