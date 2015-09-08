<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:xs="http://www.w3.org/2001/XMLSchema"
    xmlns:math="http://www.w3.org/2005/xpath-functions/math"
    xmlns:xd="http://www.oxygenxml.com/ns/doc/xsl"
    xmlns:tei="http://www.tei-c.org/ns/1.0"
    xmlns:rng="http://relaxng.org/ns/structure/1.0" 
    xmlns:sch="http://purl.oclc.org/dsdl/schematron"
    xmlns:a="http://relaxng.org/ns/compatibility/annotations/1.0"
    xmlns:xhtml="http://www.w3.org/1999/xhtml"
    xmlns:local="no:where"
    exclude-result-prefixes="xs math xd tei sch rng a local xhtml"
    version="3.0">
    <xd:doc scope="stylesheet">
        <xd:desc>
            <xd:p><xd:b>Created on:</xd:b> Mar 24, 2015</xd:p>
            <xd:p><xd:b>Author:</xd:b> Johannes Kepper</xd:p>
            <xd:p>This XSL operates on the Verovio ODD file.</xd:p>
        </xd:desc>
    </xd:doc>
    
    <xsl:output method="text"/>
    
    <xsl:variable name="tab" select="'    '" as="xs:string"/>
    <xsl:variable name="lb" select="'&#13;'" as="xs:string"/>
    <xsl:variable name="quot" select="'&quot;'" as="xs:string"/>
    
    <xsl:function name="local:resolveCases" as="xs:string">
        <xsl:param name="input" as="xs:string"/>
        
        <xsl:variable name="startString" select="upper-case(substring($input,1,1)) || lower-case(substring($input,2))" as="xs:string"/>
        
        <xsl:variable name="output" as="xs:string*">
            <xsl:analyze-string select="$startString" regex="_([a-z])">
                <xsl:matching-substring>
                    <xsl:value-of select="upper-case(regex-group(1))"/>
                </xsl:matching-substring>
                <xsl:non-matching-substring>
                    <xsl:copy/>
                </xsl:non-matching-substring>
            </xsl:analyze-string>
        </xsl:variable>
        
        <xsl:value-of select="string-join($output,'')"/>
    </xsl:function>
    
    
    <xsl:variable name="excluded.dataTypes" as="xs:string*">
        
        <xsl:value-of select="'data.DURATION'"/>
        <xsl:value-of select="'data.DURATION.cmn'"/>
        <xsl:value-of select="'data.DURATION.mensural'"/>
        <xsl:value-of select="'data.KEYSIGNATURE'"/>
        <xsl:value-of select="'data.MODUSMAIOR'"/>
        <xsl:value-of select="'data.MODUSMINOR'"/>
        <xsl:value-of select="'data.OCTAVE.DIS'"/>
        <xsl:value-of select="'data.PROLATIO'"/>
        <xsl:value-of select="'data.TEMPUS'"/>
        
    </xsl:variable>
    
    
    <xsl:template match="/">
        
        <xsl:variable name="odd" select="/" as="node()"/>
        <xsl:variable name="modules" select="distinct-values(.//tei:elementSpec/@module)" as="xs:string*"/>
        
        <!-- create config.yml -->
        <xsl:result-document href="../config/config.yml">
            
            <xsl:variable name="attributes" as="node()*">
                <xsl:for-each select="$modules">
                    <xsl:variable name="current.module" select="." as="xs:string"/>
                    
                    <xsl:sequence select="$odd//tei:attDef[ancestor::tei:classSpec[@module = $current.module and @type = 'atts']]"/>
                </xsl:for-each>
            </xsl:variable>
            
            
            <xsl:value-of select="'modules:' || $lb"/>
            <xsl:for-each select="$modules">
                
                <!-- module name: -->
                <xsl:variable name="current.module" select="." as="xs:string"/>
                <xsl:value-of select="$tab || . || ':' || $lb"/>
                <xsl:value-of select="$tab || $tab || 'attributes:' || $lb"/>
                
                <xsl:for-each select="$attributes[ancestor::tei:classSpec/@module = $current.module]">
                    <xsl:variable name="current.attribute" select="." as="node()"/>
                    <xsl:if test="$current.attribute/tei:datatype">
                        <!-- attribute name: -->
                        <xsl:value-of select="$tab || $tab || $tab || $current.attribute/@ident || ':' || $lb"/>
                        <!-- data type: -->
                        <xsl:value-of select="$tab || $tab || $tab || $tab || 'type: ' || replace($current.attribute/tei:datatype/rng:ref/@name,'\.','_') || $lb"/>
                    </xsl:if>
                    
                    
                </xsl:for-each>
            </xsl:for-each>    
        </xsl:result-document>
        
        <!-- create attdef.h -->
        <xsl:result-document href="../config/attdef.h">
            
            <xsl:value-of select="'/*****EXISTING*DATATYPES*****/' || $lb || $lb"/>
            
            <xsl:variable name="choiced.dataTypes" select="$odd//tei:macroSpec[.//rng:choice]" as="node()*"/>
            <xsl:for-each select="$choiced.dataTypes">
                <xsl:variable name="current.dataType" select="." as="node()"/>
                
                <xsl:if test="not($current.dataType/@ident = $excluded.dataTypes)">
                    <xsl:variable name="dataType.title" select="replace($current.dataType/@ident,'\.','_')" as="xs:string"/>
                    <xsl:variable name="dataType.raw" select="replace($dataType.title,'data_','')" as="xs:string"/>
                    
                    <xsl:value-of select="'/**' || $lb || ' * ' || $dataType.title || $lb || ' */' || $lb"/>
                    <xsl:value-of select="'enum ' || $dataType.title || ' {' || $lb"/>
                    <xsl:value-of select="$tab || $dataType.raw || '_NONE = 0,' || $lb"/>
                    <xsl:variable name="valItem.count" select="count($current.dataType//rng:value)" as="xs:integer"/>
                    <xsl:for-each select="$current.dataType//rng:value">
                        <xsl:variable name="comma" select="if(position() lt $valItem.count) then(',') else('')" as="xs:string"/>
                        <xsl:value-of select="$tab || $dataType.raw || '_' || replace(text(),'[ -\.]+','_') || $comma || ' // ' || normalize-space(./following-sibling::a:documentation[1]/text()) || $lb"/>
                    </xsl:for-each>
                    <xsl:value-of select="'};' || $lb || $lb"/>    
                </xsl:if>
                
            </xsl:for-each>
            
            <xsl:value-of select="$lb || $lb || '/*****GENERATED*DATATYPES*****/' || $lb || $lb"/>
            
            <xsl:variable name="valLists" select="$odd//tei:valList" as="node()*"/>
            <xsl:for-each select="$valLists">
                <xsl:variable name="current.valList" select="." as="node()"/>
                <xsl:variable name="dataType.raw" select="replace(upper-case(replace($current.valList/parent::tei:attDef/@ident,'\.','_')),':','')" as="xs:string"/>
                <xsl:variable name="dataType.class" select="replace(replace($current.valList/ancestor::tei:classSpec/@ident,'att\.',''),'\.','_')" as="xs:string"/>
                <xsl:variable name="dataType.title" select="'data_' || $dataType.class || '_' || $dataType.raw" as="xs:string"/>
                <xsl:value-of select="'/**' || $lb || ' * (generated) ' || $dataType.title || $lb || ' */' || $lb"/>
                <xsl:value-of select="'enum ' || $dataType.title || ' {' || $lb"/>
                <xsl:value-of select="$tab || $dataType.raw || '_NONE = 0,' || $lb"/>
                <xsl:variable name="valItem.count" select="count($current.valList/tei:valItem)" as="xs:integer"/>
                <xsl:for-each select="$current.valList/tei:valItem">
                    <xsl:variable name="comma" select="if(position() lt $valItem.count) then(',') else('')" as="xs:string"/>
                    <xsl:value-of select="$tab || $dataType.raw || '_' || @ident || $comma || ' // ' || normalize-space(./tei:desc/text()) || $lb"/>
                </xsl:for-each>
                <xsl:value-of select="'};' || $lb || $lb"/>
            </xsl:for-each>
        </xsl:result-document>
        
        <!-- create att.h -->
        <xsl:result-document href="../config/att.h">
            <xsl:value-of select="'/*****EXISTING*DATATYPES*****/' || $lb || $lb"/>
            <xsl:variable name="choiced.dataTypes" select="$odd//tei:macroSpec[.//rng:choice]" as="node()*"/>
            <xsl:for-each select="$choiced.dataTypes">
                <xsl:variable name="current.dataType" select="." as="node()"/>
                
                <xsl:if test="not($current.dataType/@ident = $excluded.dataTypes)">
                    <xsl:variable name="dataType.title" select="replace($current.dataType/@ident,'\.','_')" as="xs:string"/>
                    <xsl:variable name="dataType.raw" select="replace($dataType.title,'data_','')" as="xs:string"/>
                    
                    <xsl:variable name="cases.fixed" select="local:resolveCases($dataType.raw)" as="xs:string"/>
                    
                    <xsl:value-of select="$tab || 'std::string ' || $cases.fixed || 'ToStr(' || $dataType.title || ' data);' || $lb"/>
                    <xsl:value-of select="$tab || $dataType.title || ' StrTo' || $cases.fixed || '(std::string value);' || $lb || $lb"/>                     
                </xsl:if>
                
            </xsl:for-each>
            
            <xsl:value-of select="$lb || $lb || '/*****GENERATED*DATATYPES*****/' || $lb || $lb"/>
            <xsl:variable name="valLists" select="$odd//tei:valList" as="node()*"/>
            <xsl:for-each select="$valLists">
                <xsl:variable name="current.valList" select="." as="node()"/>
                <xsl:variable name="dataType.raw" select="upper-case(replace($current.valList/parent::tei:attDef/@ident,'\.','_'))" as="xs:string"/>
                <xsl:variable name="dataType.title" select="'data_' || $dataType.raw" as="xs:string"/>
                
                <xsl:variable name="cases.fixed" select="local:resolveCases($dataType.raw)" as="xs:string"/>
                
                <xsl:value-of select="$tab || 'std::string ' || $cases.fixed || 'ToStr(' || $dataType.title || ' data);' || $lb"/>
                <xsl:value-of select="$tab || $dataType.title || ' StrTo' || $cases.fixed || '(std::string value);' || $lb || $lb"/>
                
            </xsl:for-each>
            
        </xsl:result-document>
        
        <!-- create att.cpp -->
        <xsl:result-document href="../config/att.cpp">
            <xsl:variable name="choiced.dataTypes" select="$odd//tei:macroSpec[.//rng:choice]" as="node()*"/>
            <xsl:for-each select="$choiced.dataTypes">
                <xsl:variable name="current.dataType" select="." as="node()"/>
                
                <xsl:if test="not($current.dataType/@ident = $excluded.dataTypes)">
                    <xsl:variable name="dataType.title" select="replace($current.dataType/@ident,'\.','_')" as="xs:string"/>
                    <xsl:variable name="dataType.raw" select="replace($dataType.title,'data_','')" as="xs:string"/>
                    
                    <xsl:variable name="cases.fixed" select="local:resolveCases($dataType.raw)" as="xs:string"/>
                    <xsl:variable name="values" select="$current.dataType//rng:choice/rng:value" as="node()*"/>
                    
                    <xsl:value-of select="'std::string Att::' || $cases.fixed || 'ToStr(' || $dataType.title || ' data)' || $lb"/>
                    <xsl:value-of select="'{' || $lb"/>
                    <xsl:value-of select="$tab || 'std::string value;' || $lb"/>
                    <xsl:value-of select="$tab || 'switch(data)' || $lb"/>
                    <xsl:value-of select="$tab || '{' || $lb"/>
                    
                    <xsl:for-each select="$values">
                        <xsl:value-of select="$tab || $tab || 'case ' || $dataType.title || '_' || text() || ' : value = &quot;' || text() || '&quot;; break; // ' || normalize-space(following-sibling::a:documentation[1]/text()) || $lb"/>
                    </xsl:for-each>
                    <xsl:value-of select="$tab || $tab || 'default:' || $lb"/>
                    <xsl:value-of select="$tab || $tab || $tab || 'LogWarning(' || $quot ||'Unknown ' || $cases.fixed || ' ''%d''' || $quot || ', data);' || $lb"/>
                    <xsl:value-of select="$tab || $tab || $tab || 'value = ' || $quot || $quot || ';' || $lb"/>
                    <xsl:value-of select="$tab || $tab || $tab || 'break;' || $lb"/>
                    
                    <xsl:value-of select="$tab || '}' || $lb"/>
                    <xsl:value-of select="$tab || 'return value;' || $lb"/>
                    <xsl:value-of select="'}' || $lb"/>
                    <xsl:value-of select="$lb"/>
                    
                    
                    <xsl:value-of select="$dataType.title || ' Att::StrTo' || $cases.fixed || '(std::string value)' || $lb"/>
                    <xsl:value-of select="'{' || $lb"/>
                    <xsl:value-of select="$tab || 'if (value == &quot;' || $values[1]/text() || '&quot;) return ' || $dataType.title || '_' || $values[1]/text() || '; // ' || normalize-space($values[1]/following-sibling::a:documentation[1]/text()) || $lb"/>
                    <xsl:for-each select="$values[position() gt 1]">
                        <xsl:value-of select="$tab || 'else if (value == &quot;' || text() || '&quot;) return ' || $dataType.title || '_' || text() || '; // ' || normalize-space(following-sibling::a:documentation[1]/text()) || $lb"/>
                    </xsl:for-each>
                    <xsl:value-of select="$tab || 'else {' || $lb"/>
                    <xsl:value-of select="$tab || $tab || 'LogWarning(' || $quot ||'Unknown ' || $cases.fixed || ' ''%s''' || $quot || ', value.c_str() );' || $lb"/>
                    <xsl:value-of select="$tab || '}' || $lb"/>
                    <xsl:value-of select="$tab || 'return ' || $dataType.raw || '_NONE;' || $lb"/>
                    <xsl:value-of select="'}' || $lb"/>
                    <xsl:value-of select="$lb"/>
                </xsl:if>
                
            </xsl:for-each>
            
            <xsl:variable name="valLists" select="$odd//tei:valList" as="node()*"/>
            <xsl:for-each select="$valLists">
                <xsl:variable name="current.valList" select="." as="node()"/>
                <xsl:variable name="dataType.raw" select="upper-case(replace($current.valList/parent::tei:attDef/@ident,'\.','_'))" as="xs:string"/>
                <xsl:variable name="dataType.title" select="'data_' || $dataType.raw" as="xs:string"/>
                
                <xsl:variable name="cases.fixed" select="local:resolveCases($dataType.raw)" as="xs:string"/>
                <xsl:variable name="values" select="$current.valList/tei:valItem" as="node()*"/>
                
                <xsl:value-of select="'std::string Att::' || $cases.fixed || 'ToStr(' || $dataType.title || ' data)' || $lb"/>
                <xsl:value-of select="'{' || $lb"/>
                <xsl:value-of select="$tab || 'std::string value;' || $lb"/>
                <xsl:value-of select="$tab || 'switch(data) || $lb'"/>
                <xsl:value-of select="$tab || '{' || $lb"/>
                
                <xsl:for-each select="$values">
                    <xsl:value-of select="$tab || $tab || 'case ' || $dataType.title || '_' || @ident || ' : value = &quot;' || @ident || '&quot;; break; // ' || normalize-space(./tei:desc/text()) || $lb"/>
                </xsl:for-each>
                <xsl:value-of select="$tab || $tab || 'default:' || $lb"/>
                <xsl:value-of select="$tab || $tab || $tab || 'LogWarning(' || $quot ||'Unknown ' || $cases.fixed || ' ''%d''' || $quot || ', data);' || $lb"/>
                <xsl:value-of select="$tab || $tab || $tab || 'value = ' || $quot || $quot || ';' || $lb"/>
                <xsl:value-of select="$tab || $tab || $tab || 'break;' || $lb"/>
                
                <xsl:value-of select="$tab || '}' || $lb"/>
                <xsl:value-of select="$tab || 'return value;' || $lb"/>
                <xsl:value-of select="'}' || $lb"/>
                <xsl:value-of select="$lb"/>
                
                
                <xsl:value-of select="$dataType.title || ' Att::StrTo' || $cases.fixed || '(std::string value)' || $lb"/>
                <xsl:value-of select="'{' || $lb"/>
                <xsl:value-of select="$tab || 'if (value == &quot;' || $values[1]/@ident || '&quot;) return ' || $dataType.title || '_' || $values[1]/@ident || '; // ' || normalize-space($values[1]/tei:desc/text()) || $lb"/>
                <xsl:for-each select="$values[position() gt 1]">
                    <xsl:value-of select="$tab || 'else if (value == &quot;' || @ident || '&quot;) return ' || $dataType.title || '_' || @ident || '; // ' || normalize-space(./tei:desc/text()) || $lb"/>
                </xsl:for-each>
                <xsl:value-of select="$tab || 'else {' || $lb"/>
                <xsl:value-of select="$tab || $tab || 'LogWarning(' || $quot ||'Unknown ' || $cases.fixed || ' ''%s''' || $quot || ', value.c_str() );' || $lb"/>
                <xsl:value-of select="$tab || '}' || $lb"/>
                <xsl:value-of select="$tab || 'return ' || $dataType.raw || '_NONE;' || $lb"/>
                <xsl:value-of select="'}' || $lb"/>
                <xsl:value-of select="$lb"/>
            </xsl:for-each>
            
        </xsl:result-document>
        
        <xsl:result-document href="../config/documentation.html" method="html">
            <div xmlns="http://www.w3.org/1999/xhtml">
                
            </div>
        </xsl:result-document>
        
    </xsl:template>
    
</xsl:stylesheet>