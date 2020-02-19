# Install script for directory: D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/REACTPHYSICS3D")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/Build/lib/Debug/reactphysics3d.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/Build/lib/Release/reactphysics3d.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/Build/lib/MinSizeRel/reactphysics3d.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/Build/lib/RelWithDebInfo/reactphysics3d.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/reactphysics3d" TYPE FILE FILES
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/configuration.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/decimal.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/reactphysics3d.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/body/Body.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/body/CollisionBody.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/body/RigidBody.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/collision/ContactPointInfo.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/collision/ContactManifoldInfo.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/collision/broadphase/BroadPhaseAlgorithm.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/collision/broadphase/DynamicAABBTree.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/collision/narrowphase/CollisionDispatch.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/collision/narrowphase/DefaultCollisionDispatch.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/collision/narrowphase/GJK/VoronoiSimplex.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/collision/narrowphase/GJK/GJKAlgorithm.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/collision/narrowphase/SAT/SATAlgorithm.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/collision/narrowphase/NarrowPhaseAlgorithm.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/collision/narrowphase/SphereVsSphereAlgorithm.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/collision/narrowphase/CapsuleVsCapsuleAlgorithm.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/collision/narrowphase/SphereVsCapsuleAlgorithm.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/collision/narrowphase/SphereVsConvexPolyhedronAlgorithm.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/collision/narrowphase/CapsuleVsConvexPolyhedronAlgorithm.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/collision/narrowphase/ConvexPolyhedronVsConvexPolyhedronAlgorithm.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/collision/shapes/AABB.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/collision/shapes/ConvexShape.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/collision/shapes/ConvexPolyhedronShape.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/collision/shapes/ConcaveShape.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/collision/shapes/BoxShape.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/collision/shapes/CapsuleShape.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/collision/shapes/CollisionShape.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/collision/shapes/ConvexMeshShape.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/collision/shapes/SphereShape.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/collision/shapes/TriangleShape.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/collision/shapes/ConcaveMeshShape.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/collision/shapes/HeightFieldShape.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/collision/RaycastInfo.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/collision/ProxyShape.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/collision/TriangleVertexArray.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/collision/PolygonVertexArray.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/collision/TriangleMesh.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/collision/PolyhedronMesh.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/collision/HalfEdgeStructure.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/collision/CollisionDetection.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/collision/NarrowPhaseInfo.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/collision/ContactManifold.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/collision/ContactManifoldSet.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/collision/MiddlePhaseTriangleCallback.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/constraint/BallAndSocketJoint.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/constraint/ContactPoint.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/constraint/FixedJoint.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/constraint/HingeJoint.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/constraint/Joint.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/constraint/SliderJoint.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/engine/CollisionWorld.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/engine/ConstraintSolver.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/engine/ContactSolver.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/engine/DynamicsWorld.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/engine/EventListener.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/engine/Island.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/engine/Material.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/engine/OverlappingPair.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/engine/Timer.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/engine/Timer.cpp"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/collision/CollisionCallback.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/collision/OverlapCallback.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/mathematics/mathematics.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/mathematics/mathematics_functions.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/mathematics/Matrix2x2.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/mathematics/Matrix3x3.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/mathematics/Quaternion.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/mathematics/Transform.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/mathematics/Vector2.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/mathematics/Vector3.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/mathematics/Ray.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/memory/MemoryAllocator.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/memory/DefaultPoolAllocator.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/memory/DefaultSingleFrameAllocator.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/memory/DefaultAllocator.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/memory/MemoryManager.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/containers/Stack.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/containers/LinkedList.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/containers/List.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/containers/Map.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/containers/Set.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/containers/Pair.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/utils/Profiler.h"
    "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/src/utils/Logger.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "D:/Work/Github/Reality-Game-Engine/ExternalResources/reactphysics3d-0.7.1/Build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
