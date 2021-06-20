#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "Gui/nitrogenrefrigoratorguimodel.h"

using namespace std;

int main(int argc, char *argv[])
{
  QGuiApplication app(argc, argv);

  NitrogenRefrigoratorGuiModel model;
  qmlRegisterType<NitrogenRefrigoratorGuiModel>("nitrogenRefrigerator.qmlcomponets", 1, 0, "NitrogenRefrigerator");

  QQmlApplicationEngine engine;

  QQmlContext* ctxt = engine.rootContext();
  ctxt->setContextProperty("nitrogenRefrigerator", &model);

  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


  return app.exec();
}
