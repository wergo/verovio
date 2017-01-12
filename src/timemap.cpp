/////////////////////////////////////////////////////////////////////////////
// Name:        timemap.cpp
// Author:      Craig Stuart Sapp
// Created:     11/01/2017
// Copyright (c) Authors and others. All rights reserved.
/////////////////////////////////////////////////////////////////////////////

#include "timemap.h"

//----------------------------------------------------------------------------

#include <algorithm>
#include <cmath>
#include <string>

//----------------------------------------------------------------------------

#include "json/jsonxx.h"

namespace vrv {

//----------------------------------------------------------------------------
// TimemapEntry
//----------------------------------------------------------------------------

TimemapEntry::TimemapEntry(RationalNumber qtime)
{
    qstamp = qtime;
    tstamp = -1;
    tempo = 0.0;
}

void TimemapEntry::StoreIn(jsonxx::Object &obj)
{
    // double printing in jsonxx doesn't round nicely so storing as string.
    // stringstream ss;
    // ss.unsetf(ios::floatfield);
    // ss.precision(12);
    // ss << qstamp.getFloat();
    string qstring = to_string(qstamp.getNumerator());
    if (qstamp.getDenominator() > 1) {
        qstring += "," + to_string(qstamp.getDenominator());
    }
    obj << "qstamp" << qstring;
    obj << "tstamp" << int(tstamp * 1000.0 + 0.5);
    if (tempo > 0) {
        obj << "tempo" << tempo;
    }
    if (!on.empty()) {
        jsonxx::Array onids;
        for (auto id : on) {
            onids << id;
        }
        obj << "on" << onids;
    }
    if (!off.empty()) {
        jsonxx::Array offids;
        for (auto id : off) {
            offids << id;
        }
        obj << "off" << offids;
    }
}

void TimemapEntry::mergeEntry(TimemapEntry *entry)
{
    mergeEntry(*entry);
}

void TimemapEntry::mergeEntry(TimemapEntry &entry)
{
    if (!entry.on.empty()) {
        for (string id : entry.on) {
            on.insert(id);
        }
    }
    if (!entry.off.empty()) {
        for (string id : entry.off) {
            off.insert(id);
        }
    }
}

//----------------------------------------------------------------------------
// Timemap
//----------------------------------------------------------------------------

Timemap::Timemap(void)
{
}

Timemap::~Timemap()
{
    for (auto it = this->begin(), e = this->end(); it != e;) {
        TimemapEntry *tme = *it;
        this->erase(it++);
        delete tme;
    }
}

TimemapEntry *Timemap::GetByQTime(RationalNumber qtime)
{
    TimemapEntry tm(qtime);
    auto it = this->lower_bound(&tm);
    if ((it == this->end()) || ((*it)->qstamp != qtime)) {
        // create a new entry;
        TimemapEntry *tme = new TimemapEntry(qtime);
        this->insert(it, tme);
        return tme;
    }
    else {
        // found entry:
        return *it;
    }
}

void Timemap::StoreIn(jsonxx::Array &array)
{
    jsonxx::Object obj;
    for (auto it : *this) {
        obj.reset();
        it->StoreIn(obj);
        array << obj;
    }
}

RationalNumber Timemap::GetLastQStamp(void)
{
    if (this->empty()) {
        return 0;
    }
    auto it = this->end();
    it--;
    return (*it)->qstamp;
}

//----------------------------------------------------------------------------
// Static functions
//----------------------------------------------------------------------------

void _printIndent(int level, string indent, ostream &out)
{
    for (int i = 0; i < level; i++) {
        out << indent;
    }
}

void _printTree(int level, Object *obj, ostream &out)
{
    _printIndent(level, "  ", out);
    out << obj->GetClassName();
    out << endl;
    int childcount = obj->GetChildCount();
    for (int i = 0; i < childcount; i++) {
        _printTree(level + 1, obj->GetChild(i), out);
    }
}

void QueryObjectNoChildren(vector<Object *> &objs, Object *obj, const string &query)
{
    if (obj->GetClassName() == query) {
        objs.push_back(obj);
        return;
    }
    for (int i = 0; i < obj->GetChildCount(); i++) {
        QueryObjectNoChildren(objs, obj->GetChild(i), query);
    }
}

string CreateTimemapJson(Doc &doc)
{
    //_printTree(0, &doc, cout);
    // cout << "\n\n\n";

    double startingTempo = 120.0;
    if (doc.m_scoreDef.HasMidiBpm()) {
        startingTempo = doc.m_scoreDef.GetMidiBpm();
    }

    vector<Object *> measures;
    measures.reserve(1000);
    QueryObjectNoChildren(measures, &doc, "Measure");
    vector<Timemap> measureTimemaps(measures.size());
    RationalNumber currentTime = 0;
    RationalNumber duration;
    int entrycount = 0;
    for (int i = 0; i < (int)measures.size(); i++) {
        duration = GetMeasureTimemap(measureTimemaps[i], measures[i], currentTime);
        // cerr << "Measure " << i << " qduration = " << duration << endl;
        currentTime += duration;
        entrycount += measureTimemaps[i].GetEntryCount();
    }
    // cerr << "TOTAL QDURATION " << currentTime << endl;

    vector<TimemapEntry *> allmap;
    allmap.reserve(entrycount);
    for (int i = 0; i < (int)measures.size(); i++) {
        for (auto it = measureTimemaps[i].GetBeginIt(); it != measureTimemaps[i].GetEndIt(); it++) {
            if ((!allmap.empty()) && allmap.back()->qstamp == (*it)->qstamp) {
                allmap.back()->mergeEntry(*it);
                continue;
            }
            allmap.push_back(*it);
        }
    }

    if (!allmap.empty()) {
        allmap[0]->tempo = startingTempo;
    }

    // calculate tstamps
    double currentTimeInSec = 0.0;
    double currentTempo = startingTempo;
    for (int i = 0; i < (int)allmap.size(); i++) {
        if (allmap[i]->tempo > 0.0) {
            currentTempo = allmap[i]->tempo;
        }
        allmap[i]->tstamp = currentTimeInSec;
        if (i < (int)allmap.size() - 1) {
            duration = allmap[i + 1]->qstamp - allmap[i]->qstamp;
            currentTimeInSec += duration.getFloat() * 60.0 / currentTempo;
        }
    }

    jsonxx::Object object;
    jsonxx::Array array;
    for (int i = 0; i < allmap.size(); i++) {
        allmap[i]->StoreIn(object);
        array << object;
        object.reset();
    }
    return array.json();
}

RationalNumber GetMeasureTimemap(Timemap &measureTimemap, Object *measure, RationalNumber offset)
{
    vector<Object *> layers;
    QueryObjectNoChildren(layers, measure, "Layer");
    for (int i = 0; i < (int)layers.size(); i++) {
        AddChildrenToTimemap(measureTimemap, layers[i], offset);
    }
    RationalNumber endtime = measureTimemap.GetLastQStamp();
    if (endtime == 0) {
        return 0;
    }
    return endtime - offset;
}

RationalNumber GetDuration(Object *obj, RationalNumber scaling)
{
    RationalNumber output;
    ArrayOfStrAttr attlist;
    obj->GetAttributes(&attlist);
    int durindex = -1;
    int dotindex = -1;
    int graceindex = -1;
    for (int i = 0; i < (int)attlist.size(); i++) {
        if (attlist[i].first == "dur") {
            durindex = i;
        }
        else if (attlist[i].first == "dots") {
            dotindex = i;
        }
        else if (attlist[i].first == "grace") {
            graceindex = i;
        }
    }
    if (graceindex >= 0) {
        return 0;
    }
    if (durindex < 0) {
        return 0;
    }
    if (attlist[durindex].second == "maxima") {
        output = 8;
    }
    else if (attlist[durindex].second == "breve") {
        output = 2;
    }
    else if (attlist[durindex].second == "long") {
        output = 4;
    }
    else if (attlist[durindex].second.size() > 0) {
        int dur = stoi(attlist[durindex].second);
        output = 1;
        output /= dur;
    }
    else {
        return 0;
    }
    if (dotindex >= 0) {
        if (attlist[dotindex].second.size() > 0) {
            int dots = stoi(attlist[dotindex].second);
            if (dots > 0) {
                output *= pow(2, dots + 1) - 1;
                output /= pow(2, dots);
            }
        }
    }
    output *= scaling;
    return output * 4; // convert to quarter notes.
}

RationalNumber AddChildrenToTimemap(Timemap &timemap, Object *object, RationalNumber offset, RationalNumber scaling)
{
    RationalNumber currentTime = offset;
    int childcount = object->GetChildCount();
    string className;
    TimemapEntry *tme;
    string xmlid;
    RationalNumber duration;
    Object *child;
    for (int i = 0; i < childcount; i++) {
        child = object->GetChild(i);
        className = child->GetClassName();
        if (className == "Note") {
            duration = GetDuration(child, scaling);
            // cerr << "Note DURATION = " << duration << endl;
            if (duration == 0) {
                // ignoring grace notes
                continue;
            }
            xmlid = child->GetUuid();
            tme = timemap.GetByQTime(currentTime);
            tme->on.insert(xmlid);
            currentTime += duration;
            tme = timemap.GetByQTime(currentTime);
            tme->off.insert(xmlid);
        }
        else if ((className == "Rest") || (className == "Space")) {
            duration = GetDuration(child, scaling);
            // cerr << "Rest DURATION = " << duration << endl;
            currentTime += duration;
        }
        else if (className == "Chord") {
            duration = GetDuration(child, scaling);
            // cerr << "Chord DURATION = " << duration << endl;
            if (duration == 0) {
                // ignoring grace note chords
                continue;
            }
            // Could insert ID of chord:
            // xmlid = child->GetUuid();
            tme = timemap.GetByQTime(currentTime);
            InsertNoteChildrenIds(tme->on, child);
            currentTime += duration;
            tme = timemap.GetByQTime(currentTime);
            InsertNoteChildrenIds(tme->off, child);
        }
        else if (className == "Beam") {
            duration = AddChildrenToTimemap(timemap, child, currentTime, scaling);
            // cerr << "Beam DURATION = " << duration << endl;
            currentTime += duration;
        }
        else if (className == "Tuplet") {
            ArrayOfStrAttr attlist;
            child->GetAttributes(&attlist);
            int numbaseindex = -1;
            int numindex = -1;
            for (int j = 0; j < attlist.size(); j++) {
                if (attlist[j].first == "numbase") {
                    numbaseindex = j;
                }
                else if (attlist[j].first == "num") {
                    numindex = j;
                }
            }
            RationalNumber tupletscaling = 1;
            if ((numbaseindex >= 0) && (numindex >= 0)) {
                tupletscaling *= stoi(attlist[numbaseindex].second);
                tupletscaling /= stoi(attlist[numindex].second);
            }
            duration = AddChildrenToTimemap(timemap, child, currentTime, scaling * tupletscaling);
            // cerr << "Tuplet DURATION = " << duration << endl;
            currentTime += duration;
        }
        // deal with other items here
        // mRest multiRest will need to be processed here (based on prevailing time signature)
    }
    return currentTime - offset;
}

void InsertNoteChildrenIds(set<string> &ids, Object *obj)
{
    int childcount = obj->GetChildCount();
    for (int i = 0; i < childcount; i++) {
        if (obj->GetChild(i)->GetClassName() != "Note") {
            continue;
        }
        ids.insert(obj->GetChild(i)->GetUuid());
    }
}

} // namespace vrv
