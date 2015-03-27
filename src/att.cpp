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

// Converters for writing and reading


    
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

