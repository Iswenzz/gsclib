#!/bin/sh

case $1 in
	"install")
	echo "Installed gsclib shared libraries to: /usr/lib/."
	cp -v "./deps/dre2/libdre2.so" "/usr/lib/libdre2.so";
	cp -v "./deps/mysql/unix/lib/libmysqlclient.so" "/usr/lib/libmysqlclient.so.18";
	cp -v "./deps/curl/unix/lib/libcurl.so" "/usr/lib/libcurl.so.4";
	;;

	"uninstall")
	echo "Uninstalled gsclib shared libraries to: /usr/lib/."
	rm -v "/usr/lib/libdre2.so";
	rm -v "/usr/lib/libmysqlclient.so.18";
	rm -v "/usr/lib/libcurl.so.4";
	;;
esac