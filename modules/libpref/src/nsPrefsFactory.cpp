/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
 *
 * The contents of this file are subject to the Netscape Public
 * License Version 1.1 (the "License"); you may not use this file
 * except in compliance with the License. You may obtain a copy of
 * the License at http://www.mozilla.org/NPL/
 *
 * Software distributed under the License is distributed on an "AS
 * IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
 * implied. See the License for the specific language governing
 * rights and limitations under the License.
 *
 * The Original Code is Mozilla Communicator client code.
 *
 * The Initial Developer of the Original Code is Netscape Communications
 * Corporation.  Portions created by Netscape are
 * Copyright (C) 1998 Netscape Communications Corporation. All
 * Rights Reserved.
 *
 * Contributor(s):
 * Brian Nesse <bnesse@netscape.com>
 */

#include "nsIGenericFactory.h"
#include "nsPrefService.h"
#include "nsPrefBranch.h"
#include "nsIPref.h"
#include "nsAutoConfig.h"

// remove this when nsPref goes away
extern NS_IMETHODIMP nsPrefConstructor(nsISupports *aOuter, REFNSIID aIID, void **aResult);


NS_GENERIC_FACTORY_CONSTRUCTOR_INIT(nsPrefService, Init)
NS_GENERIC_FACTORY_CONSTRUCTOR_INIT(nsPrefLocalizedString, Init)
  // Factory constructor for nsAutoConfig. nsAutoConfig doesn't have a 
  //separate module so it is bundled with pref module.
NS_GENERIC_FACTORY_CONSTRUCTOR_INIT(nsAutoConfig,Init)
 
// The list of components we register
static nsModuleComponentInfo components[] = 
{
  {
    NS_PREFSERVICE_CLASSNAME, 
    NS_PREFSERVICE_CID,
    NS_PREFSERVICE_CONTRACTID, 
    nsPrefServiceConstructor
  },

  {
    NS_PREFLOCALIZEDSTRING_CLASSNAME, 
    NS_PREFLOCALIZEDSTRING_CID,
    NS_PREFLOCALIZEDSTRING_CONTRACTID, 
    nsPrefLocalizedStringConstructor
  },

  { // remove this when nsPref goes away
    NS_PREF_CLASSNAME, 
    NS_PREF_CID,
    NS_PREF_CONTRACTID, 
    nsPrefConstructor
  },
  { 
    NS_AUTOCONFIG_CLASSNAME, 
    NS_AUTOCONFIG_CID, 
    NS_AUTOCONFIG_CONTRACTID, 
    nsAutoConfigConstructor
  },
};

NS_IMPL_NSGETMODULE(nsPrefModule, components);

