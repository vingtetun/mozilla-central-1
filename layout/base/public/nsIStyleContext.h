/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * The contents of this file are subject to the Netscape Public License
 * Version 1.0 (the "NPL"); you may not use this file except in
 * compliance with the NPL.  You may obtain a copy of the NPL at
 * http://www.mozilla.org/NPL/
 *
 * Software distributed under the NPL is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the NPL
 * for the specific language governing rights and limitations under the
 * NPL.
 *
 * The Initial Developer of this code under the NPL is Netscape
 * Communications Corporation.  Portions created by Netscape are
 * Copyright (C) 1998 Netscape Communications Corporation.  All Rights
 * Reserved.
 */
#ifndef nsIStyleContext_h___
#define nsIStyleContext_h___

#include "nslayout.h"
#include "nsISupports.h"
#include "nsColor.h"
#include "nsCoord.h"
#include "nsMargin.h"
#include "nsFont.h"
#include "nsStyleCoord.h"
#include "nsStyleStruct.h"
#include "nsStyleConsts.h"

class nsIFrame;
class nsIPresContext;
class nsISupportsArray;


// The lifetime of these objects is managed by the nsIStyleContext.

struct nsStyleFont : public nsStyleStruct {
  nsFont  mFont;        // [inherited]
  nsFont  mFixedFont;   // [inherited]
  PRUint8 mFlags;       // [inherited] See nsStyleConsts.h

protected:
  nsStyleFont(const nsFont& aVariableFont, const nsFont& aFixedFont);
  ~nsStyleFont(void);
};

struct nsStyleColor : public nsStyleStruct {
  nscolor mColor;                 // [inherited]
 
  PRUint8 mBackgroundAttachment;  // [reset] See nsStyleConsts.h
  PRUint8 mBackgroundFlags;       // [reset] See nsStyleConsts.h
  PRUint8 mBackgroundRepeat;      // [reset] See nsStyleConsts.h

  nscolor mBackgroundColor;       // [reset]
  nscoord mBackgroundXPosition;   // [reset]
  nscoord mBackgroundYPosition;   // [reset]
  nsString mBackgroundImage;      // [reset] absolute url string

  PRUint8 mCursor;                // [reset] See nsStyleConsts.h NS_STYLE_CURSOR_*
  nsString mCursorImage;          // [reset] url string
  float mOpacity;                 // [reset] percentage

protected:
  nsStyleColor(void);
  ~nsStyleColor(void);
};

struct nsStyleSpacing: public nsStyleStruct {
  nsStyleSides  mMargin;          // [reset] length, percent, auto, inherit
  nsStyleSides  mPadding;         // [reset] length, percent, inherit
  nsStyleSides  mBorder;          // [reset] length, percent, See nsStyleConsts.h for enum
  PRUint8       mBorderStyle[4];  // [reset] See nsStyleConsts.h
  nscolor       mBorderColor[4];  // [reset] 

  PRBool GetMargin(nsMargin& aMargin) const;
  PRBool GetPadding(nsMargin& aPadding) const;
  PRBool GetBorder(nsMargin& aBorder) const;
  PRBool GetBorderPadding(nsMargin& aBorderPadding) const;

// XXX these are deprecated methods
  void CalcMarginFor(const nsIFrame* aFrame, nsMargin& aMargin) const;
  void CalcPaddingFor(const nsIFrame* aFrame, nsMargin& aPadding) const;
  void CalcBorderFor(const nsIFrame* aFrame, nsMargin& aBorder) const;
  void CalcBorderPaddingFor(const nsIFrame* aFrame, nsMargin& aBorderPadding) const;

protected:
  nsStyleSpacing(void);

  PRBool    mHasCachedMargin;
  PRBool    mHasCachedPadding;
  PRBool    mHasCachedBorder;
  nsMargin  mCachedMargin;
  nsMargin  mCachedPadding;
  nsMargin  mCachedBorder;
  nsMargin  mCachedBorderPadding;
};

struct nsStyleList : public nsStyleStruct {
  PRUint8   mListStyleType;             // [inherited] See nsStyleConsts.h
  PRUint8   mListStylePosition;         // [inherited] 
  nsString  mListStyleImage;            // [inherited] absolute url string

protected:
  nsStyleList(void);
  ~nsStyleList(void);
};

struct nsStylePosition : public nsStyleStruct {
  PRUint8   mPosition;                  // [reset] see nsStyleConsts.h

  nsStyleCoord  mLeftOffset;            // [reset] 
  nsStyleCoord  mTopOffset;             // [reset] 
  nsStyleCoord  mWidth;                 // [reset] coord, percent, auto, inherit
  nsStyleCoord  mMinWidth;              // [reset] coord, percent, inherit
  nsStyleCoord  mMaxWidth;              // [reset] coord, percent, null, inherit
  nsStyleCoord  mHeight;                // [reset] coord, percent, auto, inherit
  nsStyleCoord  mMinHeight;             // [reset] coord, percent, inherit
  nsStyleCoord  mMaxHeight;             // [reset] coord, percent, null, inherit

  nsStyleCoord  mZIndex;                // [reset] 

protected:
  nsStylePosition(void);
};

struct nsStyleText : public nsStyleStruct {
  PRUint8 mTextAlign;                   // [inherited] see nsStyleConsts.h
  PRUint8 mTextDecoration;              // [reset] see nsStyleConsts.h
  PRUint8 mTextTransform;               // [inherited] see nsStyleConsts.h
  PRUint8 mWhiteSpace;                  // [inherited] see nsStyleConsts.h

  nsStyleCoord  mLetterSpacing;         // [inherited] 
  nsStyleCoord  mLineHeight;            // [inherited] 
  nsStyleCoord  mTextIndent;            // [inherited] 
  nsStyleCoord  mWordSpacing;           // [inherited] 
  nsStyleCoord  mVerticalAlign;         // [reset] see nsStyleConsts.h for enums

protected:
  nsStyleText(void);
};

struct nsStyleDisplay : public nsStyleStruct {
  PRUint8 mDirection;           // [inherited] see nsStyleConsts.h NS_STYLE_DIRECTION_*
  PRUint8 mDisplay;             // [reset] see nsStyleConsts.h NS_STYLE_DISPLAY_*
  PRUint8 mFloats;              // [reset] see nsStyleConsts.h NS_STYLE_FLOAT_*
  PRUint8 mBreakType;           // [reset] see nsStyleConsts.h NS_STYLE_CLEAR_*
  PRPackedBool mBreakBefore;    // [reset] 
  PRPackedBool mBreakAfter;     // [reset] 
  PRPackedBool mVisible;        // [inherited]
  PRUint8   mOverflow;          // [reset] see nsStyleConsts.h

  PRUint8   mClipFlags;         // [reset] see nsStyleConsts.h
  nsMargin  mClip;              // [reset] offsets from respective edge

  PRBool IsBlockLevel() const {return (NS_STYLE_DISPLAY_BLOCK == mDisplay) ||
                                      (NS_STYLE_DISPLAY_LIST_ITEM == mDisplay) ||
                                      (NS_STYLE_DISPLAY_TABLE == mDisplay);}

protected:
  nsStyleDisplay(void);
};

struct nsStyleTable: public nsStyleStruct {
  PRUint8       mLayoutStrategy;// [reset] see nsStyleConsts.h NS_STYLE_TABLE_LAYOUT_*
  PRUint8       mFrame;         // [reset] see nsStyleConsts.h NS_STYLE_TABLE_FRAME_*
  PRUint8       mRules;         // [reset] see nsStyleConsts.h NS_STYLE_TABLE_RULES_*
  nsStyleCoord  mCellPadding;   // [reset] 
  nsStyleCoord  mCellSpacing;   // [reset] 
  PRInt32       mCols;          // [reset] an integer if set, or see nsStyleConsts.h NS_STYLE_TABLE_COLS_*
  nsStyleCoord  mSpanWidth;     // [reset] the amount of width this col gets from a spanning cell, if any
  PRInt32       mSpan;          // [reset] the number of columns spanned by a colgroup or col

protected:
  nsStyleTable(void);
};

//----------------------------------------------------------------------

#define NS_ISTYLECONTEXT_IID   \
 { 0x26a4d970, 0xa342, 0x11d1, \
   {0x89, 0x74, 0x00, 0x60, 0x08, 0x91, 0x1b, 0x81} }

class nsIStyleContext : public nsISupports {
public:
  virtual PRBool    Equals(const nsIStyleContext* aOther) const = 0;
  virtual PRUint32  HashValue(void) const = 0;

  virtual nsIStyleContext*  GetParent(void) const = 0;
  virtual nsISupportsArray* GetStyleRules(void) const = 0;
  virtual PRInt32 GetStyleRuleCount(void) const = 0;
  NS_IMETHOD GetPseudoType(nsIAtom*& aPseudoTag) const = 0;

  NS_IMETHOD FindChildWithRules(const nsIAtom* aPseudoTag, 
                                const nsISupportsArray* aRules,
                                nsIStyleContext*& aResult) = 0;

  // get a style data struct by ID, may return null 
  virtual const nsStyleStruct* GetStyleData(nsStyleStructID aSID) = 0;

  // get a style data struct by ID, may return null 
  virtual nsStyleStruct* GetMutableStyleData(nsStyleStructID aSID) = 0;

  // call this to prevent context from getting shared
  virtual void  ForceUnique(void) = 0;

  NS_IMETHOD RemapStyle(nsIPresContext* aPresContext) = 0;

  // call if you change style data after creation
  virtual void    RecalcAutomaticData(nsIPresContext* aPresContext) = 0;

  // debugging
  virtual void  List(FILE* out, PRInt32 aIndent) = 0;
};

// this is private to nsStyleSet, don't call it
extern NS_LAYOUT nsresult
  NS_NewStyleContext(nsIStyleContext** aInstancePtrResult,
                     nsIStyleContext* aParentContext,
                     nsIAtom* aPseudoType,
                     nsISupportsArray* aRules,
                     nsIPresContext* aPresContext);

#endif /* nsIStyleContext_h___ */
