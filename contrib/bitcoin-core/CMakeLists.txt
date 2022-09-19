cmake_minimum_required(VERSION 3.16)

project(bitcoin-core LANGUAGES CXX)
#set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} STATIC
        src/uint256.h
        src/uint256.cpp
        src/attributes.h
        src/compat/endian.h
        src/compat/byteswap.h
        src/prevector.h
        src/span.h

        src/support/lockedpool.h
        src/support/lockedpool.cpp
        src/support/allocators/zeroafterfree.h
        src/support/allocators/secure.h
        src/support/cleanse.h
        src/support/cleanse.cpp
        src/util/strencodings.h
        src/util/strencodings.cpp
        src/util/string.h
        src/util/string.cpp

        src/tinyformat.h

        src/prevector.h
        src/serialize.h

        src/crypto/common.h
        src/crypto/sha256.h
        src/crypto/sha256.cpp
        src/crypto/sha512.h
        src/crypto/sha512.cpp
        src/crypto/ripemd160.h
        src/crypto/ripemd160.cpp
        src/hash.h
        src/hash.cpp

        src/version.h
        src/crypto/hmac_sha512.h
        src/crypto/hmac_sha512.cpp
        src/crypto/hmac_sha256.h
        src/crypto/hmac_sha256.cpp

        src/util/hash_type.h
        src/crypto/sha1.h
        src/crypto/sha1.cpp
        src/base58.h
        src/base58.cpp

        src/util/vector.h

        src/crypto/aes.h
        src/crypto/aes.cpp
        )
#if (NOT ${USE_EXTERNAL_SECP256K1})
#  if (ANDROID)
#    add_library(libsecp256k1 STATIC IMPORTED)
#    set_target_properties(libsecp256k1 PROPERTIES IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/src/secp256k1/build/android/${ANDROID_ABI}/lib/libsecp256k1.a)
#    set_target_properties(libsecp256k1 PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR}/src/secp256k1/include)
#  elseif(IOS)
#    add_library(libsecp256k1 STATIC IMPORTED)
#    set_target_properties(libsecp256k1 PROPERTIES IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/src/secp256k1/build/iphoneos/libsecp256k1.a)
#    set_target_properties(libsecp256k1 PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR}/src/secp256k1/include)
#  elseif(WIN32)
#    message(FATAL_ERROR "Not support yet!")
#  else()
#    add_library(libsecp256k1 STATIC IMPORTED)
#    set_target_properties(libsecp256k1 PROPERTIES IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/src/secp256k1/.libs/libsecp256k1.a)
#    set_target_properties(libsecp256k1 PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR}/src/secp256k1/include)
#  endif()
#else()
#    add_library(libsecp256k1 STATIC IMPORTED)
#    set_target_properties(libsecp256k1 PROPERTIES IMPORTED_LOCATION ${EXTERNAL_SECP256K1_LIBRARY})
#    set_target_properties(libsecp256k1 PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${EXTERNAL_SECP256K1_INCLUDE})
#endif()

target_include_directories(${PROJECT_NAME}
        PUBLIC src
        )

target_link_libraries(${PROJECT_NAME}
        #PUBLIC libsecp256k1
        )
