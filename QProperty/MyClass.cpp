#include "MyClass.h"

MyClass::MyClass(QObject* parent)
    : QObject(parent)
    , m_visible(false)
{

}

MyClass::~MyClass()
{

}

void MyClass::setVisible(bool visible)
{
    if (visible == m_visible)
        return;
        
    m_visible = visible;
    emit visibleChanged(visible);
}

bool MyClass::getVisible() const
{
    return m_visible;
}
