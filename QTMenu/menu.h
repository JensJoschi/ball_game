#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QStringList>
#include <QLabel>

#include "menuitem.h"
QT_BEGIN_NAMESPACE
class Menu;
QT_END_NAMESPACE

class Menu : public QWidget
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    void addItems(const std::vector<MenuItemBase*>&);
    std::vector<int> getStates() const;
    void onUp(); //cycle through items.
    void onDown();
    void keyPressEvent(QKeyEvent* event) override;
private:
    int highlighted = 0;
    std::vector<MenuItemBase*> items;
};
#endif // MENU_H
