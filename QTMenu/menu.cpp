#include "menu.h"
#include <QStringList>
#include <QLabel>
#include <QVBoxLayout>
#include <QEvent>
#include <QKeyEvent>
#include "menuitem.h"

Menu::Menu(const std::vector<MenuItemBase*>& itms, QWidget *parent)
    : QWidget(parent), highlighted(0)
{
    setWindowTitle(tr("Menu"));
    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);

    QVBoxLayout* layout = new QVBoxLayout(this);
    for (const auto& content:itms){
        items.push_back(content);
        layout->addWidget(content);
    }
    setLayout(layout);

    items[0]->changeHighlighting(true);
}

void Menu::keyPressEvent(QKeyEvent* event){
    switch (event->key()) {
    case Qt::Key_Up: onUp(); break;
    case Qt::Key_Down: onDown(); break;
    case Qt::Key_Left: items[highlighted]->onLeft(); break;
    case Qt::Key_Right: items[highlighted]->onRight(); break;
    case Qt::Key_Enter: items[highlighted]->onHit(); break;
    default: QWidget::keyPressEvent(event);
    }
}

void Menu::onUp(){
    items[highlighted]->changeHighlighting(false);
    highlighted--;
    if (highlighted<0) highlighted = items.size() -1;
    items[highlighted]->changeHighlighting(true);
    update();
}

void Menu::onDown(){
    items[highlighted]->changeHighlighting(false);
    highlighted++;
    if(highlighted == static_cast<int>(items.size())) highlighted = 0;
    items[highlighted]->changeHighlighting(true);
    update();
}

std::vector<int> Menu::getStates() const{
    std::vector<int> result;
    result.reserve(items.size());
    for (auto* item : items)
        result.push_back(item->getState());
    return result;
}
