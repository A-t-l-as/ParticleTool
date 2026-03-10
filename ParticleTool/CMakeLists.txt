cmake_minimum_required(VERSION 3.16)

project(ParticleTool LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ParticleTool src/main.cpp
    src/AodCompilator/AodDirectoryCompilator.cpp src/AodCompilator/AodDirectoryCompilator.hpp src/AodCompilator/GlobalQueues.hpp src/AodCompilator/SpecialFlagsCompilator.hpp src/Apps/MyAodToParticleApp.hpp src/Apps/ParticleToMyAodApp.cpp src/Apps/ParticleToMyAodApp.hpp src/Apps/ParticleToolApp.hpp src/Cfg/CfgCompilator.cpp src/Cfg/CfgCompilator.hpp src/Cfg/CfgCompilatorUtils.hpp src/Cfg/CfgFileData.hpp src/ParticleFile/BasicParticleStructures/AllCurvesGroups.hpp src/ParticleFile/BasicParticleStructures/AllTeselatesGroups.hpp src/ParticleFile/BasicParticleStructures/CurvesAndTeselatesUtils.hpp src/ParticleFile/BasicParticleStructures/SingleCurvePoint.hpp src/ParticleFile/BasicParticleStructures/SingleCurvePointConsts.hpp src/ParticleFile/BasicParticleStructures/TeselateAndCurvePair.hpp src/ParticleFile/BasicParticleStructures/TeselateAndCurvePairConsts.hpp src/ParticleFile/CustomBlock/CustomBlockClass.cpp src/ParticleFile/CustomBlock/CustomBlockClass.hpp src/ParticleFile/CustomBlock/CustomBlockData.hpp src/ParticleFile/DynamicParticleFile/DynamicParticle/DynamicParticleClass.cpp src/ParticleFile/DynamicParticleFile/DynamicParticle/DynamicParticleClass.hpp src/ParticleFile/DynamicParticleFile/DynamicParticle/DynamicParticleData.hpp src/ParticleFile/DynamicParticleFile/WholeDynamicParticleContainer.hpp src/ParticleFile/FileHeader/FileHeaderClass.cpp src/ParticleFile/FileHeader/FileHeaderClass.hpp src/ParticleFile/FileHeader/FileHeaderData.hpp src/ParticleFile/IntroHeader/IntroductionHeaderClass.cpp src/ParticleFile/IntroHeader/IntroductionHeaderClass.hpp src/ParticleFile/IntroHeader/MshCustomBlockVectors.hpp src/ParticleFile/ParticleEmiterFile/Effect/EffectClass.cpp src/ParticleFile/ParticleEmiterFile/Effect/EffectClass.hpp src/ParticleFile/ParticleEmiterFile/Effect/EffectData.cpp src/ParticleFile/ParticleEmiterFile/Effect/EffectData.hpp src/ParticleFile/ParticleEmiterFile/Emiter/EmiterClass.cpp src/ParticleFile/ParticleEmiterFile/Emiter/EmiterClass.hpp src/ParticleFile/ParticleEmiterFile/Emiter/EmiterData.cpp src/ParticleFile/ParticleEmiterFile/Emiter/EmiterData.hpp src/ParticleFile/ParticleEmiterFile/EndOfParticle/ParticleEndClass.cpp src/ParticleFile/ParticleEmiterFile/EndOfParticle/ParticleEndClass.hpp src/ParticleFile/ParticleEmiterFile/EndOfParticle/ParticleEndData.hpp src/ParticleFile/ParticleEmiterFile/PairParticleEmiter/PairParticleEmiterClass.cpp src/ParticleFile/ParticleEmiterFile/PairParticleEmiter/PairParticleEmiterClass.hpp src/ParticleFile/ParticleEmiterFile/PairParticleEmiter/PairParticleEmiterData.hpp src/ParticleFile/ParticleEmiterFile/Particle/ParticleClass.cpp src/ParticleFile/ParticleEmiterFile/Particle/ParticleClass.hpp src/ParticleFile/ParticleEmiterFile/Particle/ParticleData.cpp src/ParticleFile/ParticleEmiterFile/Particle/ParticleData.hpp  src/ParticleFile/ParticleEmiterFile/WholeParticleEmiterContainer.hpp src/ParticleFile/ParticleFileVersionConsts.hpp src/ParticleFile/ParticleFileVersionInfo.hpp src/ParticleGlobals.hpp
    src/ParticleFile/BasicParticleStructures/ParticleCurvesAndTeselatesBase.hpp

)

target_include_directories(ParticleTool PRIVATE
    ../KsUtils
    ../KsUtils/src
)

target_link_libraries(ParticleTool PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../KsUtils/build/Desktop_Qt_6_9_3_MinGW_64_bit-Release/libKsUtils.a
)

include(GNUInstallDirs)
install(TARGETS ParticleTool
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
