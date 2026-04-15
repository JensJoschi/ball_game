#ifndef MENUITEM_H
#define MENUITEM_H

#include <QWidget>
#include <QString>
#include <QStringList>
#include <QLabel>
#include <QHBoxLayout>

#include "helpers.h"

class MenuItemBase: public QWidget
{
    Q_OBJECT
public:
    explicit MenuItemBase(const QString& l, Menus a = Menus::none, QWidget* parent = nullptr);
    virtual void onRight(){};
    virtual void onLeft(){};
    void onHit() {emit openMenu(static_cast<int> (action));}
    virtual int getState() const {return 0;}
    void changeHighlighting(bool enable);

signals:
    int openMenu(int id);

protected:
    QLabel* description;
    QHBoxLayout* layout;
    Menus action;
};


class MenuItemInt final: public MenuItemBase{
    Q_OBJECT
public:
    explicit MenuItemInt(const QString& l, int c, Menus a = Menus::none, QWidget* parent = nullptr);
    void onRight() override;
    void onLeft()  override;
    int getState() const override;
private:
    int content;
    QLabel* contentlabel;
};

class MenuItemQStrList final: public MenuItemBase{
    Q_OBJECT
public:
    explicit MenuItemQStrList(const QString& l, const QStringList& c, Menus a = Menus::none, QWidget* parent = nullptr);
    void onRight() override;
    void onLeft()  override;
    int getState() const override;

    QString getString() const; //likely not needed
private:
    QStringList content;
    QLabel* contentlabel;
    int index = 0;
};


#endif // MENUITEM_H
