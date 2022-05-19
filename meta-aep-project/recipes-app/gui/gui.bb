DESCRIPTION = "Hello World"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"
DEPENDS="ncurses"
 

PR = "r0"
 
#TODO: scrieți în SRC_URI calea către fișierul dorit. Trebuie specificat si file:// inainte
SRC_URI = "file://gui.c"

FILES_${PN}="*.h"

S = "${WORKDIR}"

 
TARGET_CC_ARCH += "${LDFLAGS}" 
 
do_compile() {
   ${CC} ${CFLAGS} ${LDFLAGS} ${WORKDIR}/gui.c -I${WORKDIR} -o ${WORKDIR}/gui -lncurses
 
}
 
do_install() {
   install -d ${D}${bindir}
   install -m 0755 -t ${D}${bindir} ${WORKDIR}/gui
}

