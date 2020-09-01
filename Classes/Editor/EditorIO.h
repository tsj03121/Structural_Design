//
//  EditorIO.h
//  Structural_Design_Temp
//
//  Created by CD-parkdaedong on 2020/08/31.
//

#ifndef EditorIO_h
#define EditorIO_h

class EditorIO
{
public:
    static EditorIO* pEditorIO;
    int dataCount = 5;
    
public:
    static EditorIO* getInstance();
};


#endif /* EditorIO_h */
