# CMakeList.txt: проект CMake для Lil_Wavy; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.28)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Lil_Wavy")
# Import PortAudio to project broskie
set(PA_USE_ASIO OFF CACHE BOOL "Disable ASIO support" FORCE)
add_subdirectory(external/portaudio-19.7.0 EXCLUDE_FROM_ALL)


set(SFML_BUILD_AUDIO ON CACHE BOOL "Build audio module" FORCE)
set(SFML_BUILD_GRAPHICS ON CACHE BOOL "Build graphics module" FORCE)
set(SFML_BUILD_WINDOW ON CACHE BOOL "Build window module" FORCE)
set(SFML_BUILD_NETWORK OFF CACHE BOOL "Build network module" FORCE)
set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "Build examples" FORCE)

add_subdirectory(external/SFML-master EXCLUDE_FROM_ALL)


# Добавьте источник в исполняемый файл этого проекта.
add_executable (Lil_Wavy "Lil_Wavy.cpp" "Lil_Wavy.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Lil_Wavy PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(Lil_Wavy PRIVATE portaudio_static
    sfml-system
    sfml-window
    sfml-graphics
    sfml-audio
)

target_include_directories(Lil_Wavy PRIVATE
    external/SFML-master/include
)
target_compile_definitions(Lil_Wavy PRIVATE)

add_dependencies(Lil_Wavy sfml-window sfml-system sfml-graphics sfml-audio)
