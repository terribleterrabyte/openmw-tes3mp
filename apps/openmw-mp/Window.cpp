//
// Created by koncord on 21.11.17.
//

#include <components/openmw-mp/NetworkMessages.hpp>
#include "Player.hpp"
#include "Window.hpp"
#include "Networking.hpp"

using namespace std;
using namespace mwmp;

void Window::Init(LuaState &lua)
{
    lua.getState()->new_usertype<Window>("Window",
                                         "addButton", &Window::addButton,
                                         "addLabel", &Window::addLabel,
                                         "addEditBox", &Window::addEditBox,
                                         "addPassiveListBox", &Window::addPassiveListBox,
                                         "addActiveListBox", &Window::addActiveListBox,
                                         "addSlider", &Window::addSlider,
                                         "show", &Window::show,
                                         "clear", &Window::clear,
                                         "setCallback", &Window::setCallback

    );
}

Window::Window(Player *player, int id) : player(player)
{
    guiWindow.id = id;
}

Window::~Window()
{

}

void Window::show()
{
    printf("Trying to show window: %d\n", guiWindow.id);
    if (guiWindow.widgets.empty())
        return;

    auto packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_GUI_WINDOW);

    player->guiWindow = guiWindow;

    packet->setPlayer(player);
    packet->Send(false);
}

void Window::clear()
{
    guiWindow.widgets.clear();
}

int Window::getID()
{
    return guiWindow.id;
}

void Window::call(const BasePlayer::GUIWindow &window)
{
    sol::table table = Networking::get().getState().getState()->create_table();

    auto fnTypeToStr = [](const BasePlayer::GUIWindow::WidgetType &type) {
        switch (type)
        {

            case BasePlayer::GUIWindow::WidgetType::Button:
                return "Button";
            case BasePlayer::GUIWindow::WidgetType::Editbox:
                return "Editbox";
            case BasePlayer::GUIWindow::WidgetType::Label:
                return "Label";
            case BasePlayer::GUIWindow::WidgetType::ListBoxActive:
                return "ListBoxActive";
            case BasePlayer::GUIWindow::WidgetType::ListBoxPassive:
                return "ListBoxPassive";
            case BasePlayer::GUIWindow::WidgetType::Slider:
                return "Slider";
        }
    };

    for (const auto &widget : window.widgets)
    {

        sol::table w = table.create(widget.name);

        w.add(fnTypeToStr(widget.type));
        if (!widget.data.empty())
            w.add(widget.data[0]);
    }
    callback.call(this, player, table);
}

void Window::setCallback(sol::function callback)
{
    /*int id = 0;
    for (auto &&cb : callbacks)
    {
        if (cb.second.get() == nullptr)
            id = cb.first;
    }
    if (id == 0)
        id = lastId++;
    callbacks[id] = make_unique(callback);*/
    this->callback = callback;
}

void Window::setSize(short width, short height)
{
    guiWindow.width = width;
    guiWindow.height = height;
}

void Window::addButton(short x, short y, const std::string &label, sol::optional<bool> active)
{
    BasePlayer::GUIWindow::Widget widget;
    widget.posX = x;
    widget.posY = y;
    widget.name = label;
    widget.type = BasePlayer::GUIWindow::WidgetType::Button;
    if (active)
        widget.disabled = !active.value();
    else
        widget.disabled = false;
    guiWindow.widgets.push_back(widget);
}

void Window::addEditBox(short x, short y, short w, short h, const std::string &id, sol::optional<bool> active)
{
    BasePlayer::GUIWindow::Widget widget;
    widget.posX = x;
    widget.posY = y;
    widget.width = w;
    widget.height = h;
    widget.name = id;
    widget.type = BasePlayer::GUIWindow::WidgetType::Editbox;
    if (active)
        widget.disabled = !active.value();
    else
        widget.disabled = false;
    guiWindow.widgets.push_back(widget);
}

void Window::addLabel(short x, short y, const std::string &label)
{
    BasePlayer::GUIWindow::Widget widget;
    widget.posX = x;
    widget.posY = y;
    widget.name = label;
    widget.type = BasePlayer::GUIWindow::WidgetType::Label;
    guiWindow.widgets.push_back(widget);
}

void Window::addPassiveListBox(short x, short y, short w, short h, const std::string &id, sol::table data,
                               sol::optional<bool> active)
{
    BasePlayer::GUIWindow::Widget widget;
    widget.posX = x;
    widget.posY = y;
    widget.width = w;
    widget.height = h;
    widget.name = id;
    widget.type = BasePlayer::GUIWindow::WidgetType::ListBoxPassive;

    if (active)
        widget.disabled = !active.value();
    else
        widget.disabled = false;

    for (const auto &item : data)
        widget.data.push_back(item.second.as<string>());

    guiWindow.widgets.push_back(widget);
}

void Window::addActiveListBox(short x, short y, short w, short h, const std::string &id, sol::table data,
                              sol::optional<bool> active)
{
    BasePlayer::GUIWindow::Widget widget;
    widget.posX = x;
    widget.posY = y;
    widget.width = w;
    widget.height = h;
    widget.name = id;
    widget.type = BasePlayer::GUIWindow::WidgetType::ListBoxActive;
    if (active)
        widget.disabled = !active.value();
    else
        widget.disabled = false;

    for (const auto &item : data)
        widget.data.push_back(item.second.as<string>());

    guiWindow.widgets.push_back(widget);
}

void Window::addSlider(short x, short y, short w, short h, const std::string &id, sol::optional<bool> active)
{
    BasePlayer::GUIWindow::Widget widget;
    widget.posX = x;
    widget.posY = y;
    widget.width = w;
    widget.height = h;
    widget.name = id;
    widget.type = BasePlayer::GUIWindow::WidgetType::Slider;
    if (active)
        widget.disabled = !active.value();
    else
        widget.disabled = false;
    guiWindow.widgets.push_back(widget);
}
