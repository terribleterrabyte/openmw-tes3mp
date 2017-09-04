#ifndef CSV_WORLD_LANDCREATOR_H
#define CSV_WORLD_LANDCREATOR_H

#include <QLabel>
#include <QSpinBox>

#include "genericcreator.hpp"

namespace CSVWorld
{
    class LandCreator : public GenericCreator
    {
            Q_OBJECT

            QLabel* mXLabel;
            QLabel* mYLabel;
            QSpinBox* mX;
            QSpinBox* mY;

        public:

            LandCreator(CSMWorld::Data& data, QUndoStack& undoStack, const CSMWorld::UniversalId& id);

            void cloneMode(const std::string& originId, const CSMWorld::UniversalId::Type type) override;

            void touch(const std::vector<CSMWorld::UniversalId>& ids) override;

            void focus() override;

            void reset() override;

            std::string getErrors() const override;

        private slots:

            void coordChanged(int value);

        protected:

            std::string getId() const override;
    };
}

#endif
