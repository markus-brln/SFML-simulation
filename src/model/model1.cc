#include "model.ih"


Model::Model()
:
    d_acceleration(vector<vector<int>>(WINDOW_SIZE.x, vector<int>(WINDOW_SIZE.y, 0)))
{
}
