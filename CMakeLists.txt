cmake_minimum_required(VERSION 3.10)

set (CMAKE_CXX_STANDARD 20)

project(smart_house)

aux_source_directory(./src SRC1)
aux_source_directory(./src/Commands SRC2)
aux_source_directory(./src/SmartObjects SRC3)
aux_source_directory(./src/Storage SRC4)
aux_source_directory(./src/Utils SRC5)

add_executable(smart_house ${SRC1} ${SRC2} ${SRC3} ${SRC4} ${SRC5})
# message(STATUS ${ALL_SRCS})

# file(GLOB smart_house_SRC "*.h" "*.cpp")
# add_executable(smart_house ${smart_house_SRC})