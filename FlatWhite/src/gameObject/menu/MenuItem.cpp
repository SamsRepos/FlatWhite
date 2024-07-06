#include "gameObject/menu/MenuItem.hpp"

namespace fw 
{

const Colour MENU_ITEM_DEFAULT_NORMAL_COLOUR      = Colour::White;
const Colour MENU_ITEM_DEFAULT_HIGHLIGHTED_COLOUR = Colour::Magenta;

const OriginPoints MENU_ITEM_DEFAULT_ORIGIN = OriginPoints::CENTRE;

MenuItem::MenuItem(
    const std::string& text, 
    const Font& font,
    const Vec2f& position, 
    std::function<void()> payload
)
    : 
    MenuItem(
        text,
        font,
        position,
        payload,
        MENU_ITEM_DEFAULT_NORMAL_COLOUR,
        MENU_ITEM_DEFAULT_HIGHLIGHTED_COLOUR,
        MENU_ITEM_DEFAULT_ORIGIN
    )
{
}

MenuItem::MenuItem(
    const std::string& text, 
    const Font& font,
    const Vec2f& position, 
    std::function<void()> payload,
    const Colour& defaultColour, 
    const Colour& highlightedColour,
    OriginPoints originPoint
)
    :
    m_highlighted(false),
    m_payload(payload),
    m_font(font)
{
    m_defaultColour = defaultColour;

    m_highlightedColour = highlightedColour;

    m_text = std::make_shared<TextComponent>(
        this,
        m_font,
        m_defaultColour,
        position,
        text,
        originPoint
    );

    addComponent(m_text);

}

void MenuItem::setHighlighted(bool highlighted)
{
    m_highlighted = highlighted;

    m_text->setColour(highlighted ? m_highlightedColour : m_defaultColour);
}

void MenuItem::runPayload()
{
    m_payload();
}


}