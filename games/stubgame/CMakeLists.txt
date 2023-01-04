cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(stubgame)
set(CMAKE_CXX_STANDARD 20)
enable_testing()

#Для студии ставим флаг, что кодировка исходников UTF-8
if(MSVC)
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif()

include_directories(../skif-solo/src)
#явно указываем куда генерировать директорию вне дерева исходников, чтобы сабмодуль не втаскивать внутрь
add_subdirectory(../skif-solo/src skif-solo-lib)

#создаём различные комбинации платформа-звук за счёт линковки
add_executable(stubgame_console_nosound stubgame.cpp)
target_link_libraries(stubgame_console_nosound skif_engine platform_console sound_none logger_simple)

add_executable(stubgame_console_miniaudio stubgame.cpp)
target_link_libraries(stubgame_console_miniaudio skif_engine platform_console sound_miniaudio logger_file)

#add_executable(stubgame_console_sound stubgame.cpp)
#target_link_libraries(stubgame_console_sound skif_engine platform_console sound_sfml logger_file)

#add_executable(stubgame_http stubgame.cpp)
#target_link_libraries(stubgame_http skif_engine platform_http sound_none logger_simple)

#add_executable(stubgame_telnet stubgame.cpp)
#target_link_libraries(stubgame_telnet skif_engine platform_telnet sound_mud_protocol logger_none)

#add_executable(stubgame_gui stubgame.cpp)
#target_link_libraries(stubgame_gui skif_engine platform_gui sound_sfml logger_simple)