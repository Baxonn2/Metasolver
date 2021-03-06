# HelloWorld is a minimal sample creating, stepping and deleting a Bullet dynamics world


set (CMAKE_CXX_STANDARD 11)

INCLUDE_DIRECTORIES(
lib
lib/bullet-2.80/src
metasolver
metasolver/strategies/
problems/clp/containers
problems/clp/objects2
problems/clp/evaluators
problems/clp
problems/clp/plugins/kdtree
metasolver/plugins/mop/strategies/
)

LINK_DIRECTORIES(
lib/bullet-2.80/src/BulletCollision
lib/bullet-2.80/src/BulletDynamics
lib/bullet-2.80/src/LinearMath
)

LINK_LIBRARIES(
 BulletDynamics BulletCollision LinearMath
)
    if(COMMAND cmake_policy)
      cmake_policy(SET CMP0003 NEW)
    endif(COMMAND cmake_policy)


 SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

# ADD_DEFINITION(-g -pg)

ADD_LIBRARY(
bsg
metasolver/SearchStrategy.cpp  
metasolver/GlobalVariables.cpp
metasolver/strategies/BSG.cpp
metasolver/strategies/Greedy.cpp  
)

#ADD_LIBRARY(
#bsg_mop
#metasolver/plugins/mop/strategies/BSGMOP.cpp
#)

ADD_LIBRARY(
clp
problems/clp/containers/AABBContainer.cpp 
problems/clp/containers/AABBTree.cpp 
problems/clp/evaluators/VCS_Function.cpp 
problems/clp/evaluators/VLossFunction.cpp 
problems/clp/objects2/AABB.cpp 
problems/clp/objects2/Block.cpp 
problems/clp/objects2/BoxShape.cpp 
problems/clp/objects2/Space.cpp
problems/clp/objects2/SpaceSet.cpp
problems/clp/objects2/Block_fsb.cpp
problems/clp/clpState.cpp 
)

ADD_LIBRARY(
clp_kdtree
problems/clp/plugins/kdtree/clpStatekd.cpp 
problems/clp/plugins/kdtree/kdNode.cpp 
problems/clp/plugins/kdtree/BlockSet.cpp 
)


ADD_LIBRARY(Catch INTERFACE)
target_include_directories(Catch INTERFACE lib)

add_executable(my_test 
problems/clp/test01.cpp)

target_link_libraries(my_test Catch)

enable_testing()
add_test(NAME MyAwesomeTest COMMAND my_test)



ADD_EXECUTABLE(CLP2017 problems/clp/main_clp.cpp)
#ADD_EXECUTABLE(CLP_MOP problems/clp/test_clp_mop.cpp)

target_link_libraries(CLP2017 bsg clp clp_kdtree)
#target_link_libraries(CLP_MOP bsg bsg_mop clp)
 

ENDIF()



IF (INTERNAL_ADD_POSTFIX_EXECUTABLE_NAMES)
			SET_TARGET_PROPERTIES(AppHelloWorld PROPERTIES  DEBUG_POSTFIX "_Debug")
			SET_TARGET_PROPERTIES(AppHelloWorld PROPERTIES  MINSIZEREL_POSTFIX "_MinsizeRel")
			SET_TARGET_PROPERTIES(AppHelloWorld PROPERTIES  RELWITHDEBINFO_POSTFIX "_RelWithDebugInfo")
ENDIF(INTERNAL_ADD_POSTFIX_EXECUTABLE_NAMES)
