// Copyright (c) 2012, Willow Garage, Inc.
// Copyright (c) 2017, Open Source Robotics Foundation, Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//    * Redistributions of source code must retain the above copyright
//      notice, this list of conditions and the following disclaimer.
//
//    * Redistributions in binary form must reproduce the above copyright
//      notice, this list of conditions and the following disclaimer in the
//      documentation and/or other materials provided with the distribution.
//
//    * Neither the name of the copyright holder nor the names of its
//      contributors may be used to endorse or promote products derived from
//      this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.


#include "rviz_common/properties/editable_enum_property.hpp"

#include <string>

#include <QCompleter>  // NOLINT: cpplint is unable to handle the include order here
#include <QString>  // NOLINT: cpplint is unable to handle the include order here

#include "rviz_common/properties/editable_combo_box.hpp"

namespace rviz_common
{
namespace properties
{

EditableEnumProperty::EditableEnumProperty(
  const QString & name,
  const QString & default_value,
  const QString & description,
  Property * parent,
  const char * changed_slot,
  QObject * receiver)
: StringProperty(name, default_value, description, parent, changed_slot, receiver)
{
}

void EditableEnumProperty::clearOptions()
{
  strings_.clear();
}

void EditableEnumProperty::addOption(const QString & option)
{
  strings_.push_back(option);
}

void EditableEnumProperty::addOptionStd(const std::string & option)
{
  addOption(QString::fromStdString(option));
}

QWidget * EditableEnumProperty::createEditor(QWidget * parent, const QStyleOptionViewItem & option)
{
  Q_UNUSED(option);

  // Emit requestOptions() to give listeners a chance to change the option list.
  Q_EMIT requestOptions(this);

  EditableComboBox * cb = new EditableComboBox(parent);
  cb->addItems(strings_);
  cb->setEditText(getValue().toString() );
  QObject::connect(
    cb, SIGNAL(currentIndexChanged(const QString&)), this,
    SLOT(setString(const QString&)));

  // TODO(unknown): need to better handle string value which is not in list.
  return cb;
}

void EditableEnumProperty::sortOptions()
{
  strings_.sort();
}

void EditableEnumProperty::setString(const QString & str)
{
  setValue(str);
}

}  // namespace properties
}  // namespace rviz_common
