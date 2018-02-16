//
// Created by koncord on 15.08.17.
//

#include <components/openmw-mp/NetworkMessages.hpp>
#include "GUI.hpp"
#include "Player.hpp"
#include "Networking.hpp"

void GUI::Init(LuaState &lua)
{
    lua.getState()->new_usertype<GUI>("GUI",
                                      "messageBox", &GUI::messageBox,
                                      "customMessageBox", &GUI::customMessageBox,
                                      "inputDialog", &GUI::inputDialog,
                                      "passwordDialog", &GUI::passwordDialog,
                                      "listBox", &GUI::listBox,
                                      "setMapVisibility", &GUI::setMapVisibility,
                                      "setMapVisibilityAll", &GUI::setMapVisibilityAll,
                                      "createWindow", &GUI::createWindow,
                                      "deleteWindow", &GUI::deleteWindow
    );
    Window::Init(lua);
}

GUI::GUI(Player *player): BaseMgr(player)
{

}

void GUI::processUpdate()
{
    player->guiMessageBox = guiQueue.front().first;
    auto packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_GUI_MESSAGEBOX);
    packet->setPlayer(player);
    packet->Send(false);
}

uint64_t GUI::generateGuiId()
{
    return RakNet::RakPeerInterface::Get64BitUniqueRandomNumber();
}

void GUI::messageBox(sol::function fn, const char *label, sol::this_environment te)
{
    mwmp::BasePlayer::GUIMessageBox mbox;

    mbox.id = generateGuiId();
    mbox.label = label;
    mbox.type = Player::GUIMessageBox::Type::MessageBox;

    guiQueue.emplace(std::move(mbox), std::move(fn));

    setChanged();
}

void GUI::customMessageBox(sol::function fn, const char *label, const char *buttons, sol::this_environment te)
{
    mwmp::BasePlayer::GUIMessageBox mbox;
    mbox.id = generateGuiId();
    mbox.label = label;
    mbox.buttons = buttons;
    mbox.type = Player::GUIMessageBox::Type::CustomMessageBox;

    guiQueue.emplace(std::move(mbox), std::move(fn));

    setChanged();
}

void GUI::inputDialog(sol::function fn, const char *label, sol::this_environment te)
{
    mwmp::BasePlayer::GUIMessageBox mbox;

    mbox.id = generateGuiId();
    mbox.label = label;
    mbox.type = Player::GUIMessageBox::Type::InputDialog;

    guiQueue.emplace(std::move(mbox), std::move(fn));

    setChanged();
}

void GUI::passwordDialog(sol::function fn, const char *label, const char *note, sol::this_environment te)
{
    mwmp::BasePlayer::GUIMessageBox mbox;

    mbox.id = generateGuiId();
    mbox.label = label;
    mbox.note = note;
    mbox.type = Player::GUIMessageBox::Type::PasswordDialog;

    guiQueue.emplace(std::move(mbox), std::move(fn));

    setChanged();
}

void GUI::listBox(sol::function fn, const char *label, const char *items, sol::this_environment te)
{
    mwmp::BasePlayer::GUIMessageBox mbox;

    mbox.id = generateGuiId();

    mbox.label = label;
    mbox.data = items;
    mbox.type = Player::GUIMessageBox::Type::ListBox;

    guiQueue.emplace(std::move(mbox), std::move(fn));

    setChanged();
}

void GUI::onGUIAction()
{
    auto mbox = std::move(guiQueue.front().first);
    auto callback = std::move(guiQueue.front().second);
    guiQueue.pop();
    if(!guiQueue.empty())
        setChanged();
    if(player->guiMessageBox.id != mbox.id)
    {
        LOG_MESSAGE_SIMPLE(Log::LOG_ERROR, "Wrong MessageBox id from %s(%d).", player->npc.mName, player->getId());
        return;
    }

    if (callback.valid())
        callback.call(player, player->guiMessageBox.data);
}

void GUI::setMapVisibility(unsigned short targetPID, unsigned short affectedPID, unsigned short state)
{
    LOG_MESSAGE(Log::LOG_WARN, "stub");
}

void GUI::setMapVisibilityAll(unsigned short targetPID, unsigned short state)
{
    LOG_MESSAGE(Log::LOG_WARN, "stub");
}

std::shared_ptr<Window> GUI::createWindow(short x, short y, sol::function fn, sol::this_environment te)
{
    int id = 0;

    for (auto &window : windows)
    {
        if (window.second == nullptr)
        {
            id = window.first;
            break;
        }
    }

    if (id == 0)
        id = lastWindowId++;

    auto window = std::make_shared<Window>(player, id);
    window->setSize(x, y);
    window->setCallback(fn);

    windows[id] = window;
    return window;
}

void GUI::deleteWindow(std::shared_ptr<Window> window)
{
    auto it = windows.find(window->getID());
    if (it != windows.end())
    {
        it->second = nullptr;
    }
}

void GUI::onGUIWindowAction()
{
    auto it = windows.find(player->guiWindow.id);
    if (it != windows.end() && it->second != nullptr)
    {
        it->second->call(player->guiWindow);
    }
}

void QuickKeys::Init(LuaState &lua)
{
    lua.getState()->new_usertype<QuickKeys>("QuickKeys",
        "addQuickKey", &QuickKeys::addQuickKey,
        "getQuickKey", &QuickKeys::getQuickKey,
        "setQuickKey", &QuickKeys::setQuickKey,
        "clear", &QuickKeys::clear,
        "size", &QuickKeys::size
        );
}

QuickKeys::QuickKeys(Player *player) : BaseMgr(player)
{

}

void QuickKeys::processUpdate()
{
    auto packet = mwmp::Networking::get().getPlayerPacketController()->GetPacket(ID_PLAYER_QUICKKEYS);
    packet->setPlayer(player);
    packet->Send(false);
    clear();
}

void QuickKeys::addQuickKey(const QuickKey &quickKey)
{
    player->quickKeyChanges.quickKeys.push_back(quickKey.quickKey);
    setChanged();
}


QuickKey QuickKeys::getQuickKey(int id) const
{
    return QuickKey(player->quickKeyChanges.quickKeys.at(id));
}

void QuickKeys::setQuickKey(int id, const QuickKey &quickKey)
{
    player->quickKeyChanges.quickKeys.at(id) = quickKey.quickKey;
    setChanged();
}

void QuickKeys::clear()
{
    player->quickKeyChanges.quickKeys.clear();
    setChanged();
}

size_t QuickKeys::size() const
{
    return player->quickKeyChanges.quickKeys.size();
}

void QuickKey::Init(LuaState &lua)
{
    lua.getState()->new_usertype<QuickKey>("QuickKey",
                                          "slot", sol::property(&QuickKey::getSlot, &QuickKey::setSlot),
                                          "type", sol::property(&QuickKey::getType, &QuickKey::setType),
                                          "itemId", sol::property(&QuickKey::getItemId, &QuickKey::setItemId)
    );
}

QuickKey::QuickKey(mwmp::QuickKey &quickKey): quickKey(quickKey)
{

}

int QuickKey::getSlot() const
{
    return quickKey.slot;
}

void QuickKey::setSlot(unsigned short slot)
{
    quickKey.slot = slot;
}

mwmp::QuickKey::Type QuickKey::getType() const
{
    return quickKey.type;
}

void QuickKey::setType(mwmp::QuickKey::Type type)
{
    quickKey.type = type;
}

std::string QuickKey::getItemId() const
{
    return quickKey.itemId;
}

void QuickKey::setItemId(const std::string &itemId)
{
    quickKey.itemId = itemId;
}
