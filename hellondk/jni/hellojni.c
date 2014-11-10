#include <jni.h>
#include "include/hellojni.h"

JNIEXPORT jstring JNICALL Java_com_example_hellojni_MainActivity_getMessage
	(JNIEnv *env, jobject thisObj) {
	
	return (*env)->NewStringUTF(env, "Hello from native code!");
}

