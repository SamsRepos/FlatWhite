#include "gameObject/GameObject.hpp"

#include "component/TextComponent.hpp"

namespace fw
{

class MenuItem : public GameObject
{
public:
    MenuItem(
        const std::string& text, 
        const Font& font,
        const Vec2f& position, 
        std::function<void()> payload
    );

    MenuItem(
        const std::string& text, 
        const Font& font,
        const Vec2f& position, 
        std::function<void()> payload,
        const Colour& defaultColour, 
        const Colour& highlightedColour,
        OriginPoints originPoint
    );

    void setHighlighted(bool highlighted);

    void runPayload();

private:
    std::shared_ptr<TextComponent> m_text;
    Font m_font;

    bool m_highlighted;

    Colour m_defaultColour;
    Colour m_highlightedColour;

    std::function<void()> m_payload;
};

}