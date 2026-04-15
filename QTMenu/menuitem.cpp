#include "menuitem.h"
#include <QStyle>

MenuItemBase::MenuItemBase(const QString& l, QWidget* parent):
    QWidget(parent)
{
    layout = new QHBoxLayout(this);
    description = new QLabel(l, this);
    layout->addWidget(description);
    setLayout(layout);
}

void MenuItemBase::changeHighlighting(bool enable){
    setProperty("highlighted", enable);
    setStyle(nullptr); //forces redrawing, not sure if safe

    //OR: <<for each QLabel>>
    // style()->unpolish(description);
    // style()->polish(description);
}

MenuItemInt::MenuItemInt(const QString& l, int c, QWidget* parent):
    MenuItemBase(l, parent), content(c)
{
    contentlabel = new QLabel(QString::number(c));
    layout->addWidget(contentlabel);
    setLayout(layout);
}

void MenuItemInt::onRight(){
    content++;
    contentlabel->setText(QString::number(content));
}
void MenuItemInt::onLeft(){
    content--;
    contentlabel->setText(QString::number(content));
}

int MenuItemInt::getState() const {
    return content;
}



MenuItemQStrList::MenuItemQStrList(
    const QString& l, const QStringList& c, QWidget* parent):
    MenuItemBase(l, parent), content(c), index(0)
{
    assert (content.size() >0);
    contentlabel = new QLabel(content[index]);
    layout->addWidget(contentlabel);
}

void MenuItemQStrList::onRight(){
    index = (index + 1) % content.size();
    contentlabel->setText(content[index]);
}

void MenuItemQStrList::onLeft(){
    index = (index == 0) ? content.size() - 1 : index - 1;
    contentlabel->setText(content[index]);
}

int MenuItemQStrList::getState() const {
    assert (index < content.size() && index >=0);
    return index;
}
QString MenuItemQStrList::getString() const {
    assert (index < content.size() && index >=0);
    return content[index];
}
