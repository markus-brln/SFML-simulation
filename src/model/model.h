#ifndef MODEL_H
#define MODEL_H

#include <SFML/Graphics.hpp>
#include "../utils/utils.h"


class Model
{
    vector<vector<int>> d_acceleration;

    public:
        Model();                            // 1.cc
        void render(sf::Image &img);
        vector<vector<int>> &acceleration();
};

#endif
