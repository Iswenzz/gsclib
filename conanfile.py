from conans import ConanFile

class gsclib(ConanFile):
	name = "gsclib"
	version = "1.2.0"
	license = "LICENCE"
	url = "https://github.com/Iswenzz/gsclib"
	description = "gsclib acts as a standard library extension for the Call of Duty 4 scripting language."

	requires = (
		"CGSC/1.1.0",
		"cwalk/1.2.5",
		"greatest/1.5.0",
		"libmysqlclient/8.0.17",
		"libcurl/7.80.0",
		"libzip/1.8.0",
		"pcre2/10.39",
		"openssl/1.1.1m",
		"zlib/1.2.12"
	)
	build_requires = "greatest/1.5.0"
	settings = "os", "arch", "compiler", "build_type"
	generators = "cmake"
	default_options = "libcurl:with_libssh2=True"

	def configure(self):
		if self.settings.os == "Windows":
			self.requires("dirent/1.23.2")
