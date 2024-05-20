/**
 * @file selector.cpp
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-05-20
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "selelctor.h"

using namespace SmoothUIToolKit::Widgets::Selector;

void SelectorBase::enter(WidgetBase* widget)
{
    if (widget == nullptr)
        return;
    _selector_base_data.current_widget = widget;
}

bool SelectorBase::back()
{
    if (_selector_base_data.current_widget->isRoot())
        return false;
    _selector_base_data.current_widget = _selector_base_data.current_widget->getParent();
    return true;
}

void SelectorBase::goLast()
{
    if (getOptionNum() <= 0)
        return;

    int new_index = _selector_base_data.selected_option_index - 1;
    if (new_index < 0)
        new_index = _selector_base_data.move_in_loop ? getOptionNum() - 1 : 0;

    goTo(new_index);
    onGoLast();
}

void SelectorBase::goNext()
{
    if (getOptionNum() <= 0)
        return;

    int new_index = _selector_base_data.selected_option_index + 1;
    if (new_index >= getOptionNum())
        new_index = _selector_base_data.move_in_loop ? 0 : getOptionNum() - 1;

    goTo(new_index);
    onGoNext();
}

void SelectorBase::goTo(int optionIndex)
{
    if (getOptionNum() <= 0)
        return;
    if (optionIndex < 0 || optionIndex > (getOptionNum() - 1))
        return;

    _selector_base_data.selected_option_index = optionIndex;
    onGoTo();
}
