#include "nitrogenrefrigoratorguimodel.h"

using namespace NitrogenRefrigoratorKernel;

StackItem::StackItem(QObject *parent): QObject(parent)
{

}

QString StackItem::getName()
{
  return _name;
}

unsigned StackItem::getIndex()
{
  return _index;
}

void StackItem::setName(QString &&name)
{
  _name = std::move(name);
}

void StackItem::setIndex(unsigned index)
{
  _index = index;
}

// ----------------------------------------------------------------------------

NitrogenRefrigoratorGuiModel::NitrogenRefrigoratorGuiModel(QObject *parent) : QObject(parent)
{
  _stacks.push_back(new StackItem());
  _stacks.push_back(new StackItem());
  _stacks.push_back(new StackItem());
  _stacks.push_back(new StackItem());
}

QQmlListProperty<StackItem> NitrogenRefrigoratorGuiModel::getStacks()
{
return QQmlListProperty<StackItem>(this, &_stacks);
}

