SUMMARY = "Utils for is8u256a read write"
SECTION = "base"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

PR = "r0"

SRC_URI = "\
    file://is8u256a.c \
	file://key_prase.c \
    file://Makefile \
"

S = "${WORKDIR}"

do_compile() {
	make clean
	make
}

do_install() {
	install -d ${D}/usr/bin
	install -m 0755 is8u256a ${D}/usr/bin
	install -m 0755 key_prase ${D}/usr/bin
}
