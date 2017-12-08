//
// Created by koncord on 04.03.16.
//

#ifndef OPENMW_GUICHAT_HPP
#define OPENMW_GUICHAT_HPP

#include <list>
#include <string>
#include <vector>
#include <unordered_map>
#include <components/widgets/box.hpp>

#include "apps/openmw/mwgui/windowbase.hpp"

namespace mwmp
{
    class GUIController;
    class GUIChat : public MWGui::WindowBase
    {
        friend class GUIController;
    public:
        enum
        {
            CHAT_DISABLED = 0,
            CHAT_ENABLED,
            CHAT_HIDDENMODE
        } CHAT_WIN_STATE;

        MyGUI::EditBox* mCommandLine;
        MyGUI::EditBox* mHistory;
        MyGUI::Button* mChannelBtns[3];
        MyGUI::Button* mChannelNextBtn;
        MyGUI::Button* mChannelPrevBtn;
        Gui::HBox* mBoxChannels;

        typedef std::list<std::string> StringList;

        // History of previous entered commands
        StringList mCommandHistory;
        StringList::iterator mCurrent;
        std::string mEditString;

        GUIChat(int x, int y, int w, int h);

        void pressedChatMode(); //switch chat mode
        void pressedSay(); // switch chat focus (if chat mode != CHAT_DISABLED)
        void setDelay(float delay);

        void Update(float dt);

        void setCaption(const std::string &str);

        virtual void onOpen();
        virtual void onClose();

        virtual bool exit();
        /*virtual void open();
        virtual void close();*/

        void setFont(const std::string &fntName);

        void onResChange(int width, int height);

        // Print a message to the console, in specified color.
        void print(unsigned channelId, const std::string &msg, const std::string& color = "#FFFFFF");

        // Clean chat
        void clean(unsigned channelId);

        void send(const std::string &str);

        void switchNetstat();

        void addChannel(unsigned ch, const std::string &name);
        void setChannel(const std::string &newName, bool saveHistory = true);
        void renameChannel(unsigned ch, const std::string &channel);
        void setChannel(unsigned ch, bool saveHistory = true);
        void closeChannel(unsigned ch);
        void redrawChnnels();
        unsigned lastPage();
        void nextChannels(MyGUI::Widget* _sender);
        void prevChannels(MyGUI::Widget* _sender);
        void onClickChannel(MyGUI::Widget* _sender);

    protected:

    private:

        void keyPress(MyGUI::Widget* _sender,
                      MyGUI::KeyCode key,
                      MyGUI::Char _char);

        void acceptCommand(MyGUI::EditBox* _sender);

        void SetEditState(bool state);

        int windowState;
        bool editState;
        bool netStat;
        float delay;
        float curTime;
        struct ChannelData
        {
            unsigned channel;
            std::string channelName;
            MyGUI::UString channelText;
            bool newMessages;
        };
        std::vector<ChannelData> channels;
        unsigned currentChannel;
        unsigned page;
        const int pageM = 3;

        typedef std::vector<ChannelData>::iterator ChannelIter;
        void setChannel(ChannelIter iter, bool saveHistory);
        ChannelIter getChannel(unsigned ch);
        MyGUI::Colour defaultColor;
    };
}
#endif //OPENMW_GUICHAT_HPP
