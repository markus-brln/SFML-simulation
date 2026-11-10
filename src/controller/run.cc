#include "controller.ih"


void Controller::run()
{
    cout << "Setting center pixel to white" << endl;

    for (size_t y = WINDOW_SIZE.y / 2 - 20; y < WINDOW_SIZE.y / 2 + 20; ++y)
    {
        for (size_t x = WINDOW_SIZE.x / 2 - 20; x < WINDOW_SIZE.x / 2 + 20; ++x)
        {
            d_viewsf.img().setPixel(Vector2u(x, y), Color{
                static_cast<std::uint8_t>(255),
                static_cast<std::uint8_t>(255),
                static_cast<std::uint8_t>(255),
                 255
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

        Model::render(d_viewsf.img());
        
        d_viewsf.draw();
    }
}
// main event+render loop
