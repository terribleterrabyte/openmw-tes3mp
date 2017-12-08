//
// Created by koncord on 07.11.17.
//

#include "GUICustomWindow.hpp"

#include <components/openmw-mp/Log.hpp>

#include "apps/openmw/mwbase/environment.hpp"
#include "apps/openmw/mwgui/windowmanagerimp.hpp"
#include "apps/openmw/mwgui/widgets.hpp"

#include <MyGUI_EditBox.h>
#include <MyGUI_Button.h>
#include <MyGUI_ListBox.h>
#include <MyGUI_Common.h>
#include <MyGUI_LayoutManager.h>
#include <components/openmw-mp/Base/BasePlayer.hpp>
#include <components/openmw-mp/NetworkMessages.hpp>
#include <apps/openmw/mwmp/Main.hpp>
#include <apps/openmw/mwmp/Networking.hpp>
#include <apps/openmw/mwmp/LocalPlayer.hpp>

using namespace mwmp;
using namespace std;

GUICustomWindow::GUICustomWindow(const BasePlayer::GUIWindow &guiMessageBox) : WindowModal("tes3mp_custom.layout")
{
    center();
    mMainWidget->setSize(guiMessageBox.width, guiMessageBox.height);
    id = guiMessageBox.id;

    //setTitle(title);

    {
        MyGUI::Button *button;
        getWidget(button, "SendButton");
        auto bsize = button->getSize();
        auto wsize = mMainWidget->getSize();
        button->eventMouseButtonClick += MyGUI::newDelegate(this, &GUICustomWindow::mousePressed);
        //button->setCaptionWithReplacing(widget.name);
        button->setSize(button->getTextSize().width + 2 * 12, button->getTextSize().height + 2 * 4);
        button->setUserData(string("Send"));
        button->setPosition(wsize.width - bsize.width - 12, wsize.height - bsize.height - 12);
    }

    for (auto &&widget : guiMessageBox.widgets)
    {
        switch (widget.type)
        {

            case BasePlayer::GUIWindow::WidgetType::Button:
                addButton(widget);
                break;
            case BasePlayer::GUIWindow::WidgetType::Editbox:
                addEditBox(widget);
                break;
            case BasePlayer::GUIWindow::WidgetType::Label:
                addLabel(widget);
                break;
            case BasePlayer::GUIWindow::WidgetType::ListBoxActive:
            case BasePlayer::GUIWindow::WidgetType::ListBoxPassive:
                addListBox(widget);
                break;
            case BasePlayer::GUIWindow::WidgetType::Slider:
                addSlider(widget);
        }
    }

}

void GUICustomWindow::addPassiveData(vector<BasePlayer::GUIWindow::Widget> &widgets)
{
    for (const auto &box : boxes)
    {
        auto name = box->getUserData<string>(false);
        if (name != nullptr)
        {
            BasePlayer::GUIWindow::Widget widget;
            widget.name = *name;
            widget.type = BasePlayer::GUIWindow::WidgetType::Editbox;
            widget.data.push_back(box->getCaption().asUTF8());
            widgets.push_back(widget);
        }
    }

    for (auto &&list : lists)
    {
        size_t selected = list->getIndexSelected();
        if (selected != MyGUI::ITEM_NONE)
        {
            auto name = list->getUserData<string>(false);
            if (name != nullptr)
            {
                BasePlayer::GUIWindow::Widget widget;
                widget.name = *name;
                widget.type = BasePlayer::GUIWindow::WidgetType::ListBoxPassive;
                widget.data.push_back(list->getItemNameAt(selected).asUTF8());
                widgets.push_back(widget);
            }
        }
    }

    for (auto &&slider : sliders)
    {
        auto name = slider->getUserData<string>(false);
        if (name != nullptr)
        {
            BasePlayer::GUIWindow::Widget widget;
            widget.name = *name;
            widget.type = BasePlayer::GUIWindow::WidgetType::Slider;
            widget.data.push_back(to_string(slider->getScrollPosition()));
            widgets.push_back(widget);
        }
    }
}

void GUICustomWindow::mousePressed(MyGUI::Widget *pressed)
{
    setVisible(false);
    MWBase::Environment::get().getWindowManager()->popGuiMode();

    auto value = pressed->getUserData<string>(false);

    if (value != nullptr)
    {
        BasePlayer::GUIWindow::Widget pressedButton;

        pressedButton.name = *value;
        pressedButton.type = BasePlayer::GUIWindow::WidgetType::Button;
        send(pressedButton);
        /*printf("Ret Value: %s\n", value->c_str());

        for (auto &&list : lists)
        {
            size_t selected = list->getIndexSelected();
            if (selected != MyGUI::ITEM_NONE)
            {
                auto value2 = list->getUserData<string>(false);
                printf("RetList: %s %s\n", value2->c_str(), list->getItemNameAt(selected).asUTF8_c_str());
            }
        }

        for (auto &&box : boxes)
        {
            auto value2 = box->getUserData<string>(false);
            if (value2 != nullptr)
            {
                printf("\tRetEdit: %s  %s\n", value2->c_str(), box->getCaption().asUTF8_c_str());
            }
        }

        for (auto &&slider : sliders)
        {
            printf("Slider: %zu\n", slider->getScrollPosition());
        }*/
    }
}

void GUICustomWindow::itemActivated(MyGUI::ListPtr sender, size_t index)
{
    /*printf("---------Item Activated---------\n");
    auto str = sender->getUserData<string>(false);
    if (str != nullptr)
        printf("ID: %s\n", str->c_str());
    printf("item: %zu\n", index);
    printf("value of item: %s\n", sender->getItemNameAt(index).asUTF8_c_str());
    printf("--------------------------------\n");*/

    auto str = sender->getUserData<string>(false);
    if (str != nullptr)
    {
        BasePlayer::GUIWindow::Widget pressedListBox;
        pressedListBox.name = *str;
        pressedListBox.type = BasePlayer::GUIWindow::WidgetType::ListBoxActive;
        pressedListBox.data.push_back(sender->getItemNameAt(index).asUTF8());
        send(pressedListBox);
    }
}

void GUICustomWindow::send(const BasePlayer::GUIWindow::Widget &widget)
{
    auto networking = mwmp::Main::get().getNetworking();
    auto player = networking->getLocalPlayer();

    player->guiWindow.widgets.clear();
    player->guiWindow.widgets.push_back(widget);
    addPassiveData(player->guiWindow.widgets);

    player->guiWindow.id = id;
    player->guiWindow.width = 0;
    player->guiWindow.height = 0;
    auto packet = networking->getPlayerPacket(ID_GUI_WINDOW);
    packet->setPlayer(player);
    packet->Send();

    setVisible(false);
    MWBase::Environment::get().getWindowManager()->popGuiMode();
}

void GUICustomWindow::onFrame(float frameDuration)
{

}

void GUICustomWindow::addButton(const BasePlayer::GUIWindow::Widget &widget)
{
    MyGUI::IntCoord dummyCoord(0, 0, 0, 0);

    auto *button = mMainWidget->createWidget<MyGUI::Button>(
            MyGUI::WidgetStyle::Child,
            string("MW_Button"),
            dummyCoord,
            MyGUI::Align::Default);

    button->eventMouseButtonClick += MyGUI::newDelegate(this, &GUICustomWindow::mousePressed);
    button->setPosition(widget.posX, widget.posY);
    button->setCaptionWithReplacing(widget.name);
    button->setSize(button->getTextSize().width + 2 * 12, button->getTextSize().height + 2 * 4);
    button->setUserData(widget.name);
    button->setEnabled(!widget.disabled);

}

void GUICustomWindow::addEditBox(const BasePlayer::GUIWindow::Widget &widget)
{
    MyGUI::IntCoord dummyCoord(0, 0, 0, 0);
    auto *editBox = mMainWidget->createWidget<MyGUI::EditBox>(
            MyGUI::WidgetStyle::Child,
            string("MW_TextEdit"),
            dummyCoord,
            MyGUI::Align::Default
    );

    editBox->setCaption(widget.name);

    editBox->setPosition(widget.posX, widget.posY);
    editBox->setSize(widget.width, widget.height);
    editBox->setUserData(string(widget.name)); // ID
    editBox->setEnabled(!widget.disabled);
    if (!widget.disabled)
        boxes.push_back(editBox);
}

void GUICustomWindow::addLabel(const BasePlayer::GUIWindow::Widget &widget)
{
    MyGUI::IntCoord dummyCoord(0, 0, 0, 0);
    auto *textBox = mMainWidget->createWidget<MyGUI::TextBox>(
            MyGUI::WidgetStyle::Child,
            string("ProgressText"),
            dummyCoord,
            MyGUI::Align::Default
    );

    textBox->setCaption(widget.name);

    textBox->setPosition(widget.posX, widget.posY);

    textBox->setSize(textBox->getTextSize().width, textBox->getTextSize().height);
}

void GUICustomWindow::addListBox(const BasePlayer::GUIWindow::Widget &widget)
{
    MyGUI::IntCoord dummyCoord(0, 0, 0, 0);
    auto *lbox = mMainWidget->createWidget<MyGUI::ListBox>(
            MyGUI::WidgetStyle::Child,
            string("MW_List"),
            dummyCoord,
            MyGUI::Align::Default
    );

    for (const auto & item : widget.data)
        lbox->addItem(item);

    lbox->setUserData(widget.name);
    lbox->setScrollPosition(0);
    lbox->setPosition(widget.posX, widget.posY);
    lbox->setSize(widget.width, widget.height);
    lbox->setEnabled(!widget.disabled);

    if (!widget.disabled)
    {
        if (widget.type == BasePlayer::GUIWindow::WidgetType::ListBoxPassive)
            lists.push_back(lbox);
        else
            lbox->eventListMouseItemActivate += MyGUI::newDelegate(this, &GUICustomWindow::itemActivated);
    }
}

void GUICustomWindow::addSlider(const BasePlayer::GUIWindow::Widget &widget)
{
    MyGUI::IntCoord dummyCoord(0, 0, 0, 0);

    auto *slider = mMainWidget->createWidget<MWGui::Widgets::MWScrollBar>(
            MyGUI::WidgetStyle::Child,
            string("MW_HScroll"),
            dummyCoord,
            MyGUI::Align::Default
    );

    slider->setPosition(widget.posX, widget.posY);
    slider->setSize(widget.width, widget.height);

    slider->setScrollRange(10000);
    slider->setScrollPage(300);
    sliders.push_back(slider);
}
