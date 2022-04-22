add_subdirectory(__test__)

target_sources(gsclib PRIVATE
	file.c
	file.h
	regex.c
	regex.h
	zip.c
	zip.h)
