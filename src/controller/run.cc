#include "controller.ih"


void Controller::run()
{
    cout << "Setting center pixels to red" << endl;

    for (size_t y = WINDOW_SIZE.y / 2 - 10; y < WINDOW_SIZE.y / 2 + 10; ++y)
    {
        for (size_t x = WINDOW_SIZE.x / 2 - 10; x < WINDOW_SIZE.x / 2 + 10; ++x)
        {
            d_viewsf.img().setPixel(Vector2u(x, y), Color{
                static_cast<std::uint8_t>(255),
                static_cast<std::uint8_t>(0),
                static_cast<std::uint8_t>(0)
            });
        }
    }

    while (d_viewsf.isOpen())
    {
        while (true)
        {
            if (optional<Event> event = d_viewsf.pollEvent())
            {
                handleEvent(*event);
            } else
            {
                break;
            }
            handleKeyPresses();             // live input
        }

        this->d_model.render(d_viewsf.img());
        
        d_viewsf.draw();
    }
}
// main event+render loop
