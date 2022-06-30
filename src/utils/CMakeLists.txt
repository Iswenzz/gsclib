add_subdirectory(__test__)

target_sources(gsclib PRIVATE
	convert.c
	convert.h
	math.c
	math.h
	player.c
	player.h
	polycmp.c
	polycmp.h
	stringutils.c
	stringutils.h
	utils.c
	utils.h
	vsnprintf.c
	vsnprintf.h)
