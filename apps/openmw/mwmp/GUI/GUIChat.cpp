//
// Created by koncord on 04.03.16.
//

#include "GUIChat.hpp"

#include <MyGUI_EditBox.h>
#include "apps/openmw/mwbase/environment.hpp"
#include "apps/openmw/mwgui/windowmanagerimp.hpp"
#include "apps/openmw/mwinput/inputmanagerimp.hpp"
#include <MyGUI_InputManager.h>
#include <components/openmw-mp/Log.hpp>
#include <boost/tokenizer.hpp>
#include <string>

#include "../Networking.hpp"
#include "../Main.hpp"
#include "../LocalPlayer.hpp"

#include "../../mwbase/world.hpp"

#include "../../mwworld/timestamp.hpp"

#include "../GUIController.hpp"


namespace mwmp
{
    GUIChat::GUIChat(int x, int y, int w, int h)
            : WindowBase("tes3mp_chat.layout")
    {
        netStat = false;
        setCoord(x, y, w, h);

        getWidget(mCommandLine, "edit_Command");
        getWidget(mHistory, "list_History");
        getWidget(mChannelPrevBtn, "btn_prev_ch");
        mChannelPrevBtn->eventMouseButtonClick += MyGUI::newDelegate(this, &GUIChat::prevChannels);
        getWidget(mChannelNextBtn, "btn_next_ch");
        mChannelNextBtn->eventMouseButtonClick += MyGUI::newDelegate(this, &GUIChat::nextChannels);
        getWidget(mBoxChannels, "box_channels");

        for (int i = 0; i < 3; ++i)
        {
            getWidget(mChannelBtns[i], "btn_ch" + std::to_string(i + 1));
            mChannelBtns[i]->eventMouseButtonClick += MyGUI::newDelegate(this, &GUIChat::onClickChannel);
        }

        // Set up the command line box
        mCommandLine->eventEditSelectAccept +=
                newDelegate(this, &GUIChat::acceptCommand);
        mCommandLine->eventKeyButtonPressed +=
                newDelegate(this, &GUIChat::keyPress);

        mHistory->setOverflowToTheLeft(true);
        mHistory->setEditWordWrap(true);
        mHistory->setTextShadow(true);
        mHistory->setTextShadowColour(MyGUI::Colour::Black);

        mHistory->setNeedKeyFocus(false);

        windowState = 0;
        mCommandLine->setVisible(false);
        mBoxChannels->setVisible(false);
        delay = 3; // 3 sec.
        page = 0;
        currentChannel = 0;
        addChannel(0, "Default");
        setChannel(0);
        redrawChnnels();
        defaultColor = mChannelPrevBtn->getTextColour();
    }

    void GUIChat::onOpen()
    {
        // Give keyboard focus to the combo box whenever the console is
        // turned on
        SetEditState(0);
        windowState = CHAT_ENABLED;
    }

    void GUIChat::onClose()
    {
        // Apparently, hidden widgets can retain key focus
        // Remove for MyGUI 3.2.2
        windowState = CHAT_DISABLED;
        SetEditState(0);
    }

    bool GUIChat::exit()
    {
        //WindowBase::exit();
        return true;
    }

    void GUIChat::acceptCommand(MyGUI::EditBox *_sender)
    {
        const std::string &cm = MyGUI::TextIterator::toTagsString(mCommandLine->getCaption());

        // If they enter nothing, then it should be canceled.
        // Otherwise, there's no way of closing without having text.
        if (cm.empty())
        {
            mCommandLine->setCaption("");
            SetEditState(false);
            return;
        }

        if (cm.find("//", 0, 2) == 0) //clientside commands
        {
            typedef boost::char_separator<char> csep;
            csep sep(" ");
            boost::tokenizer<csep> tokens(cm, sep);

            std::vector<std::string> cmd;
            for (const auto& t : tokens)
                cmd.push_back(t);

            if (cmd[0] == "//channel")
            {
                if (cmd[1] == "close")
                {
                    LOG_MESSAGE_SIMPLE(Log::LOG_INFO, "Closed \"%d\" channel", currentChannel);
                    closeChannel(currentChannel);
                }
            }

        }
        else
        {
            LOG_MESSAGE_SIMPLE(Log::LOG_INFO, "Player: %s", cm);
            send (cm);
        }

        // Add the command to the history, and set the current pointer to
        // the end of the list
        if (mCommandHistory.empty() || mCommandHistory.back() != cm)
            mCommandHistory.push_back(cm);
        mCurrent = mCommandHistory.end();
        mEditString.clear();

        mCommandLine->setCaption("");
        SetEditState(false);

    }

    void GUIChat::onResChange(int width, int height)
    {
        setCoord(10,10, width-10, height/2);
    }

    void GUIChat::setFont(const std::string &fntName)
    {
        mHistory->setFontName(fntName);
        mCommandLine->setFontName(fntName);
    }

    void GUIChat::print(unsigned channelId, const std::string &msg, const std::string &color)
    {
        if (windowState == 2 && !isVisible())
        {
            setVisible(true);
        }

        if (channelId != currentChannel)
        {
            try
            {
                auto it = getChannel(channelId);
                if (it != channels.end())
                {
                    it->channelText = color + msg;
                    it->newMessages = true;
                }
            }
            catch(std::out_of_range &e) {}
        }
        else
            mHistory->addText(color + msg);
        LOG_MESSAGE_SIMPLE(Log::LOG_INFO, "%s", msg.c_str());


    }

    void GUIChat::send(const std::string &str)
    {
        LocalPlayer *localPlayer = Main::get().getLocalPlayer();

        Networking *networking = Main::get().getNetworking();

        localPlayer->chat.action = Chat::Action::print;
        localPlayer->chat.channel = currentChannel;
        localPlayer->chat.message = str;

        networking->getPlayerPacket(ID_CHAT_MESSAGE)->setPlayer(localPlayer);
        networking->getPlayerPacket(ID_CHAT_MESSAGE)->Send();
    }

    void GUIChat::clean(unsigned channelId)
    {
        if(channelId == currentChannel)
            mHistory->setCaption("");
        else
        {
            auto it = getChannel(channelId);
            if(it != channels.end())
            {
                it->channelText.clear();
            }
        }
    }

    void GUIChat::pressedChatMode()
    {
        windowState++;
        if (windowState == 3) windowState = 0;

        std::string chatMode = windowState == CHAT_DISABLED ? "Chat disabled" :
                               windowState == CHAT_ENABLED ? "Chat enabled" :
                               "Chat in hidden mode";

        LOG_MESSAGE_SIMPLE(Log::LOG_VERBOSE, "Switch chat mode to %s", chatMode.c_str());
        MWBase::Environment::get().getWindowManager()->messageBox(chatMode);

        switch (windowState)
        {
            case CHAT_DISABLED:
                this->mMainWidget->setVisible(false);
                SetEditState(false);
                break;
            case CHAT_ENABLED:
                this->mMainWidget->setVisible(true);
                break;
            default: //CHAT_HIDDENMODE
                this->mMainWidget->setVisible(true);
                curTime = 0;
        }
    }

    void GUIChat::SetEditState(bool state)
    {
        editState = state;
        mCommandLine->setVisible(editState);
        mBoxChannels->setVisible(editState);
        MWBase::Environment::get().getWindowManager()->setKeyFocusWidget(editState ? mCommandLine : nullptr);
    }

    void GUIChat::pressedSay()
    {
        if (windowState == CHAT_DISABLED)
            return;
        else if (windowState == CHAT_HIDDENMODE)
        {
            setVisible(true);
            curTime = 0;
            editState = true;
        }
        else // CHAT_ENABLED
            editState = true;

        LOG_MESSAGE_SIMPLE(Log::LOG_VERBOSE, "Opening chat.");
        SetEditState(editState);
    }

    void GUIChat::keyPress(MyGUI::Widget *_sender, MyGUI::KeyCode key, MyGUI::Char _char)
    {
        if (mCommandHistory.empty()) return;

        // Traverse history with up and down arrows
        if (key == MyGUI::KeyCode::ArrowUp)
        {
            // If the user was editing a string, store it for later
            if (mCurrent == mCommandHistory.end())
                mEditString = mCommandLine->getOnlyText();

            if (mCurrent != mCommandHistory.begin())
            {
                --mCurrent;
                mCommandLine->setCaption(*mCurrent);
            }
        }
        else if (key == MyGUI::KeyCode::ArrowDown)
        {
            if (mCurrent != mCommandHistory.end())
            {
                ++mCurrent;

                if (mCurrent != mCommandHistory.end())
                    mCommandLine->setCaption(*mCurrent);
                else
                    // Restore the edit string
                    mCommandLine->setCaption(mEditString);
            }
        }
    }

    void GUIChat::Update(float dt)
    {
        if (windowState == CHAT_HIDDENMODE && !editState && isVisible())
        {
            curTime += dt;
            if (curTime >= delay)
            {
                SetEditState(false);
                this->mMainWidget->setVisible(false);
            }
        }

        if (netStat)
        {
            auto rss = Main::get().getNetworking()->getNetworkStatistics();
            mHistory->setCaption(rss);
        }
        static float time = 0;
        time += dt;
        if(time >= 1)
        {
            time = 0;
            static bool phase = false;
            phase = !phase;

            auto color = phase ? MyGUI::Colour::Blue : defaultColor;

            for(auto it = channels.begin(); it != channels.end(); ++it)
            {
                if(!it->newMessages || it->channel == currentChannel)
                    continue;

                long pos = it - channels.begin();

                if(pos < page * pageM)
                    mChannelPrevBtn->setTextColour(color);
                else if(pos >= page * pageM + 3)
                    mChannelNextBtn->setTextColour(color);
                else
                {
                    for(auto &btn : mChannelBtns)
                    {
                        if (it->channelName != btn->getCaption().asUTF8())
                            continue;
                        btn->setTextColour(color);
                        break;
                    }
                }
            }
        }
    }

    void GUIChat::setCaption(const std::string &str)
    {
        mHistory->setCaption(str);
    }

    void GUIChat::setDelay(float delay)
    {
        this->delay = delay;
    }

    void GUIChat::switchNetstat()
    {
        netStat = !netStat;
    }

    void GUIChat::addChannel(unsigned ch, const std::string &name)
    {
        auto channel = getChannel(ch);
        if(channel == channels.end())
        {
            LOG_MESSAGE_SIMPLE(Log::LOG_VERBOSE, "Adding channel id: %d %s", ch, name);
            channels.push_back(ChannelData{ch, name.substr(0, 9), "", false});
        }
        redrawChnnels();
    }

    void GUIChat::renameChannel(unsigned ch, const std::string &newName)
    {
        auto it = getChannel(ch);
        if(it != channels.end())
        {
            it->channelName = newName.substr(0, 9);
            redrawChnnels();
        }
    }

    void GUIChat::setChannel(const std::string &channel, bool saveHistory)
    {
        auto ch = channel.substr(0, 9);
        auto it = std::find_if(channels.begin(), channels.end(), [&ch](const ChannelData &item) {
            return item.channelName == ch;
        });

        if (it != channels.end())
            setChannel(it, saveHistory);
    }

    void GUIChat::setChannel(unsigned ch, bool saveHistory)
    {
        auto it = getChannel(ch);
        if (it != channels.end())
            setChannel(it, saveHistory);
    }

    void GUIChat::setChannel(ChannelIter it, bool saveHistory)
    {
        if (saveHistory && !mHistory->getCaption().empty())
            getChannel(currentChannel)->channelText = mHistory->getCaption();

        it->newMessages = false;
        mHistory->setCaption(it->channelText);
        currentChannel = it->channel;

        redrawChnnels();
    }

    void GUIChat::closeChannel(unsigned ch)
    {
        if (ch == 0) // that's impossible
            return;
        auto it = getChannel(ch);

        if (it != channels.end())
        {
            if (ch == it->channel)
                setChannel(0, false); // reset to default channel
            channels.erase(it);
        }
        redrawChnnels();
    }

    void GUIChat::redrawChnnels()
    {
        mChannelPrevBtn->setVisible(page != 0);
        mChannelNextBtn->setVisible(channels.size() > 3 && page != lastPage());

        mChannelPrevBtn->setTextColour(defaultColor);
        mChannelNextBtn->setTextColour(defaultColor);

        if (page >=lastPage())
            page = lastPage();
        unsigned showElems = page * pageM + 3;
        if (showElems > channels.size())
            showElems = static_cast<unsigned>(channels.size());
        auto it = channels.begin() + page * pageM;
        auto endIt = channels.begin() + showElems;
        for (auto &btn : mChannelBtns)
        {
            if (it == endIt)
                btn->setVisible(false);
            else
            {
                btn->setVisible(true);
                if (currentChannel == it->channel)
                {
                    setTitle("Chat: " + it->channelName + "(" + std::to_string(it->channel) + ")");
                    btn->setEnabled(false);
                    btn->setStateSelected(true);
                    btn->setTextColour(MyGUI::Colour::Red);
                }
                else
                {
                    btn->setEnabled(true);
                    btn->setTextColour(defaultColor);
                }
                btn->setCaption(it++->channelName);
            }
        }
    }

    void GUIChat::nextChannels(MyGUI::Widget* _sender)
    {
        page++;
        if (page > lastPage())
           page = lastPage();
        redrawChnnels();
    }

    void GUIChat::prevChannels(MyGUI::Widget* _sender)
    {
        if (page > 0)
            page--;
        redrawChnnels();
    }

    void GUIChat::onClickChannel(MyGUI::Widget *_sender)
    {
        auto sender = dynamic_cast<MyGUI::Button*>(_sender);
        setChannel(sender->getCaption().asUTF8());
    }

    unsigned GUIChat::lastPage()
    {
        return static_cast<unsigned>(channels.size() / pageM + channels.size() % pageM - 1);
    }

    GUIChat::ChannelIter GUIChat::getChannel(unsigned ch)
    {
        return std::find_if(channels.begin(), channels.end(), [&ch](const ChannelData &data){
            return data.channel == ch;
        });
    }
}
