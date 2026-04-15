#ifndef MENUITEM_H
#define MENUITEM_H

#include <QWidget>
#include <QString>
#include <QStringList>
#include <QLabel>
#include <QHBoxLayout>

class MenuItemBase: public QWidget
{
    Q_OBJECT
public:
    explicit MenuItemBase(const QString& l, QWidget* parent = nullptr);
    virtual void onRight(){};
    virtual void onLeft(){};
    void onHit() {emit activated();}
    virtual int getState() const {return 0;}
    void changeHighlighting(bool enable);

signals:
    void activated();

protected:
    QLabel* description;
    QHBoxLayout* layout;
};


class MenuItemInt final: public MenuItemBase{
    Q_OBJECT
public:
    explicit MenuItemInt(const QString& l, int c, QWidget* parent = nullptr);
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
    explicit MenuItemQStrList(const QString& l, const QStringList& c, QWidget* parent = nullptr);
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
