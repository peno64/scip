/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class de_zib_jscip_nativ_jni_JniScipSepa */

#ifndef _Included_de_zib_jscip_nativ_jni_JniScipSepa
#define _Included_de_zib_jscip_nativ_jni_JniScipSepa
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     de_zib_jscip_nativ_jni_JniScipSepa
 * Method:    sepaGetData
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_de_zib_jscip_nativ_jni_JniScipSepa_sepaGetData
  (JNIEnv *, jobject, jlong);

/*
 * Class:     de_zib_jscip_nativ_jni_JniScipSepa
 * Method:    sepaSetData
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_de_zib_jscip_nativ_jni_JniScipSepa_sepaSetData
  (JNIEnv *, jobject, jlong, jlong);

/*
 * Class:     de_zib_jscip_nativ_jni_JniScipSepa
 * Method:    sepaGetName
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_de_zib_jscip_nativ_jni_JniScipSepa_sepaGetName
  (JNIEnv *, jobject, jlong);

/*
 * Class:     de_zib_jscip_nativ_jni_JniScipSepa
 * Method:    sepaGetDesc
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_de_zib_jscip_nativ_jni_JniScipSepa_sepaGetDesc
  (JNIEnv *, jobject, jlong);

/*
 * Class:     de_zib_jscip_nativ_jni_JniScipSepa
 * Method:    sepaGetPriority
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_de_zib_jscip_nativ_jni_JniScipSepa_sepaGetPriority
  (JNIEnv *, jobject, jlong);

/*
 * Class:     de_zib_jscip_nativ_jni_JniScipSepa
 * Method:    sepaGetFreq
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_de_zib_jscip_nativ_jni_JniScipSepa_sepaGetFreq
  (JNIEnv *, jobject, jlong);

/*
 * Class:     de_zib_jscip_nativ_jni_JniScipSepa
 * Method:    sepaSetFreq
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_de_zib_jscip_nativ_jni_JniScipSepa_sepaSetFreq
  (JNIEnv *, jobject, jlong, jint);

/*
 * Class:     de_zib_jscip_nativ_jni_JniScipSepa
 * Method:    sepaGetMaxbounddist
 * Signature: (J)D
 */
JNIEXPORT jdouble JNICALL Java_de_zib_jscip_nativ_jni_JniScipSepa_sepaGetMaxbounddist
  (JNIEnv *, jobject, jlong);

/*
 * Class:     de_zib_jscip_nativ_jni_JniScipSepa
 * Method:    sepaUsesSubscip
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_de_zib_jscip_nativ_jni_JniScipSepa_sepaUsesSubscip
  (JNIEnv *, jobject, jlong);

/*
 * Class:     de_zib_jscip_nativ_jni_JniScipSepa
 * Method:    sepaGetSetupTime
 * Signature: (J)D
 */
JNIEXPORT jdouble JNICALL Java_de_zib_jscip_nativ_jni_JniScipSepa_sepaGetSetupTime
  (JNIEnv *, jobject, jlong);

/*
 * Class:     de_zib_jscip_nativ_jni_JniScipSepa
 * Method:    sepaGetTime
 * Signature: (J)D
 */
JNIEXPORT jdouble JNICALL Java_de_zib_jscip_nativ_jni_JniScipSepa_sepaGetTime
  (JNIEnv *, jobject, jlong);

/*
 * Class:     de_zib_jscip_nativ_jni_JniScipSepa
 * Method:    sepaGetNCalls
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_de_zib_jscip_nativ_jni_JniScipSepa_sepaGetNCalls
  (JNIEnv *, jobject, jlong);

/*
 * Class:     de_zib_jscip_nativ_jni_JniScipSepa
 * Method:    sepaGetNCallsAtNode
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_de_zib_jscip_nativ_jni_JniScipSepa_sepaGetNCallsAtNode
  (JNIEnv *, jobject, jlong);

/*
 * Class:     de_zib_jscip_nativ_jni_JniScipSepa
 * Method:    sepaGetNCutoffs
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_de_zib_jscip_nativ_jni_JniScipSepa_sepaGetNCutoffs
  (JNIEnv *, jobject, jlong);

/*
 * Class:     de_zib_jscip_nativ_jni_JniScipSepa
 * Method:    sepaGetNCutsFound
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_de_zib_jscip_nativ_jni_JniScipSepa_sepaGetNCutsFound
  (JNIEnv *, jobject, jlong);

/*
 * Class:     de_zib_jscip_nativ_jni_JniScipSepa
 * Method:    sepaGetNCutsApplied
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_de_zib_jscip_nativ_jni_JniScipSepa_sepaGetNCutsApplied
  (JNIEnv *, jobject, jlong);

/*
 * Class:     de_zib_jscip_nativ_jni_JniScipSepa
 * Method:    sepaGetNCutsFoundAtNode
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_de_zib_jscip_nativ_jni_JniScipSepa_sepaGetNCutsFoundAtNode
  (JNIEnv *, jobject, jlong);

/*
 * Class:     de_zib_jscip_nativ_jni_JniScipSepa
 * Method:    sepaGetNConssFound
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_de_zib_jscip_nativ_jni_JniScipSepa_sepaGetNConssFound
  (JNIEnv *, jobject, jlong);

/*
 * Class:     de_zib_jscip_nativ_jni_JniScipSepa
 * Method:    sepaGetNDomredsFound
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_de_zib_jscip_nativ_jni_JniScipSepa_sepaGetNDomredsFound
  (JNIEnv *, jobject, jlong);

/*
 * Class:     de_zib_jscip_nativ_jni_JniScipSepa
 * Method:    sepaIsDelayed
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_de_zib_jscip_nativ_jni_JniScipSepa_sepaIsDelayed
  (JNIEnv *, jobject, jlong);

/*
 * Class:     de_zib_jscip_nativ_jni_JniScipSepa
 * Method:    sepaWasLPDelayed
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_de_zib_jscip_nativ_jni_JniScipSepa_sepaWasLPDelayed
  (JNIEnv *, jobject, jlong);

/*
 * Class:     de_zib_jscip_nativ_jni_JniScipSepa
 * Method:    sepaWasSolDelayed
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_de_zib_jscip_nativ_jni_JniScipSepa_sepaWasSolDelayed
  (JNIEnv *, jobject, jlong);

/*
 * Class:     de_zib_jscip_nativ_jni_JniScipSepa
 * Method:    sepaIsInitialized
 * Signature: (J)Z
 */
JNIEXPORT jboolean JNICALL Java_de_zib_jscip_nativ_jni_JniScipSepa_sepaIsInitialized
  (JNIEnv *, jobject, jlong);

#ifdef __cplusplus
}
#endif
#endif
