DESCRIPTION = "Hello World"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"
 
PR = "r0"
 
#TODO: scrieți în SRC_URI calea către fișierul dorit. Trebuie specificat si file:// inainte
SRC_URI = "file://fiobj4fio.h \ 
file://fiobj_ary.c \ 
file://fiobj_ary.h \ 
file://fiobj_data.c \ 
file://fiobj_data.h \ 
file://fiobject.c \ 
file://fiobject.h \ 
file://fiobj.h \ 
file://fiobj_hash.c \ 
file://fiobj_hash.h \ 
file://fiobj_json.c \ 
file://fiobj_json.h \ 
file://fiobj_mustache.c \ 
file://fiobj_mustache.h \ 
file://fiobj_numbers.c \ 
file://fiobj_numbers.h \ 
file://fiobj_str.c \ 
file://fiobj_str.h \ 
file://fio.c \ 
file://fio_cli.c \ 
file://fio_cli.h \ 
file://fio.h \ 
file://fio_json_parser.h \ 
file://fio_siphash.c \ 
file://fio_siphash.h \ 
file://fio_tls.h \ 
file://fio_tls_missing.c \ 
file://fio_tls_openssl.c \ 
file://fio_tmpfile.h \ 
file://hpack.h \ 
file://http1.c \ 
file://http1.h \ 
file://http1_parser.h \ 
file://http.c \ 
file://http.h \ 
file://http_internal.c \ 
file://http_internal.h \ 
file://http_mime_parser.h \ 
file://mustache_parser.h \ 
file://redis_engine.c \ 
file://redis_engine.h \ 
file://resp_parser.h \ 
file://restserver.c \ 
file://test.sh \ 
file://websocket_parser.h \ 
file://websockets.c \ 
file://websockets.h \ 
"

FILES_${PN}="*.h"

S = "${WORKDIR}"

 
TARGET_CC_ARCH += "${LDFLAGS}" 
 
do_compile() {
   ${CC} ${CFLAGS} ${LDFLAGS} ${WORKDIR}/*.c -I${WORKDIR} -o ${WORKDIR}/restserver -lm -pthread
 
}
 
do_install() {
   install -d ${D}${bindir}
   install -m 0755 -t ${D}${bindir} ${WORKDIR}/restserver
}

