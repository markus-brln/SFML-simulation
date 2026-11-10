#include "model.ih"


void Model::render(Image& img)
{
    Vector2 size = img.getSize();

    // Create a copy of the image to read unmodified pixel data from
    Image sourceImg = img;

    // #pragma omp parallel for collapse(2)
    for (size_t y = 0; y < size.y; ++y)
    {
        for (size_t x = 0; x < size.x; ++x) // Fixed: size.y -> size.x
        {
            unsigned int rSum = 0, gSum = 0, bSum = 0, aSum = 0;
            int count = 0;

            // Iterate over the 3x3 neighborhood
            for (int dy = -1; dy <= 1; ++dy)
            {
                for (int dx = -1; dx <= 1; ++dx)
                {
                    int nx = static_cast<int>(x) + dx;
                    int ny = static_cast<int>(y) + dy;

                    // Account for edges by checking if neighbor is within bounds
                    if (nx >= 0 && nx < static_cast<int>(size.x) &&
                        ny >= 0 && ny < static_cast<int>(size.y))
                    {
                        Color c = sourceImg.getPixel(Vector2u(nx, ny));
                        rSum += c.r;
                        gSum += c.g;
                        bSum += c.b;
                        aSum += c.a;
                        count++;
                    }
                }
            }

            // Compute the average color
            img.setPixel(Vector2u(x, y), Color{
                static_cast<std::uint8_t>(rSum / count),
                static_cast<std::uint8_t>(gSum / count),
                static_cast<std::uint8_t>(bSum / count),
                static_cast<std::uint8_t>(aSum / count)
            });
        }
    }
}