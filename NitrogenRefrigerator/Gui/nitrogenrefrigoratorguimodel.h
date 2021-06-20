#ifndef NITROGENREFRIGORATORGUIMODEL_H
#define NITROGENREFRIGORATORGUIMODEL_H

#include <QObject>
#include <QQmlListProperty>

#include "CellContainer/cellcontainer.h"

class StackItem: public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString name READ getName NOTIFY nameChanged)
  Q_PROPERTY(unsigned index READ getIndex NOTIFY indexChanged)

public:
  explicit StackItem(QObject *parent = nullptr);

  QString  getName();
  unsigned getIndex();

  void setName(QString&& name);
  void setIndex(unsigned index);

signals:
   void nameChanged();
   void indexChanged();

private:
   QString _name;
   unsigned _index;
};

// ----------------------------------------------------------------------------

class NitrogenRefrigoratorGuiModel : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QQmlListProperty<StackItem> stacks READ getStacks NOTIFY stacksChanged)

public:
  explicit NitrogenRefrigoratorGuiModel(QObject *parent = nullptr);

   QQmlListProperty<StackItem> getStacks();

signals:
   void stacksChanged();

private:
   QList<StackItem*> _stacks;
   NitrogenRefrigoratorKernel::NitrogenRefrigorator _nitrogenRefirgerator;
};

#endif // NITROGENREFRIGORATORGUIMODEL_H
