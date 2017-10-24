/*
 * LibrePCB - Professional EDA for everyone!
 * Copyright (C) 2013 LibrePCB Developers, see AUTHORS.md for contributors.
 * http://librepcb.org/
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LIBREPCB_LIBRARY_EDITOR_SYMBOLEDITORWIDGET_H
#define LIBREPCB_LIBRARY_EDITOR_SYMBOLEDITORWIDGET_H

/*****************************************************************************************
 *  Includes
 ****************************************************************************************/
#include <QtCore>
#include <QtWidgets>
#include <librepcb/common/exceptions.h>
#include <librepcb/common/fileio/filepath.h>
#include <librepcb/common/graphics/if_graphicsvieweventhandler.h>
#include "../common/editorwidgetbase.h"
#include "../common/categorylisteditorwidget.h"

/*****************************************************************************************
 *  Namespace / Forward Declarations
 ****************************************************************************************/
namespace librepcb {

class GridProperties;
class GraphicsScene;

namespace library {

class Symbol;
class SymbolGraphicsItem;

namespace editor {

class SymbolEditorFsm;

namespace Ui {
class SymbolEditorWidget;
}

/*****************************************************************************************
 *  Class SymbolEditorWidget
 ****************************************************************************************/

/**
 * @brief The SymbolEditorWidget class
 *
 * @author ubruhin
 * @date 2016-10-16
 */
class SymbolEditorWidget final : public EditorWidgetBase, public IF_GraphicsViewEventHandler
{
        Q_OBJECT

    public:

        // Constructors / Destructor
        SymbolEditorWidget() = delete;
        SymbolEditorWidget(const SymbolEditorWidget& other) = delete;
        SymbolEditorWidget(const Context& context, const FilePath& fp,
                           QWidget* parent = nullptr);
        ~SymbolEditorWidget() noexcept;

        // Getters
        virtual bool hasGraphicalEditor() const noexcept override {return true;}

        // Setters
        void setToolsActionGroup(ExclusiveActionGroup* group) noexcept override;

        // Operator Overloadings
        SymbolEditorWidget& operator=(const SymbolEditorWidget& rhs) = delete;


    public slots:

        bool save() noexcept override;
        bool rotateCw() noexcept override;
        bool rotateCcw() noexcept override;
        bool remove() noexcept override;
        bool zoomIn() noexcept override;
        bool zoomOut() noexcept override;
        bool zoomAll() noexcept override;
        bool abortCommand() noexcept override;
        bool editGridProperties() noexcept override;


    private: // Methods
        /// @copydoc librepcb::IF_GraphicsViewEventHandler::graphicsViewEventHandler()
        bool graphicsViewEventHandler(QEvent* event) noexcept override;
        bool toolChangeRequested(Tool newTool) noexcept override;
        bool isInterfaceBroken() const noexcept override;


    private: // Data
        QScopedPointer<Ui::SymbolEditorWidget> mUi;
        QScopedPointer<ComponentCategoryListEditorWidget> mCategoriesEditorWidget;
        QScopedPointer<GraphicsScene> mGraphicsScene;
        QScopedPointer<Symbol> mSymbol;
        QScopedPointer<SymbolGraphicsItem> mGraphicsItem;
        QScopedPointer<SymbolEditorFsm> mFsm;

        // broken interface detection
        QSet<Uuid> mOriginalSymbolPinUuids;
};

/*****************************************************************************************
 *  End of File
 ****************************************************************************************/

} // namespace editor
} // namespace library
} // namespace librepcb

#endif // LIBREPCB_LIBRARY_EDITOR_SYMBOLEDITORWIDGET_H