/* 
 * The contents of this file are subject to the Mozilla Public License
 * Version 1.0 (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS"
 * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See
 * the License for the specific language governing rights and limitations
 * under the License.
 *
 * The Initial Developer of the Original Code is Sun Microsystems,
 * Inc. Portions created by Sun are Copyright (C) 1999 Sun Microsystems,
 * Inc. All Rights Reserved. 
 */

/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class org_mozilla_pluglet_mozilla_PlugletPeerImpl */

#ifndef _Included_org_mozilla_pluglet_mozilla_PlugletPeerImpl
#define _Included_org_mozilla_pluglet_mozilla_PlugletPeerImpl
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_mozilla_pluglet_mozilla_PlugletPeerImpl
 * Method:    getMIMEType
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_pluglet_mozilla_PlugletPeerImpl_getMIMEType
  (JNIEnv *, jobject);

/*
 * Class:     org_mozilla_pluglet_mozilla_PlugletInstancePeerImpl
 * Method:    getMode
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_mozilla_pluglet_mozilla_PlugletPeerImpl_getMode
  (JNIEnv *, jobject);

/*
 * Class:     org_mozilla_pluglet_mozilla_PlugletPeerImpl
 * Method:    getValue
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_mozilla_pluglet_mozilla_PlugletPeerImpl_getValue
  (JNIEnv *, jobject, jint);

/*
 * Class:     org_mozilla_pluglet_mozilla_PlugletPeerImpl
 * Method:    newStream
 * Signature: (Ljava/lang/String;Ljava/lang/String;)Ljava/io/OutputStream;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_pluglet_mozilla_PlugletPeerImpl_newStream
  (JNIEnv *, jobject, jstring, jstring);

/*
 * Class:     org_mozilla_pluglet_mozilla_PlugletPeerImpl
 * Method:    showStatus
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_pluglet_mozilla_PlugletPeerImpl_showStatus
  (JNIEnv *, jobject, jstring);

/*
 * Class:     org_mozilla_pluglet_mozilla_PlugletPeerImpl
 * Method:    setWindowSize
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_org_mozilla_pluglet_mozilla_PlugletPeerImpl_setWindowSize
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     org_mozilla_pluglet_mozilla_PlugletPeerImpl
 * Method:    getTagInfo
 * Signature: ()Lorg/mozilla/pluglet/mozilla/PlugletTagInfo;
 */
JNIEXPORT jobject JNICALL Java_org_mozilla_pluglet_mozilla_PlugletPeerImpl_getTagInfo
  (JNIEnv *, jobject);

/*
 * Class:     org_mozilla_pluglet_mozilla_PlugletPeerImpl
 * Method:    nativeFinalize
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_pluglet_mozilla_PlugletPeerImpl_nativeFinalize
  (JNIEnv *, jobject);

/*
 * Class:     org_mozilla_pluglet_mozilla_PlugletPeerImpl
 * Method:    nativeInitialize
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_mozilla_pluglet_mozilla_PlugletPeerImpl_nativeInitialize
  (JNIEnv *, jobject);

#ifdef __cplusplus
}
#endif
#endif
