//
//  CheckBox.cpp
//  IkasGame
//
//  Created by Mikel Eizagirre on 2014-03-20.
//
//


#include "CheckBox.h"

CheckBox::~CheckBox()
{
    
}

CheckBox* CheckBox::create(std::string onString, std::string offString, bool isOn, const ccMenuCallback& callback)
{
    CheckBox *ret = new CheckBox();
    ret->initWithString(onString, offString, isOn, callback);
    ret->autorelease();
    return ret;
}

bool CheckBox::initWithString(std::string onString, std::string offString, bool isOn, const ccMenuCallback& callback)
{
    _onString = onString;
    _offString = offString;
    _on = isOn;
    Label *label = Label::createWithSystemFont(_on ? _onString : _offString, "", 30);
    
    MenuItemLabel::initWithLabel(label, callback);
    return true;
}

void CheckBox::activate()
{
    _on = !_on;
    this->setString(_on ? _onString : _offString);
    MenuItem::activate();
}