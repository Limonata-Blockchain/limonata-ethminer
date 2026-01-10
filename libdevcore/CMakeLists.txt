file(GLOB HEADERS "*.h")
file(GLOB SOURCES "*.cpp")

find_package(Threads)

# Find secp256k1 library
find_library(SECP256K1_LIBRARY secp256k1)
find_path(SECP256K1_INCLUDE_DIR secp256k1.h)

add_library(devcore ${SOURCES} ${HEADERS})
target_link_libraries(devcore PUBLIC Boost::boost Boost::system)
target_link_libraries(devcore PRIVATE Threads::Threads)

if(SECP256K1_LIBRARY)
    target_link_libraries(devcore PUBLIC ${SECP256K1_LIBRARY})
    target_include_directories(devcore PUBLIC ${SECP256K1_INCLUDE_DIR})
endif()
