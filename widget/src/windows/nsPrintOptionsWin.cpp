/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* ***** BEGIN LICENSE BLOCK *****
 * Version: NPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Netscape Public License
 * Version 1.1 (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License at
 * http://www.mozilla.org/NPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is mozilla.org code.
 *
 * The Initial Developer of the Original Code is 
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 1998
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the NPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the NPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */
#include "nsCOMPtr.h"
#include "nsPrintOptionsWin.h"
#include "nsPrintSettingsWin.h"

#include "nsGfxCIID.h"
#include "nsIServiceManager.h"
const char kPrinterEnumeratorContractID[] = "@mozilla.org/gfx/printerenumerator;1";

/** ---------------------------------------------------
 *  See documentation in nsPrintOptionsWin.h
 *	@update 6/21/00 dwc
 */
nsPrintOptionsWin::nsPrintOptionsWin()
{

}

/** ---------------------------------------------------
 *  See documentation in nsPrintOptionsImpl.h
 *	@update 6/21/00 dwc
 */
nsPrintOptionsWin::~nsPrintOptionsWin()
{
}

/* nsIPrintSettings CreatePrintSettings (); */
NS_IMETHODIMP nsPrintOptionsWin::CreatePrintSettings(nsIPrintSettings **_retval)
{
  nsresult rv = NS_OK;
  nsPrintSettingsWin* printSettings = new nsPrintSettingsWin(); // does not initially ref count
  NS_ASSERTION(printSettings, "Can't be NULL!");

  rv = printSettings->QueryInterface(NS_GET_IID(nsIPrintSettings), (void**)_retval); // ref counts
  NS_ENSURE_SUCCESS(rv, rv);

  // nsPrintOptionImpl actually initials with "kInitSaveAll", but that is a 
  // little extreme for Windows, so here we will initialize with a sub-set of 
  // the settings
  PRUint32 flags = nsIPrintSettings.kInitSaveHeaderLeft | 
                   nsIPrintSettings.kInitSaveHeaderCenter |
                   nsIPrintSettings.kInitSaveHeaderRight |
                   nsIPrintSettings.kInitSaveFooterLeft | 
                   nsIPrintSettings.kInitSaveFooterCenter |
                   nsIPrintSettings.kInitSaveFooterRight |
                   nsIPrintSettings.kInitSaveBGColors |
                   nsIPrintSettings.kInitSaveBGImages |
                   nsIPrintSettings.kInitSaveMargins;

  InitPrintSettingsFromPrefs(*_retval, PR_FALSE, flags); // ignore return value

  return rv;
}

/* readonly attribute nsIPrintSettings globalPrintSettings; */
NS_IMETHODIMP 
nsPrintOptionsWin::GetGlobalPrintSettings(nsIPrintSettings * *aGlobalPrintSettings)
{
  if (!mGlobalPrintSettings) {
    CreatePrintSettings(getter_AddRefs(mGlobalPrintSettings));
    NS_ASSERTION(mGlobalPrintSettings, "Can't be NULL!");
    // If this still NULL, we have some very big problems going on
    NS_ENSURE_TRUE(mGlobalPrintSettings, NS_ERROR_FAILURE);

    // The very first time we should initialize from the default printer
    nsresult rv;
    nsCOMPtr<nsIPrinterEnumerator> prtEnum = do_GetService(kPrinterEnumeratorContractID, &rv);
    if (NS_SUCCEEDED(rv)) {
      PRUnichar* printerName = nsnull;
      // Not sure if all platforms will return the proper error code
      // so for insurance, make sure there is a printer name
      if (NS_SUCCEEDED(prtEnum->GetDefaultPrinterName(&printerName)) && printerName && *printerName) {
        prtEnum->InitPrintSettingsFromPrinter(printerName, mGlobalPrintSettings);
        nsMemory::Free(printerName);
      }
    }
  }

  *aGlobalPrintSettings = mGlobalPrintSettings;
  NS_ADDREF(*aGlobalPrintSettings);

  return NS_OK;
}

/* readonly attribute nsIPrintSettings newPrintSettings; */
NS_IMETHODIMP
nsPrintOptionsWin::GetNewPrintSettings(nsIPrintSettings * *aNewPrintSettings)
{
    NS_ENSURE_ARG_POINTER(aNewPrintSettings);

    nsresult rv = CreatePrintSettings(aNewPrintSettings);
    NS_ENSURE_SUCCESS(rv, rv);
    return InitPrintSettingsFromPrinter(nsnull, *aNewPrintSettings);
}

//-----------------------------------------------------------------------
NS_IMETHODIMP
nsPrintOptionsWin::InitPrintSettingsFromPrinter(const PRUnichar *aPrinterName, nsIPrintSettings *aPrintSettings)
{
    NS_ENSURE_ARG_POINTER(aPrintSettings);

    PRUnichar* printerName = nsnull;
    if (!aPrinterName) {
        GetDefaultPrinterName(&printerName);
        if (!printerName || !*printerName) return NS_OK;
    }
    nsresult rv;
    nsCOMPtr<nsIPrinterEnumerator> prtEnum = do_GetService(kPrinterEnumeratorContractID, &rv);
    if (prtEnum) {
        rv = prtEnum->InitPrintSettingsFromPrinter(aPrinterName?aPrinterName:printerName, aPrintSettings);
    }
    if (printerName) {
        nsMemory::Free(printerName);
    }
    return rv;
}

