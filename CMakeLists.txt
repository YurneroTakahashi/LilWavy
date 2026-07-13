# CMakeList.txt: проект CMake для Lil_Wavy; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.10)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Lil_Wavy")
# Import PortAudio to project broskie
set(PA_USE_ASIO OFF CACHE BOOL "Disable ASIO support" FORCE)
add_subdirectory(external/portaudio-19.7.0 EXCLUDE_FROM_ALL)


# Добавьте источник в исполняемый файл этого проекта.
add_executable (Lil_Wavy "Lil_Wavy.cpp" "Lil_Wavy.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Lil_Wavy PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(Lil_Wavy PRIVATE portaudio)


# TODO: Добавьте тесты и целевые объекты, если это необходимо.
