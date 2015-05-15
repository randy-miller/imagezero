#include "test_ImageZeroJNI.h"
#include "file.h"
#include "libiz.h"
#include "image.h"
#include "portableimage.h"

unsigned char* as_unsigned_char_array(JNIEnv *env, jbyteArray array) {
    int len = env->GetArrayLength (array);
    unsigned char *buf = new unsigned char[len];
    env->GetByteArrayRegion (array, 0, len, reinterpret_cast<jbyte*>(buf));
    return buf;
}

JNIEXPORT jint JNICALL Java_test_ImageZeroJNI_encodeImage
  (JNIEnv *env, jclass thisClass, jbyteArray input, jbyteArray output)
{
    PortableImage pi;

    pi.readHeader(as_unsigned_char_array(env, input));
    IZ::initEncodeTable();
    jbyte *output_pointer = env->GetByteArrayElements(output, NULL);
    unsigned char *end_pointer = IZ::encodeImage(pi, (unsigned char *) output_pointer);

    // return size of data written
    int size = end_pointer - (unsigned char *) output_pointer;

    env->ReleaseByteArrayElements(output, output_pointer, 0);

    return size;
}

JNIEXPORT void JNICALL Java_test_ImageZeroJNI_decodeImage
  (JNIEnv *env, jclass thisClass, jbyteArray input, jbyteArray output)
{
    PortableImage pi;

    OutputFile outfile("placeholder");
    
    jbyte *output_pointer = env->GetByteArrayElements(output, NULL);
    unsigned char *input_pointer = as_unsigned_char_array(env, input);

    IZ::initDecodeTable();    
    IZ::decodeImageSize(pi, input_pointer);
    pi.setComponents(3);

    pi.writeHeader((unsigned char *) output_pointer);
    IZ::decodeImage(pi, input_pointer);

    env->ReleaseByteArrayElements(output, output_pointer, 0);
}

JNIEXPORT jint JNICALL Java_test_ImageZeroJNI_getImageSize
  (JNIEnv *env, jclass thisClass, jbyteArray input)
{   
    PortableImage pi;
    unsigned char *input_pointer = as_unsigned_char_array(env, input);

    IZ::decodeImageSize(pi, input_pointer);
    pi.setComponents(3);
    const unsigned int data_size = pi.width() * pi.height() * pi.components() + 33;

    return data_size;
}


