//
//  EditorIO.cpp
//  Structural_Design_Temp
//
//  Created by CD-parkdaedong on 2020/08/31.
//

#include <stdio.h>
#include "EditorIO.h"

USING_NS_CC;

EditorIO* EditorIO::pEditorIO = nullptr;

EditorIO* EditorIO::getInstance()
{
    if(pEditorIO == nullptr)
    {
        pEditorIO = new EditorIO();
    }
    
    return pEditorIO;
}
