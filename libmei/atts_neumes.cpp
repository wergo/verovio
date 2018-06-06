/////////////////////////////////////////////////////////////////////////////
// Authors:     Laurent Pugin and Rodolfo Zitellini
// Created:     2014
// Copyright (c) Authors and others. All rights reserved.
//
// Code generated using a modified version of libmei
// by Andrew Hankinson, Alastair Porter, and Others
/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// NOTE: this file was generated with the Verovio libmei version and
// should not be edited because changes will be lost.
/////////////////////////////////////////////////////////////////////////////

#include "atts_neumes.h"

//----------------------------------------------------------------------------

#include <assert.h>

//----------------------------------------------------------------------------

#include "object.h"

/* #include_block */

namespace vrv {

//----------------------------------------------------------------------------
// AttEpisemaVis
//----------------------------------------------------------------------------

AttEpisemaVis::AttEpisemaVis() : Att()
{
    ResetEpisemaVis();
}

AttEpisemaVis::~AttEpisemaVis()
{
}

void AttEpisemaVis::ResetEpisemaVis()
{
    m_form = episemaVis_FORM_NONE;
    m_place = COMPASSDIRECTION_NONE;
}

bool AttEpisemaVis::ReadEpisemaVis(pugi::xml_node element)
{
    bool hasAttribute = false;
    if (element.attribute("form")) {
        this->SetForm(StrToEpisemaVisForm(element.attribute("form").value()));
        element.remove_attribute("form");
        hasAttribute = true;
    }
    if (element.attribute("place")) {
        this->SetPlace(StrToCompassdirection(element.attribute("place").value()));
        element.remove_attribute("place");
        hasAttribute = true;
    }
    return hasAttribute;
}

bool AttEpisemaVis::WriteEpisemaVis(pugi::xml_node element)
{
    bool wroteAttribute = false;
    if (this->HasForm()) {
        element.append_attribute("form") = EpisemaVisFormToStr(this->GetForm()).c_str();
        wroteAttribute = true;
    }
    if (this->HasPlace()) {
        element.append_attribute("place") = CompassdirectionToStr(this->GetPlace()).c_str();
        wroteAttribute = true;
    }
    return wroteAttribute;
}

bool AttEpisemaVis::HasForm() const
{
    return (m_form != episemaVis_FORM_NONE);
}

bool AttEpisemaVis::HasPlace() const
{
    return (m_place != COMPASSDIRECTION_NONE);
}

/* include <attplace> */

//----------------------------------------------------------------------------
// AttHispanTickVis
//----------------------------------------------------------------------------

AttHispanTickVis::AttHispanTickVis() : Att()
{
    ResetHispanTickVis();
}

AttHispanTickVis::~AttHispanTickVis()
{
}

void AttHispanTickVis::ResetHispanTickVis()
{
    m_pointing = COMPASSDIRECTION_NONE;
    m_place = COMPASSDIRECTION_NONE;
}

bool AttHispanTickVis::ReadHispanTickVis(pugi::xml_node element)
{
    bool hasAttribute = false;
    if (element.attribute("pointing")) {
        this->SetPointing(StrToCompassdirection(element.attribute("pointing").value()));
        element.remove_attribute("pointing");
        hasAttribute = true;
    }
    if (element.attribute("place")) {
        this->SetPlace(StrToCompassdirection(element.attribute("place").value()));
        element.remove_attribute("place");
        hasAttribute = true;
    }
    return hasAttribute;
}

bool AttHispanTickVis::WriteHispanTickVis(pugi::xml_node element)
{
    bool wroteAttribute = false;
    if (this->HasPointing()) {
        element.append_attribute("pointing") = CompassdirectionToStr(this->GetPointing()).c_str();
        wroteAttribute = true;
    }
    if (this->HasPlace()) {
        element.append_attribute("place") = CompassdirectionToStr(this->GetPlace()).c_str();
        wroteAttribute = true;
    }
    return wroteAttribute;
}

bool AttHispanTickVis::HasPointing() const
{
    return (m_pointing != COMPASSDIRECTION_NONE);
}

bool AttHispanTickVis::HasPlace() const
{
    return (m_place != COMPASSDIRECTION_NONE);
}

/* include <attplace> */

//----------------------------------------------------------------------------
// AttNcLog
//----------------------------------------------------------------------------

AttNcLog::AttNcLog() : Att()
{
    ResetNcLog();
}

AttNcLog::~AttNcLog()
{
}

void AttNcLog::ResetNcLog()
{
    m_liques = BOOLEAN_NONE;
    m_oct = "";
    m_pname = "";
}

bool AttNcLog::ReadNcLog(pugi::xml_node element)
{
    bool hasAttribute = false;
    if (element.attribute("liques")) {
        this->SetLiques(StrToBoolean(element.attribute("liques").value()));
        element.remove_attribute("liques");
        hasAttribute = true;
    }
    if (element.attribute("oct")) {
        this->SetOct(StrToStr(element.attribute("oct").value()));
        element.remove_attribute("oct");
        hasAttribute = true;
    }
    if (element.attribute("pname")) {
        this->SetPname(StrToStr(element.attribute("pname").value()));
        element.remove_attribute("pname");
        hasAttribute = true;
    }
    return hasAttribute;
}

bool AttNcLog::WriteNcLog(pugi::xml_node element)
{
    bool wroteAttribute = false;
    if (this->HasLiques()) {
        element.append_attribute("liques") = BooleanToStr(this->GetLiques()).c_str();
        wroteAttribute = true;
    }
    if (this->HasOct()) {
        element.append_attribute("oct") = StrToStr(this->GetOct()).c_str();
        wroteAttribute = true;
    }
    if (this->HasPname()) {
        element.append_attribute("pname") = StrToStr(this->GetPname()).c_str();
        wroteAttribute = true;
    }
    return wroteAttribute;
}

bool AttNcLog::HasLiques() const
{
    return (m_liques != BOOLEAN_NONE);
}

bool AttNcLog::HasOct() const
{
    return (m_oct != "");
}

bool AttNcLog::HasPname() const
{
    return (m_pname != "");
}

/* include <attpname> */

//----------------------------------------------------------------------------
// AttNcForm
//----------------------------------------------------------------------------

AttNcForm::AttNcForm() : Att()
{
    ResetNcForm();
}

AttNcForm::~AttNcForm()
{
}

void AttNcForm::ResetNcForm()
{
    m_angled = BOOLEAN_NONE;
    m_con = ncForm_CON_NONE;
    m_curve = ncForm_CURVE_NONE;
    m_hooked = BOOLEAN_NONE;
    m_len = ncForm_LEN_NONE;
    m_sShape = "";
    m_tilt = COMPASSDIRECTION_NONE;
    m_waves = 0;
}

bool AttNcForm::ReadNcForm(pugi::xml_node element)
{
    bool hasAttribute = false;
    if (element.attribute("angled")) {
        this->SetAngled(StrToBoolean(element.attribute("angled").value()));
        element.remove_attribute("angled");
        hasAttribute = true;
    }
    if (element.attribute("con")) {
        this->SetCon(StrToNcFormCon(element.attribute("con").value()));
        element.remove_attribute("con");
        hasAttribute = true;
    }
    if (element.attribute("curve")) {
        this->SetCurve(StrToNcFormCurve(element.attribute("curve").value()));
        element.remove_attribute("curve");
        hasAttribute = true;
    }
    if (element.attribute("hooked")) {
        this->SetHooked(StrToBoolean(element.attribute("hooked").value()));
        element.remove_attribute("hooked");
        hasAttribute = true;
    }
    if (element.attribute("len")) {
        this->SetLen(StrToNcFormLen(element.attribute("len").value()));
        element.remove_attribute("len");
        hasAttribute = true;
    }
    if (element.attribute("sShape")) {
        this->SetSShape(StrToStr(element.attribute("sShape").value()));
        element.remove_attribute("sShape");
        hasAttribute = true;
    }
    if (element.attribute("tilt")) {
        this->SetTilt(StrToCompassdirection(element.attribute("tilt").value()));
        element.remove_attribute("tilt");
        hasAttribute = true;
    }
    if (element.attribute("waves")) {
        this->SetWaves(StrToInt(element.attribute("waves").value()));
        element.remove_attribute("waves");
        hasAttribute = true;
    }
    return hasAttribute;
}

bool AttNcForm::WriteNcForm(pugi::xml_node element)
{
    bool wroteAttribute = false;
    if (this->HasAngled()) {
        element.append_attribute("angled") = BooleanToStr(this->GetAngled()).c_str();
        wroteAttribute = true;
    }
    if (this->HasCon()) {
        element.append_attribute("con") = NcFormConToStr(this->GetCon()).c_str();
        wroteAttribute = true;
    }
    if (this->HasCurve()) {
        element.append_attribute("curve") = NcFormCurveToStr(this->GetCurve()).c_str();
        wroteAttribute = true;
    }
    if (this->HasHooked()) {
        element.append_attribute("hooked") = BooleanToStr(this->GetHooked()).c_str();
        wroteAttribute = true;
    }
    if (this->HasLen()) {
        element.append_attribute("len") = NcFormLenToStr(this->GetLen()).c_str();
        wroteAttribute = true;
    }
    if (this->HasSShape()) {
        element.append_attribute("sShape") = StrToStr(this->GetSShape()).c_str();
        wroteAttribute = true;
    }
    if (this->HasTilt()) {
        element.append_attribute("tilt") = CompassdirectionToStr(this->GetTilt()).c_str();
        wroteAttribute = true;
    }
    if (this->HasWaves()) {
        element.append_attribute("waves") = IntToStr(this->GetWaves()).c_str();
        wroteAttribute = true;
    }
    return wroteAttribute;
}

bool AttNcForm::HasAngled() const
{
    return (m_angled != BOOLEAN_NONE);
}

bool AttNcForm::HasCon() const
{
    return (m_con != ncForm_CON_NONE);
}

bool AttNcForm::HasCurve() const
{
    return (m_curve != ncForm_CURVE_NONE);
}

bool AttNcForm::HasHooked() const
{
    return (m_hooked != BOOLEAN_NONE);
}

bool AttNcForm::HasLen() const
{
    return (m_len != ncForm_LEN_NONE);
}

bool AttNcForm::HasSShape() const
{
    return (m_sShape != "");
}

bool AttNcForm::HasTilt() const
{
    return (m_tilt != COMPASSDIRECTION_NONE);
}

bool AttNcForm::HasWaves() const
{
    return (m_waves != 0);
}

/* include <attwaves> */

//----------------------------------------------------------------------------
// AttSignifLetVis
//----------------------------------------------------------------------------

AttSignifLetVis::AttSignifLetVis() : Att()
{
    ResetSignifLetVis();
}

AttSignifLetVis::~AttSignifLetVis()
{
}

void AttSignifLetVis::ResetSignifLetVis()
{
    m_place = COMPASSDIRECTION_NONE;
}

bool AttSignifLetVis::ReadSignifLetVis(pugi::xml_node element)
{
    bool hasAttribute = false;
    if (element.attribute("place")) {
        this->SetPlace(StrToCompassdirection(element.attribute("place").value()));
        element.remove_attribute("place");
        hasAttribute = true;
    }
    return hasAttribute;
}

bool AttSignifLetVis::WriteSignifLetVis(pugi::xml_node element)
{
    bool wroteAttribute = false;
    if (this->HasPlace()) {
        element.append_attribute("place") = CompassdirectionToStr(this->GetPlace()).c_str();
        wroteAttribute = true;
    }
    return wroteAttribute;
}

bool AttSignifLetVis::HasPlace() const
{
    return (m_place != COMPASSDIRECTION_NONE);
}

/* include <attplace> */

bool Att::SetNeumes(Object *element, std::string attrType, std::string attrValue)
{
    if (element->HasAttClass(ATT_EPISEMAVIS)) {
        AttEpisemaVis *att = dynamic_cast<AttEpisemaVis *>(element);
        assert(att);
        if (attrType == "form") {
            att->SetForm(att->StrToEpisemaVisForm(attrValue));
            return true;
        }
        if (attrType == "place") {
            att->SetPlace(att->StrToCompassdirection(attrValue));
            return true;
        }
    }
    if (element->HasAttClass(ATT_HISPANTICKVIS)) {
        AttHispanTickVis *att = dynamic_cast<AttHispanTickVis *>(element);
        assert(att);
        if (attrType == "pointing") {
            att->SetPointing(att->StrToCompassdirection(attrValue));
            return true;
        }
        if (attrType == "place") {
            att->SetPlace(att->StrToCompassdirection(attrValue));
            return true;
        }
    }
    if (element->HasAttClass(ATT_NCLOG)) {
        AttNcLog *att = dynamic_cast<AttNcLog *>(element);
        assert(att);
        if (attrType == "liques") {
            att->SetLiques(att->StrToBoolean(attrValue));
            return true;
        }
        if (attrType == "oct") {
            att->SetOct(att->StrToStr(attrValue));
            return true;
        }
        if (attrType == "pname") {
            att->SetPname(att->StrToStr(attrValue));
            return true;
        }
    }
    if (element->HasAttClass(ATT_NCFORM)) {
        AttNcForm *att = dynamic_cast<AttNcForm *>(element);
        assert(att);
        if (attrType == "angled") {
            att->SetAngled(att->StrToBoolean(attrValue));
            return true;
        }
        if (attrType == "con") {
            att->SetCon(att->StrToNcFormCon(attrValue));
            return true;
        }
        if (attrType == "curve") {
            att->SetCurve(att->StrToNcFormCurve(attrValue));
            return true;
        }
        if (attrType == "hooked") {
            att->SetHooked(att->StrToBoolean(attrValue));
            return true;
        }
        if (attrType == "len") {
            att->SetLen(att->StrToNcFormLen(attrValue));
            return true;
        }
        if (attrType == "sShape") {
            att->SetSShape(att->StrToStr(attrValue));
            return true;
        }
        if (attrType == "tilt") {
            att->SetTilt(att->StrToCompassdirection(attrValue));
            return true;
        }
        if (attrType == "waves") {
            att->SetWaves(att->StrToInt(attrValue));
            return true;
        }
    }
    if (element->HasAttClass(ATT_SIGNIFLETVIS)) {
        AttSignifLetVis *att = dynamic_cast<AttSignifLetVis *>(element);
        assert(att);
        if (attrType == "place") {
            att->SetPlace(att->StrToCompassdirection(attrValue));
            return true;
        }
    }

    return false;
}

void Att::GetNeumes(const Object *element, ArrayOfStrAttr *attributes)
{
    if (element->HasAttClass(ATT_EPISEMAVIS)) {
        const AttEpisemaVis *att = dynamic_cast<const AttEpisemaVis *>(element);
        assert(att);
        if (att->HasForm()) {
            attributes->push_back(std::make_pair("form", att->EpisemaVisFormToStr(att->GetForm())));
        }
        if (att->HasPlace()) {
            attributes->push_back(std::make_pair("place", att->CompassdirectionToStr(att->GetPlace())));
        }
    }
    if (element->HasAttClass(ATT_HISPANTICKVIS)) {
        const AttHispanTickVis *att = dynamic_cast<const AttHispanTickVis *>(element);
        assert(att);
        if (att->HasPointing()) {
            attributes->push_back(std::make_pair("pointing", att->CompassdirectionToStr(att->GetPointing())));
        }
        if (att->HasPlace()) {
            attributes->push_back(std::make_pair("place", att->CompassdirectionToStr(att->GetPlace())));
        }
    }
    if (element->HasAttClass(ATT_NCLOG)) {
        const AttNcLog *att = dynamic_cast<const AttNcLog *>(element);
        assert(att);
        if (att->HasLiques()) {
            attributes->push_back(std::make_pair("liques", att->BooleanToStr(att->GetLiques())));
        }
        if (att->HasOct()) {
            attributes->push_back(std::make_pair("oct", att->StrToStr(att->GetOct())));
        }
        if (att->HasPname()) {
            attributes->push_back(std::make_pair("pname", att->StrToStr(att->GetPname())));
        }
    }
    if (element->HasAttClass(ATT_NCFORM)) {
        const AttNcForm *att = dynamic_cast<const AttNcForm *>(element);
        assert(att);
        if (att->HasAngled()) {
            attributes->push_back(std::make_pair("angled", att->BooleanToStr(att->GetAngled())));
        }
        if (att->HasCon()) {
            attributes->push_back(std::make_pair("con", att->NcFormConToStr(att->GetCon())));
        }
        if (att->HasCurve()) {
            attributes->push_back(std::make_pair("curve", att->NcFormCurveToStr(att->GetCurve())));
        }
        if (att->HasHooked()) {
            attributes->push_back(std::make_pair("hooked", att->BooleanToStr(att->GetHooked())));
        }
        if (att->HasLen()) {
            attributes->push_back(std::make_pair("len", att->NcFormLenToStr(att->GetLen())));
        }
        if (att->HasSShape()) {
            attributes->push_back(std::make_pair("sShape", att->StrToStr(att->GetSShape())));
        }
        if (att->HasTilt()) {
            attributes->push_back(std::make_pair("tilt", att->CompassdirectionToStr(att->GetTilt())));
        }
        if (att->HasWaves()) {
            attributes->push_back(std::make_pair("waves", att->IntToStr(att->GetWaves())));
        }
    }
    if (element->HasAttClass(ATT_SIGNIFLETVIS)) {
        const AttSignifLetVis *att = dynamic_cast<const AttSignifLetVis *>(element);
        assert(att);
        if (att->HasPlace()) {
            attributes->push_back(std::make_pair("place", att->CompassdirectionToStr(att->GetPlace())));
        }
    }
}

} // vrv namespace
