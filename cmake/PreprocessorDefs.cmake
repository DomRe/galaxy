set(GALAXY_PREPROCESSOR_FLAGS
    "UNICODE"
    "_UNICODE"
    "IMGUI_IMPL_OPENGL_LOADER_GLAD"
    "AL_LIBTYPE_STATIC"
    "GLM_FORCE_INLINE"
    "GLM_FORCE_INTRINSICS"
    "GLM_FORCE_XYZW_ONLY"
    "GLM_FORCE_SIZE_T_LENGTH"
    "GLM_FORCE_SILENT_WARNINGS"
    "GLM_FORCE_CTOR_INIT"
    "GLM_FORCE_RADIANS"
    "GLFW_INCLUDE_NONE"
    "STB_IMAGE_IMPLEMENTATION"
    "STB_IMAGE_WRITE_IMPLEMENTATION"
    "STB_IMAGE_RESIZE_IMPLEMENTATION"
    "STB_IMAGE_STATIC"
    "STB_IMAGE_WRITE_STATIC"
    "STB_IMAGE_RESIZE_STATIC"
    "SOL_CXX17_FEATURES"
    "SOL_ALL_SAFETIES_ON"
)

if (WIN32)
    set (OS_FLAGS
        "WIN32"
        "_WIN32"
        "WIN64"
        "_WIN64"
        "WIN32_LEAN_AND_MEAN"
        "NOMINMAX"
        "_CRT_SECURE_NO_WARNINGS"
        "_CRT_SECURE_NO_DEPRECATE"
        "_CRT_NONSTDC_NO_DEPRECATE"
        "_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS"
    )

    set(GALAXY_PREPROCESSOR_FLAGS_DEBUG
        "${OS_FLAGS}"
        "${GALAXY_PREPROCESSOR_FLAGS}"
        "_DEBUG"
        "_CONSOLE"
    )

    set(GALAXY_PREPROCESSOR_FLAGS_RELEASE
        "${OS_FLAGS}"
        "${GALAXY_PREPROCESSOR_FLAGS}"
        "NDEBUG"
        "_WINDOWS"
    )
else()
    set (OS_FLAGS
        "UNIX"
        "LINUX"
        "LINUX64"
        "UNIX64"
        "POISX"
        "POISX64"
        "_GLIBCXX_HAS_GTHREADS"
        "_GLIBCXX_USE_NANOSLEEP"
        "_GLIBCXX_PARALLEL"
    )

    set(GALAXY_PREPROCESSOR_FLAGS_DEBUG
        "${OS_FLAGS}"
        "${GALAXY_PREPROCESSOR_FLAGS}"
        "_DEBUG"
        "_GLIBCXX_SANITIZE_VECTOR"
    )

    set(GALAXY_PREPROCESSOR_FLAGS_RELEASE
        "${OS_FLAGS}"
        "${GALAXY_PREPROCESSOR_FLAGS}"
        "NDEBUG"
    )
endif()