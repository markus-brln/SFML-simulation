#include "model.ih"


void Model::render(Image& img)
{
    Vector2 size = img.getSize();

    Image sourceImg = img;
    float viscosity_factor = 0.1;

    // #pragma omp parallel for collapse(2)
    for (size_t y = 0; y < size.y; ++y)
    {
        for (size_t x = 0; x < size.x; ++x) // Fixed: size.y -> size.x
        {
            float rSum = 0, gSum = 0, bSum = 0, aSum = 0;
            float count = 0;

            // Iterate over the neighborhood
            for (int dy = -5; dy <= 5; ++dy)
            {
                for (int dx = -5; dx <= 5; ++dx)
                {
                    int nx = static_cast<int>(x) + dx;
                    int ny = static_cast<int>(y) + dy;

                    // Account for edges by checking if neighbor is within bounds
                    if (nx >= 0 && nx < static_cast<int>(size.x) &&
                        ny >= 0 && ny < static_cast<int>(size.y))
                    {
                        Color c = sourceImg.getPixel(Vector2u(nx, ny));
                        rSum += static_cast<float>(c.r);
                        count++;
                    }
                }
            }
            float neighbour_avg = rSum / count;
            Color old_color = sourceImg.getPixel(Vector2u(x, y));
            int old_acceleration = this->acceleration()[x][y];
            int new_acceleration = static_cast<int>(
                (static_cast<float>(old_acceleration) +
                    (neighbour_avg - static_cast<float>(old_color.r))
                    * viscosity_factor
                ) * 0.99
            );
            this->acceleration()[x][y] = new_acceleration;

            int new_value = static_cast<std::uint8_t>(old_color.r + new_acceleration);
            if (new_value > 255)
            {
                new_value = 255;
            }
            if (new_value < 0)
            {
                new_value = 0;
            }

            Color new_color = Color{
                static_cast<uint8_t>(new_value),
                0,
                0
            };

            img.setPixel(Vector2u(x, y), new_color);
        }
    }
}

