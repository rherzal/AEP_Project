LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"
PR = "r0"

inherit update-rc.d
INITSCRIPT_NAME   = "startup.sh"
INITSCRIPT_PARAMS = "defaults 99"
RDEPENDS_${PN}   += "initscripts"

SRC_URI = "file://startup.sh"

CONFFILES_${PN}  += "${sysconfdir}/init.d/startup.sh"

do_install() {
    install -d ${D}${sysconfdir}/init.d
    install -m 0755 ${WORKDIR}/startup.sh ${D}${sysconfdir}/init.d/
    
}


