//
// Created by koncord on 07.11.17.
//

#pragma once


#include <components/openmw-mp/Base/BasePlayer.hpp>
#include <apps/openmw/mwgui/widgets.hpp>
#include "apps/openmw/mwgui/windowbase.hpp"

namespace mwmp
{

    class GUICustomWindow : public MWGui::WindowModal
    {
    public:
        explicit GUICustomWindow(const BasePlayer::GUIWindow &guiMessageBox);
        void mousePressed(MyGUI::Widget *_widget);
        void itemActivated(MyGUI::ListPtr sender, size_t index);
        void onFrame(float frameDuration);

        void addButton(const BasePlayer::GUIWindow::Widget &widget);
        void addEditBox(const BasePlayer::GUIWindow::Widget &widget);
        void addLabel(const BasePlayer::GUIWindow::Widget &widget);
        void addListBox(const BasePlayer::GUIWindow::Widget &widget);
        void addSlider(const BasePlayer::GUIWindow::Widget &widget);

    private:
        std::vector<MyGUI::ListBox*> lists;
        std::vector<MyGUI::EditBox*> boxes;
        std::vector<MWGui::Widgets::MWScrollBar*> sliders;
        int id;

        void addPassiveData(std::vector<BasePlayer::GUIWindow::Widget> &widgets);
        void send(const BasePlayer::GUIWindow::Widget &widget);
    };
}
