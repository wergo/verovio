/////////////////////////////////////////////////////////////////////////////
// Name:        att.h
// Author:      Laurent Pugin
// Created:     2014
// Copyright (c) Authors and others. All rights reserved.
/////////////////////////////////////////////////////////////////////////////

#ifndef __VRV_ATT_H__
#define __VRV_ATT_H__

#include <typeinfo>
#include <string>

//----------------------------------------------------------------------------

#include "attdef.h"

namespace vrv {
    
class Object;

//----------------------------------------------------------------------------
// Att
//----------------------------------------------------------------------------

/**
 * This base class for all MEI att classes.
 * It is not an abstract class but it should not be instanciated directly.
 * The att classes are generated with the libmei parser for Verovio.
*/
class Att
{
public:
    /** @name Constructors and destructor */
    ///@{
    Att( );
    virtual ~Att();
    ///@}
    
    /** 
     * @name static method for blind attribute modification
     * The implementation is implemented by LibMEI in each module corresponding file
     * Use in the toolkit for applying attribute modification to unspecified elements
     * See Toolkit::Set method
     * Files to be uncommented according to the inclusion of the corresponding LibMEI files
     */
    ///@{
    //static bool SetAnalysis( Object *element, std::string attrType, std::string attrValue );
    static bool SetCmn( Object *element, std::string attrType, std::string attrValue );
    //static bool SetCmnornaments( Object *element, std::string attrType, std::string attrValue );
    static bool SetCritapp( Object *element, std::string attrType, std::string attrValue );
    //static bool SetEdittrans( Object *element, std::string attrType, std::string attrValue );
    //static bool SetFacsimile( Object *element, std::string attrType, std::string attrValue );
    //static bool SetFigtable( Object *element, std::string attrType, std::string attrValue );
    //static bool SetHarmony( Object *element, std::string attrType, std::string attrValue );
    //static bool SetHeader( Object *element, std::string attrType, std::string attrValue );
    //static bool SetLinkalign( Object *element, std::string attrType, std::string attrValue );
    //static bool SetLyrics( Object *element, std::string attrType, std::string attrValue );
    static bool SetMensural( Object *element, std::string attrType, std::string attrValue );
    //static bool SetMidi( Object *element, std::string attrType, std::string attrValue );
    static bool SetPagebased( Object *element, std::string attrType, std::string attrValue );
    //static bool SetNeumes( Object *element, std::string attrType, std::string attrValue );
    static bool SetShared( Object *element, std::string attrType, std::string attrValue );
    //static bool SetTablature( Object *element, std::string attrType, std::string attrValue );

    /**
     * Idem for getting attributes as strings
     */
    //static void GetAnalysis( Object *element, ArrayOfStrAttr *attributes );
    static void GetCmn( Object *element, ArrayOfStrAttr *attributes );
    //static void GetCmnornaments( Object *element, ArrayOfStrAttr *attributes );
    static void GetCritapp( Object *element, ArrayOfStrAttr *attributes );
    //static void GetEdittrans( Object *element, ArrayOfStrAttr *attributes );
    //static void GetFacsimile( Object *element, ArrayOfStrAttr *attributes );
    //static void GetFigtable( Object *element, ArrayOfStrAttr *attributes );
    //static void GetHarmony( Object *element, ArrayOfStrAttr *attributes );
    //static void GetHeader( Object *element, ArrayOfStrAttr *attributes );
    //static void GetLinkalign( Object *element, ArrayOfStrAttr *attributes );
    //static void GetLyrics( Object *element, ArrayOfStrAttr *attributes );
    static void GetMensural( Object *element, ArrayOfStrAttr *attributes );
    //static void GetMidi( Object *element, ArrayOfStrAttr *attributes );
    static void GetPagebased( Object *element, ArrayOfStrAttr *attributes );
    //static void GetNeumes( Object *element, ArrayOfStrAttr *attributes );
    static void GetShared( Object *element, ArrayOfStrAttr *attributes );
    //static void GetTablature( Object *element, ArrayOfStrAttr *attributes );
    ///@}
    
public:
    /** Dummy string converter */
    std::string StrToStr(std::string str);
    
    /** @name Basic converters for writing */
    ///@{
    std::string DblToStr(double data);
    std::string IntToStr(int data);
    ///@}
    
    /** @name Basic converters for reading */
    ///@{
    double StrToDbl(std::string value);
    int StrToInt(std::string value);

    /** @name Specific method excluded from the ODD */
    ///@{
    
    std::string DurToStr(data_DURATION data);
    data_DURATION StrToDur(std::string value);
    
    ///@}
    
    //-------------------------------------------------------------------//
    // Inclusion of the definition of the methods generated from the ODD //
    //-------------------------------------------------------------------//
    std::string FontweightToStr(data_FONTWEIGHT data);
    data_FONTWEIGHT StrToFontweight(std::string value);
        
    std::string KeySignatureToStr(data_KEYSIGNATURE data);
    data_KEYSIGNATURE StrToKeySignature(std::string value);
    
    std::string LayerschemeToStr(data_LAYERSCHEME data);
    data_LAYERSCHEME StrToLayerscheme(std::string value);
    
    std::string LigatureToStr(data_LIGATURE data);
    data_LIGATURE StrToLigature(std::string value);
    
    std::string MensurationSignToStr(data_MENSURATIONSIGN data);
    data_MENSURATIONSIGN StrToMensurationSign(std::string value);
    
    std::string MeterSignToStr(data_METERSIGN data);
    data_METERSIGN StrToMeterSign(std::string value);
    
    std::string ModeToStr(data_MODE data);
    data_MODE StrToMode(std::string value);

    #include "att_converters.h"
    
};
    
//----------------------------------------------------------------------------
// AttComparison
//----------------------------------------------------------------------------

class AttComparison
{
    
public:
    AttComparison( const std::type_info *elementType ) {
        m_elementType = elementType;
    };
    
    virtual bool operator() (Object *object);
    
    const std::type_info *GetType() { return m_elementType; };
    
    bool MatchesType( Object *object );
    
protected:
    const std::type_info *m_elementType;
};
    
} // namespace vrv

#endif
