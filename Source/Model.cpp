/*
  ==============================================================================

    Model.cpp
    Created: 12 Mar 2024 6:27:51am
    Author:  dharvey

  ==============================================================================
*/

#include "Model.h"

template std::unordered_map<int, QuantaBlocks::SyncDenominatorChoice*> Enumeration<QuantaBlocks::SyncDenominatorChoice>::enum_map;

QuantaBlocks::SyncDenominatorChoice QuantaBlocks::SyncDenominatorChoice::C01{ 1, NAMEOF(SyncDenominatorChoice::C01),  "1",  1 };
QuantaBlocks::SyncDenominatorChoice QuantaBlocks::SyncDenominatorChoice::C02{ 2, NAMEOF(SyncDenominatorChoice::C02),  "2",  2 };
QuantaBlocks::SyncDenominatorChoice QuantaBlocks::SyncDenominatorChoice::C04{ 3, NAMEOF(SyncDenominatorChoice::C04),  "4",  4 };
QuantaBlocks::SyncDenominatorChoice QuantaBlocks::SyncDenominatorChoice::C08{ 4, NAMEOF(SyncDenominatorChoice::C08),  "8",  8 };
QuantaBlocks::SyncDenominatorChoice QuantaBlocks::SyncDenominatorChoice::C12{ 5, NAMEOF(SyncDenominatorChoice::C12), "12", 12 };
QuantaBlocks::SyncDenominatorChoice QuantaBlocks::SyncDenominatorChoice::C16{ 6, NAMEOF(SyncDenominatorChoice::C16), "16", 16 };
QuantaBlocks::SyncDenominatorChoice QuantaBlocks::SyncDenominatorChoice::C32{ 7, NAMEOF(SyncDenominatorChoice::C32), "32", 32 };

QuantaBlocks::SyncDenominatorChoice* QuantaBlocks::SyncDenominatorChoice::getByLabel(const juce::String& label)
{
    QuantaBlocks::SyncDenominatorChoice* ptr;
    try
    {
        for (auto choice_kvp : enum_map)
        {
            auto choice = choice_kvp.second;
            if (choice->label.compare(label) == 0)
            {
                return choice;
            }
        }
        throw std::exception("Matching label not found.");
    }
    catch (std::exception ex)
    {
        system("PAUSE"); // haha
    }
}

QuantaBlocks::SyncDenominatorChoice* QuantaBlocks::SyncDenominatorChoice::getByDenomintatorValue(const int& denominator_value)
{
    QuantaBlocks::SyncDenominatorChoice* ptr;
    try
    {
        for (auto choice_kvp : enum_map)
        {
            auto choice = choice_kvp.second;
            if (choice->denominator_value == denominator_value) // todo combine these and paramterize the predicate
            {
                return choice;
            }
        }
        throw std::exception("Matching denominator value not found.");
    }
    catch (std::exception ex)
    {
        system("PAUSE"); // haha
    }
}
