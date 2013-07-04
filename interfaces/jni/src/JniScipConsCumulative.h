/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class de_zib_jscip_nativ_jni_JniScipConsCumulative */

#ifndef _Included_de_zib_jscip_nativ_jni_JniScipConsCumulative
#define _Included_de_zib_jscip_nativ_jni_JniScipConsCumulative
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     de_zib_jscip_nativ_jni_JniScipConsCumulative
 * Method:    includeConshdlrCumulative
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_de_zib_jscip_nativ_jni_JniScipConsCumulative_includeConshdlrCumulative
  (JNIEnv *, jobject, jlong);

/*
 * Class:     de_zib_jscip_nativ_jni_JniScipConsCumulative
 * Method:    createConsCumulative
 * Signature: (JLjava/lang/String;I[J[I[IIZZZZZZZZZZ)J
 */
JNIEXPORT jlong JNICALL Java_de_zib_jscip_nativ_jni_JniScipConsCumulative_createConsCumulative
  (JNIEnv *, jobject, jlong, jstring, jint, jlongArray, jintArray, jintArray, jint, jboolean, jboolean, jboolean, jboolean, jboolean, jboolean, jboolean, jboolean, jboolean, jboolean);

/*
 * Class:     de_zib_jscip_nativ_jni_JniScipConsCumulative
 * Method:    createConsBasicCumulative
 * Signature: (JLjava/lang/String;I[J[I[II)J
 */
JNIEXPORT jlong JNICALL Java_de_zib_jscip_nativ_jni_JniScipConsCumulative_createConsBasicCumulative
  (JNIEnv *, jobject, jlong, jstring, jint, jlongArray, jintArray, jintArray, jint);

/*
 * Class:     de_zib_jscip_nativ_jni_JniScipConsCumulative
 * Method:    setHminCumulative
 * Signature: (JJI)V
 */
JNIEXPORT void JNICALL Java_de_zib_jscip_nativ_jni_JniScipConsCumulative_setHminCumulative
  (JNIEnv *, jobject, jlong, jlong, jint);

/*
 * Class:     de_zib_jscip_nativ_jni_JniScipConsCumulative
 * Method:    getHminCumulative
 * Signature: (JJ)I
 */
JNIEXPORT jint JNICALL Java_de_zib_jscip_nativ_jni_JniScipConsCumulative_getHminCumulative
  (JNIEnv *, jobject, jlong, jlong);

/*
 * Class:     de_zib_jscip_nativ_jni_JniScipConsCumulative
 * Method:    setHmaxCumulative
 * Signature: (JJI)V
 */
JNIEXPORT void JNICALL Java_de_zib_jscip_nativ_jni_JniScipConsCumulative_setHmaxCumulative
  (JNIEnv *, jobject, jlong, jlong, jint);

/*
 * Class:     de_zib_jscip_nativ_jni_JniScipConsCumulative
 * Method:    getHmaxCumulative
 * Signature: (JJ)I
 */
JNIEXPORT jint JNICALL Java_de_zib_jscip_nativ_jni_JniScipConsCumulative_getHmaxCumulative
  (JNIEnv *, jobject, jlong, jlong);

/*
 * Class:     de_zib_jscip_nativ_jni_JniScipConsCumulative
 * Method:    getVarsCumulative
 * Signature: (JJ)[J
 */
JNIEXPORT jlongArray JNICALL Java_de_zib_jscip_nativ_jni_JniScipConsCumulative_getVarsCumulative
  (JNIEnv *, jobject, jlong, jlong);

/*
 * Class:     de_zib_jscip_nativ_jni_JniScipConsCumulative
 * Method:    getNVarsCumulative
 * Signature: (JJ)I
 */
JNIEXPORT jint JNICALL Java_de_zib_jscip_nativ_jni_JniScipConsCumulative_getNVarsCumulative
  (JNIEnv *, jobject, jlong, jlong);

/*
 * Class:     de_zib_jscip_nativ_jni_JniScipConsCumulative
 * Method:    getCapacityCumulative
 * Signature: (JJ)I
 */
JNIEXPORT jint JNICALL Java_de_zib_jscip_nativ_jni_JniScipConsCumulative_getCapacityCumulative
  (JNIEnv *, jobject, jlong, jlong);

/*
 * Class:     de_zib_jscip_nativ_jni_JniScipConsCumulative
 * Method:    getDurationsCumulative
 * Signature: (JJ)[I
 */
JNIEXPORT jintArray JNICALL Java_de_zib_jscip_nativ_jni_JniScipConsCumulative_getDurationsCumulative
  (JNIEnv *, jobject, jlong, jlong);

/*
 * Class:     de_zib_jscip_nativ_jni_JniScipConsCumulative
 * Method:    getDemandsCumulative
 * Signature: (JJ)[I
 */
JNIEXPORT jintArray JNICALL Java_de_zib_jscip_nativ_jni_JniScipConsCumulative_getDemandsCumulative
  (JNIEnv *, jobject, jlong, jlong);

/*
 * Class:     de_zib_jscip_nativ_jni_JniScipConsCumulative
 * Method:    checkCumulativeCondition
 * Signature: (JJI[J[I[IIIIJZ)Z
 */
JNIEXPORT jboolean JNICALL Java_de_zib_jscip_nativ_jni_JniScipConsCumulative_checkCumulativeCondition
  (JNIEnv *, jobject, jlong, jlong, jint, jlongArray, jintArray, jintArray, jint, jint, jint, jlong, jboolean);

/*
 * Class:     de_zib_jscip_nativ_jni_JniScipConsCumulative
 * Method:    respropCumulativeCondition
 * Signature: (JI[J[I[IIIIJIIJD[Z)I
 */
JNIEXPORT jint JNICALL Java_de_zib_jscip_nativ_jni_JniScipConsCumulative_respropCumulativeCondition
  (JNIEnv *, jobject, jlong, jint, jlongArray, jintArray, jintArray, jint, jint, jint, jlong, jint, jint, jlong, jdouble, jbooleanArray);

/*
 * Class:     de_zib_jscip_nativ_jni_JniScipConsCumulative
 * Method:    visualizeConsCumulative
 * Signature: (JJ)V
 */
JNIEXPORT void JNICALL Java_de_zib_jscip_nativ_jni_JniScipConsCumulative_visualizeConsCumulative
  (JNIEnv *, jobject, jlong, jlong);

#ifdef __cplusplus
}
#endif
#endif
