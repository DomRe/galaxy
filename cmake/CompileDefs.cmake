set(GALAXY_COMPILE_FLAGS_DEBUG
    /QIntel-jcc-erratum
    /std:c++latest
    /WX-
    /MP
    /GF
    /EHsc
    /fp:except
    /fp:precise
    /bigobj
    /Y-
    /W4
    /JMC
    /ZI
    /Od
    /RTC1
    /MTd
    /GS
    /GR
    /sdl
    /Zc:preprocessor
)

set(GALAXY_COMPILE_FLAGS_RELEASE
    /QIntel-jcc-erratum
    /std:c++latest
    /WX-
    /MP
    /GF
    /EHsc
    /fp:except
    /fp:precise
    /bigobj
    /Y-
    /w
    /O2
    /Oi
    /Ot
    /GL
    /MT
    /GS-
    /Gy
    /GR-
    /Zc:preprocessor
)