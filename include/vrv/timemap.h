/////////////////////////////////////////////////////////////////////////////
// Name:        timemap.h
// Author:      Craig Stuart Sapp
// Created:     11/01/2017
// Copyright (c) Authors and others. All rights reserved.
/////////////////////////////////////////////////////////////////////////////

#ifndef __VRV_TIMEMAP_H__
#define __VRV_TIMEMAP_H__

#include <set>

#include "RationalNumber.h"
#include "doc.h"
#include "jsonxx.h"

namespace vrv {

class TimemapEntry {
public:
    TimemapEntry(RationalNumber qtime);
    RationalNumber qstamp; // score time in quarter notes
    double tstamp; // real time in seconds (if non-negative)
    double tempo; // quarter notes per minute (if greater than 0)
    set<string> on; // list of elements to turn on
    set<string> off; // list of elements to turn off

    void StoreIn(jsonxx::Object &obj);
    void mergeEntry(TimemapEntry *entry);
    void mergeEntry(TimemapEntry &entry);
};

struct StampCompare {
    bool operator()(TimemapEntry *const tme1, const TimemapEntry *tme2) { return tme1->qstamp < tme2->qstamp; }
    bool operator()(const RationalNumber &rn, TimemapEntry *const tme) { return rn < tme->qstamp; }
    bool operator()(TimemapEntry *const tme, const RationalNumber &rn) { return tme->qstamp < rn; }
};

typedef set<TimemapEntry *, StampCompare> TimemapSet;

class Timemap : protected TimemapSet {
public:
    Timemap(void);
    ~Timemap();
    int GetEntryCount(void) { return this->size(); }
    TimemapSet::iterator GetBeginIt(void) { return this->begin(); }
    TimemapSet::iterator GetEndIt(void) { return this->end(); }
    RationalNumber GetLastQStamp(void);
    TimemapEntry *GetByQTime(RationalNumber qtime);
    void StoreIn(jsonxx::Array &array);
};

void QueryObjectNoChildren(vector<Object *> &objs, Object *obj, const string &query);
RationalNumber GetDuration(Object *obj, RationalNumber scaling = 1);
string CreateTimemapJson(Doc &doc);
RationalNumber GetMeasureTimemap(Timemap &measureTimemap, Object *measure, RationalNumber offset);
RationalNumber AddChildrenToTimemap(
    Timemap &timemap, Object *object, RationalNumber offset = 0, RationalNumber scaling = 1);
void InsertNoteChildrenIds(set<string> &ids, Object *obj);

} // namespace vrv

#endif
