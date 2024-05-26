set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_custom_target(clang-tidy
	COMMAND find . -type f \( -name '*.c' -o -name '*.h' \) -not -path './build/*' -exec clang-tidy --config-file=.clang-tidy {} +
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

add_custom_target(clang-format
	COMMAND find . -type f \( -name '*.c' -o -name '*.h' \) -not -path './build/*' -exec clang-format -style=file -i --verbose {} +
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

set_target_properties(clang-tidy PROPERTIES FOLDER Clang)
set_target_properties(clang-format PROPERTIES FOLDER Clang)
