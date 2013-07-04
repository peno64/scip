/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class de_zib_jscip_nativ_jni_JniScipConsAbspower */

#ifndef _Included_de_zib_jscip_nativ_jni_JniScipConsAbspower
#define _Included_de_zib_jscip_nativ_jni_JniScipConsAbspower
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     de_zib_jscip_nativ_jni_JniScipConsAbspower
 * Method:    includeConshdlrAbspower
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_de_zib_jscip_nativ_jni_JniScipConsAbspower_includeConshdlrAbspower
  (JNIEnv *, jobject, jlong);

/*
 * Class:     de_zib_jscip_nativ_jni_JniScipConsAbspower
 * Method:    createConsAbspower
 * Signature: (JLjava/lang/String;JJDDDDDZZZZZZZZZZ)J
 */
JNIEXPORT jlong JNICALL Java_de_zib_jscip_nativ_jni_JniScipConsAbspower_createConsAbspower
  (JNIEnv *, jobject, jlong, jstring, jlong, jlong, jdouble, jdouble, jdouble, jdouble, jdouble, jboolean, jboolean, jboolean, jboolean, jboolean, jboolean, jboolean, jboolean, jboolean, jboolean);

/*
 * Class:     de_zib_jscip_nativ_jni_JniScipConsAbspower
 * Method:    createConsBasicAbspower
 * Signature: (JLjava/lang/String;JJDDDDD)J
 */
JNIEXPORT jlong JNICALL Java_de_zib_jscip_nativ_jni_JniScipConsAbspower_createConsBasicAbspower
  (JNIEnv *, jobject, jlong, jstring, jlong, jlong, jdouble, jdouble, jdouble, jdouble, jdouble);

/*
 * Class:     de_zib_jscip_nativ_jni_JniScipConsAbspower
 * Method:    getNlRowAbspower
 * Signature: (JJ[J)V
 */
JNIEXPORT void JNICALL Java_de_zib_jscip_nativ_jni_JniScipConsAbspower_getNlRowAbspower
  (JNIEnv *, jobject, jlong, jlong, jlongArray);

/*
 * Class:     de_zib_jscip_nativ_jni_JniScipConsAbspower
 * Method:    getNonlinearVarAbspower
 * Signature: (JJ)J
 */
JNIEXPORT jlong JNICALL Java_de_zib_jscip_nativ_jni_JniScipConsAbspower_getNonlinearVarAbspower
  (JNIEnv *, jobject, jlong, jlong);

/*
 * Class:     de_zib_jscip_nativ_jni_JniScipConsAbspower
 * Method:    getLinearVarAbspower
 * Signature: (JJ)J
 */
JNIEXPORT jlong JNICALL Java_de_zib_jscip_nativ_jni_JniScipConsAbspower_getLinearVarAbspower
  (JNIEnv *, jobject, jlong, jlong);

/*
 * Class:     de_zib_jscip_nativ_jni_JniScipConsAbspower
 * Method:    getExponentAbspower
 * Signature: (JJ)D
 */
JNIEXPORT jdouble JNICALL Java_de_zib_jscip_nativ_jni_JniScipConsAbspower_getExponentAbspower
  (JNIEnv *, jobject, jlong, jlong);

/*
 * Class:     de_zib_jscip_nativ_jni_JniScipConsAbspower
 * Method:    getOffsetAbspower
 * Signature: (JJ)D
 */
JNIEXPORT jdouble JNICALL Java_de_zib_jscip_nativ_jni_JniScipConsAbspower_getOffsetAbspower
  (JNIEnv *, jobject, jlong, jlong);

/*
 * Class:     de_zib_jscip_nativ_jni_JniScipConsAbspower
 * Method:    getCoefLinearAbspower
 * Signature: (JJ)D
 */
JNIEXPORT jdouble JNICALL Java_de_zib_jscip_nativ_jni_JniScipConsAbspower_getCoefLinearAbspower
  (JNIEnv *, jobject, jlong, jlong);

/*
 * Class:     de_zib_jscip_nativ_jni_JniScipConsAbspower
 * Method:    getLhsAbspower
 * Signature: (JJ)D
 */
JNIEXPORT jdouble JNICALL Java_de_zib_jscip_nativ_jni_JniScipConsAbspower_getLhsAbspower
  (JNIEnv *, jobject, jlong, jlong);

/*
 * Class:     de_zib_jscip_nativ_jni_JniScipConsAbspower
 * Method:    getRhsAbspower
 * Signature: (JJ)D
 */
JNIEXPORT jdouble JNICALL Java_de_zib_jscip_nativ_jni_JniScipConsAbspower_getRhsAbspower
  (JNIEnv *, jobject, jlong, jlong);

/*
 * Class:     de_zib_jscip_nativ_jni_JniScipConsAbspower
 * Method:    getViolationAbspower
 * Signature: (JJJ)D
 */
JNIEXPORT jdouble JNICALL Java_de_zib_jscip_nativ_jni_JniScipConsAbspower_getViolationAbspower
  (JNIEnv *, jobject, jlong, jlong, jlong);

#ifdef __cplusplus
}
#endif
#endif
