#include "renderer.h"

class Simulater : public Renderer
{
public:
    Simulater(const std::string &title, const int &width, const int &height,
              const bool isWhite = true) : Renderer(title, width, height, isWhite) {}

    ~Simulater() {}

    void update() override;
};