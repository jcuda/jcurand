/*
 * JCurand - Java bindings for CURAND, the NVIDIA CUDA random
 * number generation library, to be used with JCuda
 *
 * Copyright (c) 2010-2015 Marco Hutter - http://www.jcuda.org
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include "JCurand.hpp"
#include "JCurand_common.hpp"
#include <iostream>
#include <string>

/**
 * Called when the library is loaded. Will initialize all
 * required field and method IDs
 */
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *jvm, void *reserved)
{
    JNIEnv *env = NULL;
    if (jvm->GetEnv((void **)&env, JNI_VERSION_1_4))
    {
        return JNI_ERR;
    }

    Logger::log(LOG_TRACE, "Initializing JCurand\n");

    jclass cls = NULL;

    // Initialize the JNIUtils and PointerUtils
    if (initJNIUtils(env) == JNI_ERR) return JNI_ERR;
    if (initPointerUtils(env) == JNI_ERR) return JNI_ERR;

    return JNI_VERSION_1_4;
}


/*
 * Set the log level
 *
 * Class:     jcuda_jcurand_JCurand
 * Method:    setLogLevelNative
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_jcuda_jcurand_JCurand_setLogLevelNative
  (JNIEnv *env, jclass cla, jint logLevel)
{
    Logger::setLogLevel((LogLevel)logLevel);
}






/**
 * Converts the given jobject
 * into a int*
 * and returns whether this conversion succeeded.
 */
bool toNative(JNIEnv *env, jobject &input, int* &output)
{
    output = (int*)getPointer(env, input);
    return true;
}

/**
 * Converts the given jobject
 * into a unsigned int*
 * and returns whether this conversion succeeded.
 */
bool toNative(JNIEnv *env, jobject &input, unsigned int* &output)
{
    output = (unsigned int*)getPointer(env, input);
    return true;
}

/**
 * Converts the given jobject
 * into a float*
 * and returns whether this conversion succeeded.
 */
bool toNative(JNIEnv *env, jobject &input, float* &output)
{
    output = (float*)getPointer(env, input);
    return true;
}

/**
 * Converts the given jobject
 * into a double*
 * and returns whether this conversion succeeded.
 */
bool toNative(JNIEnv *env, jobject &input, double* &output)
{
    output = (double*)getPointer(env, input);
    return true;
}


JNIEXPORT jint JNICALL Java_jcuda_jcurand_JCurand_curandGetPropertyNative(JNIEnv *env, jclass cls, jint type, jintArray value)
{
    // Null-checks for non-primitive arguments
    // type is primitive
    if (value == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'value' is null for curandGetProperty");
        return JCURAND_STATUS_INTERNAL_ERROR;
    }

    // Log message
    Logger::log(LOG_TRACE, "Executing curandGetProperty(type=%d, value=%p)\n",
        type, value);

    // Native variable declarations
    libraryPropertyType type_native;
    int value_native;

    // Obtain native variable values
    type_native = (libraryPropertyType)type;
    // value is write-only

    // Native function call
    curandStatus_t jniResult_native = curandGetProperty(type_native, &value_native);

    // Write back native variable values
    // type is primitive
    if (!set(env, value, 0, (jint)value_native)) return JCURAND_STATUS_INTERNAL_ERROR;

    // Return the result
    jint jniResult = (jint)jniResult_native;
    return jniResult;
}






//=== Auto-generated part: ===================================================

/**
 * <pre>
 * \brief Create new random number generator.
 *
 * Creates a new random number generator of type \p rng_type
 * and returns it in \p *generator.
 *
 * Legal values for \p rng_type are:
 * - CURAND_RNG_PSEUDO_DEFAULT
 * - CURAND_RNG_PSEUDO_XORWOW
 * - CURAND_RNG_QUASI_DEFAULT
 * - CURAND_RNG_QUASI_SOBOL32
 * - CURAND_RNG_QUASI_SCRAMBLED_SOBOL32
 * - CURAND_RNG_QUASI_SOBOL64
 * - CURAND_RNG_QUASI_SCRAMBLED_SOBOL64
 *
 * When \p rng_type is CURAND_RNG_PSEUDO_DEFAULT, the type chosen
 * is CURAND_RNG_PSEUDO_XORWOW.  \n
 * When \p rng_type is CURAND_RNG_QUASI_DEFAULT,
 * the type chosen is CURAND_RNG_QUASI_SOBOL32.
 *
 * The default values for \p rng_type = CURAND_RNG_PSEUDO_XORWOW are:
 * - \p seed = 0
 * - \p offset = 0
 * - \p ordering = CURAND_ORDERING_PSEUDO_DEFAULT
 *
 * The default values for \p rng_type = CURAND_RNG_QUASI_SOBOL32 are:
 * - \p dimensions = 1
 * - \p offset = 0
 * - \p ordering = CURAND_ORDERING_QUASI_DEFAULT
 *
 * The default values for \p rng_type = CURAND_RNG_QUASI_SOBOL64 are:
 * - \p dimensions = 1
 * - \p offset = 0
 * - \p ordering = CURAND_ORDERING_QUASI_DEFAULT
 *
 * The default values for \p rng_type = CURAND_RNG_QUASI_SCRAMBBLED_SOBOL32 are:
 * - \p dimensions = 1
 * - \p offset = 0
 * - \p ordering = CURAND_ORDERING_QUASI_DEFAULT
 *
 * The default values for \p rng_type = CURAND_RNG_QUASI_SCRAMBLED_SOBOL64 are:
 * - \p dimensions = 1
 * - \p offset = 0
 * - \p ordering = CURAND_ORDERING_QUASI_DEFAULT
 *
 * @param generator - Pointer to generator
 * @param rng_type - Type of generator to create
 *
 * @return
 *
 * CURAND_STATUS_ALLOCATION_FAILED if memory could not be allocated \n
 * CURAND_STATUS_INITIALIZATION_FAILED if there was a problem setting up the GPU \n
 * CURAND_STATUS_VERSION_MISMATCH if the header file version does not match the
 *   dynamically linked library version \n
 * CURAND_STATUS_TYPE_ERROR if the value for \p rng_type is invalid \n
 * CURAND_STATUS_SUCCESS if generator was created successfully \n
 * </pre>
 */
JNIEXPORT jint JNICALL Java_jcuda_jcurand_JCurand_curandCreateGeneratorNative(JNIEnv *env, jclass cls, jobject generator, jint rng_type)
{
    // Null-checks for non-primitive arguments
    if (generator == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'generator' is null for curandCreateGenerator");
        return JCURAND_STATUS_INTERNAL_ERROR;
    }

    // Log message
    Logger::log(LOG_TRACE, "Executing curandCreateGenerator(generator=%p, rng_type=%d)\n",
        generator, rng_type);

    // Native variable declarations
    curandGenerator_t generator_native;
    curandRngType_t rng_type_native;

    // Obtain native variable values
    rng_type_native = (curandRngType_t)rng_type;

    // Native function call
    curandStatus_t result_native = curandCreateGenerator(&generator_native, rng_type_native);

    // Write back native variable values
    setNativePointerValue(env, generator, (jlong)generator_native);

    // Return the result
    return (jint)result_native;
}

/**
 * <pre>
 * \brief Create new host CPU random number generator.
 *
 * Creates a new host CPU random number generator of type \p rng_type
 * and returns it in \p *generator.
 *
 * Legal values for \p rng_type are:
 * - CURAND_RNG_PSEUDO_DEFAULT
 * - CURAND_RNG_PSEUDO_XORWOW
 * - CURAND_RNG_QUASI_DEFAULT
 * - CURAND_RNG_QUASI_SOBOL32
 *
 * When \p rng_type is CURAND_RNG_PSEUDO_DEFAULT, the type chosen
 * is CURAND_RNG_PSEUDO_XORWOW.  \n
 * When \p rng_type is CURAND_RNG_QUASI_DEFAULT,
 * the type chosen is CURAND_RNG_QUASI_SOBOL32.
 *
 * The default values for \p rng_type = CURAND_RNG_PSEUDO_XORWOW are:
 * - \p seed = 0
 * - \p offset = 0
 * - \p ordering = CURAND_ORDERING_PSEUDO_DEFAULT
 *
 * The default values for \p rng_type = CURAND_RNG_QUASI_SOBOL32 are:
 * - \p dimensions = 1
 * - \p offset = 0
 * - \p ordering = CURAND_ORDERING_QUASI_DEFAULT
 *
 * The default values for \p rng_type = CURAND_RNG_QUASI_SOBOL64 are:
 * - \p dimensions = 1
 * - \p offset = 0
 * - \p ordering = CURAND_ORDERING_QUASI_DEFAULT
 *
 * The default values for \p rng_type = CURAND_RNG_QUASI_SCRAMBLED_SOBOL32 are:
 * - \p dimensions = 1
 * - \p offset = 0
 * - \p ordering = CURAND_ORDERING_QUASI_DEFAULT
 *
 * The default values for \p rng_type = CURAND_RNG_QUASI_SCRAMBLED_SOBOL64 are:
 * - \p dimensions = 1
 * - \p offset = 0
 * - \p ordering = CURAND_ORDERING_QUASI_DEFAULT
 *
 * @param generator - Pointer to generator
 * @param rng_type - Type of generator to create
 *
 * @return
 *
 * CURAND_STATUS_ALLOCATION_FAILED if memory could not be allocated \n
 * CURAND_STATUS_INITIALIZATION_FAILED if there was a problem setting up the GPU \n
 * CURAND_STATUS_VERSION_MISMATCH if the header file version does not match the
 *   dynamically linked library version \n
 * CURAND_STATUS_TYPE_ERROR if the value for \p rng_type is invalid \n
 * CURAND_STATUS_SUCCESS if generator was created successfully \n
 * </pre>
 */
JNIEXPORT jint JNICALL Java_jcuda_jcurand_JCurand_curandCreateGeneratorHostNative(JNIEnv *env, jclass cls, jobject generator, jint rng_type)
{
    // Null-checks for non-primitive arguments
    if (generator == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'generator' is null for curandCreateGeneratorHost");
        return JCURAND_STATUS_INTERNAL_ERROR;
    }

    // Log message
    Logger::log(LOG_TRACE, "Executing curandCreateGeneratorHost(generator=%p, rng_type=%d)\n",
        generator, rng_type);

    // Native variable declarations
    curandGenerator_t generator_native;
    curandRngType_t rng_type_native;

    // Obtain native variable values
    rng_type_native = (curandRngType_t)rng_type;

    // Native function call
    curandStatus_t result_native = curandCreateGeneratorHost(&generator_native, rng_type_native);

    // Write back native variable values
    setNativePointerValue(env, generator, (jlong)generator_native);

    // Return the result
    return (jint)result_native;
}

/**
 * <pre>
 * \brief Destroy an existing generator.
 *
 * Destroy an existing generator and free all memory associated with its state.
 *
 * @param generator - Generator to destroy
 *
 * @return
 *
 * CURAND_STATUS_NOT_INITIALIZED if the generator was never created \n
 * CURAND_STATUS_SUCCESS if generator was destroyed successfully \n
 * </pre>
 */
JNIEXPORT jint JNICALL Java_jcuda_jcurand_JCurand_curandDestroyGeneratorNative(JNIEnv *env, jclass cls, jobject generator)
{
    // Null-checks for non-primitive arguments
    if (generator == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'generator' is null for curandDestroyGenerator");
        return JCURAND_STATUS_INTERNAL_ERROR;
    }

    // Log message
    Logger::log(LOG_TRACE, "Executing curandDestroyGenerator(generator=%p)\n",
        generator);

    // Native variable declarations
    curandGenerator_t generator_native;

    // Obtain native variable values
    generator_native = (curandGenerator_t)getNativePointerValue(env, generator);

    // Native function call
    curandStatus_t result_native = curandDestroyGenerator(generator_native);

    // Return the result
    return (jint)result_native;
}

/**
 * <pre>
 * \brief Return the version number of the library.
 *
 * Return in \p *version the version number of the dynamically linked CURAND
 * library.  The format is the same as CUDART_VERSION from the CUDA Runtime.
 * The only supported configuration is CURAND version equal to CUDA Runtime
 * version.
 *
 * @param version - CURAND library version
 *
 * @return
 *
 * CURAND_STATUS_SUCCESS if the version number was successfully returned \n
 * </pre>
 */
JNIEXPORT jint JNICALL Java_jcuda_jcurand_JCurand_curandGetVersionNative(JNIEnv *env, jclass cls, jintArray version)
{
    // Null-checks for non-primitive arguments
    if (version == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'version' is null for curandGetVersion");
        return JCURAND_STATUS_INTERNAL_ERROR;
    }

    // Log message
    Logger::log(LOG_TRACE, "Executing curandGetVersion(version=%p)\n",
        version);

    // Native variable declarations
    int version_native;

    // Native function call
    curandStatus_t result_native = curandGetVersion(&version_native);

    // Write back native variable values
    set(env, version, 0, (jint)version_native);

    // Return the result
    return (jint)result_native;
}

/**
 * <pre>
 * \brief Set the current stream for CURAND kernel launches.
 *
 * Set the current stream for CURAND kernel launches.  All library functions
 * will use this stream until set again.
 *
 * @param generator - Generator to modify
 * @param stream - Stream to use or ::NULL for null stream
 *
 * @return
 *
 * CURAND_STATUS_NOT_INITIALIZED if the generator was never created \n
 * CURAND_STATUS_SUCCESS if stream was set successfully \n
 * </pre>
 */
JNIEXPORT jint JNICALL Java_jcuda_jcurand_JCurand_curandSetStreamNative(JNIEnv *env, jclass cls, jobject generator, jobject stream)
{
    // Null-checks for non-primitive arguments
    if (generator == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'generator' is null for curandSetStream");
        return JCURAND_STATUS_INTERNAL_ERROR;
    }
    if (stream == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'stream' is null for curandSetStream");
        return JCURAND_STATUS_INTERNAL_ERROR;
    }

    // Log message
    Logger::log(LOG_TRACE, "Executing curandSetStream(generator=%p, stream=%p)\n",
        generator, stream);

    // Native variable declarations
    curandGenerator_t generator_native;
    cudaStream_t stream_native;

    // Obtain native variable values
    generator_native = (curandGenerator_t)getNativePointerValue(env, generator);
    stream_native = (cudaStream_t)getNativePointerValue(env, stream);

    // Native function call
    curandStatus_t result_native = curandSetStream(generator_native, stream_native);

    // Return the result
    return (jint)result_native;
}

/**
 * <pre>
 * \brief Set the seed value of the pseudo-random number generator.
 *
 * Set the seed value of the pseudorandom number generator.
 * All values of seed are valid.  Different seeds will produce different sequences.
 * Different seeds will often not be statistically correlated with each other,
 * but some pairs of seed values may generate sequences which are statistically correlated.
 *
 * @param generator - Generator to modify
 * @param seed - Seed value
 *
 * @return
 *
 * CURAND_STATUS_NOT_INITIALIZED if the generator was never created \n
 * CURAND_STATUS_TYPE_ERROR if the generator is not a pseudorandom number generator \n
 * CURAND_STATUS_SUCCESS if generator seed was set successfully \n
 * </pre>
 */
JNIEXPORT jint JNICALL Java_jcuda_jcurand_JCurand_curandSetPseudoRandomGeneratorSeedNative(JNIEnv *env, jclass cls, jobject generator, jlong seed)
{
    // Null-checks for non-primitive arguments
    if (generator == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'generator' is null for curandSetPseudoRandomGeneratorSeed");
        return JCURAND_STATUS_INTERNAL_ERROR;
    }

    // Log message
    Logger::log(LOG_TRACE, "Executing curandSetPseudoRandomGeneratorSeed(generator=%p, seed=%p)\n",
        generator, seed);

    // Native variable declarations
    curandGenerator_t generator_native;
    unsigned long long seed_native;

    // Obtain native variable values
    generator_native = (curandGenerator_t)getNativePointerValue(env, generator);
    seed_native = (unsigned long long)seed;

    // Native function call
    curandStatus_t result_native = curandSetPseudoRandomGeneratorSeed(generator_native, seed_native);

    // Return the result
    return (jint)result_native;
}

/**
 * <pre>
 * \brief Set the absolute offset of the pseudo or quasirandom number generator.
 *
 * Set the absolute offset of the pseudo or quasirandom number generator.
 *
 * All values of offset are valid.  The offset position is absolute, not
 * relative to the current position in the sequence.
 *
 * @param generator - Generator to modify
 * @param offset - Absolute offset position
 *
 * @return
 *
 * CURAND_STATUS_NOT_INITIALIZED if the generator was never created \n
 * CURAND_STATUS_SUCCESS if generator offset was set successfully \n
 * </pre>
 */
JNIEXPORT jint JNICALL Java_jcuda_jcurand_JCurand_curandSetGeneratorOffsetNative(JNIEnv *env, jclass cls, jobject generator, jlong offset)
{
    // Null-checks for non-primitive arguments
    if (generator == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'generator' is null for curandSetGeneratorOffset");
        return JCURAND_STATUS_INTERNAL_ERROR;
    }

    // Log message
    Logger::log(LOG_TRACE, "Executing curandSetGeneratorOffset(generator=%p, offset=%p)\n",
        generator, offset);

    // Native variable declarations
    curandGenerator_t generator_native;
    unsigned long long offset_native;

    // Obtain native variable values
    generator_native = (curandGenerator_t)getNativePointerValue(env, generator);
    offset_native = (unsigned long long)offset;

    // Native function call
    curandStatus_t result_native = curandSetGeneratorOffset(generator_native, offset_native);

    // Return the result
    return (jint)result_native;
}

/**
 * <pre>
 * \brief Set the ordering of results of the pseudo or quasirandom number generator.
 *
 * Set the ordering of results of the pseudo or quasirandom number generator.
 *
 * Legal values of \p order for pseudorandom generators are:
 * - CURAND_ORDERING_PSEUDO_DEFAULT
 * - CURAND_ORDERING_PSEUDO_BEST
 * - CURAND_ORDERING_PSEUDO_SEEDED
 *
 * Legal values of \p order for quasirandom generators are:
 * - CURAND_ORDERING_QUASI_DEFAULT
 *
 * @param generator - Generator to modify
 * @param order - Ordering of results
 *
 * @return
 *
 * CURAND_STATUS_NOT_INITIALIZED if the generator was never created \n
 * CURAND_STATUS_OUT_OF_RANGE if the ordering is not valid \n
 * CURAND_STATUS_SUCCESS if generator ordering was set successfully \n
 * </pre>
 */
JNIEXPORT jint JNICALL Java_jcuda_jcurand_JCurand_curandSetGeneratorOrderingNative(JNIEnv *env, jclass cls, jobject generator, jint order)
{
    // Null-checks for non-primitive arguments
    if (generator == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'generator' is null for curandSetGeneratorOrdering");
        return JCURAND_STATUS_INTERNAL_ERROR;
    }

    // Log message
    Logger::log(LOG_TRACE, "Executing curandSetGeneratorOrdering(generator=%p, order=%d)\n",
        generator, order);

    // Native variable declarations
    curandGenerator_t generator_native;
    curandOrdering_t order_native;

    // Obtain native variable values
    generator_native = (curandGenerator_t)getNativePointerValue(env, generator);
    order_native = (curandOrdering_t)order;

    // Native function call
    curandStatus_t result_native = curandSetGeneratorOrdering(generator_native, order_native);

    // Return the result
    return (jint)result_native;
}

/**
 * <pre>
 * \brief Set the number of dimensions.
 *
 * Set the number of dimensions to be generated by the quasirandom number
 * generator.
 *
 * Legal values for \p num_dimensions are 1 to 20000.
 *
 * @param generator - Generator to modify
 * @param num_dimensions - Number of dimensions
 *
 * @return
 *
 * CURAND_STATUS_NOT_INITIALIZED if the generator was never created \n
 * CURAND_STATUS_OUT_OF_RANGE if num_dimensions is not valid \n
 * CURAND_STATUS_TYPE_ERROR if the generator is not a quasirandom number generator \n
 * CURAND_STATUS_SUCCESS if generator ordering was set successfully \n
 * </pre>
 */
JNIEXPORT jint JNICALL Java_jcuda_jcurand_JCurand_curandSetQuasiRandomGeneratorDimensionsNative(JNIEnv *env, jclass cls, jobject generator, jint num_dimensions)
{
    // Null-checks for non-primitive arguments
    if (generator == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'generator' is null for curandSetQuasiRandomGeneratorDimensions");
        return JCURAND_STATUS_INTERNAL_ERROR;
    }

    // Log message
    Logger::log(LOG_TRACE, "Executing curandSetQuasiRandomGeneratorDimensions(generator=%p, num_dimensions=%d)\n",
        generator, num_dimensions);

    // Native variable declarations
    curandGenerator_t generator_native;
    unsigned int num_dimensions_native = 0;

    // Obtain native variable values
    generator_native = (curandGenerator_t)getNativePointerValue(env, generator);
    num_dimensions_native = (unsigned int)num_dimensions;

    // Native function call
    curandStatus_t result_native = curandSetQuasiRandomGeneratorDimensions(generator_native, num_dimensions_native);

    // Return the result
    return (jint)result_native;
}

/**
 * <pre>
 * \brief Generate 32-bit pseudo or quasirandom numbers.
 *
 * Use \p generator to generate \p num 32-bit results into the device memory at
 * \p outputPtr.  The device memory must have been previously allocated and be
 * large enough to hold all the results.  Launches are done with the stream
 * set using ::curandSetStream(), or the null stream if no stream has been set.
 *
 * Results are 32-bit values with every bit random.
 *
 * @param generator - Generator to use
 * @param outputPtr - Pointer to device memory to store CUDA-generated results, or
 *                 Pointer to host memory to store CPU-generated results
 * @param num - Number of random 32-bit values to generate
 *
 * @return
 *
 * CURAND_STATUS_NOT_INITIALIZED if the generator was never created \n
 * CURAND_STATUS_PREEXISTING_FAILURE if there was an existing error from
 *     a previous kernel launch \n
 * CURAND_STATUS_LENGTH_NOT_MULTIPLE if the number of output samples is
 *    not a multiple of the quasirandom dimension \n
 * CURAND_STATUS_LAUNCH_FAILURE if the kernel launch failed for any reason \n
 * CURAND_STATUS_SUCCESS if the results were generated successfully \n
 * </pre>
 */
JNIEXPORT jint JNICALL Java_jcuda_jcurand_JCurand_curandGenerateNative(JNIEnv *env, jclass cls, jobject generator, jobject outputPtr, jlong num)
{
    // Null-checks for non-primitive arguments
    if (generator == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'generator' is null for curandGenerate");
        return JCURAND_STATUS_INTERNAL_ERROR;
    }
    if (outputPtr == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'outputPtr' is null for curandGenerate");
        return JCURAND_STATUS_INTERNAL_ERROR;
    }

    // Log message
    Logger::log(LOG_TRACE, "Executing curandGenerate(generator=%p, outputPtr=%p, num=%ld)\n",
        generator, outputPtr, num);

    // Native variable declarations
    curandGenerator_t generator_native;
    unsigned int* outputPtr_native = NULL;
    size_t num_native = 0;

    // Obtain native variable values
    generator_native = (curandGenerator_t)getNativePointerValue(env, generator);
    PointerData *outputPtrPointerData = initPointerData(env, outputPtr);
    if (outputPtrPointerData == NULL)
    {
        return JCURAND_STATUS_INTERNAL_ERROR;
    }
    outputPtr_native = (unsigned int*)outputPtrPointerData->getPointer(env);
    num_native = (size_t)num;

    // Native function call
    curandStatus_t result_native = curandGenerate(generator_native, outputPtr_native, num_native);

    // Write back native variable values
    if (!releasePointerData(env, outputPtrPointerData)) return JCURAND_STATUS_INTERNAL_ERROR;

    // Return the result
    return (jint)result_native;
}

/**
 * <pre>
 * \brief Generate 64-bit quasirandom numbers.
 *
 * Use \p generator to generate \p num 64-bit results into the device memory at
 * \p outputPtr.  The device memory must have been previously allocated and be
 * large enough to hold all the results.  Launches are done with the stream
 * set using ::curandSetStream(), or the null stream if no stream has been set.
 *
 * Results are 64-bit values with every bit random.
 *
 * @param generator - Generator to use
 * @param outputPtr - Pointer to device memory to store CUDA-generated results, or
 *                 Pointer to host memory to store CPU-generated results
 * @param num - Number of random 64-bit values to generate
 *
 * @return
 *
 * CURAND_STATUS_NOT_INITIALIZED if the generator was never created \n
 * CURAND_STATUS_PREEXISTING_FAILURE if there was an existing error from
 *     a previous kernel launch \n
 * CURAND_STATUS_LENGTH_NOT_MULTIPLE if the number of output samples is
 *    not a multiple of the quasirandom dimension \n
 * CURAND_STATUS_LAUNCH_FAILURE if the kernel launch failed for any reason \n
 * CURAND_STATUS_SUCCESS if the results were generated successfully \n
 * </pre>
 */
JNIEXPORT jint JNICALL Java_jcuda_jcurand_JCurand_curandGenerateLongLongNative(JNIEnv *env, jclass cls, jobject generator, jobject outputPtr, jlong num)
{
    // Null-checks for non-primitive arguments
    if (generator == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'generator' is null for curandGenerateLongLong");
        return JCURAND_STATUS_INTERNAL_ERROR;
    }
    if (outputPtr == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'outputPtr' is null for curandGenerateLongLong");
        return JCURAND_STATUS_INTERNAL_ERROR;
    }

    // Log message
    Logger::log(LOG_TRACE, "Executing curandGenerateLongLong(generator=%p, outputPtr=%p, num=%ld)\n",
        generator, outputPtr, num);

    // Native variable declarations
    curandGenerator_t generator_native;
    unsigned long long* outputPtr_native = NULL;
    size_t num_native = 0;

    // Obtain native variable values
    generator_native = (curandGenerator_t)getNativePointerValue(env, generator);
    PointerData *outputPtrPointerData = initPointerData(env, outputPtr);
    if (outputPtrPointerData == NULL)
    {
        return JCURAND_STATUS_INTERNAL_ERROR;
    }
    outputPtr_native = (unsigned long long*)outputPtrPointerData->getPointer(env);
    num_native = (size_t)num;

    // Native function call
    curandStatus_t result_native = curandGenerateLongLong(generator_native, outputPtr_native, num_native);

    // Write back native variable values
    if (!releasePointerData(env, outputPtrPointerData)) return JCURAND_STATUS_INTERNAL_ERROR;

    // Return the result
    return (jint)result_native;
}

/**
 * <pre>
 * \brief Generate uniformly distributed floats.
 *
 * Use \p generator to generate \p num float results into the device memory at
 * \p outputPtr.  The device memory must have been previously allocated and be
 * large enough to hold all the results.  Launches are done with the stream
 * set using ::curandSetStream(), or the null stream if no stream has been set.
 *
 * Results are 32-bit floating point values between \p 0.0f and \p 1.0f,
 * excluding \p 0.0f and including \p 1.0f.
 *
 * @param generator - Generator to use
 * @param outputPtr - Pointer to device memory to store CUDA-generated results, or
 *                 Pointer to host memory to store CPU-generated results
 * @param num - Number of floats to generate
 *
 * @return
 *
 * CURAND_STATUS_NOT_INITIALIZED if the generator was never created \n
 * CURAND_STATUS_PREEXISTING_FAILURE if there was an existing error from
 *    a previous kernel launch \n
 * CURAND_STATUS_LAUNCH_FAILURE if the kernel launch failed for any reason \n
 * CURAND_STATUS_LENGTH_NOT_MULTIPLE if the number of output samples is
 *    not a multiple of the quasirandom dimension \n
 * CURAND_STATUS_SUCCESS if the results were generated successfully \n
 * </pre>
 */
JNIEXPORT jint JNICALL Java_jcuda_jcurand_JCurand_curandGenerateUniformNative(JNIEnv *env, jclass cls, jobject generator, jobject outputPtr, jlong num)
{
    // Null-checks for non-primitive arguments
    if (generator == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'generator' is null for curandGenerateUniform");
        return JCURAND_STATUS_INTERNAL_ERROR;
    }
    if (outputPtr == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'outputPtr' is null for curandGenerateUniform");
        return JCURAND_STATUS_INTERNAL_ERROR;
    }

    // Log message
    Logger::log(LOG_TRACE, "Executing curandGenerateUniform(generator=%p, outputPtr=%p, num=%ld)\n",
        generator, outputPtr, num);

    // Native variable declarations
    curandGenerator_t generator_native;
    float* outputPtr_native = NULL;
    size_t num_native = 0;

    // Obtain native variable values
    generator_native = (curandGenerator_t)getNativePointerValue(env, generator);
    PointerData *outputPtrPointerData = initPointerData(env, outputPtr);
    if (outputPtrPointerData == NULL)
    {
        return JCURAND_STATUS_INTERNAL_ERROR;
    }
    outputPtr_native = (float*)outputPtrPointerData->getPointer(env);
    num_native = (size_t)num;

    // Native function call
    curandStatus_t result_native = curandGenerateUniform(generator_native, outputPtr_native, num_native);

    // Write back native variable values
    if (!releasePointerData(env, outputPtrPointerData)) return JCURAND_STATUS_INTERNAL_ERROR;

    // Return the result
    return (jint)result_native;
}

/**
 * <pre>
 * \brief Generate uniformly distributed doubles.
 *
 * Use \p generator to generate \p num double results into the device memory at
 * \p outputPtr.  The device memory must have been previously allocated and be
 * large enough to hold all the results.  Launches are done with the stream
 * set using ::curandSetStream(), or the null stream if no stream has been set.
 *
 * Results are 64-bit double precision floating point values between
 * \p 0.0 and \p 1.0, excluding \p 0.0 and including \p 1.0.
 *
 * @param generator - Generator to use
 * @param outputPtr - Pointer to device memory to store CUDA-generated results, or
 *                 Pointer to host memory to store CPU-generated results
 * @param num - Number of doubles to generate
 *
 * @return
 *
 * CURAND_STATUS_NOT_INITIALIZED if the generator was never created \n
 * CURAND_STATUS_PREEXISTING_FAILURE if there was an existing error from
 *    a previous kernel launch \n
 * CURAND_STATUS_LAUNCH_FAILURE if the kernel launch failed for any reason \n
 * CURAND_STATUS_LENGTH_NOT_MULTIPLE if the number of output samples is
 *    not a multiple of the quasirandom dimension \n
 * CURAND_STATUS_ARCH_MISMATCH if the GPU does not support double precision \n
 * CURAND_STATUS_SUCCESS if the results were generated successfully \n
 * </pre>
 */
JNIEXPORT jint JNICALL Java_jcuda_jcurand_JCurand_curandGenerateUniformDoubleNative(JNIEnv *env, jclass cls, jobject generator, jobject outputPtr, jlong num)
{
    // Null-checks for non-primitive arguments
    if (generator == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'generator' is null for curandGenerateUniformDouble");
        return JCURAND_STATUS_INTERNAL_ERROR;
    }
    if (outputPtr == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'outputPtr' is null for curandGenerateUniformDouble");
        return JCURAND_STATUS_INTERNAL_ERROR;
    }

    // Log message
    Logger::log(LOG_TRACE, "Executing curandGenerateUniformDouble(generator=%p, outputPtr=%p, num=%ld)\n",
        generator, outputPtr, num);

    // Native variable declarations
    curandGenerator_t generator_native;
    double* outputPtr_native = NULL;
    size_t num_native = 0;

    // Obtain native variable values
    generator_native = (curandGenerator_t)getNativePointerValue(env, generator);
    PointerData *outputPtrPointerData = initPointerData(env, outputPtr);
    if (outputPtrPointerData == NULL)
    {
        return JCURAND_STATUS_INTERNAL_ERROR;
    }
    outputPtr_native = (double*)outputPtrPointerData->getPointer(env);
    num_native = (size_t)num;

    // Native function call
    curandStatus_t result_native = curandGenerateUniformDouble(generator_native, outputPtr_native, num_native);

    // Write back native variable values
    if (!releasePointerData(env, outputPtrPointerData)) return JCURAND_STATUS_INTERNAL_ERROR;

    // Return the result
    return (jint)result_native;
}

/**
 * <pre>
 * \brief Generate normally distributed floats.
 *
 * Use \p generator to generate \p num float results into the device memory at
 * \p outputPtr.  The device memory must have been previously allocated and be
 * large enough to hold all the results.  Launches are done with the stream
 * set using ::curandSetStream(), or the null stream if no stream has been set.
 *
 * Results are 32-bit floating point values with mean \p mean and standard
 * deviation \p stddev.
 *
 * Normally distributed results are generated from pseudorandom generators
 * with a Box-Muller transform, and so require \p num to be even.
 * Quasirandom generators use an inverse cumulative distribution
 * function to preserve dimensionality.
 *
 * There may be slight numerical differences between results generated
 * on the GPU with generators created with ::curandCreateGenerator()
 * and results calculated on the CPU with generators created with
 * ::curandCreateGeneratorHost().  These differences arise because of
 * differences in results for transcendental functions.  In addition,
 * future versions of CURAND may use newer versions of the CUDA math
 * library, so different versions of CURAND may give slightly different
 * numerical values.
 *
 * @param generator - Generator to use
 * @param outputPtr - Pointer to device memory to store CUDA-generated results, or
 *                 Pointer to host memory to store CPU-generated results
 * @param n - Number of floats to generate
 * @param mean - Mean of normal distribution
 * @param stddev - Standard deviation of normal distribution
 *
 * @return
 *
 * CURAND_STATUS_NOT_INITIALIZED if the generator was never created \n
 * CURAND_STATUS_PREEXISTING_FAILURE if there was an existing error from
 *    a previous kernel launch \n
 * CURAND_STATUS_LAUNCH_FAILURE if the kernel launch failed for any reason \n
 * CURAND_STATUS_LENGTH_NOT_MULTIPLE if the number of output samples is
 *    not a multiple of the quasirandom dimension, or is not a multiple
 *    of two for pseudorandom generators \n
 * CURAND_STATUS_SUCCESS if the results were generated successfully \n
 * </pre>
 */
JNIEXPORT jint JNICALL Java_jcuda_jcurand_JCurand_curandGenerateNormalNative(JNIEnv *env, jclass cls, jobject generator, jobject outputPtr, jlong n, jfloat mean, jfloat stddev)
{
    // Null-checks for non-primitive arguments
    if (generator == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'generator' is null for curandGenerateNormal");
        return JCURAND_STATUS_INTERNAL_ERROR;
    }
    if (outputPtr == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'outputPtr' is null for curandGenerateNormal");
        return JCURAND_STATUS_INTERNAL_ERROR;
    }

    // Log message
    Logger::log(LOG_TRACE, "Executing curandGenerateNormal(generator=%p, outputPtr=%p, n=%ld, mean=%f, stddev=%f)\n",
        generator, outputPtr, n, mean, stddev);

    // Native variable declarations
    curandGenerator_t generator_native;
    float* outputPtr_native = NULL;
    size_t n_native = 0;
    float mean_native = 0.0f;
    float stddev_native = 0.0f;

    // Obtain native variable values
    generator_native = (curandGenerator_t)getNativePointerValue(env, generator);
    PointerData *outputPtrPointerData = initPointerData(env, outputPtr);
    if (outputPtrPointerData == NULL)
    {
        return JCURAND_STATUS_INTERNAL_ERROR;
    }
    outputPtr_native = (float*)outputPtrPointerData->getPointer(env);
    n_native = (size_t)n;
    mean_native = (float)mean;
    stddev_native = (float)stddev;

    // Native function call
    curandStatus_t result_native = curandGenerateNormal(generator_native, outputPtr_native, n_native, mean_native, stddev_native);

    // Write back native variable values
    if (!releasePointerData(env, outputPtrPointerData)) return JCURAND_STATUS_INTERNAL_ERROR;

    // Return the result
    return (jint)result_native;
}

/**
 * <pre>
 * \brief Generate normally distributed doubles.
 *
 * Use \p generator to generate \p num double results into the device memory at
 * \p outputPtr.  The device memory must have been previously allocated and be
 * large enough to hold all the results.  Launches are done with the stream
 * set using ::curandSetStream(), or the null stream if no stream has been set.
 *
 * Results are 64-bit floating point values with mean \p mean and standard
 * deviation \p stddev.
 *
 * Normally distributed results are generated from pseudorandom generators
 * with a Box-Muller transform, and so require \p num to be even.
 * Quasirandom generators use an inverse cumulative distribution
 * function to preserve dimensionality.
 *
 * There may be slight numerical differences between results generated
 * on the GPU with generators created with ::curandCreateGenerator()
 * and results calculated on the CPU with generators created with
 * ::curandCreateGeneratorHost().  These differences arise because of
 * differences in results for transcendental functions.  In addition,
 * future versions of CURAND may use newer versions of the CUDA math
 * library, so different versions of CURAND may give slightly different
 * numerical values.
 *
 * @param generator - Generator to use
 * @param outputPtr - Pointer to device memory to store CUDA-generated results, or
 *                 Pointer to host memory to store CPU-generated results
 * @param n - Number of doubles to generate
 * @param mean - Mean of normal distribution
 * @param stddev - Standard deviation of normal distribution
 *
 * @return
 *
 * CURAND_STATUS_NOT_INITIALIZED if the generator was never created \n
 * CURAND_STATUS_PREEXISTING_FAILURE if there was an existing error from
 *    a previous kernel launch \n
 * CURAND_STATUS_LAUNCH_FAILURE if the kernel launch failed for any reason \n
 * CURAND_STATUS_LENGTH_NOT_MULTIPLE if the number of output samples is
 *    not a multiple of the quasirandom dimension, or is not a multiple
 *    of two for pseudorandom generators \n
 * CURAND_STATUS_ARCH_MISMATCH if the GPU does not support double precision \n
 * CURAND_STATUS_SUCCESS if the results were generated successfully \n
 * </pre>
 */
JNIEXPORT jint JNICALL Java_jcuda_jcurand_JCurand_curandGenerateNormalDoubleNative(JNIEnv *env, jclass cls, jobject generator, jobject outputPtr, jlong n, jdouble mean, jdouble stddev)
{
    // Null-checks for non-primitive arguments
    if (generator == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'generator' is null for curandGenerateNormalDouble");
        return JCURAND_STATUS_INTERNAL_ERROR;
    }
    if (outputPtr == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'outputPtr' is null for curandGenerateNormalDouble");
        return JCURAND_STATUS_INTERNAL_ERROR;
    }

    // Log message
    Logger::log(LOG_TRACE, "Executing curandGenerateNormalDouble(generator=%p, outputPtr=%p, n=%ld, mean=%lf, stddev=%lf)\n",
        generator, outputPtr, n, mean, stddev);

    // Native variable declarations
    curandGenerator_t generator_native;
    double* outputPtr_native = NULL;
    size_t n_native = 0;
    double mean_native = 0.0;
    double stddev_native = 0.0;

    // Obtain native variable values
    generator_native = (curandGenerator_t)getNativePointerValue(env, generator);
    PointerData *outputPtrPointerData = initPointerData(env, outputPtr);
    if (outputPtrPointerData == NULL)
    {
        return JCURAND_STATUS_INTERNAL_ERROR;
    }
    outputPtr_native = (double*)outputPtrPointerData->getPointer(env);
    n_native = (size_t)n;
    mean_native = (double)mean;
    stddev_native = (double)stddev;

    // Native function call
    curandStatus_t result_native = curandGenerateNormalDouble(generator_native, outputPtr_native, n_native, mean_native, stddev_native);

    // Write back native variable values
    if (!releasePointerData(env, outputPtrPointerData)) return JCURAND_STATUS_INTERNAL_ERROR;

    // Return the result
    return (jint)result_native;
}

/**
 * <pre>
 * \brief Generate log-normally distributed floats.
 *
 * Use \p generator to generate \p num float results into the device memory at
 * \p outputPtr.  The device memory must have been previously allocated and be
 * large enough to hold all the results.  Launches are done with the stream
 * set using ::curandSetStream(), or the null stream if no stream has been set.
 *
 * Results are 32-bit floating point values with log-normal distribution based on
 * an associated normal distribution with mean \p mean and standard deviation \p stddev.
 *
 * Normally distributed results are generated from pseudorandom generators
 * with a Box-Muller transform, and so require \p num to be even.
 * Quasirandom generators use an inverse cumulative distribution
 * function to preserve dimensionality.
 * The normally distributed results are transformed into log-normal distribution.
 *
 * There may be slight numerical differences between results generated
 * on the GPU with generators created with ::curandCreateGenerator()
 * and results calculated on the CPU with generators created with
 * ::curandCreateGeneratorHost().  These differences arise because of
 * differences in results for transcendental functions.  In addition,
 * future versions of CURAND may use newer versions of the CUDA math
 * library, so different versions of CURAND may give slightly different
 * numerical values.
 *
 * @param generator - Generator to use
 * @param outputPtr - Pointer to device memory to store CUDA-generated results, or
 *                 Pointer to host memory to store CPU-generated results
 * @param n - Number of floats to generate
 * @param mean - Mean of associated normal distribution
 * @param stddev - Standard deviation of associated normal distribution
 *
 * @return
 *
 * CURAND_STATUS_NOT_INITIALIZED if the generator was never created \n
 * CURAND_STATUS_PREEXISTING_FAILURE if there was an existing error from
 *    a previous kernel launch \n
 * CURAND_STATUS_LAUNCH_FAILURE if the kernel launch failed for any reason \n
 * CURAND_STATUS_LENGTH_NOT_MULTIPLE if the number of output samples is
 *    not a multiple of the quasirandom dimension, or is not a multiple
 *    of two for pseudorandom generators \n
 * CURAND_STATUS_SUCCESS if the results were generated successfully \n
 * </pre>
 */
JNIEXPORT jint JNICALL Java_jcuda_jcurand_JCurand_curandGenerateLogNormalNative(JNIEnv *env, jclass cls, jobject generator, jobject outputPtr, jlong n, jfloat mean, jfloat stddev)
{
    // Null-checks for non-primitive arguments
    if (generator == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'generator' is null for curandGenerateLogNormal");
        return JCURAND_STATUS_INTERNAL_ERROR;
    }
    if (outputPtr == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'outputPtr' is null for curandGenerateLogNormal");
        return JCURAND_STATUS_INTERNAL_ERROR;
    }

    // Log message
    Logger::log(LOG_TRACE, "Executing curandGenerateLogNormal(generator=%p, outputPtr=%p, n=%ld, mean=%f, stddev=%f)\n",
        generator, outputPtr, n, mean, stddev);

    // Native variable declarations
    curandGenerator_t generator_native;
    float* outputPtr_native = NULL;
    size_t n_native = 0;
    float mean_native = 0.0f;
    float stddev_native = 0.0f;

    // Obtain native variable values
    generator_native = (curandGenerator_t)getNativePointerValue(env, generator);
    PointerData *outputPtrPointerData = initPointerData(env, outputPtr);
    if (outputPtrPointerData == NULL)
    {
        return JCURAND_STATUS_INTERNAL_ERROR;
    }
    outputPtr_native = (float*)outputPtrPointerData->getPointer(env);
    n_native = (size_t)n;
    mean_native = (float)mean;
    stddev_native = (float)stddev;

    // Native function call
    curandStatus_t result_native = curandGenerateLogNormal(generator_native, outputPtr_native, n_native, mean_native, stddev_native);

    // Write back native variable values
    if (!releasePointerData(env, outputPtrPointerData)) return JCURAND_STATUS_INTERNAL_ERROR;

    // Return the result
    return (jint)result_native;
}

/**
 * <pre>
 * \brief Generate log-normally distributed doubles.
 *
 * Use \p generator to generate \p num double results into the device memory at
 * \p outputPtr.  The device memory must have been previously allocated and be
 * large enough to hold all the results.  Launches are done with the stream
 * set using ::curandSetStream(), or the null stream if no stream has been set.
 *
 * Results are 64-bit floating point values with log-normal distribution based on
 * an associated normal distribution with mean \p mean and standard deviation \p stddev.
 *
 * Normally distributed results are generated from pseudorandom generators
 * with a Box-Muller transform, and so require \p num to be even.
 * Quasirandom generators use an inverse cumulative distribution
 * function to preserve dimensionality.
 * The normally distributed results are transformed into log-normal distribution.
 *
 * There may be slight numerical differences between results generated
 * on the GPU with generators created with ::curandCreateGenerator()
 * and results calculated on the CPU with generators created with
 * ::curandCreateGeneratorHost().  These differences arise because of
 * differences in results for transcendental functions.  In addition,
 * future versions of CURAND may use newer versions of the CUDA math
 * library, so different versions of CURAND may give slightly different
 * numerical values.
 *
 * @param generator - Generator to use
 * @param outputPtr - Pointer to device memory to store CUDA-generated results, or
 *                 Pointer to host memory to store CPU-generated results
 * @param n - Number of doubles to generate
 * @param mean - Mean of normal distribution
 * @param stddev - Standard deviation of normal distribution
 *
 * @return
 *
 * CURAND_STATUS_NOT_INITIALIZED if the generator was never created \n
 * CURAND_STATUS_PREEXISTING_FAILURE if there was an existing error from
 *    a previous kernel launch \n
 * CURAND_STATUS_LAUNCH_FAILURE if the kernel launch failed for any reason \n
 * CURAND_STATUS_LENGTH_NOT_MULTIPLE if the number of output samples is
 *    not a multiple of the quasirandom dimension, or is not a multiple
 *    of two for pseudorandom generators \n
 * CURAND_STATUS_ARCH_MISMATCH if the GPU does not support double precision \n
 * CURAND_STATUS_SUCCESS if the results were generated successfully \n
 * </pre>
 */
JNIEXPORT jint JNICALL Java_jcuda_jcurand_JCurand_curandGenerateLogNormalDoubleNative(JNIEnv *env, jclass cls, jobject generator, jobject outputPtr, jlong n, jdouble mean, jdouble stddev)
{
    // Null-checks for non-primitive arguments
    if (generator == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'generator' is null for curandGenerateLogNormalDouble");
        return JCURAND_STATUS_INTERNAL_ERROR;
    }
    if (outputPtr == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'outputPtr' is null for curandGenerateLogNormalDouble");
        return JCURAND_STATUS_INTERNAL_ERROR;
    }

    // Log message
    Logger::log(LOG_TRACE, "Executing curandGenerateLogNormalDouble(generator=%p, outputPtr=%p, n=%ld, mean=%lf, stddev=%lf)\n",
        generator, outputPtr, n, mean, stddev);

    // Native variable declarations
    curandGenerator_t generator_native;
    double* outputPtr_native = NULL;
    size_t n_native = 0;
    double mean_native = 0.0;
    double stddev_native = 0.0;

    // Obtain native variable values
    generator_native = (curandGenerator_t)getNativePointerValue(env, generator);
    PointerData *outputPtrPointerData = initPointerData(env, outputPtr);
    if (outputPtrPointerData == NULL)
    {
        return JCURAND_STATUS_INTERNAL_ERROR;
    }
    outputPtr_native = (double*)outputPtrPointerData->getPointer(env);
    n_native = (size_t)n;
    mean_native = (double)mean;
    stddev_native = (double)stddev;

    // Native function call
    curandStatus_t result_native = curandGenerateLogNormalDouble(generator_native, outputPtr_native, n_native, mean_native, stddev_native);

    // Write back native variable values
    if (!releasePointerData(env, outputPtrPointerData)) return JCURAND_STATUS_INTERNAL_ERROR;

    // Return the result
    return (jint)result_native;
}




/*
 * Class:     jcuda_jcurand_JCurand
 * Method:    curandCreatePoissonDistributionNative
 * Signature: (DLjcuda/jcurand/curandDiscreteDistribution;)I
 */
JNIEXPORT jint JNICALL Java_jcuda_jcurand_JCurand_curandCreatePoissonDistributionNative
  (JNIEnv *env, jclass cls, jdouble lambda, jobject discrete_distribution)
{
    // Null-checks for non-primitive arguments
    if (discrete_distribution == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'discrete_distribution' is null for curandCreatePoissonDistribution");
        return JCURAND_STATUS_INTERNAL_ERROR;
    }

    // Log message
    Logger::log(LOG_TRACE, "Executing curandCreatePoissonDistribution(lambda=%lf, discrete_distribution=%p)\n",
        lambda, discrete_distribution);

    // Native variable declarations
    double lambda_native = 0.0;
    curandDiscreteDistribution_t discrete_distribution_native;

    // Obtain native variable values
    lambda_native = (double)lambda;
    discrete_distribution_native = NULL;

    // Native function call
    curandStatus_t result_native = curandCreatePoissonDistribution(lambda, &discrete_distribution_native);

    // Write back native variable values
    setNativePointerValue(env, discrete_distribution, (jlong)discrete_distribution_native);

    // Return the result
    return (jint)result_native;
}


/*
 * Class:     jcuda_jcurand_JCurand
 * Method:    curandDestroyDistributionNative
 * Signature: (Ljcuda/jcurand/curandDiscreteDistribution;)I
 */
JNIEXPORT jint JNICALL Java_jcuda_jcurand_JCurand_curandDestroyDistributionNative
  (JNIEnv *env, jclass cls, jobject discrete_distribution)
{
    // Null-checks for non-primitive arguments
    if (discrete_distribution == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'discrete_distribution' is null for curandDestroyDistribution");
        return JCURAND_STATUS_INTERNAL_ERROR;
    }

    // Log message
    Logger::log(LOG_TRACE, "Executing curandDestroyDistribution(discrete_distribution=%p)\n",
        discrete_distribution);

    // Native variable declarations
    curandDiscreteDistribution_t discrete_distribution_native;

    // Obtain native variable values
    discrete_distribution_native = (curandDiscreteDistribution_t)getNativePointerValue(env, discrete_distribution);

    // Native function call
    curandStatus_t result_native = curandDestroyDistribution(discrete_distribution_native);

    // Return the result
    return (jint)result_native;
}


/*
 * Class:     jcuda_jcurand_JCurand
 * Method:    curandGeneratePoissonNative
 * Signature: (Ljcuda/jcurand/curandGenerator;Ljcuda/Pointer;JD)I
 */
JNIEXPORT jint JNICALL Java_jcuda_jcurand_JCurand_curandGeneratePoissonNative
  (JNIEnv *env, jclass cls, jobject generator, jobject outputPtr, jlong n, jdouble lambda)
{
    // Null-checks for non-primitive arguments
    if (generator == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'generator' is null for curandGeneratePoisson");
        return JCURAND_STATUS_INTERNAL_ERROR;
    }
    if (outputPtr == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'outputPtr' is null for curandGeneratePoisson");
        return JCURAND_STATUS_INTERNAL_ERROR;
    }

    // Log message
    Logger::log(LOG_TRACE, "Executing curandGeneratePoisson(generator=%p, outputPtr=%p, n=%ld, lambda=%lf)\n",
        generator, outputPtr, n, lambda);

    // Native variable declarations
    curandGenerator_t generator_native;
    unsigned int* outputPtr_native = NULL;
    size_t n_native = 0;
    double lambda_native = 0.0;

    // Obtain native variable values
    generator_native = (curandGenerator_t)getNativePointerValue(env, generator);
    PointerData *outputPtrPointerData = initPointerData(env, outputPtr);
    if (outputPtrPointerData == NULL)
    {
        return JCURAND_STATUS_INTERNAL_ERROR;
    }
    outputPtr_native = (unsigned int*)outputPtrPointerData->getPointer(env);
    n_native = (size_t)n;
    lambda_native = (double)lambda;

    // Native function call
    curandStatus_t result_native = curandGeneratePoisson(generator_native, outputPtr_native, n_native, lambda_native);

    // Write back native variable values
    if (!releasePointerData(env, outputPtrPointerData)) return JCURAND_STATUS_INTERNAL_ERROR;

    // Return the result
    return (jint)result_native;

}





/**
 * <pre>
 * \brief Setup starting states.
 *
 * Generate the starting state of the generator.  This function is
 * automatically called by generation functions such as
 * ::curandGenerate() and ::curandGenerateUniform().
 * It can be called manually for performance testing reasons to separate
 * timings for starting state generation and random number generation.
 *
 * @param generator - Generator to update
 *
 * @return
 *
 * CURAND_STATUS_NOT_INITIALIZED if the generator was never created \n
 * CURAND_STATUS_PREEXISTING_FAILURE if there was an existing error from
 *     a previous kernel launch \n
 * CURAND_STATUS_LAUNCH_FAILURE if the kernel launch failed for any reason \n
 * CURAND_STATUS_SUCCESS if the seeds were generated successfully \n
 * </pre>
 */
JNIEXPORT jint JNICALL Java_jcuda_jcurand_JCurand_curandGenerateSeedsNative(JNIEnv *env, jclass cls, jobject generator)
{
    // Null-checks for non-primitive arguments
    if (generator == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'generator' is null for curandGenerateSeeds");
        return JCURAND_STATUS_INTERNAL_ERROR;
    }

    // Log message
    Logger::log(LOG_TRACE, "Executing curandGenerateSeeds(generator=%p)\n",
        generator);

    // Native variable declarations
    curandGenerator_t generator_native;

    // Obtain native variable values
    generator_native = (curandGenerator_t)getNativePointerValue(env, generator);

    // Native function call
    curandStatus_t result_native = curandGenerateSeeds(generator_native);

    // Return the result
    return (jint)result_native;
}

/**
 * <pre>
 * \brief Get direction vectors for 32-bit quasirandom number generation.
 *
 * Get a pointer to an array of direction vectors that can be used
 * for quasirandom number generation.  The resulting pointer will
 * reference an array of direction vectors in host memory.
 *
 * The array contains vectors for many dimensions.  Each dimension
 * has 32 vectors.  Each individual vector is an unsigned int.
 *
 * Legal values for \p set are:
 * - CURAND_DIRECTION_VECTORS_32_JOEKUO6 (20,000 dimensions)
 * - CURAND_SCRAMBLED_DIRECTION_VECTORS_32_JOEKUO6 (20,000 dimensions)
 *
 * @param vectors - Address of pointer in which to return direction vectors
 * @param set - Which set of direction vectors to use
 *
 * @return
 *
 * CURAND_STATUS_OUT_OF_RANGE if the choice of set is invalid \n
 * CURAND_STATUS_SUCCESS if the pointer was set successfully \n
 * </pre>
 */
JNIEXPORT jint JNICALL Java_jcuda_jcurand_JCurand_curandGetDirectionVectors32Native(JNIEnv *env, jclass cls, jobjectArray vectors, jint set)
{
    // Null-checks for non-primitive arguments
    if (vectors == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'vectors' is null for curandGetDirectionVectors32");
        return JCURAND_STATUS_INTERNAL_ERROR;
    }

    int length = env->GetArrayLength(vectors);
    if (length < 1)
    {
        ThrowByName(env, "java/lang/IllegalArgumentException", "Parameter 'vectors' must have a size >= 1");
        return JCURAND_STATUS_INTERNAL_ERROR;
    }

    // Log message
    Logger::log(LOG_TRACE, "Executing curandGetDirectionVectors32(vectors=%p, set=%d)\n",
        vectors, set);

    // Native variable declarations
    curandDirectionVectors32_t* vectors_native;
    curandDirectionVectorSet_t set_native;

    // Obtain native variable values
    set_native = (curandDirectionVectorSet_t)set;

    // Native function call
    curandStatus_t result = curandGetDirectionVectors32(&vectors_native, set_native);

    if (set_native != CURAND_DIRECTION_VECTORS_32_JOEKUO6 &&
        set_native != CURAND_SCRAMBLED_DIRECTION_VECTORS_32_JOEKUO6)
    {
        Logger::log(LOG_ERROR, "Unknown set type for curandGetDirectionVectors32: %d\n", set_native);
        return JCURAND_STATUS_INTERNAL_ERROR;
    }

    // Write back native variable values
    int dimensions = 20000;
    int numVectors = 32;
    jclass intArrayClass = env->FindClass("[I");
    if (intArrayClass == NULL)
    {
        Logger::log(LOG_ERROR, "Could not find int array class\n");
        return JCURAND_STATUS_INTERNAL_ERROR;
    }
    jobjectArray intArrays = env->NewObjectArray(dimensions, intArrayClass, NULL);
    if (intArrays == NULL)
    {
        Logger::log(LOG_ERROR, "Could not create outer result array\n");
        return JCURAND_STATUS_INTERNAL_ERROR;
    }
    for (int i=0; i<dimensions; i++)
    {
        jintArray intArray = env->NewIntArray(numVectors);
        if (intArray == NULL)
        {
            Logger::log(LOG_ERROR, "Could not create inner result array\n");
            return JCURAND_STATUS_INTERNAL_ERROR;
        }
        jint* arrayData = (jint*)env->GetPrimitiveArrayCritical(intArray, NULL);
        if (arrayData == NULL)
        {
            Logger::log(LOG_ERROR, "Could not access inner result array\n");
            return JCURAND_STATUS_INTERNAL_ERROR;
        }
        for (int j=0; j<numVectors; j++)
        {
            arrayData[j] = (jint)vectors_native[i][j];
        }
        env->ReleasePrimitiveArrayCritical(intArray, arrayData, 0);
        env->SetObjectArrayElement(intArrays, i, intArray);
        if (env->ExceptionCheck())
        {
            return JCURAND_STATUS_INTERNAL_ERROR;
        }
    }
    env->SetObjectArrayElement(vectors, 0, intArrays);
    if (env->ExceptionCheck())
    {
       return JCURAND_STATUS_INTERNAL_ERROR;
    }

    return (jint)result;
}

/**
 * <pre>
 * \brief Get scramble constants for 32-bit scrambled Sobol' .
 *
 * Get a pointer to an array of scramble constants that can be used
 * for quasirandom number generation.  The resulting pointer will
 * reference an array of unsinged ints in host memory.
 *
 * The array contains constants for many dimensions.  Each dimension
 * has a single unsigned int constant.
 *
 * @param constants - Address of pointer in which to return scramble constants
 *
 * @return
 *
 * CURAND_STATUS_SUCCESS if the pointer was set successfully \n
 * </pre>
 */
JNIEXPORT jint JNICALL Java_jcuda_jcurand_JCurand_curandGetScrambleConstants32Native(JNIEnv *env, jclass cls, jobjectArray constants)
{
    // Null-checks for non-primitive arguments
    if (constants == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'constants' is null for curandGetScrambleConstants32");
        return JCURAND_STATUS_INTERNAL_ERROR;
    }

    int length = env->GetArrayLength(constants);
    if (length < 1)
    {
        ThrowByName(env, "java/lang/IllegalArgumentException", "Parameter 'constants' must have a size >= 1");
        return JCURAND_STATUS_INTERNAL_ERROR;
    }

    // Log message
    Logger::log(LOG_TRACE, "Executing curandGetScrambleConstants32(constants=%p)\n",
        constants);

    // Native variable declarations
    unsigned int* constants_native;

    // Native function call
    curandStatus_t result = curandGetScrambleConstants32(&constants_native);

    // Write back native variable values

    // Documentation: "The array contains constants for many dimensions"
    // WTFITS? One, Two, Many? Assuming 20000 like for direction vectors...
    int many = 20000;
    jintArray intArray = env->NewIntArray(many);
    if (intArray == NULL)
    {
        Logger::log(LOG_ERROR, "Could not create result array\n");
        return JCURAND_STATUS_INTERNAL_ERROR;
    }
    jint* arrayData = (jint*)env->GetPrimitiveArrayCritical(intArray, NULL);
    if (arrayData == NULL)
    {
        Logger::log(LOG_ERROR, "Could not access inner result array\n");
        return JCURAND_STATUS_INTERNAL_ERROR;
    }
    for (int i=0; i<many; i++)
    {
        arrayData[i] = (jint)constants_native[i];
    }
    env->ReleasePrimitiveArrayCritical(intArray, arrayData, 0);
    if (env->ExceptionCheck())
    {
        return JCURAND_STATUS_INTERNAL_ERROR;
    }
    env->SetObjectArrayElement(constants, 0, intArray);
    if (env->ExceptionCheck())
    {
       return JCURAND_STATUS_INTERNAL_ERROR;
    }

    return (jint)result;
}

/**
 * <pre>
 * \brief Get direction vectors for 64-bit quasirandom number generation.
 *
 * Get a pointer to an array of direction vectors that can be used
 * for quasirandom number generation.  The resulting pointer will
 * reference an array of direction vectors in host memory.
 *
 * The array contains vectors for many dimensions.  Each dimension
 * has 64 vectors.  Each individual vector is an unsigned long long.
 *
 * Legal values for \p set are:
 * - CURAND_DIRECTION_VECTORS_64_JOEKUO6 (20,000 dimensions)
 * - CURAND_SCRAMBLED_DIRECTION_VECTORS_64_JOEKUO6 (20,000 dimensions)
 *
 * @param vectors - Address of pointer in which to return direction vectors
 * @param set - Which set of direction vectors to use
 *
 * @return
 *
 * CURAND_STATUS_OUT_OF_RANGE if the choice of set is invalid \n
 * CURAND_STATUS_SUCCESS if the pointer was set successfully \n
 * </pre>
 */
JNIEXPORT jint JNICALL Java_jcuda_jcurand_JCurand_curandGetDirectionVectors64Native(JNIEnv *env, jclass cls, jobjectArray vectors, jint set)
{
    // Null-checks for non-primitive arguments
    if (vectors == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'vectors' is null for curandGetDirectionVectors64");
        return JCURAND_STATUS_INTERNAL_ERROR;
    }

    int length = env->GetArrayLength(vectors);
    if (length < 1)
    {
        ThrowByName(env, "java/lang/IllegalArgumentException", "Parameter 'vectors' must have a size >= 1");
        return JCURAND_STATUS_INTERNAL_ERROR;
    }

    // Log message
    Logger::log(LOG_TRACE, "Executing curandGetDirectionVectors64(vectors=%p, set=%d)\n",
        vectors, set);

    // Native variable declarations
    curandDirectionVectors64_t* vectors_native;
    curandDirectionVectorSet_t set_native;

    // Obtain native variable values
    set_native = (curandDirectionVectorSet_t)set;

    // Native function call
    curandStatus_t result = curandGetDirectionVectors64(&vectors_native, set_native);

    if (set_native != CURAND_DIRECTION_VECTORS_64_JOEKUO6 &&
        set_native != CURAND_SCRAMBLED_DIRECTION_VECTORS_64_JOEKUO6)
    {
        Logger::log(LOG_ERROR, "Unknown set type for curandGetDirectionVectors64: %d\n", set_native);
        return JCURAND_STATUS_INTERNAL_ERROR;
    }

    // Write back native variable values
    int dimensions = 20000;
    int numVectors = 64;
    jclass longArrayClass = env->FindClass("[J");
    if (longArrayClass == NULL)
    {
        Logger::log(LOG_ERROR, "Could not find long array class\n");
        return JCURAND_STATUS_INTERNAL_ERROR;
    }
    jobjectArray longArrays = env->NewObjectArray(dimensions, longArrayClass, NULL);
    if (longArrays == NULL)
    {
        Logger::log(LOG_ERROR, "Could not create outer result array\n");
        return JCURAND_STATUS_INTERNAL_ERROR;
    }
    for (int i=0; i<dimensions; i++)
    {
        jlongArray longArray = env->NewLongArray(numVectors);
        if (longArray == NULL)
        {
            Logger::log(LOG_ERROR, "Could not create inner result array\n");
            return JCURAND_STATUS_INTERNAL_ERROR;
        }
        jlong* arrayData = (jlong*)env->GetPrimitiveArrayCritical(longArray, NULL);
        if (arrayData == NULL)
        {
            Logger::log(LOG_ERROR, "Could not access inner result array\n");
            return JCURAND_STATUS_INTERNAL_ERROR;
        }
        for (int j=0; j<numVectors; j++)
        {
            arrayData[j] = (jlong)vectors_native[i][j];
        }
        env->ReleasePrimitiveArrayCritical(longArray, arrayData, 0);
        env->SetObjectArrayElement(longArrays, i, longArray);
        if (env->ExceptionCheck())
        {
            return JCURAND_STATUS_INTERNAL_ERROR;
        }
    }
    env->SetObjectArrayElement(vectors, 0, longArrays);
    if (env->ExceptionCheck())
    {
       return JCURAND_STATUS_INTERNAL_ERROR;
    }

    return (jint)result;
}

/**
 * <pre>
 * \brief Get scramble constants for 64-bit scrambled Sobol' .
 *
 * Get a pointer to an array of scramble constants that can be used
 * for quasirandom number generation.  The resulting pointer will
 * reference an array of unsinged long longs in host memory.
 *
 * The array contains constants for many dimensions.  Each dimension
 * has a single unsigned long long constant.
 *
 * @param constans - Address of pointer in which to return scramble constants
 *
 * @return
 *
 * CURAND_STATUS_SUCCESS if the pointer was set successfully \n
 * </pre>
 */
JNIEXPORT jint JNICALL Java_jcuda_jcurand_JCurand_curandGetScrambleConstants64Native(JNIEnv *env, jclass cls, jobjectArray constants)
{
    // Null-checks for non-primitive arguments
    if (constants == NULL)
    {
        ThrowByName(env, "java/lang/NullPointerException", "Parameter 'constants' is null for curandGetScrambleConstants64");
        return JCURAND_STATUS_INTERNAL_ERROR;
    }

    int length = env->GetArrayLength(constants);
    if (length < 1)
    {
        ThrowByName(env, "java/lang/IllegalArgumentException", "Parameter 'constants' must have a size >= 1");
        return JCURAND_STATUS_INTERNAL_ERROR;
    }

    // Log message
    Logger::log(LOG_TRACE, "Executing curandGetScrambleConstants64(constants=%p)\n",
        constants);

    // Native variable declarations
    unsigned long long *constants_native;

    // Native function call
    curandStatus_t result = curandGetScrambleConstants64(&constants_native);

    // Write back native variable values

    // Documentation: "The array contains constants for many dimensions"
    // WTFITS? One, Two, Many? Assuming 20000 like for direction vectors...
    int many = 20000;
    jlongArray longArray = env->NewLongArray(many);
    if (longArray == NULL)
    {
        Logger::log(LOG_ERROR, "Could not create result array\n");
        return JCURAND_STATUS_INTERNAL_ERROR;
    }
    jlong* arrayData = (jlong*)env->GetPrimitiveArrayCritical(longArray, NULL);
    if (arrayData == NULL)
    {
        Logger::log(LOG_ERROR, "Could not access inner result array\n");
        return JCURAND_STATUS_INTERNAL_ERROR;
    }
    for (int i=0; i<many; i++)
    {
        arrayData[i] = (jlong)constants_native[i];
    }
    env->ReleasePrimitiveArrayCritical(longArray, arrayData, 0);
    if (env->ExceptionCheck())
    {
        return JCURAND_STATUS_INTERNAL_ERROR;
    }
    env->SetObjectArrayElement(constants, 0, longArray);
    if (env->ExceptionCheck())
    {
       return JCURAND_STATUS_INTERNAL_ERROR;
    }

    return (jint)result;
}

