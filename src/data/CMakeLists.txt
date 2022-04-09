add_subdirectory(__test__)

target_sources(gsclib PRIVATE
   regex.c
   regex.h
   zip.c
   zip.h)
