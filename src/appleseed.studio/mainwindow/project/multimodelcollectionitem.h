
//
// This source file is part of appleseed.
// Visit http://appleseedhq.net/ for additional information and resources.
//
// This software is released under the MIT license.
//
// Copyright (c) 2010-2012 Francois Beaune, Jupiter Jazz Limited
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#ifndef APPLESEED_STUDIO_MAINWINDOW_PROJECT_MULTIMODELCOLLECTIONITEM_H
#define APPLESEED_STUDIO_MAINWINDOW_PROJECT_MULTIMODELCOLLECTIONITEM_H

// appleseed.studio headers.
#include "mainwindow/project/collectionitem.h"
#include "mainwindow/project/entitybrowser.h"
#include "mainwindow/project/entityeditorwindow.h"
#include "mainwindow/project/multimodelentityeditorformfactory.h"
#include "mainwindow/project/multimodelentityitem.h"
#include "mainwindow/project/tools.h"

// appleseed.renderer headers.
#include "renderer/api/entity.h"

// appleseed.foundation headers.
#include "foundation/platform/compiler.h"
#include "foundation/utility/uid.h"

// Qt headers.
#include <QTreeWidgetItem>

// Standard headers.
#include <cassert>
#include <memory>
#include <string>

// Forward declarations.
namespace appleseed     { namespace studio { class ItemBase; } }
namespace appleseed     { namespace studio { class ProjectBuilder; } }
namespace foundation    { class Dictionary; }
class QString;

namespace appleseed {
namespace studio {

template <typename Entity, typename ParentEntity, typename ParentItem>
class MultiModelCollectionItem
  : public CollectionItem<Entity, ParentEntity, ParentItem>
{
  public:
    MultiModelCollectionItem(
        const foundation::UniqueID  class_uid,
        const QString&              title,
        ParentEntity&               parent,
        ParentItem*                 parent_item,
        ProjectBuilder&             project_builder);

  private:
    typedef CollectionItem<Entity, ParentEntity, ParentItem> Base;
    typedef MultiModelCollectionItem<Entity, ParentEntity, ParentItem> This;

    virtual ItemBase* create_item(Entity* entity) OVERRIDE;

    virtual void slot_create() OVERRIDE;
};


//
// MultiModelCollectionItem class implementation.
//

template <typename Entity, typename ParentEntity, typename ParentItem>
MultiModelCollectionItem<Entity, ParentEntity, ParentItem>::MultiModelCollectionItem(
    const foundation::UniqueID      class_uid,
    const QString&                  title,
    ParentEntity&                   parent,
    ParentItem*                     parent_item,
    ProjectBuilder&                 project_builder)
  : Base(class_uid, title, parent, parent_item, project_builder)
{
}

template <typename Entity, typename ParentEntity, typename ParentItem>
ItemBase* MultiModelCollectionItem<Entity, ParentEntity, ParentItem>::create_item(Entity* entity)
{
    assert(entity);

    return
        new MultiModelEntityItem<Entity, ParentEntity, This>(
            entity,
            Base::m_parent,
            this,
            Base::m_project_builder);
}

template <typename Entity, typename ParentEntity, typename ParentItem>
void MultiModelCollectionItem<Entity, ParentEntity, ParentItem>::slot_create()
{
    typedef typename renderer::EntityTraits<Entity> EntityTraits;

    const std::string window_title =
        std::string("Create ") +
        EntityTraits::get_human_readable_entity_type_name();

    const std::string name_suggestion =
        get_name_suggestion(
            EntityTraits::get_entity_type_name(),
            EntityTraits::get_entity_container(Base::m_parent));

    typedef typename EntityTraits::FactoryRegistrarType FactoryRegistrarType;

    std::auto_ptr<EntityEditorWindow::IFormFactory> form_factory(
        new MultiModelEntityEditorFormFactory<FactoryRegistrarType>(
            Base::m_project_builder.template get_factory_registrar<Entity>(),
            name_suggestion));

    std::auto_ptr<EntityEditorWindow::IEntityBrowser> entity_browser(
        new EntityBrowser<ParentEntity>(Base::m_parent));

    open_entity_editor(
        QTreeWidgetItem::treeWidget(),
        window_title,
        Base::m_project_builder.get_project(),
        form_factory,
        entity_browser,
        this,
        SLOT(slot_create_accepted(foundation::Dictionary)));
}

}       // namespace studio
}       // namespace appleseed

#endif  // !APPLESEED_STUDIO_MAINWINDOW_PROJECT_MULTIMODELCOLLECTIONITEM_H
