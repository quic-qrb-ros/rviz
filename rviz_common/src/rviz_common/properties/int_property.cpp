// Copyright (c) 2012, Willow Garage, Inc.
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


#include "rviz_common/properties/int_property.hpp"

#include <climits>  // for INT_MAX and INT_MIN

#include <QtGlobal>  // NOLINT: cpplint is unable to handle the include order here
#include <QSpinBox>  // NOLINT: cpplint is unable to handle the include order here
#include <QString>  // NOLINT: cpplint is unable to handle the include order here

namespace rviz_common
{
namespace properties
{

IntProperty::IntProperty(
  const QString & name,
  int default_value,
  const QString & description,
  Property * parent,
  const char * changed_slot,
  QObject * receiver,
  int min_value,
  int max_value)
: Property(name, default_value, description, parent, changed_slot, receiver),
  min_(min_value),
  max_(max_value)
{
}

bool IntProperty::setValue(const QVariant & new_value)
{
  return Property::setValue(qBound(min_, new_value.toInt(), max_));
}

int IntProperty::getInt() const
{
  return getValue().toInt();
}

void IntProperty::setMin(int min)
{
  min_ = min;
  setValue(getValue() );
}

int IntProperty::getMin()
{
  return min_;
}

void IntProperty::setMax(int max)
{
  max_ = max;
  setValue(getValue() );
}

int IntProperty::getMax()
{
  return max_;
}

QWidget * IntProperty::createEditor(QWidget * parent, const QStyleOptionViewItem & option)
{
  Q_UNUSED(option);
  QSpinBox * editor = new QSpinBox(parent);
  editor->setFrame(false);
  editor->setRange(min_, max_);
  connect(editor, SIGNAL(valueChanged(int)), this, SLOT(setInt(int)));
  return editor;
}

void IntProperty::setInt(int new_value)
{
  setValue(new_value);
}

}  // namespace properties
}  // namespace rviz_common
