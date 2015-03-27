/////////////////////////////////////////////////////////////////////////////
// Name:        att.cpp
// Author:      Laurent Pugin
// Created:     2014
// Copyright (c) Laurent Pugin. All rights reserved.
/////////////////////////////////////////////////////////////////////////////


#include "att.h"

//----------------------------------------------------------------------------

#include <stdlib.h>

//----------------------------------------------------------------------------

#include "object.h"
#include "vrv.h"

namespace vrv {

//----------------------------------------------------------------------------
// Att
//----------------------------------------------------------------------------

Att::Att()
{
}

Att::~Att()
{
}
        
std::string Att::StrToStr(std::string str)
{
    return str;
}

// Basic converters for writing    

std::string Att::DblToStr(double data)
{
    return StringFormat("%f", data);
}
    
std::string Att::IntToStr(int data)
{
    return StringFormat("%d", data);
}
    
// Basic converters for reading

double Att::StrToDbl(std::string value)
{
    return atof( value.c_str() );
}
int Att::StrToInt(std::string value)
{
    return atoi( value.c_str() );
}

// Converters for writing and reading not generated from the ODD (see ./libmei/att_converters)
    
std::string Att::DurToStr(data_DURATION data)
{
    std::string value;
    if (data == DURATION_maxima) value = "maxima";
    else if (data == DURATION_longa) value = "longa";
    else if (data == DURATION_brevis) value = "brevis";
    else if (data == DURATION_semibrevis) value = "semibrevis";
    else if (data == DURATION_minima) value = "minima";
    else if (data == DURATION_semiminima) value = "semiminima";
    else if (data == DURATION_fusa) value = "fusa";
    else if (data == DURATION_semifusa) value = "semifusa";
    else if (data == DURATION_long) value = "long";
    else if (data == DURATION_breve) value = "breve";
    else if (data == DURATION_1) value = "1";
    else if (data == DURATION_2) value = "2";
    else if (data == DURATION_4) value = "4";
    else if (data == DURATION_8) value = "8";
    else if (data == DURATION_16) value = "16";
    else if (data == DURATION_32) value = "32";
    else if (data == DURATION_64) value = "64";
    else if (data == DURATION_128) value = "128";
    else if (data == DURATION_256) value = "256";
    else {
        LogWarning("Unknown duration '%d'", data);
        value = "4";
    }
    return value;
}

data_DURATION Att::StrToDur(std::string value)
{
    data_DURATION dur;
    if (value == "maxima") dur = DURATION_maxima;
    else if (value == "longa") dur = DURATION_longa;
    else if (value == "brevis") dur = DURATION_brevis;
    else if (value == "semibrevis") dur = DURATION_semibrevis;
    else if (value == "minima") dur = DURATION_minima;
    else if (value == "semiminima") dur = DURATION_semiminima;
    else if (value == "fusa") dur = DURATION_fusa;
    else if (value == "semifusa") dur = DURATION_semifusa;
    else if (value == "long") dur = DURATION_long;
    else if (value == "breve") dur = DURATION_breve;
    else if (value == "1") dur = DURATION_1;
    else if (value == "2") dur = DURATION_2;
    else if (value == "4") dur = DURATION_4;
    else if (value == "8") dur = DURATION_8;
    else if (value == "16") dur = DURATION_16;
    else if (value == "32") dur = DURATION_32;
    else if (value == "64") dur = DURATION_64;
    else if (value == "128") dur = DURATION_128;
    else if (value == "256") dur = DURATION_256;
    else {
        if ((value.length() > 0) && (value[value.length()-1] == 'p')) {
            LogWarning("PPQ duration dur_s are not supported");
        }
        else {
            LogWarning("Unknown @dur dur '%s'", value.c_str());
        }
        dur = DURATION_NONE;
    }
    return dur;
}
    
//----------------------------------------------------------------------------
// AttComparison
//----------------------------------------------------------------------------

bool AttComparison::operator()(Object *object)
{
    if  (typeid(*object) == *m_elementType) {
        return true;
    }
    return false;
}
    
bool AttComparison::MatchesType(Object *object)
{
    if  (typeid(*object) == *m_elementType) {
        return true;
    }
    return false;
}
    
} // namespace vrv

