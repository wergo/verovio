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

#ifndef __VRV_ATTS_NEUMES_H__
#define __VRV_ATTS_NEUMES_H__

#include "att.h"
#include "attdef.h"
#include "pugixml.hpp"

//----------------------------------------------------------------------------

#include <string>

namespace vrv {

//----------------------------------------------------------------------------
// AttEpisemaVis
//----------------------------------------------------------------------------

class AttEpisemaVis : public Att {
public:
    AttEpisemaVis();
    virtual ~AttEpisemaVis();

    /** Reset the default values for the attribute class **/
    void ResetEpisemaVis();

    /** Read the values for the attribute class **/
    bool ReadEpisemaVis(pugi::xml_node element);

    /** Write the values for the attribute class **/
    bool WriteEpisemaVis(pugi::xml_node element);

    /**
     * @name Setters, getters and presence checker for class members.
     * The checker returns true if the attribute class is set (e.g., not equal
     * to the default value)
     **/
    ///@{
    void SetForm(episemaVis_FORM form_) { m_form = form_; }
    episemaVis_FORM GetForm() const { return m_form; }
    bool HasForm() const;
    //
    void SetPlace(data_COMPASSDIRECTION place_) { m_place = place_; }
    data_COMPASSDIRECTION GetPlace() const { return m_place; }
    bool HasPlace() const;
    ///@}

private:
    /** Indicates to what degree the harmonic label is supported by the notation. **/
    episemaVis_FORM m_form;
    /** Records the placement of the beam relative to the events it affects. **/
    data_COMPASSDIRECTION m_place;

    /* include <attplace> */
};

//----------------------------------------------------------------------------
// AttHispanTickVis
//----------------------------------------------------------------------------

class AttHispanTickVis : public Att {
public:
    AttHispanTickVis();
    virtual ~AttHispanTickVis();

    /** Reset the default values for the attribute class **/
    void ResetHispanTickVis();

    /** Read the values for the attribute class **/
    bool ReadHispanTickVis(pugi::xml_node element);

    /** Write the values for the attribute class **/
    bool WriteHispanTickVis(pugi::xml_node element);

    /**
     * @name Setters, getters and presence checker for class members.
     * The checker returns true if the attribute class is set (e.g., not equal
     * to the default value)
     **/
    ///@{
    void SetPointing(data_COMPASSDIRECTION pointing_) { m_pointing = pointing_; }
    data_COMPASSDIRECTION GetPointing() const { return m_pointing; }
    bool HasPointing() const;
    //
    void SetPlace(data_COMPASSDIRECTION place_) { m_place = place_; }
    data_COMPASSDIRECTION GetPlace() const { return m_place; }
    bool HasPlace() const;
    ///@}

private:
    /** Direction toward which the mark points. **/
    data_COMPASSDIRECTION m_pointing;
    /** Records the placement of the beam relative to the events it affects. **/
    data_COMPASSDIRECTION m_place;

    /* include <attplace> */
};

//----------------------------------------------------------------------------
// AttNcLog
//----------------------------------------------------------------------------

class AttNcLog : public Att {
public:
    AttNcLog();
    virtual ~AttNcLog();

    /** Reset the default values for the attribute class **/
    void ResetNcLog();

    /** Read the values for the attribute class **/
    bool ReadNcLog(pugi::xml_node element);

    /** Write the values for the attribute class **/
    bool WriteNcLog(pugi::xml_node element);

    /**
     * @name Setters, getters and presence checker for class members.
     * The checker returns true if the attribute class is set (e.g., not equal
     * to the default value)
     **/
    ///@{
    void SetLiques(data_BOOLEAN liques_) { m_liques = liques_; }
    data_BOOLEAN GetLiques() const { return m_liques; }
    bool HasLiques() const;
    //
    void SetOct(std::string oct_) { m_oct = oct_; }
    std::string GetOct() const { return m_oct; }
    bool HasOct() const;
    //
    void SetPname(std::string pname_) { m_pname = pname_; }
    std::string GetPname() const { return m_pname; }
    bool HasPname() const;
    ///@}

private:
    /** --- **/
    data_BOOLEAN m_liques;
    /** Captures written octave information. **/
    std::string m_oct;
    /** Contains a written pitch name. **/
    std::string m_pname;

    /* include <attpname> */
};

//----------------------------------------------------------------------------
// AttNcForm
//----------------------------------------------------------------------------

class AttNcForm : public Att {
public:
    AttNcForm();
    virtual ~AttNcForm();

    /** Reset the default values for the attribute class **/
    void ResetNcForm();

    /** Read the values for the attribute class **/
    bool ReadNcForm(pugi::xml_node element);

    /** Write the values for the attribute class **/
    bool WriteNcForm(pugi::xml_node element);

    /**
     * @name Setters, getters and presence checker for class members.
     * The checker returns true if the attribute class is set (e.g., not equal
     * to the default value)
     **/
    ///@{
    void SetAngled(data_BOOLEAN angled_) { m_angled = angled_; }
    data_BOOLEAN GetAngled() const { return m_angled; }
    bool HasAngled() const;
    //
    void SetCon(ncForm_CON con_) { m_con = con_; }
    ncForm_CON GetCon() const { return m_con; }
    bool HasCon() const;
    //
    void SetCurve(ncForm_CURVE curve_) { m_curve = curve_; }
    ncForm_CURVE GetCurve() const { return m_curve; }
    bool HasCurve() const;
    //
    void SetHooked(data_BOOLEAN hooked_) { m_hooked = hooked_; }
    data_BOOLEAN GetHooked() const { return m_hooked; }
    bool HasHooked() const;
    //
    void SetLen(ncForm_LEN len_) { m_len = len_; }
    ncForm_LEN GetLen() const { return m_len; }
    bool HasLen() const;
    //
    void SetSShape(std::string sShape_) { m_sShape = sShape_; }
    std::string GetSShape() const { return m_sShape; }
    bool HasSShape() const;
    //
    void SetTilt(data_COMPASSDIRECTION tilt_) { m_tilt = tilt_; }
    data_COMPASSDIRECTION GetTilt() const { return m_tilt; }
    bool HasTilt() const;
    //
    void SetWaves(int waves_) { m_waves = waves_; }
    int GetWaves() const { return m_waves; }
    bool HasWaves() const;
    ///@}

private:
    /** --- **/
    data_BOOLEAN m_angled;
    /**
     * Describes the symbols typically used to indicate breaks between syllables and
     * their functions.
     **/
    ncForm_CON m_con;
    /** --- **/
    ncForm_CURVE m_curve;
    /** --- **/
    data_BOOLEAN m_hooked;
    /** --- **/
    ncForm_LEN m_len;
    /** --- **/
    std::string m_sShape;
    /** --- **/
    data_COMPASSDIRECTION m_tilt;
    /** Number of quilisma "waves". **/
    int m_waves;

    /* include <attwaves> */
};

//----------------------------------------------------------------------------
// AttSignifLetVis
//----------------------------------------------------------------------------

class AttSignifLetVis : public Att {
public:
    AttSignifLetVis();
    virtual ~AttSignifLetVis();

    /** Reset the default values for the attribute class **/
    void ResetSignifLetVis();

    /** Read the values for the attribute class **/
    bool ReadSignifLetVis(pugi::xml_node element);

    /** Write the values for the attribute class **/
    bool WriteSignifLetVis(pugi::xml_node element);

    /**
     * @name Setters, getters and presence checker for class members.
     * The checker returns true if the attribute class is set (e.g., not equal
     * to the default value)
     **/
    ///@{
    void SetPlace(data_COMPASSDIRECTION place_) { m_place = place_; }
    data_COMPASSDIRECTION GetPlace() const { return m_place; }
    bool HasPlace() const;
    ///@}

private:
    /** Records the placement of the beam relative to the events it affects. **/
    data_COMPASSDIRECTION m_place;

    /* include <attplace> */
};

} // vrv namespace

#endif // __VRV_ATTS_NEUMES_H__
